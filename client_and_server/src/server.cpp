#include "ros/ros.h"
#include "commen_msg/FootSteps.h"
#include "commen_msg/planning_request.h"
#include <commen_msg/capture_global_path.h>
#include <iostream>
#include <show/matplotlib_show.h>
#include <vector>
#include <utl/data_type.h>
#include "Pathplan/path.h"
#include "PathSmooth/PathSmooth.h"
#include "FootStep/FootstepPlan.h"

using namespace std;
ros::ServiceClient globalPathClient;

/**
 * @brief 请求回调函数
 * @param request 规划的输入 
 * @param response 规划的输出
 * @todo GaoZhifa
*/
bool planning(commen_msg::planning_request::Request & request, commen_msg::planning_request::Response & response)
{
    // cout<<request.walk_case<<" "<<request.direct<<endl;
    cout<<request.walk_case.at(0)<<" "<<request.walk_case.at(1)<<" "<<request.direct<<endl;
    // 设定起点，终点，初始时刻的前后脚关系
    // 设定起点，终点，初始时刻的前后脚关系
    gpath::tc_path *mypath = new gpath::tc_path();
    gfootstepplan::tc_PathCapture *mycpath;
    gfootstepplan::tc_Footstep *myfootstep;
    // 输入地图

    // 输出规划结果
    // ros::service::waitForService("/capture_global_path");
    
    commen_msg::capture_global_path srv;
    globalPathClient.call(srv);
    ROS_INFO("succeed? : %s", srv.response.result.c_str());
    gpathsmooth::gfnGeneratePathFromTxt(mypath, "/home/qimao/myCode/navigation/Data/globalPath1cm.txt");
    // gpathsmooth::gfnGeneratePathFromROSMsgs(mypath, "/home/qimao/myCode/navigation/Data/globalPath1cm.txt");
    gpathsmooth::gfnvSaveDataWithFile(mypath, "../Data/GPath.dat");

    // gpathsmooth::gfnvPathTransLine(mypath); // 路径拉直
    // gpathsmooth::gfnvSaveDataWithFile(mypath, "../Data/GPathTransLine.dat");

    // gpathsmooth::gfnvPathSmooth(mypath); // 路径光滑处理
    // gpathsmooth::gfnvSaveDataWithFile(mypath, "../Data/GPathSmooth.dat");

    gfootstepplan::tc_BHRhard hardpara(0.30, 10, 0.1); // BHR 运动学参数设置- 最大步长，最大转弯角度（度），左右脚距中心距离
    // mycpath = &gfootstepplan::gfnvCapturePathV2(mypath, hardpara);
    // mycpath = &gfootstepplan::gfnvCapturePathV3(mypath, hardpara,0.01);
    mycpath = &gfootstepplan::gfnvCapturePathV4(mypath, hardpara, 0.005);
    gfootstepplan::gfnvSaveCPath(mycpath, "/home/qimao/myCode/navigation/Data/GPathCaputer.dat");

    myfootstep = &gfootstepplan::gfndPlantFootStepPlannerV2(mycpath, hardpara); // 落脚点规划结果输出到 myfootstep
    gfootstepplan::gfnvSaveFoot(myfootstep, "/home/qimao/myCode/navigation/Data/GFoot.dat");


    // 将规划结果给response

    commen_msg::FootStep step1, step2;
    step1.is_left = 1;
    step1.x = 0.1;
    step1.y = 0.1;
    step1.z = 0.0;
    step1.roll = 0.;
    step1.pitch = 0.0;
    step1.yaw = 0.0;
    step2.is_left = 0;
    step2.x = 0.1;
    step2.y = -0.1;
    step2.z = 0.0;
    step2.roll = 0.;
    step2.pitch = 0.0;
    step2.yaw = 0.0;
    response.result_steps.emplace_back(step1);
    response.result_steps.emplace_back(step2);
    cout<<"the result data is: "<<endl;
    for (size_t i = 0; i < response.result_steps.size(); i++)
    {
        cout<<i<<": "<<response.result_steps.at(i).is_left<<" "<<response.result_steps.at(i).x<<" "<<response.result_steps.at(i).y<<" "<<response.result_steps.at(i).z<<" "<<response.result_steps.at(i).roll<<" "<<response.result_steps.at(i).pitch<<" "<<response.result_steps.at(i).yaw<<endl;
    }
    vector<LEECHAO::FootStep> footsteps;
    for (auto & step : response.result_steps)
    {
        // step.is_left
        // LEECHAO::FootStep tmpstep(bool(step.is_left), step.x, step.y, step.z, step.roll, step.pitch. step.yaw);
        LEECHAO::FootStep tmpstep;
        tmpstep.is_left = step.is_left;
        tmpstep.x       = step.x;
        tmpstep.y       = step.y;
        tmpstep.z       = step.z;
        // tmpstep.roll    = step.roll;
        // tmpstep.pitch   = step.pitch;
        tmpstep.yaw     = step.yaw;
        footsteps.emplace_back(tmpstep);
    }
    show(footsteps);
    return true;
}
 
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"server");
    ros::NodeHandle nh;
    globalPathClient = nh.serviceClient<commen_msg::capture_global_path>("/capture_global_path");
    ros::ServiceServer server = nh.advertiseService("planning_service",planning);//回调函数返回的是布尔类型。第一个参数是话题，第二个参数是回调函数，这个回调函数就相当于是处理请求的，处理请求在这里就有被封装好的对象。
    ROS_INFO("server is running....");
    ros::spin();
    return 0;
}