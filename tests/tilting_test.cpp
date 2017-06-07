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
  pub=nh.advertise<std_msgs::Float64>("commands", 1000);
}

void Publisher::move(float request)
{
  std_msgs::Float64 msg;
  msg.data = request;
  pub.publish(msg);
}
  
int main(int argc, char **argv)
{
  //setup
  ros::init(argc, argv, "Test_Tilting");
  ros::NodeHandle nh;
  Publisher motor;

  //variables
  int start;
  int interval;
  int max;
  int min;
  int pause;
  int current;
  int future;

  //intitialize parameters
  nh.param("starting_point", start, 0);
  nh.param("interval", interval, 45);
  nh.param("maximum", max, 90);
  nh.param("minimum", min, -90);
  nh.param("pause", pause, 1);

  //set to starting point
  motor.move(start);
  current = start;

while(ros::ok())
  {
    while(current < max)
    {
      ros::Duration(pause).sleep();
      future = current + interval; 
      motor.move(future);
      current = future;
    }
    current = max; 

    while (current > min)
    {
      ros::Duration(pause).sleep();
      future = current - interval; 
      motor.move(future);
      current = future;
    }
    current = min;

  }
}
