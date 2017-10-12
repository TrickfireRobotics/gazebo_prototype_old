#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"

ros::Publisher fr_pub;
ros::Publisher fl_pub;
ros::Publisher rr_pub;
ros::Publisher rl_pub;

void callback(const geometry_msgs::Twist::ConstPtr& msg) {
  std_msgs::Float64 fr_msg, rr_msg, fl_msg, rl_msg;
  float r = msg->linear.y + msg->angular.z, l = msg->linear.y - msg->angular.z;
  fr_msg.data = r;
  rr_msg.data = r;
  fl_msg.data = l;
  rl_msg.data = l;
  fr_pub.publish(fr_msg);
  fl_pub.publish(fl_msg);
  rr_pub.publish(rr_msg);
  rl_pub.publish(rl_msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "twist_to_motors");

  ros::NodeHandle n;

  fr_pub = n.advertise<std_msgs::Float64>("/exc/wheel_fr_velocity_controller/command", 1);
  fl_pub = n.advertise<std_msgs::Float64>("/exc/wheel_fl_velocity_controller/command", 1);
  rr_pub = n.advertise<std_msgs::Float64>("/exc/wheel_rr_velocity_controller/command", 1);
  rl_pub = n.advertise<std_msgs::Float64>("/exc/wheel_rl_velocity_controller/command", 1);
  ros::Subscriber sub = n.subscribe("/move_base/cmd_vel", 1, callback);

  ros::spin();

  return 0;
}
