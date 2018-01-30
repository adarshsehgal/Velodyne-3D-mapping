#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
//#include <turtlesim/Pose.h>
/*
void poseCallback(const turtlesim::PoseConstPtr& msg){
	static tf::TransformBroadcaster br;
	tf::Transform transform;
	transform.setOrigin(tf::Vector3(msg->x, msg->y, 0.0));
	tf::Quaternion q;
	q.setRPY(0, 0, msg->theta);
	transform.setRotation(q);
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "VirtualTarget", "turtle1"));
}
*/
void poseCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->pose.pose.position.x, msg->pose.pose.position.y, 0.0));
        
    tf::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    
    transform.setRotation(q);
    
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "VirtualTarget", "JR2"));
}

int main(int argc, char** argv){
	ros::init(argc, argv, "my_tf_broadcaster");
	ros::NodeHandle node;
	ros:: Subscriber sub = node.subscribe("/summit_xl_control/odom", 10, &poseCallback); //turtle1/pose

	ros::spin();
	return 0;
}

