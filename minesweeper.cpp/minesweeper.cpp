#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include<Windows.h>

#define ROW_MAX 100//地图初始化
#define COL_MAX 100
#define SIZE 39 //每个格子大小
IMAGE img[31];

void GameInit1(int ROW, int COL, int num, char map[][COL_MAX], char upmap[][COL_MAX]) // 地图初始化
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < ROW + 2; i++) // 初始化游戏区和辅助区
    {
        for (int j = 0; j < COL + 2; j++)
        {
            map[i][j] = '0';
            upmap[i][j] = '0';
        }
    }
    int n = 0;
    while (n < num) // 添加地雷
    {
        int r = rand() % ROW + 1;
        int c = rand() % COL + 1;
        if (map[r][c] != '*')
        {
            map[r][c] = '*';
            n++;
        }
    }
    // 补充数字
    for (int i = 1; i <= ROW; i++) // 遍历雷区
    {
        for (int j = 1; j <= COL; j++)
        {
            upmap[i][j] = '.';
            if (map[i][j] != '*') // 找到非雷区
            {
                for (int m = i - 1; m <= i + 1; m++)
                {
                    for (int n = j - 1; n <= j + 1; n++)
                    {
                        if (map[m][n] == '*')
                        {
                            map[i][j]++; // 打上数字标记
                        }
                    }
                }
            }
        }
    }
}

void GameInit2(int x, int y, int ROW, int COL, int num, char map[][COL_MAX], char upmap[][COL_MAX]) // 重生地图初始化
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < ROW + 2; i++) // 初始化游戏区和辅助区
    {
        for (int j = 0; j < COL + 2; j++)
        {
            map[i][j] = '0';
            upmap[i][j] = '0';
        }
    }
    int n = 0;
    while (n < num) // 添加地雷
    {
        int r = rand() % ROW + 1;
        int c = rand() % COL + 1;
        if (map[r][c] != '*'&&r!=x&&c!=y)
        {
            map[r][c] = '*';
            n++;
        }
    }
    // 补充数字
    for (int i = 1; i <= ROW; i++) // 遍历雷区
    {
        for (int j = 1; j <= COL; j++)
        {
            upmap[i][j] = '.';
            if (map[i][j] != '*') // 找到非雷区
            {
                for (int m = i - 1; m <= i + 1; m++)
                {
                    for (int n = j - 1; n <= j + 1; n++)
                    {
                        if (map[m][n] == '*')
                        {
                            map[i][j]++; // 打上数字标记
                        }
                    }
                }
            }
        }
    }
}

void PrintMap(int bom0, int bom1, int bom2, int bom3, int time0, int time1, int time2, int time3, int ROW, int COL, char map[][COL_MAX]) // 打印内地图
{
    for (int i = 1; i <= ROW; i++)
    {
        for (int j = 1; j <= COL; j++)
        {
            //printf("%c", map[i][j]);
            if (map[i][j] >= '0' && map[i][j] <= '8')
            {
                putimage((j - 1) * SIZE, i * SIZE, &img[map[i][j] - 48]);
            }
            else if (map[i][j] == '*')
            {
                putimage((j - 1) * SIZE, i * SIZE, &img[9]);
            }
            /*if (j == COL)
            {
                printf("\n");
            }*/
        }
    }
    for (int i = 0; i < COL; i++)
    {
        putimage(i * SIZE, 0, &img[14]);
    }
    //输出计数器和计时器
    putimage(0, 0, &img[14]);
    putimage(SIZE * COL - 100, 1, &img[time0 + 15]);
    putimage(SIZE * COL - 80, 1, &img[time1 + 15]);
    putimage(SIZE * COL - 60, 1, &img[27]);
    putimage(SIZE * COL - 50, 1, &img[time2 + 15]);
    putimage(SIZE * COL - 30, 1, &img[time3 + 15]);
    if (bom1 < 0)//雷数出现负数
    {
        putimage(105, 1, &img[bom0 + 15]);
        putimage(125, 1, &img[bom1 + 15]);
        putimage(145, 1, &img[bom2 + 15]);
        putimage(165, 1, &img[-1 * bom3 + 15]);
    }
    else
    {
        putimage(105, 1, &img[bom0 + 15]);
        putimage(125, 1, &img[bom1 + 15]);
        putimage(145, 1, &img[bom2 + 15]);
        putimage(165, 1, &img[bom3 + 15]);
    }
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, L"微软雅黑");
    settextcolor(BLACK);
    outtextxy(SIZE * COL - 155, 5, L"时间:");
    outtextxy(5, 5, L"剩余雷数:");
}

void PrintUpmap(int bom0, int bom1, int bom2, int bom3, int time0, int time1, int time2, int time3, int ROW, int COL, char upmap[][COL_MAX]) // 打印外地图
{
    for (int i = 1; i <= ROW; i++)
    {
        for (int j = 1; j <= COL; j++)
        {
            //printf("%c", upmap[i][j]);
            if (upmap[i][j] == '.')
            {
                putimage((j - 1) * SIZE, i * SIZE, &img[12]);
            }
            else if(upmap[i][j]>='0'&&upmap[i][j]<='8')
            {
                putimage((j - 1) * SIZE, i * SIZE, &img[upmap[i][j]-48]);
            }
            else if (upmap[i][j]=='!')
            {
                putimage((j - 1) * SIZE, i * SIZE, &img[10]);
            }
            else if (upmap[i][j] == '?')
            {
                putimage((j - 1) * SIZE, i * SIZE, &img[11]);
            }
            /*if (j == COL)
            {
                printf("\n");
            }*/
        }
    }
    for (int i = 0; i < COL; i++)
    {
        putimage(i*SIZE, 0, &img[14]);
    }
    //输出计数器和计时器
    putimage(0, 0, &img[14]);
    putimage(SIZE * COL - 100, 1, &img[time0 + 15]);
    putimage(SIZE * COL - 80, 1, &img[time1 + 15]);
    putimage(SIZE * COL - 60, 1, &img[27]);
    putimage(SIZE * COL - 50, 1, &img[time2 + 15]);
    putimage(SIZE * COL - 30, 1, &img[time3 + 15]);
    if (bom1 < 0)//雷数出现负数
    {
        putimage(105, 1, &img[bom0 + 15]);
        putimage(125, 1, &img[bom1 + 15]);
        putimage(145, 1, &img[bom2 + 15]);
        putimage(165, 1, &img[-1 * bom3 + 15]);
    }
    else
    {
        putimage(105, 1, &img[bom0 + 15]);
        putimage(125, 1, &img[bom1 + 15]);
        putimage(145, 1, &img[bom2 + 15]);
        putimage(165, 1, &img[bom3 + 15]);
    }
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, L"微软雅黑");
    settextcolor(BLACK);
    outtextxy(SIZE * COL - 155, 5, L"时间:");
    outtextxy(5, 5, L"剩余雷数:");
}

void PrintLosemap(int bom0, int bom1, int bom2, int bom3, int time0, int time1, int time2, int time3, int ROW, int COL, char map[][COL_MAX], char upmap[][COL_MAX]) // 打印失败地图
{
    for (int i = 1; i <= ROW; i++)
    {
        for (int j = 1; j <= COL; j++)
        {
            if (map[i][j] == '*')
            {
                upmap[i][j] = map[i][j];
                //printf("%c", upmap[i][j]);
                putimage((j - 1) * SIZE, i * SIZE, &img[9]);
            }
            else if (map[i][j] == '$')
            {
                upmap[i][j] = map[i][j];
                //printf("%c", upmap[i][j]);
                putimage((j - 1) * SIZE, i * SIZE, &img[13]);
            }
            else if (map[i][j] == '^')
            {
                upmap[i][j] = map[i][j];
                putimage((j - 1) * SIZE, i * SIZE, &img[26]);
            }
            else
            {
                //printf("%c", upmap[i][j]);
                if (upmap[i][j] == '.')
                {
                    putimage((j - 1) * SIZE, i * SIZE, &img[12]);
                }
                else if (upmap[i][j] >= '0' && upmap[i][j] <= '8')
                {
                    putimage((j - 1) * SIZE, i * SIZE, &img[upmap[i][j] - 48]);
                }
                else if (upmap[i][j] == '!')
                {
                    putimage((j - 1) * SIZE, i * SIZE, &img[10]);
                }
                else if (upmap[i][j] == '?')
                {
                    putimage((j - 1) * SIZE, i * SIZE, &img[11]);
                }
            }
            /*if (j == COL)
            {
                printf("\n");
            }*/
        }
    }
    for (int i = 0; i < COL; i++)
    {
        putimage(i * SIZE, 0, &img[14]);
    }
    //输出计数器和计时器
    putimage(0, 0, &img[14]);
    putimage(SIZE * COL - 100, 1, &img[time0 + 15]);
    putimage(SIZE * COL - 80, 1, &img[time1 + 15]);
    putimage(SIZE * COL - 60, 1, &img[27]);
    putimage(SIZE * COL - 50, 1, &img[time2 + 15]);
    putimage(SIZE * COL - 30, 1, &img[time3 + 15]);
    if (bom1 < 0)//雷数出现负数
    {
        putimage(105, 1, &img[bom0 + 15]);
        putimage(125, 1, &img[bom1 + 15]);
        putimage(145, 1, &img[bom2 + 15]);
        putimage(165, 1, &img[-1 * bom3 + 15]);
    }
    else
    {
        putimage(105, 1, &img[bom0 + 15]);
        putimage(125, 1, &img[bom1 + 15]);
        putimage(145, 1, &img[bom2 + 15]);
        putimage(165, 1, &img[bom3 + 15]);
    }
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, L"微软雅黑");
    settextcolor(BLACK);
    outtextxy(SIZE * COL - 155, 5, L"时间:");
    outtextxy(5, 5, L"剩余雷数:");
}

void OpenZero(int* count, int x, int y, int ROW, int COL, char map[][COL_MAX], char upmap[][COL_MAX], int visited[][COL_MAX]) // 0的爆炸展开
{
    if (visited[x][y] == 1 || (upmap[x][y] != '.' && upmap[x][y] != '?')) // 已经展开过的格子或非展开状态的格子，不进行递归展开
    {
        return;
    }
    visited[x][y] = 1;
    upmap[x][y] = map[x][y];
    (*count)++;

    if (map[x][y] == '0')
    {
        for (int m = x - 1; m <= x + 1; m++)
        {
            for (int n = y - 1; n <= y + 1; n++)
            {
                if (m >= 1 && m <= ROW && n >= 1 && n <= COL)
                {
                    OpenZero(count, m, n, ROW, COL, map, upmap, visited);
                }
            }
        }
    }
}

void DouClick(int* count, int x, int y, int ROW, int COL, char map[][COL_MAX], char upmap[][COL_MAX]) // 实现双击操作
{
    int k = 0;
    for (int m = x - 1; m <= x + 1; m++)
    {
        for (int n = y - 1; n <= y + 1; n++)
        {
            if (m >= 1 && m <= ROW && n >= 1 && n <= COL)
            {
                if (map[m][n] == '*' && upmap[m][n] == '!') // 判断雷是否被标记
                {
                    k++;
                }
                else if (map[m][n] != '*' && upmap[m][n] == '!')
                {
                    upmap[0][0] = '@';
                    map[m][n] = '^';
                    k += 20;
                    break;
                }
            }
        }
    }
    if (map[x][y] == k + 48) // 符合双击打开的情况
    {
        for (int m = x - 1; m <= x + 1; m++)
        {
            for (int n = y - 1; n <= y + 1; n++)
            {
                if (m >= 1 && m <= ROW && n >= 1 && n <= COL)
                {
                    if (map[m][n] >= '0' && map[m][n] <= '8' && (upmap[m][n] == '.' || upmap[m][n] == '?'))
                    {
                        if (map[m][n] == '0')
                        {
                            int visited[ROW_MAX][COL_MAX] = { 0 };
                            OpenZero(count, m, n, ROW, COL, map, upmap, visited);
                        }
                        else
                        {
                            upmap[m][n] = map[m][n];
                            (*count)++;
                        }
                    }
                }
            }
        }
    }
}

void PlayGame(int* m,int* f,int* count, int* step, int* mineCount, int ROW, int COL, char map[][COL_MAX], char upmap[][COL_MAX])
{
    int x, y;
    MOUSEMSG msg ;
    while (1)//检测是否有鼠标消息，防止计时“暂停”
    {
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) // 左键
            {
                y = msg.x / SIZE + 1;
                x = msg.y / SIZE;
                msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONUP)//单击
                {
                    *step += 1;
                    if (x < 1 || y < 1)
                    {
                        *step -= 1;
                    }
                    if (map[x][y] == '*' && upmap[x][y] != '!') // 点到雷
                    {
                        if (*step == 1)//新手保护机制
                        {
                            GameInit2(x, y, ROW, COL, *mineCount, map, upmap);
                        }
                        else
                        {
                            map[x][y] = '$';
                            upmap[0][0] = '@';
                        }
                    }
                    if (map[x][y] >= '0' && map[x][y] <= '8' && (upmap[x][y] == '.' || upmap[x][y] == '?') && upmap[x][y] != '!')
                    {
                        if (map[x][y] == '0') // 点到0
                        {
                            int visited[ROW_MAX][COL_MAX] = { 0 };
                            OpenZero(count, x, y, ROW, COL, map, upmap, visited);
                        }
                        else
                        {
                            upmap[x][y] = map[x][y];
                            (*count)++;
                        }
                    }

                }
                else if (msg.uMsg == WM_RBUTTONDOWN)//双击
                {
                    *step += 1;
                    if (x < 1 || y < 1)
                    {
                        *step -= 1;
                    }
                    if (upmap[x][y] >= '1' && upmap[x][y] <= '8')
                    {
                        DouClick(count, x, y, ROW, COL, map, upmap);
                    }
                }
            }
            else if (msg.uMsg == WM_RBUTTONDOWN) // 右标雷
            {
                y = msg.x / SIZE + 1;
                x = msg.y / SIZE;
                *step += 1;
                if (x < 1 || y < 1)
                {
                    *step -= 1;
                }
                y = msg.x / SIZE + 1;
                x = msg.y / SIZE;
                if (upmap[x][y] == '.')
                {
                    *mineCount -= 1;
                    upmap[x][y] = '!';
                }
                else if (upmap[x][y] == '!')
                {
                    *mineCount += 1;
                    upmap[x][y] = '?';
                }
                else if (upmap[x][y] == '?')
                {
                    upmap[x][y] = '.';
                }
            }
        }
        else
        {
            break;
        }
    }
    
}


int main()
{
    
    // 0-8为数字，9为雷，10为旗子，11为问号，12为空格
    loadimage(&img[0], L"./0.jpg", SIZE, SIZE);
    loadimage(&img[1], L"./1.jpg", SIZE, SIZE);
    loadimage(&img[2], L"./2.jpg", SIZE, SIZE);
    loadimage(&img[3], L"./3.jpg", SIZE, SIZE);
    loadimage(&img[4], L"./4.jpg", SIZE, SIZE);
    loadimage(&img[5], L"./5.jpg", SIZE, SIZE);
    loadimage(&img[6], L"./6.jpg", SIZE, SIZE);
    loadimage(&img[7], L"./7.jpg", SIZE, SIZE);
    loadimage(&img[8], L"./8.jpg", SIZE, SIZE);
    loadimage(&img[9], L"./9.jpg", SIZE, SIZE);
    loadimage(&img[10], L"./10.jpg", SIZE, SIZE);
    loadimage(&img[11], L"./11.jpg", SIZE, SIZE);
    loadimage(&img[12], L"./12.jpg", SIZE, SIZE);
    loadimage(&img[13], L"./13.jpg", SIZE, SIZE);
    loadimage(&img[14], L"./33.jpg", SIZE, SIZE);
    //数字展示
    loadimage(&img[15], L"./20.jpg", 20, 35);//0
    loadimage(&img[16], L"./21.jpg", 20, 35);//1
    loadimage(&img[17], L"./22.jpg", 20, 35);
    loadimage(&img[18], L"./23.jpg", 20, 35);
    loadimage(&img[19], L"./24.jpg", 20, 35);
    loadimage(&img[20], L"./25.jpg", 20, 35);
    loadimage(&img[21], L"./26.jpg", 20, 35);
    loadimage(&img[22], L"./27.jpg", 20, 35);
    loadimage(&img[23], L"./28.jpg", 20, 35);
    loadimage(&img[24], L"./29.jpg", 20, 35);
    loadimage(&img[25], L"./30.jpg", 20, 35);
    loadimage(&img[26], L"./31.jpg", SIZE, SIZE);
    loadimage(&img[27], L"./32.jpg", 10, 35);//：
    int page = 0;
    B://重新开始
    int step = 0, count = 0,m=0,f=0,start,end,time0=0,time1=0,time2=0,time3=0,bom0=0,bom1=0,bom2=0,bom3=0,isok;
    char upmap[ROW_MAX][COL_MAX];
    char map[ROW_MAX][COL_MAX]; // 根据游戏规则，最大为24*30，可以把最大值都设置为100
    int row = 0, col = 0, mineCount = 0;
    wchar_t s[10];
    //加载游戏封面
    loadimage(&img[28], L"./34.jpg", 800, 440);
    loadimage(&img[29], L"./35.jpg", 800, 440);
    loadimage(&img[30], L"./36.jpg", 800, 440);
    HWND hwnd1 = initgraph(800, 440, 0);//游戏封面
    SetWindowPos(hwnd1, HWND_TOP, 450, 250, 0, 0, SWP_NOSIZE);//设置游戏窗口出现位置
    if (page == 0)
    {
        putimage(0, 0, &img[28]);
    }
    else
    {
        putimage(0, 0, &img[29]);
    }
    while (page == 0)
    {

        int x, y;
        MOUSEMSG msg;
        while (1)//检测是否有鼠标消息
        {

            if (MouseHit())
            {
                msg = GetMouseMsg();
                x = msg.x;
                y = msg.y;
                if (msg.uMsg == WM_LBUTTONDOWN && x >= 303 && y >= 152 && x <= 488 && y <= 330)
                {
                    putimage(0, 0, &img[29]);
                    page = 1;
                }
            }
            else
            {
                break;
            }

        }

    }
    A://返回按键
    while (page == 1)
    {
        int x, y;
        MOUSEMSG msg;
        while (1)//检测是否有鼠标消息
        {

            if (MouseHit())
            {
                msg = GetMouseMsg();
                x = msg.x;
                y = msg.y;
                if (msg.uMsg == WM_LBUTTONDOWN && x >= 297 && x <= 478)
                {
                    if (y >= 115 && y <= 174)
                    {
                        row = 9;
                        col = 9;
                        mineCount = 10;
                        page = 2;
                    }
                    if (y >= 198 && y <= 256)
                    {
                        row = 16;
                        col = 16;
                        mineCount = 40;
                        page = 2;
                    }
                    if (y >= 280 && y <= 337)
                    {
                        row = 16;
                        col = 30;
                        mineCount = 99;
                        page = 2;
                    }
                    if (y >= 362 && y <= 420)
                    {
                        putimage(0, 0, &img[30]);
                        page = 3;
                    }

                }
            }
            else
            {
                break;
            }

        }
    }
    while (page == 3)
    {
        int x, y;
        MOUSEMSG msg;
        while (1)//检测是否有鼠标消息
        {

            if (MouseHit())
            {
                msg = GetMouseMsg();
                x = msg.x;
                y = msg.y;
                if (msg.uMsg == WM_LBUTTONDOWN && x >= 304 && x <= 461)
                {
                    if (y >= 97 && y <= 148)//行
                    {
                        InputBox(s, 10, L"请输入行数");
                        row = _wtoi(s);//转为整型
                        if (row > 24)
                        {
                            MessageBox(hwnd1, L"行数不宜大于24行，请重新设置！", L"错误提示", MB_OK);
                            row = 0;
                        }
                    }
                    if (y >= 166 && y <= 216)//列
                    {
                        InputBox(s, 10, L"请输入列数");
                        col = _wtoi(s);
                        if (col > 30)
                        {
                            MessageBox(hwnd1, L"列数不宜大于30列，请重新设置！", L"错误提示", MB_OK);
                            col = 0;
                        }
                    }
                    if (y >= 237 && y <= 287)//雷
                    {
                        InputBox(s, 10, L"请输入地雷数");
                        mineCount = _wtoi(s);
                    }
                    if (y >= 305 && y <= 355)//开始
                    {
                        if (row > 0 && col > 0 && mineCount > 0)
                        {
                            if (mineCount <= row * col * 0.25)
                            {
                                page = 4;
                            }
                            else
                            {
                                MessageBox(hwnd1, L"雷数不应大于总格数的25%，否则，你将无法取胜，请重新设置！", L"错误提示", MB_OK);
                            }
                        }
                        else
                        {
                            MessageBox(hwnd1, L"参数未设置完全，或者设置有误，请重新设置！", L"错误提示", MB_OK);
                        }
                    }
                    if (y >= 373 && y <= 424)//返回
                    {
                        putimage(0, 0, &img[29]);
                        row = 0;
                        col = 0;
                        mineCount = 0;
                        page = 1;
                        goto A;
                    }

                }
            }
            else
            {
                break;
            }

        }
    }
    //closegraph();
    int MineCount = mineCount;
    bom1 = mineCount / 100;//取百位
    bom2 = mineCount / 10 % 10;//取十位
    bom3 = mineCount % 10;//取个位
    GameInit1(row, col, mineCount, map, upmap);
    //PrintMap(bom1, bom2, bom3, time1, time2, time3, row, col, map);

    HWND hwnd2 = initgraph(col * SIZE, (row+1)* SIZE, 0);
    SetWindowPos(hwnd2, HWND_TOP, 350, 10, 0, 0, SWP_NOSIZE);//设置游戏窗口出现位置

    PrintUpmap(bom0, bom1, bom2, bom3, time0, time1, time2, time3, row, col, upmap);
    start = clock();//开始计时
    while (1)//开始游戏
    {
        int kind = 0;
        if (step >= 0 && row * col != MineCount + count && upmap[0][0] != '@') // 继续
        {
            //printf("Game in progress\n");
            //printf("%d %d\n", step, mineCount);
            //PrintMap(row, col, map);
            //printf("\n");

            end = clock();
            int q = (end - start) / 1000;//取秒
            time0 = q / 600 % 10;
            time1 = q / 60 % 10;//取百位
            time2 = q / 10 % 6;//取十位
            time3 = q % 10;//取个位
            if (mineCount >= 0)
            {
                bom0 = mineCount / 1000;
                bom1 = mineCount / 100;//取百位
                bom2 = mineCount / 10 % 10;//取十位
                bom3 = mineCount % 10;//取个位
            }
            else
            {
                bom0 = 10;
                bom1 = ( mineCount * (-1)) / 100;
                bom2 = ( mineCount * (-1)) / 10 % 10;//取十位
                bom3 = ( mineCount * (-1)) % 10;//取个位
            }
            BeginBatchDraw();//双缓存技术处理闪屏
            PrintUpmap(bom0,bom1, bom2, bom3, time0, time1, time2, time3, row, col, upmap); // 打印外地图
            EndBatchDraw();
        }
        if (step >= 1 && row * col == MineCount + count) // 胜利
        {
            //printf("Game over, you win\n");
            //printf("%d %d\n", step, mineCount);
            while (1)
            {
                PrintMap(bom0, bom1, bom2, bom3, time0, time1, time2, time3, row, col, map); // 打印内地图
                MessageBox(hwnd2, L"你赢了，不愧是BYR！", L"胜利提示", MB_OK);
                isok = MessageBox(hwnd2, L"是否重玩", L"提示", MB_OKCANCEL);
                break;
            }
            break;
        }
        
        if (upmap[0][0] == '@') // 失败
        {
            //printf("Hit mine, you lose\n");
            //printf("%d %d\n", step, mineCount);
            while (1)
            {
                PrintLosemap(bom0, bom1, bom2, bom3, time0, time1, time2, time3, row, col, map, upmap);
                MessageBox(hwnd2, L"你输了哥们，注意点哈！", L"失败提示", MB_OK);
                isok = MessageBox(hwnd2, L"是否重玩", L"提示", MB_OKCANCEL);
                break;
            }
            break;
        }
        else
        {
            PlayGame(&m,&f,&count, &step, &mineCount, row, col, map, upmap);
        }
    }
    closegraph();
    if (isok==IDOK)
    {
        page = 1;
        goto B;
    }
    return 0;
}
