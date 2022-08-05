#include<algorithm>
#include<iostream>
#include<cstring>
#include<stdio.h>
#include<math.h>
#include<string>
#include<stdio.h>
#include<queue>
#include<stack>
#include<map>
#include<deque>
using namespace std;

struct edge//保存边的情况，to为通往的边，不需要保存from
{
    int to;
    int v;
    friend bool operator<(const edge& x, const edge& y)//优先队列即最小堆
    {
        return x.v > y.v;
    }
};

priority_queue<edge>q;
int vis[105];//判断是否标记数组
int p[105][105];//存图
int n;
int main()
{
    int i, j, s, key;
    edge now;
    while (scanf("%d", &n) != EOF)
    {
        for (i = 0; i < n; i++)
        {
            vis[i] = 0;//初始化一下
            for (j = 0; j < n; j++)
            {
                scanf("%d", &p[i][j]);
            }
        }
        s = 0;
        vis[0] = 1;//标记起始点
        key = 0;//随便找起始点
        while (!q.empty())q.pop();
        for (i = 0; i < n - 1; i++)//n-1次
        {
            for (j = 0; j < n; j++)//记入新加入点的情况
            {
                if (!vis[j])//没标记过的点就加入全家桶套餐
                {
                    now.to = j;
                    now.v = p[key][j];
                    q.push(now);
                }
            }
            while (!q.empty() && vis[q.top().to])//最小边但是标记过就放弃
            {
                q.pop();
            }
            if (q.empty())
                break;
            now = q.top();
            key = now.to;
            s += now.v;//累加最小边的和
            vis[key] = 1;
            q.pop();
        }
        printf("%d\n", s);
    }
    return 0;
}