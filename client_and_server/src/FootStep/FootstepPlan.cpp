#include "FootStep/FootstepPlan.h"
#include <cmath>
#include <stdio.h>
gfootstepplan::tc_PathCapture pathcapture;
gfootstepplan::tc_Footstep gfootstep; // V1-有问题
gfootstepplan::tc_Footstep _footstep;
void tfnGFoot1()
{
    gpath::tc_path *mypath;

    mypath = &gpath::api_PathPlaningReturn(0, 0, 432, 20);
    gpathsmooth::gfnvSaveDataWithFile(mypath, "../../GPath.dat");
    gpathsmooth::gfnvPathTransLine(mypath);
    gpathsmooth::gfnvSaveDataWithFile(mypath, "../../GPathTransLine.dat");
    gpathsmooth::gfnvPathSmooth(mypath);
    gpathsmooth::gfnvSaveDataWithFile(mypath, "../../GPathSmooth.dat");

    gfootstepplan::tc_BHRhard hardpara(0.35,10,0.08);
    gfootstepplan::gfnvCapturePath(mypath,hardpara);
    gpathsmooth::gfnvSaveDataWithFile(mypath, "../../GPathCaputer.dat");

    gfootstepplan::gfndPlantFootStepPlanner(mypath, hardpara);
    gfootstepplan::gfnvSaveFoot(&gfootstep, "../../GFoot.dat");
}
void tfnGFoot2()
{
    gpath::tc_path *mypath;
    gfootstepplan::tc_PathCapture *mycpath;
    gfootstepplan::tc_Footstep *myfootstep;

    mypath = &gpath::api_PathPlaningReturn(0, 0, 432, 20);
    //std::cout << "|-- FootstepPlan nPathNodeNum:"<< mypath->nPathNodeNum << std::endl;
    gpathsmooth::gfnvSaveDataWithFile(mypath, "../../GPath.dat");
    
    gpathsmooth::gfnvPathTransLine(mypath);
    gpathsmooth::gfnvSaveDataWithFile(mypath, "../../GPathTransLine.dat");

    gpathsmooth::gfnvPathSmooth(mypath);
    //std::cout << "|-- gfnvPathSmooth nPathNodeNum:" << mypath->nPathNodeNum << std::endl;
    gpathsmooth::gfnvSaveDataWithFile(mypath, "../../GPathSmooth.dat");

    gfootstepplan::tc_BHRhard hardpara(0.35, 10, 0.08);
    mycpath = &gfootstepplan::gfnvCapturePathV2(mypath, hardpara);
    //std::cout << "|-- gfnvCapturePathV2 nPathNodeNum:" << mypath->nPathNodeNum << std::endl;
    gfootstepplan::gfnvSaveCPath(mycpath, "../../GPathCaputer.dat");

    myfootstep = &gfootstepplan::gfndPlantFootStepPlannerV2(mycpath, hardpara);
    //std::cout << "|-- gfndPlantFootStepPlannerV2 nPathNodeNum:" << mycpath->GCAPTURE_PATH_NUM<< std::endl;
    gfootstepplan::gfnvSaveFoot(myfootstep, "../../GFoot.dat");
}

double gfootstepplan::gfndCaculateTurningTheta(gpath::tc_path *_path, int ginow, int gilast)
{
    double lgdReturn = 0;
    lgdReturn = atan2f((_path->global_path_cor[ginow].y - _path->global_path_cor[gilast].y), (_path->global_path_cor[ginow].x - _path->global_path_cor[gilast].x));
    return lgdReturn;
}
/* 捕获点 */

void gfootstepplan::gfnvCapturePath(gpath::tc_path *_path, gfootstepplan::tc_BHRhard hardpara)
{
    double lgaodsteplen = hardpara.dmaxstep;        // 默认最大步长 0.35
    double lgaodsteptheta = hardpara.dmaxsteptheta * Gdeg2rad; // 默认最大转角10度 10 * Grad2deg; //
    int lgnInterval = 5;                   // 控制步长变化间隔
    static int lgsni = 0;                  // 捕获点下标
    static int lgsniend = 100 * lgaodsteplen / lgnInterval;
    int lgnlast = 0;       // 上一个捕获点的下标
    int lgnChangeLast = 0; // 上一次捕获点变化的多少

    int FPATH_NODE_NUM = _path->nPathNodeNum;

    for (int i = 0; i < FPATH_NODE_NUM; i++)
    {
        if (gpathsmooth::gfnnTurningChangFlag(_path, i, 18)) // 不是圆弧处
        {
            if (i < 50 && gpathsmooth::gfnnTurningChangFlag(_path, i, 18)) // 开始时，控制步长由小到大
            {
                _path->global_path_cor[lgsni].x = _path->global_path_cor[i].x;
                _path->global_path_cor[lgsni].y = _path->global_path_cor[i].y;
                _path->global_path_cor[lgsni].z = _path->global_path_cor[i].z;
                _path->global_path_cor[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i; // 上一次的路径点，用于计算角度变化
                if (lgsni * lgnInterval <= 35)
                {
                    i = i + lgsni * lgnInterval;         // 由0-5-10-15-20-25-30-35逐渐增加变化，直到设定的最大变化
                    lgnChangeLast = lgsni * lgnInterval; // 保存此次变化量视为上一次的变化量
                }
                else
                {
                    i = i + lgnChangeLast;
                }
            }
            else if (i > (FPATH_NODE_NUM - 50))
            {
                _path->global_path_cor[lgsni].x = _path->global_path_cor[i].x;
                _path->global_path_cor[lgsni].y = _path->global_path_cor[i].y;
                _path->global_path_cor[lgsni].z = _path->global_path_cor[i].z;
                _path->global_path_cor[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path,i, lgnlast);
                lgnlast = i;
                if (lgsniend * lgnInterval <= 35 && lgsniend >= 0)
                {
                    i = i + lgsniend * lgnInterval;         // 由0-5-10-15-20-25-30-35逐渐增加变化，直到设定的最大变化
                    lgnChangeLast = lgsniend * lgnInterval; // 保存此次变化量视为上一次的变化量
                }
                else
                {
                    i = FPATH_NODE_NUM - 1;
                    // i = i + lgnChangeLast;
                }
                lgsniend--;
            }
            else
            {
                _path->global_path_cor[lgsni].x = _path->global_path_cor[i].x;
                _path->global_path_cor[lgsni].y = _path->global_path_cor[i].y;
                _path->global_path_cor[lgsni].z = _path->global_path_cor[i].z;
                _path->global_path_cor[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i; // 上一次的路径点，用于计算角度变化
                i = i + lgnChangeLast;
            }
            lgsni++;
        }
        else
        {
            if (gpathsmooth::gfnnTurningChangFlag(_path, i, 2))
            {
                _path->global_path_cor[lgsni].x = _path->global_path_cor[i].x;
                _path->global_path_cor[lgsni].y = _path->global_path_cor[i].y;
                _path->global_path_cor[lgsni].z = _path->global_path_cor[i].z;
                _path->global_path_cor[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i;
                i = i + 5;
            }
            else
            {
                _path->global_path_cor[lgsni].x = _path->global_path_cor[i].x;
                _path->global_path_cor[lgsni].y = _path->global_path_cor[i].y;
                _path->global_path_cor[lgsni].z = _path->global_path_cor[i].z;
                _path->global_path_cor[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i; // 上一次的路径点，用于计算角度变化
                i = i + 2;
            }

            lgsni++;
        }    
    }
    pathcapture.GCAPTURE_PATH_NUM = lgsni;
}
gfootstepplan::tc_PathCapture &gfootstepplan::gfnvCapturePathV2(gpath::tc_path *_path, gfootstepplan::tc_BHRhard hardpara)
{
    double lgaodsteplen = hardpara.dmaxstep;                   // 默认最大步长 0.35
    double lgaodsteptheta = hardpara.dmaxsteptheta * Gdeg2rad; // 默认最大转角10度 10 * Grad2deg; //
    int lgnInterval = 5;                                       // 控制步长变化间隔
    static int lgsni = 0;                                      // 捕获点下标
    static int lgsniend = 100 * lgaodsteplen / lgnInterval;
    int lgnlast = 0;       // 上一个捕获点的下标
    int lgnChangeLast = 0; // 上一次捕获点变化的多少

    int lgngap = 10; // 18; 2023-05-26(10)

    int FPATH_NODE_NUM = _path->nPathNodeNum;

    for (int i = 0; i < FPATH_NODE_NUM; i++)
    {
        if (gpathsmooth::gfnnTurningChangFlag(_path, i, lgngap)) // 不是圆弧处
        {
            if (i < 50 && gpathsmooth::gfnnTurningChangFlag(_path, i, lgngap)) // 开始时，控制步长由小到大
            {
                pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i; // 上一次的路径点，用于计算角度变化
                if (lgsni * lgnInterval <= 35)
                {
                    i = i + lgsni * lgnInterval;         // 由0-5-10-15-20-25-30-35逐渐增加变化，直到设定的最大变化
                    lgnChangeLast = lgsni * lgnInterval; // 保存此次变化量视为上一次的变化量
                }
                else
                {
                    i = i + lgnChangeLast;
                }
            }
            else if (i > (FPATH_NODE_NUM - 50))
            {
                pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i;
                if (lgsniend * lgnInterval <= 35 && lgsniend >= 0)
                {
                    i = i + lgsniend * lgnInterval;         // 由0-5-10-15-20-25-30-35逐渐增加变化，直到设定的最大变化
                    lgnChangeLast = lgsniend * lgnInterval; // 保存此次变化量视为上一次的变化量
                }
                else
                {
                    i = FPATH_NODE_NUM - 1;
                    // i = i + lgnChangeLast;
                }
                lgsniend--;
            }
            else
            {
                pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i; // 上一次的路径点，用于计算角度变化
                i = i + lgnChangeLast;
            }
            lgsni++;
        }
        else
        {
            if (gpathsmooth::gfnnTurningChangFlag(_path, i, 2))
            {
                pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i;
                i = i + 5;
            }
            else
            {
                pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i; // 上一次的路径点，用于计算角度变化
                i = i + 2;
            }

            lgsni++;
        }
    }
    pathcapture.GCAPTURE_PATH_NUM = lgsni;
    std::cout << "|-- in gfnvCapturePathV2 GCAPTURE_PATH_NUM:" << lgsni << std::endl;
    return pathcapture;
}
// double map_resolution is map resolution, the unit is m
gfootstepplan::tc_PathCapture &gfootstepplan::gfnvCapturePathV3(gpath::tc_path *_path, gfootstepplan::tc_BHRhard hardpara,double map_resolution)
{
    double lgaodsteplen = hardpara.dmaxstep;                   // 默认最大步长 0.35
    double lgaodsteptheta = hardpara.dmaxsteptheta * Gdeg2rad; // 默认最大转角10度 10 * Grad2deg; //
    double lgnDetaStepLen = 0.05;                              // progressive increase step length(m) with real robot 每次变化的增加量
    double lgnInterval = lgnDetaStepLen / map_resolution;         // progressive increase step i with map_resolution 变化的增加量对应的增加的栅格数目（对应分辨率，）
    std::cout << "lgnInterval:" << lgnInterval << std::endl;

    static int lgsni = 0;                                   // 捕获点下标
    static int lgsniend = lgaodsteplen / lgnDetaStepLen;    // 到达最大步长需要的步数

    int lgnlast = 0;       // 上一个捕获点的对应的路径下标
    int lgnChangeLast = 0; // 上一次捕获点变化的多少

    int lgngap = 0.10 / map_resolution; // 18; 2023-05-26(10) 判断转弯向前后扩展的点数

    int FPATH_NODE_NUM = _path->nPathNodeNum;

    int lgnStartToMaxStep, lgnStartToMaxStepI, lgnStartToMaxStepIwithRSL; 
    lgnStartToMaxStep = lgsniend - 2; // 不要到达最大步长，缩小一点
    lgnStartToMaxStepI = (int)(lgnDetaStepLen*100*(1 + lgnStartToMaxStep) * lgnStartToMaxStep / 2); //增长到接近最大步长走过的长度cm，也是1cm对应的栅格数
    lgnStartToMaxStepIwithRSL = lgnStartToMaxStepI / (map_resolution * 100);                        // 增长到接近最大步长走过对应的栅格数 (分辨率 map_resolution)

    for (int i = 0; i < FPATH_NODE_NUM; i++)
    {
        if (gpathsmooth::gfnnTurningChangFlag(_path, i, lgngap)) // 不是圆弧处
        {
            if (i < lgnStartToMaxStepIwithRSL && gpathsmooth::gfnnTurningChangFlag(_path, i, lgngap)) // 开始时，控制步长由小到大
            {
                pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i; // 上一次的路径点，用于计算角度变化
                if (lgsni * lgnDetaStepLen <= lgaodsteplen) // 第 lgsni 步 步长
                {
                    i = i + (int)(lgsni * lgnInterval);  // 每步增加对应的路径节点
                    lgnChangeLast = (int)(lgsni * lgnInterval); // 保存此次路径点变化视为上一次的变化 ，栅格数
                }
                else
                {
                    i = i + lgnChangeLast;  // 达到最大后，以这样的固定数变化
                }
            }
            // else if (i > (FPATH_NODE_NUM - lgnStartToMaxStepIwithRSL)) //靠近终点时 
            // {
            //     pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
            //     pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
            //     pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
            //     pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
            //     lgnlast = i;
            //     if (lgsniend * lgnInterval <= 35 && lgsniend >= 0)
            //     {
            //         i = i + lgsniend * lgnInterval;         // 由0-5-10-15-20-25-30-35逐渐增加变化，直到设定的最大变化
            //         lgnChangeLast = lgsniend * lgnInterval; // 保存此次变化量视为上一次的变化量
            //     }
            //     else
            //     {
            //         i = FPATH_NODE_NUM - 1;
            //         // i = i + lgnChangeLast;
            //     }
            //     lgsniend--;
            // }
            else
            {
                pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i; // 上一次的路径点，用于计算角度变化
                i = i + lgnChangeLast;
            }
            lgsni++;
        }
        else
        {
            if (gpathsmooth::gfnnTurningChangFlag(_path, i, 2))
            {
                pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
                lgnlast = i;
                i = i + (int)(lgnInterval);
            }
            // else
            // {
            //     pathcapture.capurepath[lgsni].x = _path->global_path_cor[i].x;
            //     pathcapture.capurepath[lgsni].y = _path->global_path_cor[i].y;
            //     pathcapture.capurepath[lgsni].z = _path->global_path_cor[i].z;
            //     pathcapture.capurepath[lgsni].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, lgnlast);
            //     lgnlast = i; // 上一次的路径点，用于计算角度变化
            //     i = i + 2;
            // }

            lgsni++;
        }
    }
    pathcapture.GCAPTURE_PATH_NUM = lgsni;
    std::cout << "|-- in gfnvCapturePathV2 GCAPTURE_PATH_NUM:" << lgsni << std::endl;
    return pathcapture;
}

gfootstepplan::tc_PathCapture &gfootstepplan::gfnvCapturePathV4(gpath::tc_path *_path, gfootstepplan::tc_BHRhard hardpara,double map_resolution)
{
    double dMaxStepLen = hardpara.dmaxstep; // max step length
    double dMaxStepTurnAngel = hardpara.dmaxsteptheta*Gdeg2rad; // max step turn angle
    double dDetaStepLen = 0.05;                               // progressive increase step length(m) with real robot 每次变化的增加量
    double dDetaStepGrid = dDetaStepLen / map_resolution;       // progressive increase step i with map_resolution 变化的增加量对应的增加的栅格数目（对应分辨率，保留小数位，后续再约等于整数）
    static int nCapi = 0;                                  // 当前捕获点下标
    static int nCapLasti = 0;                              //上一个捕获点的下标
    int nCapChangeLasti = 0;                               // 上一次捕获点变化的多少栅格
    static int nMaxLenToStep = round(dMaxStepLen / dDetaStepLen); // 到达最大步长需要的步数
    int nChangeGap = 0.10 / map_resolution;

    int nStartToMaxStep, nStartToMaxStepI, nStartToMaxStepIwithRSL;
    nStartToMaxStep = nMaxLenToStep - 2;                                                        // 不要到达最大步长，缩小一点
    nStartToMaxStepI = (int)(dDetaStepLen * 100 * (1 + nStartToMaxStep) * nStartToMaxStep / 2); // 增长到接近最大步长走过的长度cm，也是1cm对应的栅格数
    nStartToMaxStepIwithRSL = nStartToMaxStepI / (map_resolution * 100);                            // 增长到接近最大步长走过对应的栅格数 (分辨率 map_resolution)

    static int nTurnFlag = 0;

    for (int i = 0; i < _path->nPathNodeNum; i++)
    {   
        if (gpathsmooth::gfnnTurningChangFlag(_path, i, nChangeGap)) // 不是圆弧处
        {
            if (i < nStartToMaxStepIwithRSL && gpathsmooth::gfnnTurningChangFlag(_path, i, nChangeGap))
            {
                pathcapture.capurepath[nCapi].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[nCapi].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[nCapi].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[nCapi].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, nCapLasti);
                nCapLasti = i; // 上一次的路径点，用于计算角度变化
                if (nTurnFlag * dDetaStepLen <= dMaxStepLen)
                {
                    i = i + nTurnFlag * dDetaStepGrid;
                    nCapChangeLasti = nTurnFlag * dDetaStepGrid; // 保存此次变化视为上一次的变化
                }
                else
                {
                    i = i + nCapChangeLasti;
                }
                nTurnFlag++; // 如果不是转弯点，标志位置 +1
            }
            else if (i > (_path->nPathNodeNum - nStartToMaxStepIwithRSL))
            {
                pathcapture.capurepath[nCapi].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[nCapi].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[nCapi].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[nCapi].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, nCapLasti);
                nCapLasti = i; // 上一次的路径点，用于计算角度变化

                i = i + dDetaStepGrid;

                nTurnFlag++; // 如果不是转弯点，标志位置 +1
            }
            else
            {
                pathcapture.capurepath[nCapi].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[nCapi].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[nCapi].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[nCapi].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, nCapLasti);
                nCapLasti = i; // 上一次的路径点，用于计算角度变化

                i = i + nCapChangeLasti;
                nTurnFlag++; // 如果不是转弯点，标志位置 +1
            }

            nCapi++;
        }
        else // 是圆弧处
        {
            nTurnFlag = 0;
            if (gpathsmooth::gfnnTurningChangFlag(_path, i, 2/(100*map_resolution)))
            {
                pathcapture.capurepath[nCapi].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[nCapi].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[nCapi].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[nCapi].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, nCapLasti);
                nCapLasti = i;
                i = i + dDetaStepGrid;
            }
            else
            {
                pathcapture.capurepath[nCapi].x = _path->global_path_cor[i].x;
                pathcapture.capurepath[nCapi].y = _path->global_path_cor[i].y;
                pathcapture.capurepath[nCapi].z = _path->global_path_cor[i].z;
                pathcapture.capurepath[nCapi].theta = gfootstepplan::gfndCaculateTurningTheta(_path, i, nCapLasti);
                nCapLasti = i; // 上一次的路径点，用于计算角度变化
                i = i + dDetaStepGrid/2;
            }

            nCapi++;
        }
        
    }
    pathcapture.GCAPTURE_PATH_NUM = nCapi;
    std::cout << "|-- in gfnvCapturePathV4 GCAPTURE_PATH_NUM:" << nCapi << std::endl;
    return pathcapture;
}
double gfootstepplan::gfndPlantFootStepPlanner(gpath::tc_path *_path, gfootstepplan::tc_BHRhard hardpara)
{
    double lgaodsteplen = hardpara.dmaxstep; // 默认最大步长
    double lgaodsteptheta = hardpara.dmaxsteptheta * Gdeg2rad; // 默认最大转角10度 10*Grad2deg;//
    double lgaodstepWidth = hardpara.dstepwidth;
    int lgaonLeftOrRight = 1;
    
    for (int i = 0; i < pathcapture.GCAPTURE_PATH_NUM; i++)
    {
        gfootstep.gfoot[i] = gpathsmooth::gaofnGPFramTrans(_path->global_path_cor[i].x, _path->global_path_cor[i].y, _path->global_path_cor[i].theta, 0.0, lgaonLeftOrRight * lgaodstepWidth);
        gfootstep.gfoot[i].theta = _path->global_path_cor[i].theta;
        
        lgaonLeftOrRight = -lgaonLeftOrRight;
    }
    return 0;
}

gfootstepplan::tc_Footstep &gfootstepplan::gfndPlantFootStepPlannerV2(gfootstepplan::tc_PathCapture *_cpath, gfootstepplan::tc_BHRhard hardpara)
{
    // gfootstepplan::tc_Footstep *_footstep;

    double lgaodsteplen = hardpara.dmaxstep;                   // 默认最大步长
    double lgaodsteptheta = hardpara.dmaxsteptheta * Gdeg2rad; // 默认最大转角10度 10*Grad2deg;//
    double lgaodstepWidth = hardpara.dstepwidth;
    int lgaonLeftOrRight = -1;

    for (int i = 0; i < pathcapture.GCAPTURE_PATH_NUM; i++)
    {
        _footstep.gfoot[i] = gpathsmooth::gaofnGPFramTrans(_cpath->capurepath[i].x, _cpath->capurepath[i].y, _cpath->capurepath[i].theta, 0.0, lgaonLeftOrRight * lgaodstepWidth);
        _footstep.gfoot[i].theta = _cpath->capurepath[i].theta;

        lgaonLeftOrRight = -lgaonLeftOrRight;
    }

    // set the last foot align at the last last foot 
    _footstep.gfoot[pathcapture.GCAPTURE_PATH_NUM] = gpathsmooth::gaofnGPFramTrans(_cpath->capurepath[pathcapture.GCAPTURE_PATH_NUM-1].x, _cpath->capurepath[pathcapture.GCAPTURE_PATH_NUM-1].y, _cpath->capurepath[pathcapture.GCAPTURE_PATH_NUM-1].theta, 0.0, lgaonLeftOrRight * lgaodstepWidth);
    _footstep.gfoot[pathcapture.GCAPTURE_PATH_NUM].theta = _cpath->capurepath[pathcapture.GCAPTURE_PATH_NUM - 1].theta;

    std::cout << "api_gfndPlantFootStepPlannerV2 end" << std::endl;
    return _footstep;
}
void gfootstepplan::gfnvSaveFoot(gfootstepplan::tc_Footstep *_foot, char *filetest)
{
    FILE *foot_node;
    foot_node = fopen(filetest, "wb");
    // printf("save _path->nPathNodeNum data %d\n", pathcapture.GCAPTURE_PATH_NUM);

    fprintf(foot_node, "%s %s %s %s\n", "path_x", "path_y", "path_z", "path_theta");
    // fprintf(path_node, "%s %s %s %s ", "capture_x", "capture_y", "capture_z", "capture_theta");
    // fprintf(path_node, "%s %s %s %s\n", "foot_x", "foot_y", "foot_z", "foot_theta");

    for (int i = 0; i < MAX_ARRAY_NUM; i++)
    {
        fprintf(foot_node, "%lf %lf %lf %lf\n", _foot->gfoot[i].x, _foot->gfoot[i].y, _foot->gfoot[i].z, _foot->gfoot[i].theta);
    }
    fclose(foot_node);
}

void gfootstepplan::gfnvSaveCPath(gfootstepplan::tc_PathCapture *_cpath, char *filetest)
{
    FILE *path_node_cp;
    path_node_cp = fopen(filetest, "wb");
    // printf("save _path->nPathNodeNum data %d\n", _cpath->GCAPTURE_PATH_NUM);

    fprintf(path_node_cp, "%s %s %s %s\n", "cpath_x", "cpath_y", "cpath_z", "cpath_theta");
    // fprintf(path_node, "%s %s %s %s ", "capture_x", "capture_y", "capture_z", "capture_theta");
    // fprintf(path_node, "%s %s %s %s\n", "foot_x", "foot_y", "foot_z", "foot_theta");
    
    for (int i = 0; i < _cpath->GCAPTURE_PATH_NUM; i++)
    {
        //printf("%i %lf %lf\n",i, _cpath->capurepath[i].x, _cpath->capurepath[i].y);
        fprintf(path_node_cp, "%lf %lf %lf %lf\n", _cpath->capurepath[i].x, _cpath->capurepath[i].y, _cpath->capurepath[i].z,_cpath->capurepath[i].theta);
    }
    fclose(path_node_cp);
}