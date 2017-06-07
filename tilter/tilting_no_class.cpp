#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<dynamixel_msgs/JointState.h>


/*This code allows the motor to move back and forth to a maximum and minimum defined in parameters.*/

using namespace std;

float error;

void obtainValues(const dynamixel_msgs::JointState &msg){
    error = msg.error;
}

void checkError() {
    while(error>0.002) {
        ros::Duration(0.01).sleep();
        ros::Subscriber sub=nh.subscribe("/tilt_controller/state", 5, &obtainValues); //checks error
    }
}

 void moveMotor(double position)
{
    pub_motor = nh.advertise<std_msgs::Float64>("/tilt_controller/command", 10);
    double convert = (position * 3.14/180);
    std_msgs::Float64 aux;
    aux.data = convert;
    pub_motor.publish(aux);
    ROS_INFO_STREAM(aux);
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "Motor_Tilt");
    ros::NodeHandle nh;
    ros::Publisher pub_motor;

    //variables
    int max;
    int min;
    double pause;

    //intitialize parameters
    nh.param("maximum", max, 45);
    nh.param("minimum", min, -45);
    nh.param("pause", pause, 0.5);

    while(ros::ok()) {

        moveMotor(max);
        checkError();
        ros::Duration(pause).sleep();
    
        moveMotor(min);
        checkError();
        ros::Duration(pause).sleep();
  
        ros::spinOnce();
    }
}
