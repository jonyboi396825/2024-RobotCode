#pragma once

#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>

#include "ShuffleboardSender/ShuffleboardSender.h"

#include "Util/Poses.h"
#include "Util/Mechanism.h"
#include "Util/TrapezoidalProfile.h"

#include "Constants/ShooterConstants.h"

using CANcoder = ctre::phoenix6::hardware::CANcoder;
using TalonFX = ctre::phoenix6::hardware::TalonFX;

class Pivot : public Mechanism{
    public:
        enum State{
            STOP,
            UNHOOK,
            AIMING,
            AT_TARGET,
            JUST_VOLTAGE
        };

        Pivot(std::string name, bool enabled, bool shuffleboard);

        void Stop();

        void SetAngle(double angle);
        void SetVoltage(double volts);

        void Zero();
        void ZeroRelative();

        bool AtTarget();

        void SetPID(ShooterConstants::PID pid);
        void SetTolerance(double posTol);
        void SetHooked(bool hooked);
        Poses::Pose1D GetPose();
        double GetTolerance();
        double GetTargetTime();

        std::string GetStateStr();

    private:
        Poses::Pose1D GetAbsPose();
        Poses::Pose1D GetRelPose();

        void CoreInit() override;
        void CorePeriodic() override;
        void CoreTeleopPeriodic() override;

        void CoreShuffleboardInit() override;
        void CoreShuffleboardPeriodic() override;
        State state_;

        TalonFX motor_;
        TalonFX motorChild_;
        
        double volts_;
        double maxVolts_ = ShooterConstants::PIVOT_MAX_VOLTS;

        CANcoder encoder_;
        double offset_;
        double relOffset_;
        double gearing_ = ShooterConstants::PIVOT_GEARING;

        bool hooked_;
        double tempTarg_; //Temporary target (to reaim after unhooking)

        struct Bounds{
            double min;
            double max;
        } bounds_;

        ShooterConstants::PID pid_ = ShooterConstants::PIVOT_PID;
        double pidMax_ = ShooterConstants::PIVOT_PID_MAX;
        double accum_;
        double prevT_;
        ShooterConstants::Feedforward ff_ = ShooterConstants::PIVOT_FF;
        ShooterConstants::Incher inch_ = ShooterConstants::PIVOT_INCH;
        int cycle_;
        double inchTol_ = ShooterConstants::PIVOT_INCH_TOL;
        double inchDead_ = ShooterConstants::PIVOT_INCH_DEADBAND;
        double frctn_ = ShooterConstants::PIVOT_FRCTN; //Increase voltage as friction increases with sin(angle)

        double posTol_;
        double velTol_;
        double regenTol_ = ShooterConstants::PIVOT_REGEN_TOL;
        
        double maxV_;
        double maxA_;
        TrapezoidalProfile profile_;

        Poses::Pose1D currPose_; //Angle (rad)

        std::string StateToString(State state);
        ShuffleboardSender shuff_;
};