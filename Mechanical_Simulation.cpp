//有n个重物，每个重物系在一条足够长的绳子上。每条绳子自上而下穿过桌面上的洞，然后系在一起。
//假设绳子是完全弹性的（不会造成能量损失），桌子足够高（因而重物不会垂到地上），且忽略所有的摩擦。
//问绳结X最终平衡于何处。
//注意：桌面上的洞都比绳结X小得多，所以即使某个重物特别重，绳结X也不可能穿过桌面上的洞掉下来，最多是卡在某个洞口处。
//文件的第一行为一个正整数n（1≤n≤1000），表示重物和洞的数目。
//接下来的n行，每行是3个整数：Xi.Yi.Wi，分别表示第i个洞的坐标以及第 i个重物的重量。(-10000≤x,y≤10000, 0<w≤1000 )
//可以认为这是优化问题，优化目标是合力为0
//每个重物产生的力大小固定，方向会改变。解法是模拟物理过程，每一步根据合力方向移动绳结X，移动距离随合力大小变化。
//当移动方向改变时，说明移动步长因子move太大了，可以调小一些。

#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int n;
double x, y; //X的x,y坐标。
bool XF, YF; //XF表示向X轴正向移动

struct Position 
{
    int x;
    int y;
    int power;
} positions[1005];

void solve(double move) 
{
    double X, Y, temp;
    X = Y = 0;
    for (int i = 1; i <= n; i++) 
    {
        temp = sqrt((x - positions[i].x) * (x - positions[i].x) + (y - positions[i].y) * (y - positions[i].y));//记录该点到原点的欧几里得距离
        if (temp == 0)//判断是否与原点重合
            continue;
        //正交分解，X是沿x轴的分量
        X += positions[i].power / temp * (positions[i].x - x);
        Y += positions[i].power / temp * (positions[i].y - y);
    }
    temp = sqrt(X * X + Y * Y);//计算正交分解后的合力
    //将原点在合力方向上位移一定距离
    x += move / temp * X;
    y += move / temp * Y;
}

int main() 
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", &positions[i].x, &positions[i].y, &positions[i].power);
    double move = 5000, tx, ty;
    while (true) 
    {
        //记录移动前原点的位置
        tx = x;
        ty = y;
        solve(move);//按照步长移动原点
        if (abs(tx - x) < 0.00001 && abs(ty - y) < 0.00001)//判断是否满足要求
            break;
        if ((XF != (x > tx)) || (YF != (y > ty))) 
        {//如果移动方向发生改变
            //记录移动方向
            XF = x > tx;
            YF = y > ty;
            move = move * 0.5;//缩小移动方向
        }
    }
    printf("%.3f %.3f", x, y);
    return 0;
}
