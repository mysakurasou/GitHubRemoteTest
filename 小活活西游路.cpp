#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

/*
	A��С���
	T: �ơ�ɮ
	W: �򡡿�
	Y: ������  [��ǰ����+1]
	X: ������
	P: ������
	���֣�     [��ǰ����+����-'0']

	��һ����Ҫ�ķ�һ��ʱ��
*/

const int maxn = 150;
const int maxm = 150;
const int maxs = 1<<2;            // 3��״̬

int dir[] = {0,-1,0,1,0};         // ����

int sx,sy;                        // С���λ��[��ʼλ��]
int ex,ey;                        // ����λ��[����λ��]
int result;                       // ���ٽ���

int n,m;
char map[maxn][maxm+1];           // ��ͼ
int d[maxs][maxn][maxm];          // 0 ����һ���ˣ�1����һ����+��ɮ��2����һ����+��գ�3������ɮ�����
struct Node
{
    Node() {}
    Node(int ss,int xx,int yy)
    {
        s = ss , x = xx , y =yy;
    }
    int s,x,y;
} a,b;
queue<Node>q;   // ����

void init()
{
    result = -1;
    // ====================== ��ʼ������ =================================
    memset(d,-1,sizeof d);
    // ===================== �ҳ�С���λ�ú;���λ�� ====================
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
    // ==================== ��ʼ����ʼλ�� ==============================
    d[0][sx][sy] = 0;
    // ==================== ��ʼ������ ==================================
    while(!q.empty()) q.pop();
    // ========================= ���뿪ʼλ�� ===========================
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

            // ������Χ
            if(b.x < 0 || b.y < 0 || b.x >= n || b.y >= m) continue;

            // ����
            if(map[b.x][b.y] == 'P') continue;

            // �¸�λ����������ʱ��
            if(map[b.x][b.y] == 'X' && (d[b.s][b.x][b.y] == -1 || d[b.s][b.x][b.y] > d[a.s][a.x][a.y] ) )
            {
                d[b.s][b.x][b.y] = d[a.s][a.x][a.y]; // ȡ����
                continue;
            }

            int add = 0;

            // �¸�λ������ɮ�Ļ�
            if(map[b.x][b.y] == 'T')
            {
                b.s = a.s | 1;
            }

            // �¸�λ������յĻ�,�Ҵ�����ɮ��ʱ��
            if(map[b.x][b.y] == 'W' && (b.s & 1) == 1)
            {
                // ������ɮ��ʱ�򣬿����ո����
                b.s = a.s | 2;
            }

            // �¸�λ�������ֵ�ʱ��
            if(map[b.x][b.y] == 'Y')
            {
                // ��������ղ��ܽ���
                if( (b.s & 2) != 2) continue;;
                add = 1;
            }

            // ��ͨ���ֵ�ʱ��
            if(map[b.x][b.y] >= '0' && map[b.x][b.y] <= '9')
            {
                add = map[b.x][b.y] - 48;
            }

            if(d[b.s][b.x][b.y] == -1 || d[b.s][b.x][b.y] > d[a.s][a.x][a.y] + add)
            {
                d[b.s][b.x][b.y] = d[a.s][a.x][a.y] + add;
                q.push(Node(b.s,b.x,b.y));// ѹ�����
            }
        }
    }
}

int main()
{
    while(~scanf("%d %d",&n,&m))
    {
        for(int i=0; i<n; i++)  scanf("%s",map[i]); // �����ͼ

        init(); // ��ʼ��

        bfs(); // ����

        // ����3��״̬
        for(int i=0; i<4; i++)
        {
            // ��ǰ״̬û��ȡ��
            if(d[i][ex][ey] == -1) continue;

            if(result == -1 || d[i][ex][ey] < result)
            {
                result = d[i][ex][ey];
            }
        }

        // ������
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


