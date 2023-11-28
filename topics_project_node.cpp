#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include "std_msgs/Float32.h"
#include <geometry_msgs/Twist.h>



ros::Publisher pub;
ros::Subscriber sub;
sensor_msgs::LaserScan lsvalue;
geometry_msgs::Twist vel;




void Callback(const sensor_msgs::LaserScan& sub_msg)


   {
        int ranges = sub_msg.ranges.size();
        ROS_INFO_STREAM(lsvalue.ranges[360]);

   }


        void get_laserscan_to_cmd()
            {
              geometry_msgs::Twist vel;
              if (lsvalue.ranges[360] > 1)
              {
                vel.linear.x = 0.5;
                vel.angular.z = 0;
              }
              else if (lsvalue.ranges[360]< 1)
              {
                vel.linear.x = 0;
                vel.angular.z = 0.5;
              }
              else if (lsvalue.ranges[719]< 1)
              {
                vel.linear.x = 0;
                vel.angular.z = -0.5;
              }
              else if (lsvalue.ranges[0]< 1)
              {
                vel.linear.x = 0;
                vel.angular.z = 0.5;
              }
              
              pub.publish(vel);
              ros::Rate loop_rate(10);
            }


int main(int argc, char** argv) 

{

ros::init(argc, argv, "topics_project_node"); // node name
ros::NodeHandle n;

pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 50);   //publisher
sub = n.subscribe("/scan", 1000, Callback); // subscriber



ros::Rate loop_rate(10);


while (ros::ok())

{


ros::spinOnce();
loop_rate.sleep();

}

    return 0;
}