#include "Pathplan/path.h"
#include <float.h> // FLT_MAX
#include <math.h>
#include <stack>
#include <set>
#include <string.h> //memset

using namespace gpath;
/*--------------  ȫ�ֱ��� ---------------------*/
ts_pose wallpose, step1pose, step2pose, step3pose, step4pose;  // �������ϰ���λ��
tc_path g_path;

static int nPathNodeNum;
/*--------------  ���� ---------------------*/

/*--------------  ��ͼ�������� ---------------------*/
/***** ��ʼ��դ��Ԫ��Ϣ�����ڵ㣬f,g,hֵ����Ԫ�񾫶ȣ��߶ȣ����ͣ�ռ����� *****/
void gpath::fnvInitCell(ts_cell _grid[][ROW])
{
    // std::cout << "fnvInitCell start" << std::endl;
    int R = 0;
    int C = 0;
    for (C = 0; C < COL; C++)
    {
        _grid[C][R].m_nSelf_i = C;               // ����դ��������������������
        for (R = 0; R < ROW; R++)
        {
            _grid[C][R].m_nSelf_j = R;
            _grid[C][R].m_f = FLT_MAX;           // ��ʼֵ�������
            _grid[C][R].m_g = FLT_MAX;
            _grid[C][R].m_h = FLT_MAX;
            _grid[C][R].m_nParent_i = -1;        // û�г�ʼ���ڵ�
            _grid[C][R].m_nParent_j = -1;
            _grid[C][R].m_Hight = 0;             // Ĭ�ϵ�Ԫ��߶���ϢΪ0������ƽ�ص���
            _grid[C][R].m_Width = 0.5;           // ÿ����Ԫ��ľ���
            _grid[C][R].MARKER_TYPE = PlANT;  // ��Ԫ�����ڵĵ�������
            _grid[C][R].m_nIsEmpty = 0;          // ��Ԫ��ռ�������0-û��ռ�ã�1-��ռ��

            // grid[R][C] = _grid[R][C].m_nIsEmpty;
        }
    }
    // std::cout << "fnvInitCell end" << std::endl;
}

/****** �����ϰ���ϰ������㣬�յ�x��y���꣬�߶ȣ����ȣ����ͣ��Ƿ�ռ�ã���ͼ��Ϣ�������������յ�******************/
void gpath::fnvSetObstacle(int Begin_x, int End_x, int Begin_y, int End_y, double H, double W, int MARK, int isempty, ts_cell _grid[][ROW], ts_pose markpose) // �����ϰ���
{
    for (int i = Begin_x; i < End_x; i++) // ��ʼ������λ����Ϣ
    {
        for (int j = Begin_y; j < End_y; j++)
        {
            _grid[i][j].m_Hight = H;
            _grid[i][j].m_Width = W;
            _grid[i][j].MARKER_TYPE = MARK;
            _grid[i][j].m_nIsEmpty = isempty;
            // grid[i][j] = Cell[i][j].m_nIsEmpty; // isempty �����õ�Ԫ���Ƿ�ռ�ã�grid[][]��������һЩ��ʼ���
        }
    }
    markpose.startx = Begin_x;
    markpose.endx = End_x;
    markpose.starty = Begin_y;
    markpose.endy = End_y;
}

/*** ��ʼ���ϰ�����Ϣ ***/
void gpath::fnvInitObstacle(ts_cell _grid[][ROW]) // ��ʼ���ϰ���λ�ú���״��Ϣ
{
    // std::cout << "fnvInitObstacle start" << std::endl;
    gpath::fnvSetObstacle(130, 180, 0, 60, 0.5, 0.5, WALL, 1, _grid, wallpose);
    // std::cout << "fnvInitObstacle end" << std::endl;
}
/*** ��ʼ����ͼ��դ����Ϣ���ϰ�����Ϣ  ***/
void gpath::fnInitGridMap(ts_cell _grid[][ROW]) // ��ʼ��դ���ͼ
{
    gpath::fnvInitCell(_grid); // ��ʼ��դ��Ԫ��Ϣ
    gpath::fnvInitObstacle(_grid); // ��ʼ���ϰ���λ�ú���״��Ϣ
}

/*** ��ʼ�����դ����Ϣ  ****/
void gpath::fnvInitStart(ts_cell _grid[][ROW], pa_point m_Start, pa_point m_Goal)
{
    int i, j;
    i = m_Start.first;
    j = m_Start.second;

    _grid[i][j].m_nSelf_i = i;
    _grid[i][j].m_nSelf_j = j;
    _grid[i][j].m_Hight = 0;
    _grid[i][j].m_f = 0.0;
    _grid[i][j].m_g = 0.0;
    _grid[i][j].m_h = 0.0;
    _grid[i][j].m_nParent_i = i;
    _grid[i][j].m_nParent_j = j;
    _grid[i][j].m_nIsEmpty = 0;
    _grid[i][j].MARKER_TYPE = PlANT;
}

/*--------------  ��ͼ��Ϣ�жϺ��� ---------------------*/
/*** �жϸ����ĵ�Ԫ���Ƿ񳬳���ͼ�߽� ****/
bool gpath::fnisValid(int m_nCol, int m_nRow)
{
    return (m_nRow >= 0) && (m_nRow < ROW) && (m_nCol >= 0) && (m_nCol < COL);
}
/*** �жϸ����ĵ�Ԫ���Ƿ�ռ�� ****/
bool gpath::fnisEmpty(ts_cell _grid[][ROW], int m_nCol, int m_nRow)
{
    if (_grid[m_nCol][m_nRow].m_nIsEmpty == 0)
        return (true);
    else
        return (false);
}
/*** �жϸ����ĵ�Ԫ���Ƿ�ռ�ã��Ƿ������߸߶� ****/
bool gpath::fnisEmptyWithHeight(ts_cell _grid[][ROW], int m_nCol, int m_nRow, double Hight)
{
    if (_grid[m_nCol][m_nRow].m_nIsEmpty == 0 || Hight <= HeightStep)
        return (true);
    else
        return (false);
}
/*** �жϸ����ĵ�Ԫ���Ƿ���Ŀ��� ****/
bool gpath::fnisGoal(int m_nCol, int m_nRow, pa_point m_Goal)
{
    if (m_nCol == m_Goal.first && m_nRow == m_Goal.second)
        return (true);
    else
        return (false);
}
/*** �жϸ����������յ㵥Ԫ���Ƿ���Ч���Ƿ�Ϊռ�� ****/
void gpath::fncellCheck(ts_cell _grid[][ROW], pa_point m_Start, pa_point m_Goal)
{
    if (gpath::fnisValid(m_Start.first, m_Start.second) == false)
        printf("Start is invalid\n");
    if (gpath::fnisValid(m_Goal.first, m_Goal.second) == false)
        printf("Goal is invalid\n");
    if (gpath::fnisEmpty(_grid, m_Start.first, m_Start.second) == false)
        printf("Start is blocked\n");
    if (gpath::fnisEmpty(_grid, m_Goal.first, m_Goal.second) == false)
        printf("Goal is blocked\n");
    return;
}
/*** �жϸ����Ĵ��߶ȵĵ�Ԫ���Ƿ���Ч���Ƿ�Ϊռ�� ****/
void gpath::fncellCheckWithHeight(ts_cell _grid[][ROW], pa_point m_Start, pa_point m_Goal, double Hight)
{
    if (gpath::fnisValid(m_Start.first, m_Start.second) == false)
        printf("Start is invalid\n");
    if (gpath::fnisValid(m_Goal.first, m_Goal.second) == false)
        printf("Goal is invalid\n");
    // if (isEmpty(grid, m_Start.first, m_Start.second) == false) printf("Start is blocked\n");
    if (gpath::fnisEmptyWithHeight(_grid, m_Start.first, m_Start.second, Hight) == false)
        printf("Goal is blocked\n");
    if (gpath::fnisEmptyWithHeight(_grid, m_Goal.first, m_Goal.second, Hight) == false)
        printf("Goal is blocked\n");
    return;
}
/*** ��������ֵ h ****/
double gpath::fncalculateHValue(int m_nCol, int m_nRow, pa_point m_Goal)
{
    return ((double)sqrt((m_nCol - m_Goal.first) * (m_nCol - m_Goal.first) + (m_nRow - m_Goal.second) * (m_nRow - m_Goal.second)));
}
/*** ��������ֵ h ****/
double gpath::fncalculateH_HValue(int m_nCol, int m_nRow, pa_point m_Goal, double Height)
{
    return ((double)sqrt((m_nCol - m_Goal.first) * (m_nCol - m_Goal.first) + (m_nRow - m_Goal.second) * (m_nRow - m_Goal.second)));
}

double gpath::fncalculateAValue(int m_nCol, int m_nRow, pa_point m_Goal, double Height, double Width)
{
    // considering barriers height when up off maxHeight,its value is infinite,others is a line value.
    // f(n) = Wp*(g(n)+h(n))+Wh*Ch*Cw*a(n)
    // a(n) = 10*(H_obstacle/H_fstep)
    double AnValue;
    double Wp, Wh, Ch, Cw;
    if (Height <= HeightStep && (Width >= WidthStep || Width <= 0.03))
    {
        Ch = 1;
        Cw = 1;
        AnValue = 10 * Height / HeightStep;
    }
    else
    {
        Ch = FLT_MAX;
        Cw = FLT_MAX;
        AnValue = FLT_MAX;
    }
    return AnValue;
}
/*** ��Ŀ��㵽��㽫·��ѹջ��Path�� ****/
void gpath::fntracePath(ts_cell _grid[][ROW], pa_point m_Goal)
{
    Fvalue = 0;
    int m_nCol = m_Goal.first;
    int m_nRow = m_Goal.second;
    static int pnum = 0;
    // ֻҪĳ���ڵ�ĸ��ڵ����Լ������������㣬ֹͣѭ�����������Ҳ��Ҫ���뵽Path�С�
    while (!(_grid[m_nCol][m_nRow].m_nParent_i == m_nCol && _grid[m_nCol][m_nRow].m_nParent_j == m_nRow))
    {
        pnum++;
        g_path.setGlobalPath(m_nCol, m_nRow);
        // �鿴���ڵ�
        int temp_col = _grid[m_nCol][m_nRow].m_nParent_i;
        int temp_row = _grid[m_nCol][m_nRow].m_nParent_j;
        
        m_nCol = temp_col;
        m_nRow = temp_row;

        Fvalue += _grid[m_nCol][m_nRow].m_f;
    }
    g_path.setGlobalPath(m_nCol, m_nRow);
    return;
}
/*** ������ͼ ****/
void gpath::api_AStarSearchWithHeight(ts_cell _grid[][ROW], pa_point m_Start, pa_point m_Goal)
{
    // std::cout << "In Astar search" << std::endl;
    /***** �������� *********/
    bool closedList[ROW][COL]; // ����Ѿ��������ĵ�
    std::set<papa_point> openList; // ������ڼ��������Χ�� papa_point-������ֵ
    bool foundGoal = false;
    double Wp = 1, Wh = 0;

    /***** ���ɵ�ͼ���ж�����յ�������Ч�� *****/
    gpath::fnvInitStart(_grid, m_Start, m_Goal);                                                        // ��ʼ����㣬���ڵ㣬�ڵ�����
    gpath::fncellCheckWithHeight(_grid, m_Start, m_Goal, _grid[m_Start.first][m_Start.second].m_Hight); // �������Ƿ���Ч

    memset(closedList, false, sizeof(closedList)); // �� closedList ��λΪfalse,��ʾδ��������;

    int i, j;
    i = m_Start.first;
    j = m_Start.second;
    openList.insert(std::make_pair(0.0, std::make_pair(i, j))); // ������ڼ��������Χ��
    static int test_i = 0; 
    while (!openList.empty())
    {
        test_i++;
        papa_point p = *openList.begin(); // ��openList��ȡ��������
        openList.erase(openList.begin()); // ��openList��ɾ���õ㣬׼������closeList��
        i = p.second.first;               // ����ֵ-����ֵ��x,y��
        j = p.second.second;
        closedList[i][j] = true; // ȡ���ĵ����closeList��������������ˣ�

        double gNew, hNew, fNew;
        // std::cout << "api_AStarSearchWithHeight while:" << test_i << std::endl;
        if (gpath::fnisValid(i - 1, j) == true)
        {
            if (gpath::fnisGoal(i - 1, j, m_Goal) == true)
            {
                
                _grid[i - 1][j].m_nParent_i = i;
                _grid[i - 1][j].m_nParent_j = j;
                gpath::fntracePath(_grid, m_Goal);
                foundGoal = true;
                return;
            }
            else if (closedList[i - 1][j] == false && gpath::fnisEmptyWithHeight(_grid, i - 1, j, _grid[i - 1][j].m_Hight) == true)
            {
                gNew = _grid[i][j].m_g + 1.0;
                hNew = gpath::fncalculateH_HValue(i - 1, j, m_Goal, _grid[i - 1][j].m_Hight);
                fNew = Wp * (gNew + hNew) + Wh * gpath::fncalculateAValue(i - 1, j, m_Goal, _grid[i - 1][j].m_Hight, _grid[i - 1][j].m_Width);

                if (_grid[i - 1][j].m_f == FLT_MAX || _grid[i - 1][j].m_f > fNew)
                {
                    openList.insert(std::make_pair(fNew, std::make_pair(i - 1, j)));

                    _grid[i - 1][j].m_f = fNew;
                    _grid[i - 1][j].m_g = gNew;
                    _grid[i - 1][j].m_h = hNew;
                    _grid[i - 1][j].m_nParent_i = i;
                    _grid[i - 1][j].m_nParent_j = j;
                }
            }
        }

        if (gpath::fnisValid(i + 1, j) == true)
        {
            if (gpath::fnisGoal(i + 1, j, m_Goal) == true)
            {
                _grid[i + 1][j].m_nParent_i = i;
                _grid[i + 1][j].m_nParent_j = j;

                gpath::fntracePath(_grid, m_Goal);
                foundGoal = true;
                return;
            }
            else if (closedList[i + 1][j] == false && gpath::fnisEmptyWithHeight(_grid, i + 1, j, _grid[i + 1][j].m_Hight) == true)
            {
                gNew = _grid[i][j].m_g + 1.0;
                hNew = gpath::fncalculateH_HValue(i + 1, j, m_Goal, _grid[i + 1][j].m_Hight);
                fNew = Wp * (gNew + hNew) + Wh * gpath::fncalculateAValue(i + 1, j, m_Goal, _grid[i + 1][j].m_Hight, _grid[i + 1][j].m_Width);
                if (_grid[i + 1][j].m_f == FLT_MAX ||
                    _grid[i + 1][j].m_f > fNew)
                {
                    openList.insert(std::make_pair(fNew, std::make_pair(i + 1, j)));

                    _grid[i + 1][j].m_f = fNew;
                    _grid[i + 1][j].m_g = gNew;
                    _grid[i + 1][j].m_h = hNew;
                    _grid[i + 1][j].m_nParent_i = i;
                    _grid[i + 1][j].m_nParent_j = j;
                }
            }
        }

        if (gpath::fnisValid(i, j + 1) == true)
        {

            if (gpath::fnisGoal(i, j + 1, m_Goal) == true)
            {

                _grid[i][j + 1].m_nParent_i = i;
                _grid[i][j + 1].m_nParent_j = j;

                gpath::fntracePath(_grid, m_Goal);
                foundGoal = true;
                return;
            }

            else if (closedList[i][j + 1] == false && gpath::fnisEmptyWithHeight(_grid, i, j + 1, _grid[i][j + 1].m_Hight) == true)
            {
                gNew = _grid[i][j].m_g + 1.0;
                hNew = gpath::fncalculateH_HValue(i, j + 1, m_Goal, _grid[i][j + 1].m_Hight);
                fNew = Wp * (gNew + hNew) + Wh * gpath::fncalculateAValue(i, j + 1, m_Goal, _grid[i][j + 1].m_Hight, _grid[i][j + 1].m_Width);

                if (_grid[i][j + 1].m_f == FLT_MAX ||_grid[i][j + 1].m_f > fNew)
                {
                    openList.insert(std::make_pair(fNew,std::make_pair(i, j + 1)));

                    _grid[i][j + 1].m_f = fNew;
                    _grid[i][j + 1].m_g = gNew;
                    _grid[i][j + 1].m_h = hNew;
                    _grid[i][j + 1].m_nParent_i = i;
                    _grid[i][j + 1].m_nParent_j = j;
                }
            }
        }

        if (gpath::fnisValid(i, j - 1) == true)
        {
            if (gpath::fnisGoal(i, j - 1, m_Goal) == true)
            {

                _grid[i][j - 1].m_nParent_i = i;
                _grid[i][j - 1].m_nParent_j = j;

                gpath::fntracePath(_grid, m_Goal);
                foundGoal = true;
                return;
            }

            else if (closedList[i][j - 1] == false && gpath::fnisEmptyWithHeight(_grid, i, j - 1, _grid[i][j - 1].m_Hight) == true)
            {
                gNew = _grid[i][j].m_g + 1.0;
                hNew = gpath::fncalculateH_HValue(i, j - 1, m_Goal, _grid[i][j - 1].m_Hight);
                fNew = Wp * (gNew + hNew) + Wh * gpath::fncalculateAValue(i, j - 1, m_Goal, _grid[i][j - 1].m_Hight, _grid[i][j - 1].m_Width);

                if (_grid[i][j - 1].m_f == FLT_MAX ||
                    _grid[i][j - 1].m_f > fNew)
                {
                    openList.insert(std::make_pair(fNew,
                                              std::make_pair(i, j - 1)));

                    _grid[i][j - 1].m_f = fNew;
                    _grid[i][j - 1].m_g = gNew;
                    _grid[i][j - 1].m_h = hNew;
                    _grid[i][j - 1].m_nParent_i = i;
                    _grid[i][j - 1].m_nParent_j = j;
                }
            }
        }

        if (gpath::fnisValid(i - 1, j + 1) == true)
        {
            if (gpath::fnisGoal(i - 1, j + 1, m_Goal) == true)
            {

                _grid[i - 1][j + 1].m_nParent_i = i;
                _grid[i - 1][j + 1].m_nParent_j = j;
                // printf("The m_Goalination cell is found\n");
                gpath::fntracePath(_grid, m_Goal);
                foundGoal = true;
                return;
            }

            else if (closedList[i - 1][j + 1] == false && gpath::fnisEmptyWithHeight(_grid, i - 1, j + 1, _grid[i - 1][j + 1].m_Hight) == true)
            {
                gNew = _grid[i][j].m_g + 1.414;
                hNew = gpath::fncalculateH_HValue(i - 1, j + 1, m_Goal, _grid[i - 1][j + 1].m_Hight);
                fNew = Wp * (gNew + hNew) + Wh * gpath::fncalculateAValue(i - 1, j + 1, m_Goal, _grid[i - 1][j + 1].m_Hight, _grid[i - 1][j + 1].m_Width);

                if (_grid[i - 1][j + 1].m_f == FLT_MAX ||
                    _grid[i - 1][j + 1].m_f > fNew)
                {
                    openList.insert(std::make_pair(fNew,
                                              std::make_pair(i - 1, j + 1)));
                    _grid[i - 1][j + 1].m_f = fNew;
                    _grid[i - 1][j + 1].m_g = gNew;
                    _grid[i - 1][j + 1].m_h = hNew;
                    _grid[i - 1][j + 1].m_nParent_i = i;
                    _grid[i - 1][j + 1].m_nParent_j = j;
                }
            }
        }

        if (gpath::fnisValid(i - 1, j - 1) == true)
        {

            if (gpath::fnisGoal(i - 1, j - 1, m_Goal) == true)
            {

                _grid[i - 1][j - 1].m_nParent_i = i;
                _grid[i - 1][j - 1].m_nParent_j = j;

                gpath::fntracePath(_grid, m_Goal);
                foundGoal = true;
                return;
            }

            else if (closedList[i - 1][j - 1] == false && gpath::fnisEmptyWithHeight(_grid, i - 1, j - 1, _grid[i - 1][j - 1].m_Hight) == true)
            {
                gNew = _grid[i][j].m_g + 1.414;
                hNew = gpath::fncalculateH_HValue(i - 1, j - 1, m_Goal, _grid[i - 1][j - 1].m_Hight);
                fNew = Wp * (gNew + hNew) + Wh * gpath::fncalculateAValue(i - 1, j - 1, m_Goal, _grid[i - 1][j - 1].m_Hight, _grid[i - 1][j - 1].m_Width);
                if (_grid[i - 1][j - 1].m_f == FLT_MAX ||
                    _grid[i - 1][j - 1].m_f > fNew)
                {
                    openList.insert(std::make_pair(fNew, std::make_pair(i - 1, j - 1)));

                    _grid[i - 1][j - 1].m_f = fNew;
                    _grid[i - 1][j - 1].m_g = gNew;
                    _grid[i - 1][j - 1].m_h = hNew;
                    _grid[i - 1][j - 1].m_nParent_i = i;
                    _grid[i - 1][j - 1].m_nParent_j = j;
                }
            }
        }

        if (gpath::fnisValid(i + 1, j + 1) == true)
        {

            if (gpath::fnisGoal(i + 1, j + 1, m_Goal) == true)
            {

                _grid[i + 1][j + 1].m_nParent_i = i;
                _grid[i + 1][j + 1].m_nParent_j = j;

                gpath::fntracePath(_grid, m_Goal);
                foundGoal = true;
                return;
            }

            else if (closedList[i + 1][j + 1] == false && gpath::fnisEmptyWithHeight(_grid, i + 1, j + 1, _grid[i + 1][j + 1].m_Hight) == true)
            {
                gNew = _grid[i][j].m_g + 1.414;
                hNew = gpath::fncalculateH_HValue(i + 1, j + 1, m_Goal, _grid[i + 1][j + 1].m_Hight);
                fNew = Wp * (gNew + hNew) + Wh * gpath::fncalculateAValue(i + 1, j + 1, m_Goal, _grid[i + 1][j + 11].m_Hight, _grid[i + 1][j + 1].m_Width);
                if (_grid[i + 1][j + 1].m_f == FLT_MAX ||
                    _grid[i + 1][j + 1].m_f > fNew)
                {
                    openList.insert(std::make_pair(fNew,
                                              std::make_pair(i + 1, j + 1)));
                    _grid[i + 1][j + 1].m_f = fNew;
                    _grid[i + 1][j + 1].m_g = gNew;
                    _grid[i + 1][j + 1].m_h = hNew;
                    _grid[i + 1][j + 1].m_nParent_i = i;
                    _grid[i + 1][j + 1].m_nParent_j = j;
                }
            }
        }

        if (gpath::fnisValid(i + 1, j - 1) == true)
        {

            if (gpath::fnisGoal(i + 1, j - 1, m_Goal) == true)
            {
                _grid[i + 1][j - 1].m_nParent_i = i;
                _grid[i + 1][j - 1].m_nParent_j = j;
                gpath::fntracePath(_grid, m_Goal);
                foundGoal = true;
                return;
            }

            else if (closedList[i + 1][j - 1] == false && gpath::fnisEmptyWithHeight(_grid, i + 1, j - 1, _grid[i + 1][j - 1].m_Hight) == true)
            {
                gNew = _grid[i][j].m_g + 1.414;
                hNew = gpath::fncalculateH_HValue(i + 1, j - 1, m_Goal, _grid[i + 1][j - 1].m_Hight);
                fNew = Wp * (gNew + hNew) + Wh * gpath::fncalculateAValue(i + 1, j - 1, m_Goal, _grid[i + 1][j - 1].m_Hight, _grid[i + 1][j - 1].m_Width);
                if (_grid[i + 1][j - 1].m_f == FLT_MAX ||
                    _grid[i + 1][j - 1].m_f > fNew)
                {
                    openList.insert(std::make_pair(fNew,
                                              std::make_pair(i + 1, j - 1)));
                    _grid[i + 1][j - 1].m_f = fNew;
                    _grid[i + 1][j - 1].m_g = gNew;
                    _grid[i + 1][j - 1].m_h = hNew;
                    _grid[i + 1][j - 1].m_nParent_i = i;
                    _grid[i + 1][j - 1].m_nParent_j = j;
                }
            }
        }

    }
    std::cout << "api_AStarSearchWithHeight while end" << std::endl;
    if (foundGoal == false)
        printf("Failed to find the m_Goalination Cell\n");
    return;
}
/*** ��ȡ·�� ****/
int gpath::api_PathPlaning(int _sx, int _sy, int _gx, int _gy)
{
    /** ����·�� **/
    std::cout << "api_pathplanning start" << std::endl;
    gpath::fnInitGridMap(g_grid);
    std::cout << "fnInitGridMap end" << std::endl;

    g_path.setStartandGoal(_sx,_sy,_gx,_gy);
    std::cout << "setStartandGoal end" << std::endl;

    gpath::api_AStarSearchWithHeight(g_grid, g_path.global_start, g_path.global_goal);
    std::cout << "api_AStarSearchWithHeight end" << std::endl;

    nPathNodeNum = g_path.getnPathNodeNum();
    std::cout << "|-- nPathNodeNum :" << nPathNodeNum << std::endl;
    std::cout << "|-- Start :" << g_path.global_start.first << "," << g_path.global_start.second << std::endl;
    std::cout << "|-- End   :" << g_path.global_goal.first << "," << g_path.global_goal.second << std::endl;

    for (int i = 0; i < nPathNodeNum; i++)
    {
        pa_point place = g_path.getPathPoint();
        g_path.global_path_cor[i].x = (double)place.first / 100;
        g_path.global_path_cor[i].y = (double)place.second / 100;
        g_path.global_path_cor[i].z = 0.0;
        g_path.dValuePlus += g_grid[place.first][place.second].m_f;
        g_path.delPathPoint();
    }
    for (int i = nPathNodeNum; i < MAX_ARRAY_NUM; i++) // ��ʣ��ĵ�Ҳ��λΪ����Ŀ���
    {
        g_path.global_path_cor[i].x = g_path.global_path_cor[nPathNodeNum-1].x;
        g_path.global_path_cor[i].y = g_path.global_path_cor[nPathNodeNum-1].y;
        g_path.global_path_cor[i].z = g_path.global_path_cor[nPathNodeNum-1].z;
    }
    std::cout << "api_pathplanning end" <<std::endl;
    return 0;
}
/*** ��ȡ·�� ������ ****/
tc_path &gpath::api_PathPlaningReturn(int _sx, int _sy, int _gx, int _gy)
{
    /** ����·�� **/
    // std::cout << "api_pathplanning" << std::endl;
    gpath::fnInitGridMap(g_grid);
    // std::cout << "fnInitGridMap end" << std::endl;

    g_path.setStartandGoal(_sx, _sy, _gx, _gy);
    // std::cout << "setStartandGoal end" << std::endl;

    gpath::api_AStarSearchWithHeight(g_grid, g_path.global_start, g_path.global_goal);
    // std::cout << "api_AStarSearchWithHeight end" << std::endl;

    nPathNodeNum = g_path.getnPathNodeNum();
    g_path.getnPathNodeNum();
    std::cout << "|-- api_PathPlaningReturn nPathNodeNum :" << nPathNodeNum << std::endl;
    // std::cout << "|-- Start :" << g_path.global_start.first << "," << g_path.global_start.second << std::endl;
    // std::cout << "|-- End   :" << g_path.global_goal.first << "," << g_path.global_goal.second << std::endl;

    for (int i = 0; i < nPathNodeNum; i++)
    {
        pa_point place = g_path.getPathPoint();
        g_path.global_path_cor[i].x = (double)place.first / 100;
        g_path.global_path_cor[i].y = (double)place.second / 100;
        g_path.global_path_cor[i].z = 0.0;
        g_path.dValuePlus += g_grid[place.first][place.second].m_f;
        g_path.delPathPoint();
    }
    for (int i = nPathNodeNum; i < MAX_ARRAY_NUM; i++) // ��ʣ��ĵ�Ҳ��λΪ����Ŀ���
    {
        g_path.global_path_cor[i].x = g_path.global_path_cor[nPathNodeNum - 1].x;
        g_path.global_path_cor[i].y = g_path.global_path_cor[nPathNodeNum - 1].y;
        g_path.global_path_cor[i].z = g_path.global_path_cor[nPathNodeNum - 1].z;
    }
    std::cout << "api_PathPlaningReturn end" << std::endl;
    return g_path;
}
//*** ���ݱ��� *** /
/*
    ���ܣ��������ɵ�ȫ��·��������㣬��ŵ�
    �ļ���pathnode.dat
    ע�⣺���ɵ�·����PATH_NODE_NUM������������ŵ�CAPTURE_PATH_NUM������PATH_NODE_NUM�������ı�0���룬ʹ��ʱע��
*/
void gpath::gfnvSaveData()
{
    // printf("start save data %d\n", nPathNodeNum);
    FILE *path_node;
    // path_node = fopen("F:/LD/ProgramCode/BHR/NewRobot/GPF/GPathAndFoot_1.1.1/pathnode.dat", "wb");
    path_node = fopen("../../Gpathnode.dat", "wb");

    fprintf(path_node, "%s %s %s ", "path_x", "path_y", "path_z");
    // fprintf(path_node, "%s %s %s %s ", "capture_x", "capture_y", "capture_z", "capture_theta");
    // fprintf(path_node, "%s %s %s %s\n", "foot_x", "foot_y", "foot_z", "foot_theta");

    for (int i = 0; i < nPathNodeNum; i++)
    {
        fprintf(path_node, "%lf %lf %lf\n", g_path.global_path_cor[i].x, g_path.global_path_cor[i].y, g_path.global_path_cor[i].z);
        // fprintf(path_node, "%lf %lf %lf %lf ", gaosdCapurePath[i][0], gaosdCapurePath[i][1], gaosdCapurePath[i][2], gaosdCapurePath[i][3]);
        // fprintf(path_node, "%lf %lf %lf %lf\n", gaosdfoot[i][0], gaosdfoot[i][1], gaosdfoot[i][2], gaosdfoot[i][3]);
    }
    fclose(path_node);
    printf("end save path data !!!\n");
}

