#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<tf/transform_broadcaster.h>

/*This code allows the motor to move back and forth to a maximum and minimum defined in parameters.*/

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
