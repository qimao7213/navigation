#pragma once
#ifndef __PATH_DATA_H__
#define __PATH_DATA_H__

#include <utility>  // pair
#include <iostream>

#define HeightStep 0.25 // foot max step size
#define WidthStep 0.27  // foot width
#define SETPOVER 0.05   //

namespace gpath
{
    typedef struct CELL // 閿熸枻鎷烽敓鏂ゆ嫹閿熼叺纭锋嫹閿熺煫鍖℃嫹閿熸枻鎷烽敓鐨嗩亷鎷烽敓鏂ゆ嫹閿熸枻鎷锋伅
    {
        int m_nIsEmpty;
        int m_nSelf_i;
        int m_nSelf_j;

        int m_nParent_i;
        int m_nParent_j;
        double m_Hight; // 閿熸枻鎷峰厓閿熸枻鎷峰彣閿燂拷
        double m_Width; // 閿熸枻鎷峰厓閿熸枻鎷烽敓鏂ゆ嫹榫嬮敓渚ヮ剨鎷烽敓杞匡拷1
        double m_f;
        double m_g;
        double m_h;
        int MARKER_TYPE; // 閿熸枻鎷峰厓閿熸枻鎷烽敓鏂ゆ嫹閿熼叺锝忔嫹鍙伴敓闃讹綇鎷峰 ...
    } ts_cell;

    typedef struct POSE
    {
        int startx = 0;
        int starty = 0;
        int endx = 0;
        int endy = 0;
        int hightz = 0;
    } ts_pose;

    enum e_EnvTypy
    {
        PlANT = 0,
        STEP1,
        STEP2,
        STEP3,
        STEP4,
        STEP5,
        WALL = 10,
        SLENDER = 11
    };

    typedef struct PathCoordinate
    {
        double x = 0;
        double y = 0;
        double z = 0;
        double theta = 0;
    } ts_PathCoord,ts_FootCoord;

    typedef std::pair<int, int> pa_point;           // 閿熸枻鎷烽敓鏂ゆ嫹閿燂拷
    typedef std::pair<double, pa_point> papa_point; // 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰€奸敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿燂拷

} // namespace gpath


#endif //__PATH_DATA_H__