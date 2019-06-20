# Mecanum-drive
  
The Mecanum wheel is a design for a wheel that can move a vehicle in any direction. It is a conventional wheel with a series of rollers attached to its circumference. These rollers typically each have an axis of rotation at 45° to the plane of the wheel and at 45° to a line through the centre of the roller parallel to the axis of rotation of the wheel.

![Mecanum wheels](/Illustrations/LeftAndRight_Mecanum_Wheel.png)

By alternating wheels with left and right-handed rollers, in such a way that each wheel applies force roughly at right angles to the wheelbase diagonal the wheel is on, the vehicle is stable and can be made to move in any direction and turn by varying the speed and direction of rotation of each wheel.

![Mecanum wheel arrangement](/Illustrations/Mecanum_Wheel_Installation_02.png)

Moving all four wheels in the same direction causes forward or backward movement, running the wheels on one side in the opposite direction to those on the other side causes rotation of the vehicle, and running the wheels on one diagonal in the opposite direction to those on the other diagonal causes sideways movement. Combinations of these wheel motions allow for vehicle motion in any direction with any vehicle rotation (including no rotation at all).

![Mecanum wheel combinations](/Illustrations/wheel-rotations.jpg)

# Kinematics

One of the most important part of using this type of wheels for a drive is the ability to use them to their potential. The equations we are going to derive for the mecanum drive will give the programmer the ability to make to drive move in any direction desired and the velocity to be given to the individual wheels will be calculated by these equations. These equations are called Inverse-Kinematic equations

Kinematics - Calculation of the resultant motion from many forces being applied or exerted on the drive.


Inverse kinematics - Calculation of individial exerted force from the resultant

![derivation](/Illustrations/Derivation.PNG) 

And from this the final Inverse-Kinematic equations come out to be 

![final equations](/Illustrations/final equations.PNG)

These equations can be used to manipulate the velocity and position of the drive. The code for the drive implementation can be found in this repository. These code have been written for Arduino Mega 2560. They can be changed by a few tweaks according to the board you are using.