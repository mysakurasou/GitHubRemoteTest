#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

/*
	A：小活活
	T: 唐　僧
	W: 悟　空
	Y: 妖　怪  [当前劫难+1]
	X: 西　经
	P: 禁　地
	数字：     [当前劫难+数字-'0']

	走一步需要耗费一天时间
*/

const int maxn = 150;
const int maxm = 150;
const int maxs = 1<<2;            // 3个状态

int dir[] = {0,-1,0,1,0};         // 方向

int sx,sy;                        // 小活活位置[开始位置]
int ex,ey;                        // 经书位置[结束位置]
int result;                       // 最少劫难

int n,m;
char map[maxn][maxm+1];           // 地图
int d[maxs][maxn][maxm];          // 0 代表一个人，1代表一个人+唐僧，2代表一个人+悟空，3代表唐僧和悟空
struct Node
{
    Node() {}
    Node(int ss,int xx,int yy)
    {
        s = ss , x = xx , y =yy;
    }
    int s,x,y;
} a,b;
queue<Node>q;   // 队列

void init()
{
    result = -1;
    // ====================== 初始化数组 =================================
    memset(d,-1,sizeof d);
    // ===================== 找出小活活位置和经书位置 ====================
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(map[i][j] == 'A')  sx = i,sy = j;
            if(map[i][j] == 'X')  ex = i,ey = j;
        }
    }
}

void bfs()
{
    // ==================== 初始化起始位置 ==============================
    d[0][sx][sy] = 0;
    // ==================== 初始化队列 ==================================
    while(!q.empty()) q.pop();
    // ========================= 插入开始位置 ===========================
    q.push(Node(0,sx,sy));

    while(!q.empty())
    {
        a = q.front();
        q.pop();

        for(int i=0; i<4; i++)
        {
            b.s = a.s;
            b.x = a.x + dir[i];
            b.y = a.y + dir[i+1];

            // 超出范围
            if(b.x < 0 || b.y < 0 || b.x >= n || b.y >= m) continue;

            // 禁地
            if(map[b.x][b.y] == 'P') continue;

            // 下个位置是西经的时候
            if(map[b.x][b.y] == 'X' && (d[b.s][b.x][b.y] == -1 || d[b.s][b.x][b.y] > d[a.s][a.x][a.y] ) )
            {
                d[b.s][b.x][b.y] = d[a.s][a.x][a.y]; // 取最少
                continue;
            }

            int add = 0;

            // 下个位置是唐僧的话
            if(map[b.x][b.y] == 'T')
            {
                b.s = a.s | 1;
            }

            // 下个位置是悟空的话,且存在唐僧的时候
            if(map[b.x][b.y] == 'W' && (b.s & 1) == 1)
            {
                // 存在唐僧的时候，可以收复悟空
                b.s = a.s | 2;
            }

            // 下个位置是妖怪的时候
            if(map[b.x][b.y] == 'Y')
            {
                // 不存在悟空不能进入
                if( (b.s & 2) != 2) continue;;
                add = 1;
            }

            // 普通数字的时候
            if(map[b.x][b.y] >= '0' && map[b.x][b.y] <= '9')
            {
                add = map[b.x][b.y] - 48;
            }

            if(d[b.s][b.x][b.y] == -1 || d[b.s][b.x][b.y] > d[a.s][a.x][a.y] + add)
            {
                d[b.s][b.x][b.y] = d[a.s][a.x][a.y] + add;
                q.push(Node(b.s,b.x,b.y));// 压入队列
            }
        }
    }
}

int main()
{
    while(~scanf("%d %d",&n,&m))
    {
        for(int i=0; i<n; i++)  scanf("%s",map[i]); // 输入地图

        init(); // 初始化

        bfs(); // 搜索

        // 检索3层状态
        for(int i=0; i<4; i++)
        {
            // 当前状态没有取到
            if(d[i][ex][ey] == -1) continue;

            if(result == -1 || d[i][ex][ey] < result)
            {
                result = d[i][ex][ey];
            }
        }

        // 输出结果
        if(result == -1)
        {
            puts("Dream, SAO!");
        }
        else
        {
            printf("%d\n",result);
        }
    }
    return 0;
}


