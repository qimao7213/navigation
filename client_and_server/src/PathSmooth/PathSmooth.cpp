#include "PathSmooth/PathSmooth.h"
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
/*
    功能：判断是否是在圆弧转弯点
    通过计算当前点和其后的lgnGap个点组成的直线斜率
    与其后的2*lgnGap和lgnGap组成的直线斜率是否相等；
*/
bool gpathsmooth::gfnnTurningChangFlag(gpath::tc_path *_path, int gi, int gap)
{
    int lgnReturn = 0;
    int lgnGap = gap; // 2
    double lgdlater1 = 0;
    double lgdlater2 = 0;
    double lgdFPS = 0.00025; // 精度很重要，决定非转弯处的判断的准确性

    lgdlater1 = (_path->global_path_cor[gi + lgnGap].y - _path->global_path_cor[gi].y) / (_path->global_path_cor[gi + lgnGap].x - _path->global_path_cor[gi].x);

    lgdlater2 = (_path->global_path_cor[gi + 2 * lgnGap].y - _path->global_path_cor[gi + lgnGap].y) / (_path->global_path_cor[gi + 2 * lgnGap].x - _path->global_path_cor[gi + lgnGap].x);

    if (fabs(lgdlater1 - lgdlater2) < lgdFPS)
    {
        lgnReturn = 1;
    }
    else
    {
        lgnReturn = 0;
    }
    return lgnReturn;
}
/* 判断是否是转弯点 */

bool gpathsmooth::gfnbIFTurning(int i, gpath::ts_PathCoord pathnode[]) //_interval = 6
{
    double ldgaoDoubleEPS = 0.00003;                // double型数据精度，用于比较大小的 0.00003
    double ldgaoChange[MAX_ARRAY_NUM] = {0.0};      // 计算当前节点斜率
    double ldgaoChangeLast[MAX_ARRAY_NUM] = {0.0};  // 计算上一次斜率
    double ldgaoChangeLater[MAX_ARRAY_NUM] = {0.0}; // 计算之后节点的斜率
    bool isturning = 0;                             // 判断是否是转弯点

    ldgaoChange[i] = (pathnode[i].y - pathnode[i - 1].y) / (pathnode[i].x - pathnode[i - 1].x);
    ldgaoChangeLast[i] = (pathnode[i - 1].y - pathnode[i - 6].y) / (pathnode[i - 1].x - pathnode[i - 6].x);
    ldgaoChangeLater[i] = (pathnode[i + 1].y - pathnode[i].y) / (pathnode[i + 1].x - pathnode[i].x);
    // printf("ldgaoChangeLast[%d] = %f\tldgaoChange[%d] = %f\tldgaoChangeLater[%d] = %f\n", i, ldgaoChangeLast[i], i, ldgaoChange[i], i, ldgaoChangeLater[i]);
    if (fabs(ldgaoChange[i] - ldgaoChangeLast[i]) < ldgaoDoubleEPS && fabs(ldgaoChange[i] - ldgaoChangeLater[i]) > ldgaoDoubleEPS) // 之前斜率基本没变化，之后斜率有变化，就是转弯点
    {
        isturning = 1;
        // printf("\033[1;45;33m  转弯点：%d  \033[0m \n", i);
        // printf("fpathnodex = %f,fpathnodey=%f\n", fpathnodex[i], fpathnodey[i]);
        // printf("转弯点：%d\n", i);
    }
    return isturning;
}
/* 将路径中的波折点拉直 */
void gpathsmooth::gfnvPathTransLine(gpath::tc_path *_path)
{
    int lngaoNodeOffset = 2;    // 偏置，以防最后点的选择超过终点，提前结束
    static int lngaoTemp = 0;   // 中间变量
    int lngaoFlag1 = 0;         //
    double ldgaoGap[2] = {0.0}; //

    for (int i = 10; i <= _path->nPathNodeNum - lngaoNodeOffset; i++)
    {

        if (gpathsmooth::gfnbIFTurning(i, _path->global_path_cor)) // 判断一下转弯点，记录当前转弯点
        {
            // printf("\033[1;45;33m  转弯点进入操作循环：%d  \033[0m \n", i);
            lngaoFlag1++;       // 用于避免对从起点到第一个转折点的处理，没必要处理
            if (lngaoFlag1 > 1) // 从第二个转折点开始处理数据
            {
                // printf("\033[1;45;33m  开始分割：%d——%d  \033[0m \n", lngaoTemp, i);
                ldgaoGap[0] = (_path->global_path_cor[i].x - _path->global_path_cor[lngaoTemp].x) / (i - lngaoTemp); // 将前后两个转折点间距离平分
                ldgaoGap[1] = (_path->global_path_cor[i].y - _path->global_path_cor[lngaoTemp].y) / (i - lngaoTemp);
                for (int j = lngaoTemp; j <= i; j++)
                {
                    _path->global_path_cor[j].x = _path->global_path_cor[lngaoTemp].x + (j - lngaoTemp) * ldgaoGap[0]; // 平分后重新赋值
                    _path->global_path_cor[j].y = _path->global_path_cor[lngaoTemp].y + (j - lngaoTemp) * ldgaoGap[1];
                }
            }
            lngaoTemp = i; // 保存当前转折点，做为下次循环的上次转折点
        }
        else if (fabs(100 * _path->global_path_cor[i + lngaoNodeOffset - 1].x - _path->global_goal.first) < 0.0001 && fabs(100 * _path->global_path_cor[i + lngaoNodeOffset - 1].y - _path->global_goal.second) < 0.0001) // 如果点的选择已经遍历到终点，则做最后的终点和上一次转折点间的处理
        {
            // printf("\033[1;45;42m  最后的转点！！！%d,%d,%d \033[0m \n", i, lngaoTemp, PATH_NODE_NUM);
            double gx = (double)_path->global_goal.first / 100;
            double gy = (double)_path->global_goal.second / 100;
            // printf("GOAL = %lf,%lf\n", gx, gy);
            ldgaoGap[0] = (gx - _path->global_path_cor[lngaoTemp].x) / (_path->nPathNodeNum - 1 - lngaoTemp);
            ldgaoGap[1] = (gy - _path->global_path_cor[lngaoTemp].y) / (_path->nPathNodeNum - 1 - lngaoTemp);

            for (int j = lngaoTemp; j < _path->nPathNodeNum; j++)
            {
                _path->global_path_cor[j].x = _path->global_path_cor[lngaoTemp].x + (j - lngaoTemp) * ldgaoGap[0];
                _path->global_path_cor[j].y = _path->global_path_cor[lngaoTemp].y + (j - lngaoTemp) * ldgaoGap[1];
            }
        }
        else
        {
            // printf("\033[1;45;44m  普通点！！！%d \033[0m \n",i);
            /// printf("是否是终点 ： %d\n", i + lngaoNodeOffset);
            // printf("当前点是：%lf\t%lf\n", fpathnodex[i+1], fpathnodey[i+1]);
            // printf("当前点相加是：%lf\t%lf\n", fpathnodex[i + lngaoNodeOffset - 1], fpathnodey[i + lngaoNodeOffset - 1]);
        }
    }
}
void gpathsmooth::gfnvSaveDataTransLine(gpath::tc_path *_path)
{
    FILE *path_node_tran;
    path_node_tran = fopen("../../pathnodeTransLine.dat", "wb");
    // printf("save _path->nPathNodeNum data %d\n", _path->nPathNodeNum);

    fprintf(path_node_tran, "%s %s %s\n", "path_x", "path_y", "path_z");
    // fprintf(path_node, "%s %s %s %s ", "capture_x", "capture_y", "capture_z", "capture_theta");
    // fprintf(path_node, "%s %s %s %s\n", "foot_x", "foot_y", "foot_z", "foot_theta");

    for (int i = 0; i < _path->nPathNodeNum; i++)
    {
        fprintf(path_node_tran, "%lf %lf %lf\n", _path->global_path_cor[i].x, _path->global_path_cor[i].y, _path->global_path_cor[i].z);
    }
    fclose(path_node_tran);
}

void gpathsmooth::gfnvSaveDataWithFile(gpath::tc_path *_path,char *filetest)
{
    FILE *path_node_tran;
    path_node_tran = fopen(filetest, "wb");
    // printf("save _path->nPathNodeNum data %d\n", _path->nPathNodeNum);
    fprintf(path_node_tran, "%s %s %s\n", "path_x", "path_y", "path_z");
    // fprintf(path_node, "%s %s %s %s ", "capture_x", "capture_y", "capture_z", "capture_theta");
    // fprintf(path_node, "%s %s %s %s\n", "foot_x", "foot_y", "foot_z", "foot_theta");

    for (int i = 0; i < _path->nPathNodeNum; i++)
    {
        fprintf(path_node_tran, "%lf %lf %lf\n", _path->global_path_cor[i].x, _path->global_path_cor[i].y, _path->global_path_cor[i].z);
    }
    fclose(path_node_tran);
}
void gpathsmooth::gfnGeneratePathFromTxt(gpath::tc_path *_path, const std::string filename)
{
    std::ifstream fGlobalPath;
    fGlobalPath.open(filename);
    if(!fGlobalPath)
    {
        std::cout << "A wrong file path!  " <<  filename.c_str() << std::endl;
    }
    int numPoint = 0;
    while(!fGlobalPath.eof())
    {
        std::string s;
        getline(fGlobalPath,s);
        // cout << s.c_str() << endl;
        if(!s.empty())
        {
            std::stringstream ss;
            ss << s;
            std::string sss;
            ss >> sss;
            if(sss == "#")
            {
                continue;
            }
            if(numPoint == 40)
                int b = 0;
            _path->global_path_cor[numPoint].x = (double)atof(sss.c_str());
            ss >> sss;
            _path->global_path_cor[numPoint].y = (double)atof(sss.c_str());
            _path->global_path_cor[numPoint].z = 0;
            _path->global_path_cor[numPoint].theta = 0;
            numPoint ++;
        }
    }
    _path->nPathNodeNum = numPoint;
    // -_path->global_start.first = 
    std::cout << "generated a path with " << numPoint << " points. " << std::endl; 
    for (int i = numPoint; i < MAX_ARRAY_NUM; i++) // ��ʣ��ĵ�Ҳ��λΪ����Ŀ���
    {
        _path->global_path_cor[i].x = _path->global_path_cor[numPoint - 1].x;
        _path->global_path_cor[i].y = _path->global_path_cor[numPoint - 1].y;
        _path->global_path_cor[i].z = _path->global_path_cor[numPoint - 1].z;
    }
    std::cout << "generate a path end!" << std::endl;
}



/* 坐标转换：旋转矩阵；
       输入：局部坐标系原点dlx,dly,当前的局部坐标系方向（弧度）
             局部坐标系中的某点的位置dllx,dlly；
       输出: 某点在全局坐标系中的位置；
*/
gpath::ts_PathCoord gpathsmooth::gaofnGPFramTrans(double dlx, double dly, double dltheta, double dllx, double dlly)
{
    double ldgaoTransR[3][3] = {
        {cos(dltheta), -sin(dltheta), 0.0},
        {sin(dltheta), cos(dltheta), 0.0},
        {0.0, 0.0, 1}};                        // 绕Z轴旋转矩阵
    double ldgaoFramO[3] = {dlx, dly, 0.0};    // 局部坐标系原点坐标
    double ldgaoFram[3] = {0};                 // 转换后的坐标
    double ldgaoOffSet[3] = {dllx, dlly, 0.0}; // 某点在局部坐标系中的位置
    
    double ldgaoTemp[3] = {0};
    // static int lngaoLegFlag = 1;           //左右脚的标志位
    gpath::ts_PathCoord pathtrfo;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ldgaoFram[j] = ldgaoTransR[i][j] * /*lngaoLegFlag */ ldgaoOffSet[j]; // 旋转矩阵对应位置元素与局部坐标系中位置相乘
        }
        ldgaoTemp[i] = ldgaoFram[0] + ldgaoFram[1] + ldgaoFram[2] + ldgaoFramO[i]; // 旋转以后与局部坐标原点相加
    }
    pathtrfo.x = ldgaoTemp[0];
    pathtrfo.y = ldgaoTemp[1];
    pathtrfo.z = ldgaoTemp[2];
    pathtrfo.theta = dltheta;
    return pathtrfo;
}
gpath::ts_PathCoord gpathsmooth::gaofnGPFramTransV2(double dlx, double dly, double dltheta, double dllx, double dlly)
{
    double ldgaoTransR[3][3] = {
        {cos(dltheta), -sin(dltheta), 0.0},
        {sin(dltheta), cos(dltheta), 0.0},
        {0.0, 0.0, 1}};                        // 绕Z轴旋转矩阵
    double ldgaoFramO[3] = {dlx, dly, 0.0};    // 局部坐标系原点坐标
    double ldgaoFram[3] = {0};                 // 转换后的坐标
    double ldgaoOffSet[3] = {dllx, dlly, 0.0}; // 某点在局部坐标系中的位置

    double ldgaoTemp[3] = {0};
    // static int lngaoLegFlag = 1;           //左右脚的标志位
    gpath::ts_PathCoord pathtrfo;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ldgaoFram[j] = ldgaoTransR[i][j] * /*lngaoLegFlag */ ldgaoOffSet[j]; // 旋转矩阵对应位置元素与局部坐标系中位置相乘
        }
        ldgaoTemp[i] = ldgaoFram[0] + ldgaoFram[1] + ldgaoFram[2] + ldgaoFramO[i]; // 旋转以后与局部坐标原点相加
    }
    pathtrfo.x = ldgaoTemp[0];
    pathtrfo.y = ldgaoTemp[1];
    pathtrfo.z = ldgaoTemp[2];
    pathtrfo.theta = dltheta;
    return pathtrfo;
}
/*
    功能：计算斜线上的与水平线上的距离相等的路径节点
    输入：交叉点或转弯点initn,
          总的路径点个数loopN，
          默认期望的长度defualtfootL；
          确定哪边是斜线flag: 0-右边是斜线，1-左边是斜线
    输出：斜线上的路径点 ndefualt；
*/
int gpathsmooth::ReturnCaculatNDefualt(gpath::ts_PathCoord pathnode[],int initn, int loopN, double defualtfootL, int flag)
{
    int ndefualt = 0;
    switch (flag)
    {
    case 0:
        // printf("case flag = 0\n");
        for (int i = initn + 1; i < loopN - 1; i++)
        { // 找到能使的步长接近默认步长的路径上的节点
            if (abs(defualtfootL - sqrt(pow(pathnode[i].x - pathnode[initn].x, 2) + pow(pathnode[i].y - pathnode[initn].y, 2))) <= 0.01)
            {
                ndefualt = i;
                break; // 跳出for循环
            }
            else
            {
                ndefualt = loopN - 1;
            }
        }
        break;
    case 1:
        // printf("case flag = 1\n");
        for (int i = initn - 1; i > 0; i--)
        { // 找到能使的步长接近默认步长的路径上的节点
            if (abs(defualtfootL - sqrt(pow(pathnode[i].x - pathnode[initn].x, 2) + pow(pathnode[i].y - pathnode[initn].y, 2))) <= 0.01)
            {
                ndefualt = i;
                break; // 跳出for循环
            }
            else
            {
                ndefualt = loopN - 1;
            }
        }
        break;
    default:
        break;
    }
    return ndefualt;
}
/*
    功能：计算圆心，半径，圆心角
*/
gpathsmooth::ts_circle gpathsmooth::gfnvCircleCentrAndRand(double theta1, double x1, double y1, double theta2, double x2, double y2)
{
    double xz = 0, yz = 0, kz = 0;
    double x0 = 0, y0 = 0;
    double b1 = 0, b2 = 0, k1 = 0, k2 = 0;
    double x = 0, y = 0;
    double R = 0;
    int k1New, k2New;
    gpathsmooth::ts_circle RT;
    k1 = tan(theta1);
    k2 = tan(theta2);
    k1New = round(180 / 3.14 * theta1);
    k2New = round(180 / 3.14 * theta2);
    // xz = (x1 + x2) / 2; yz = (y1 + y2) / 2;
    if (k1New == 90 && k2New == 90)
    {
        printf("!!! ERROR: k1 = k2= 90\n");
    }
    else if (k1New == 90 && k2New != 0)
    {
        y0 = y1;
        kz = -1 / k2;
        b2 = y2 - kz * x2;
        x0 = (y0 - b2) / kz;
        // printf(" k1 = 90 , k2 != 90\n");
    }
    else if (k2New == 90 && k1New != 0)
    {
        y0 = y2;
        k1 = -1 / k1;
        b1 = y1 - k1 * x1;
        x0 = (y0 - b1) / k1;
        // printf(" k2 = 90\n");
    }
    else if (k1New == 0 && k2New != 90)
    {
        x0 = x1;
        kz = -1 / k2;
        b2 = y2 - kz * x2;
        y0 = kz * x0 + b2;
        // printf("k1,x1,y1,k2,x2,y2 == %f,%f,%f,%f,%f,%f\n", k1, x1, y1, k2, x2, y2);
        // printf("x0 = %f,y0 = %f\n", x0, y0);
    }
    else if (k2New == 0 && k1New != 90)
    {
        x0 = x2;
        k1 = -1 / k1;
        b1 = y1 - k1 * x1;
        y0 = k1 * x0 + b1;
        // printf(" k2 = 0\n");
    }
    else
    {
        kz = -1 / k2;
        k1 = -1 / k1;
        b1 = y1 - k1 * x1;
        b2 = y2 - kz * x2;
        x0 = (b2 - b1) / (k1 - kz);
        y0 = k1 * x0 + b1;
        // printf("k1 k2 = random\n");
    }
    R = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
    RT.x = x0;
    RT.y = y0;
    RT.R = R;
    RT.Angle = fabs(theta2 - theta1);
    return RT;
}

/* 路径光滑处理 */
void gpathsmooth::gfnvPathSmooth(gpath::tc_path *_path)
{
    
    int lngaoNodeOffset = 2;  // 偏置，以防最后点的选择超过终点，提前结束
    int lngaoLenNLater = 0;   // 转折点前ldgaoChangeLen对应的点
    int lngaoLenNBefore = 0;  // 转折点后ldgaoChangeLen对应的点
    int lngaoLenGap = 0;      // 转折点前和后相差的点个数
    int lngaoLenGapBefor = 0; // 相对与转折点前的相对点个数
    int lngaoLenGapLater = 0; // 相对与转折点后的相对点个数

    gpathsmooth::ts_circle lrtgaoTurningCircle; // 接收转折点处的圆心，半径，圆心角
    double ldgaoThetaBefore = 0; // 转折点和准备开始转的斜率，用于求圆心
    double ldgaoThetaLater = 0;  // 转折点和转完以后转的斜率，用于求圆心
    double ldgaoChangeLen = 0.1; // 转折点处提起多长开始转

    gpath::ts_PathCoord pathtrforeciev;// 用于接收坐标变换后的值
    for (int i = 10; i < _path->nPathNodeNum - lngaoNodeOffset; i++)
    {
        if (gpathsmooth::gfnbIFTurning(i,_path->global_path_cor))
        {
            if (_path->global_path_cor[i].y == _path->global_path_cor[i - 1].y && _path->global_path_cor[i].y != _path->global_path_cor[i + 1].y)
            {
                lngaoLenNLater = gpathsmooth::ReturnCaculatNDefualt(_path->global_path_cor, i, _path->nPathNodeNum, ldgaoChangeLen, 0);
                lngaoLenNBefore = i - 0.1 * 100;
                lngaoLenGap = lngaoLenNLater - lngaoLenNBefore;
                lngaoLenGapBefor = i - lngaoLenNBefore;
                lngaoLenGapLater = lngaoLenNLater - i;

                ldgaoThetaBefore = atan2f(_path->global_path_cor[i].y - _path->global_path_cor[lngaoLenNBefore].y, _path->global_path_cor[i].x - _path->global_path_cor[lngaoLenNBefore].x);
                ldgaoThetaLater = atan2f(_path->global_path_cor[lngaoLenNLater].y - _path->global_path_cor[i].y, _path->global_path_cor[lngaoLenNLater].x - _path->global_path_cor[i].x);

                lrtgaoTurningCircle = gpathsmooth::gfnvCircleCentrAndRand(ldgaoThetaBefore, _path->global_path_cor[lngaoLenNBefore].x, _path->global_path_cor[lngaoLenNBefore].y, ldgaoThetaLater, _path->global_path_cor[lngaoLenNLater].x, _path->global_path_cor[lngaoLenNLater].y);

                if (ldgaoThetaLater - ldgaoThetaBefore > 0)
                {
                    for (int j = 0; j <= lngaoLenGap; j++)
                    {
                        pathtrforeciev = gpathsmooth::gaofnGPFramTrans(lrtgaoTurningCircle.x, lrtgaoTurningCircle.y, j * lrtgaoTurningCircle.Angle / lngaoLenGap, 0, -lrtgaoTurningCircle.R);

                        _path->global_path_cor[i - lngaoLenGapBefor + j].x = pathtrforeciev.x;
                        _path->global_path_cor[i - lngaoLenGapBefor + j].y = pathtrforeciev.y;
                    }
                }
                else
                {
                    for (int j = 0; j <= lngaoLenGap; j++)
                    {
                        pathtrforeciev = gpathsmooth::gaofnGPFramTrans(lrtgaoTurningCircle.x, lrtgaoTurningCircle.y, -j * lrtgaoTurningCircle.Angle / lngaoLenGap, 0, lrtgaoTurningCircle.R);

                        _path->global_path_cor[i - lngaoLenGapBefor + j].x = pathtrforeciev.x;
                        _path->global_path_cor[i - lngaoLenGapBefor + j].y = pathtrforeciev.y;
                    }
                }
            }
            else if (_path->global_path_cor[i].y != _path->global_path_cor[i - 1].y && _path->global_path_cor[i].y == _path->global_path_cor[i + 1].y)
            {
                lngaoLenNLater = i + 0.1 * 100;
                lngaoLenNBefore = gpathsmooth::ReturnCaculatNDefualt(_path->global_path_cor, i, _path->nPathNodeNum, ldgaoChangeLen, 1);                
                lngaoLenGap = lngaoLenNLater - lngaoLenNBefore;
                lngaoLenGapBefor = i - lngaoLenNBefore;
                lngaoLenGapLater = lngaoLenNLater - i;

                ldgaoThetaBefore = atan2f(_path->global_path_cor[i].y - _path->global_path_cor[lngaoLenNBefore].y, _path->global_path_cor[i].x - _path->global_path_cor[lngaoLenNBefore].x);
                ldgaoThetaLater = atan2f(_path->global_path_cor[lngaoLenNLater].y - _path->global_path_cor[i].y, _path->global_path_cor[lngaoLenNLater].x - _path->global_path_cor[i].x);

                lrtgaoTurningCircle = gpathsmooth::gfnvCircleCentrAndRand(ldgaoThetaBefore, _path->global_path_cor[lngaoLenNBefore].x, _path->global_path_cor[lngaoLenNBefore].y, ldgaoThetaLater, _path->global_path_cor[lngaoLenNLater].x, _path->global_path_cor[lngaoLenNLater].y);

                for (int j = 0; j < lngaoLenGap; j++)
                {
                    if (ldgaoThetaLater - ldgaoThetaBefore > 0)
                    {
                        for (int j = 0; j <= lngaoLenGap; j++)
                        {
                            pathtrforeciev = gpathsmooth::gaofnGPFramTrans(lrtgaoTurningCircle.x, lrtgaoTurningCircle.y, ldgaoThetaBefore + j * lrtgaoTurningCircle.Angle / lngaoLenGap, 0, -lrtgaoTurningCircle.R);
                            _path->global_path_cor[i - lngaoLenGapBefor + j].x = pathtrforeciev.x;
                            _path->global_path_cor[i - lngaoLenGapBefor + j].y = pathtrforeciev.y;
                        }
                    }
                    else
                    {
                        for (int j = 0; j <= lngaoLenGap; j++)
                        {
                            pathtrforeciev = gpathsmooth::gaofnGPFramTrans(lrtgaoTurningCircle.x, lrtgaoTurningCircle.y, ldgaoThetaBefore - j * lrtgaoTurningCircle.Angle / lngaoLenGap, 0, lrtgaoTurningCircle.R);
                            _path->global_path_cor[i - lngaoLenGapBefor + j].x = pathtrforeciev.x;
                            _path->global_path_cor[i - lngaoLenGapBefor + j].y = pathtrforeciev.y;
                        }
                    }
                }
            }
            else
            {
                lngaoLenNLater = gpathsmooth::ReturnCaculatNDefualt(_path->global_path_cor, i, _path->nPathNodeNum, ldgaoChangeLen, 0);
                lngaoLenNBefore = gpathsmooth::ReturnCaculatNDefualt(_path->global_path_cor, i, _path->nPathNodeNum, ldgaoChangeLen, 1);
                
                lngaoLenGap = lngaoLenNLater - lngaoLenNBefore;
                lngaoLenGapBefor = i - lngaoLenNBefore;
                lngaoLenGapLater = lngaoLenNLater - i;

                ldgaoThetaBefore = atan2f(_path->global_path_cor[i].y - _path->global_path_cor[lngaoLenNBefore].y, _path->global_path_cor[i].x - _path->global_path_cor[lngaoLenNBefore].x);
                ldgaoThetaLater = atan2f(_path->global_path_cor[lngaoLenNLater].y - _path->global_path_cor[i].y, _path->global_path_cor[lngaoLenNLater].x - _path->global_path_cor[i].x);
                lrtgaoTurningCircle = gpathsmooth::gfnvCircleCentrAndRand(ldgaoThetaBefore, _path->global_path_cor[lngaoLenNBefore].x, _path->global_path_cor[lngaoLenNBefore].y, ldgaoThetaLater, _path->global_path_cor[lngaoLenNLater].x, _path->global_path_cor[lngaoLenNLater].y);

                for (int j = 0; j < lngaoLenGap; j++)
                {
                    if (ldgaoThetaLater - ldgaoThetaBefore > 0)
                    {
                        for (int j = 0; j <= lngaoLenGap; j++)
                        {
                            pathtrforeciev = gpathsmooth::gaofnGPFramTrans(lrtgaoTurningCircle.x, lrtgaoTurningCircle.y, ldgaoThetaBefore + j * lrtgaoTurningCircle.Angle / lngaoLenGap, 0, -lrtgaoTurningCircle.R);
                            _path->global_path_cor[i - lngaoLenGapBefor + j].x = pathtrforeciev.x;
                            _path->global_path_cor[i - lngaoLenGapBefor + j].y = pathtrforeciev.y;
                        }
                    }
                    else
                    {
                        for (int j = 0; j <= lngaoLenGap; j++)
                        {
                            pathtrforeciev = gpathsmooth::gaofnGPFramTrans(lrtgaoTurningCircle.x, lrtgaoTurningCircle.y, ldgaoThetaBefore - j * lrtgaoTurningCircle.Angle / lngaoLenGap, 0, lrtgaoTurningCircle.R);
                            _path->global_path_cor[i - lngaoLenGapBefor + j].x = pathtrforeciev.x;
                            _path->global_path_cor[i - lngaoLenGapBefor + j].y = pathtrforeciev.y;
                        }
                    }
                }
            }
        }
    }
    std::cout << "api_gfnvPathSmooth end" << std::endl;
}