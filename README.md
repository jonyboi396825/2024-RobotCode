# 2024 Robot Code

Note: The code was written in the upstream repository: [Eaglestrike/2024-Robot-Code](https://github.com/Eaglestrike/2024-RobotCode)

![Team 114's 2024 Robot Shooting a Note](https://github.com/Eaglestrike/2024-RobotCode/assets/81734282/e5211249-c13c-4aa7-82e5-60e48d73c8c0)

This repository contains the code for the 2024 season robot of FRC Team 114 (Eaglestrike). This code was written collaboratively by four people, with each person programming a different functionality of the robot. As the code lead, I managed the logistics of assigning members to tasks, worked closely with design and assembly teams, and ensured communication among all members.

## Robot Functionality

I programmed the swerve drivebase, localization logic, and autonomus pathing logic, while leading the programming team to implement the other mechanisms and functionality.

### Swerve Drive
- Programmed the logic for determining the angles and speeds of four wheels on the robot, allowing our robot to be fast and agile while moving across the field.
- Used trigonometry to calculate angles for each wheel when strafing.
- Utilized vector algebra to determine speeds and angles for each wheel when turning while moving.
- Used a PID algorithm for each wheel to turn the wheel towards a precise angle.

### Localization
- Programmed logic for allowing the robot to know where it is on the field at all times.
- Utilized and tuned Kalman Filter to integrate velocity data and combine it with PhotonVision's AprilTag camera data to determine best estimate for robot's position on the field.
- Enabled robot to shoot more accurately with better localization data.

### Autonomous Pathing
- Wrote a cubic Hermite spline library to generate smooth and continuous autonomous path splines for the robot.
- Programmed and tuned the drivebase to follow these splines using feedforward and PID control algorithms within 1 cm of precision.
- Achieved an autonomous routine that can pick up and shoot five pieces  during the 15 seconds autonomous period.

### Shooter
- Implemented feedforward and PID algorithms to precisely control the pivot motor of the shooter within 0.5 degrees of precision, allowing us to be flexible while shooting game pieces.
- Collected shooter angle and flywheel speed data for different locations around the field, and used linear interpolation to interpolate between these points, enabling us to have precise shots.

### Intake
- Used PID and feedforward to control the pivot of the intake, allowing it to quickly pick up game pieces from the ground in 2 seconds.
- Used beam breaks to determine whether a game piece is inside the robot.

### Climb
- Utilized a constant force spring and a spool to control the movement of the climb.
- Used a linear servo to control the ratchet so that the climb does not spring back up after the match.

### LEDs
- Used PWM signals to control the LEDs on the robot, allowing drivers to know the status of the robot.
