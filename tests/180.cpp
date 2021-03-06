#include<ros/ros.h>
#include<std_msgs/Float64.h>


using namespace std;

class Publisher
{
  private:
  ros::NodeHandle nh;
  ros::Publisher pub;
  public:
  Publisher();
  void move(float request);
};

Publisher::Publisher()
{
  pub=nh.advertise<std_msgs::Float64>("commands", 1);
}

void Publisher::move(float request)
{
  std_msgs::Float64 msg;
  msg.data = request;
  pub.publish(msg);
}
  
int main(int argc, char **argv)
{
  ros::init(argc, argv, "Test_180");
  ros::NodeHandle nh;
  Publisher motor;

  while(ros::ok())
  {
    motor.move(180);
    ros::Duration(1.5).sleep();

    motor.move(0);
    ros::Duration(1.5).sleep();

    motor.move(-180);
    ros::Duration(1.5).sleep();

    motor.move(0);
    ros::Duration(1.5).sleep();
  }

}
