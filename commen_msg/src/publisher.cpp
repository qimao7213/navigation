#include "ros/ros.h"
#include "commen_msg/FootStep.h"
#include <iostream>
int main(int argc,char **argv)
{
    //ROS节点初始化
    ros::init(argc,argv,"person_publisher");  

    //创建句柄
    ros::NodeHandle n;    

    //创建一个Publisher,发布名为/person_info的话题，消息类型为package1::Person,队列长度为10        
    ros::Publisher person_info_pub  =  n.advertise<commen_msg::FootStep>("/foot_step",10); 
    
    //设置循环频率(HZ)，与loop_rate.sleep()函数关联，如果下一帧信息不满足频率要求则系统延时
    ros::Rate loop_rate(1);   
    int tmp = 0;
    while(ros::ok())
    {   //初始化package1::Person类型的消息
        commen_msg::FootStep step;
        step.x = 1;
        step.y = tmp;
        tmp++;
        //发布消息
        person_info_pub.publish(step);
        std::cout<<step.x<<" "<<step.y<<" "<<step.z<<" "<<step.roll<<" "<<step.pitch<<" "<<step.yaw<<std::endl;
        //按照循环频率延时
        loop_rate.sleep();
    }
    return 0;
}
