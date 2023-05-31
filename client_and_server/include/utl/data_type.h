#ifndef DATA_TYPE_H_
#define DATA_TYPE_H_
namespace LEECHAO
{
/**
 * @brief 感知端与控制端通信数据，一个float4个字节
*/
struct  Com_Data
{
    // 行走方向，相对当前机器人状态，yaw方向
    char flag[2];
    double direct = 0.;
    double left_arm_joints[6] = {0.};
    double right_arm_joints[6] = {0.};
    double left_leg_joints[6] = {0.};
    double right_leg_joints[6] = {0.};
};

/**
 * @brief 落脚点数据格式
*/
struct FootStep
{
    bool is_left;
    // double x, y, z, roll, yaw, pitch;
    double x, y, z, yaw;
    // FootStep():is_left(true),x(0.),y(0.),z(0.),roll(0.),pitch(0.),yaw(0.)
    // {

    // }
    // FootStep(bool is_left_, double x_, double y_, double z_, double roll_, double pitch_, double yaw_):is_left(is_left_), x(x_), y(y_), z(z_), roll(roll_), yaw(yaw_), pitch(pitch_)
    // {

    // }
};



}

#endif