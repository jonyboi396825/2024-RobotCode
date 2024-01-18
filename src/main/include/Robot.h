// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <AHRS.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "Controller/Controller.h"
#include "Drive/SwerveControl.h"
#include "Util/Logger.h"
#include "Util/SocketClient.h"

// TEST
#include "Intake/Rollers.h"

class Robot : public frc::TimedRobot {
public:
  Robot();
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;

private: 
  void ShuffleboardInit();
  void ShuffleboardPeriodic();

  // Controller
  Controller m_controller;

  // navX
  AHRS *m_navx;

  // Swerve
  SwerveControl m_swerveController{true, false};

  // Jetson
  SocketClient m_client;

  // Logger
  FRCLogger m_logger;
  bool m_prevIsLogging;

  // Rollers
  Rollers m_rollers;
};
