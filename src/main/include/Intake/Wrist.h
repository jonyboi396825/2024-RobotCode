#pragma once

#define WRIST_AUTOTUNING false

#include <ctre/phoenix6/TalonFX.hpp>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Util/TrapezoidalProfile.h"
#include <ctre/phoenix6/CANcoder.hpp>
#include "Util/Mechanism.h"
#include "Util/Logger.h"
#include "ShuffleboardSender/ShuffleboardSender.h"
#include "Constants/IntakeConstants.h"

#if WRIST_AUTOTUNING
#include "FFAutoTuner/FFAutotuner.h"
#endif

using ctre::phoenix6::hardware::TalonFX;
using ctre::phoenix6::hardware::CANcoder;

class Wrist: public Mechanism{
    public:
        Wrist(bool enabled, bool dbg);

        enum MechState{
            MOVING,
            AT_TARGET,
            STOPPED,
            COAST,
            CONST_VOLTAGE //Mainly testing state (but could be used for )
            #if WRIST_AUTOTUNING
            ,AUTOTUNING
            #endif
        };
        
        void Zero();
        void ManualPeriodic(double wristVolts);
        void CoreTeleopPeriodic() override;
        void CorePeriodic() override; 
        void CoreShuffleboardPeriodic() override;
        void CoreShuffleboardInit() override;
        void MoveTo(double newPos);
        void Log(FRCLogger& logger);
        void Coast();
        void Kill();
        bool ProfileDone();
        double GetPos();
        MechState GetState();
        // double getSetPt();
        double GetMaxVolts();
        double GetManualVolts();
    private:
        void MoveToSetPt();
        void ChangeSetPt(double newPos); //pos should be in radians, w 0 as extended and parallel to ground
        void UpdatePose();
        double FFPIDCalculate();
        bool AtSetpoint();
        void ResetPID();
        void SetVoltage();
        double GetRelPos();
        
        TalonFX m_wristMotor {IntakeConstants::WRIST_MOTOR};

        //MEMBER VARS
        //state vars
        MechState m_state = MechState::STOPPED;

        //profile vars

        double wristVolts;
        double m_setPt; 
        double m_newSetPt = -1;
        double m_curPos, m_curVel, m_curAcc; // cur pose
        double m_totalErr = 0; // integral of position error for PID

        double m_absEncoderInit;

        //Shuffleboard
        ShuffleboardSender m_shuff;
        double MAX_VEL = 20.0, MAX_ACC = 35.0;
        TrapezoidalProfile m_trapezoidalProfile;
        
        #if WRIST_AUTOTUNING
        FFAutotuner m_autoTuner {"Wrist Autotuner", FFAutotuner::ARM};
        #endif

        //Constants
        double m_kp = 1.75, m_ki = 0.1, m_kd = 0.1;
        double m_s = 0.32, m_g =0.455, m_v = 0.46, m_a = 0.045;

        double MAX_POS = 1.9, MIN_POS = -0.75;

        double POS_TOLERANCE = 0.05;

        double ENCODER_OFFSET = 1.68 + M_PI/2.0 - 1.3411 + 0.1134;
        
        double MAX_VOLTS = 12.0;
        double MANUAL_MAX_VOLTS = 5.0;
        
        // will prob change
        double REL_CONV_FACTOR = 1.0 * (8.0 / 66.0) * (18.0 / 66.0);
        //for dbg
        double m_voltReq = 0.0;

        bool m_wasCoasting = false;
};