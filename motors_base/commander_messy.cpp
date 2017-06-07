#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<stdio.h>
#include<dynamixel_msgs/JointState.h>

using namespace std;

float error;
float place;
int go = 0;

//creates all commands for each motor
class Dynamixel
{
  private:
  ros::NodeHandle n;
  ros::Publisher pub_n;
  public:
  Dynamixel();
  void checkError();
  int moveMotor(double position);
  void transfer(const std_msgs::Float64 &msg);
};

//creates publisher
Dynamixel::Dynamixel()
{
  pub_n = n.advertise<std_msgs::Float64>("/tilt_controller/command", 1);
}

//creates message and publishes -> takes in deg, conv to rad, pub
int Dynamixel::moveMotor(double position)
{
  double convert = (position * 3.14/180);
  ROS_INFO_STREAM("hi");
  std_msgs::Float64 aux;  
  aux.data = convert;
  pub_n.publish(aux);
  ROS_INFO_STREAM(aux);
  return 1;
}

//cheks for error to ensure alignment
void Dynamixel::checkError()
{
  while(error>0.002)
  {
    ros::Duration(0.01).sleep();
  }
}

//obtains error value to allow for alignment
void obtainValues(const dynamixel_msgs::JointState &msg)
{
  error = msg.error;
}



//sets motor to external command
void transfer(const std_msgs::Float64 &msg)
{
  place = msg.data;


ROS_INFO("GOt command, publish to motor");
  //go = 1;
}


int main (int argc, char **argv)
{
  //startup
  ros::init(argc, argv, "motor_commander");
  ros::NodeHandle nh;
  
  ROS_WARN_STREAM("Please hold for 5");
  ros::Duration(5).sleep();

  //creates 1 Dynamixel named motor
  Dynamixel motor;

  //subscribers for aligning and external commands
  ros::Subscriber sub_1=nh.subscribe("/tilt_controller/state", 5, &obtainValues); //align
  ros::Subscriber sub_2=nh.subscribe("/commands", 5, &transfer);  //external

  //publisher to permit initilization
  ros::Publisher pub=nh.advertise<std_msgs::Float64>("/initialized", 1);
  std_msgs::Float64 org;
  org.data = 0;
  pub.publish(org);  //not ready
  motor.moveMotor(0); //initilization
  motor.checkError();

  motor.moveMotor(180); //initilization
  motor.checkError();
  std_msgs::Float64 msg;
  msg.data = 1;
  pub.publish(msg);  //initilization complete

  ROS_INFO("msg sent");
  

  //ros::spin();

  while(ros::ok())
  {
    if(go == 1)
    {
      motor.moveMotor(place);
      motor.checkError();
      ros::Duration(0.5).sleep(); //saftety break
      go = 0;
    }
    
    else
    {}
  }
}
