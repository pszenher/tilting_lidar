#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<tf/transform_broadcaster.h>

/*This code allows the motor to move a certain interval, specified in degrees, and then pause.  A maximum and minimum angle can be specified, as well as the starting point.  The pause and interval ammount can be changed as well.

In this version, the motor first goes to the starting position, then the maximum angle, and finally the minumum angle.  The motor than oscillates between the maximum and minimum angles. */

using namespace std;
  
int main(int argc, char **argv)
{
  //setup
  ros::init(argc, argv, "Motor_Tilt");
  ros::NodeHandle nh;

  //variables
  int max;
  int min;
  double pause;

  //intitialize parameters
  nh.param("maximum", max, 45);
  nh.param("minimum", min, -45);
  nh.param("pause", pause, 0.5);
  current = start;


while(ros::ok()) {

    motor.move(max);
    motor.checkError();
    ros::Duration(pause).sleep();
    
    motor.move(min);
    motor.checkError();
    ros::Duration(pause).sleep();
  
    ros::spinOnce();
}
