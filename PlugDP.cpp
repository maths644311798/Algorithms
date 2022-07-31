#define _CRT_SECURE_NO_WARNINGS
//参考陈丹琦《基于连通性状态压缩的动态规划问题》
// 0表示无插头， 1表示左括号插头， 2表示右括号插头
// 虽然上述分析是3进制，但为了方便，存储用4进制
//1个格子的状态占2 bit
//状态数太多，所以状态需要Hash
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include <unordered_map>

using namespace std;

//state是状态，dp是方案总数


int n, m, mapx[20][20] = { 0 }, endx, endy;
long long int all_ans = 0;

unordered_map<int, long long int> dp[2];

int bits[28] = { 0 }; //bits[i]是2*i

//2个变量在0,1之间切换，作为滚动数组下标
int pre = 1, cnt = 0;

inline void ini()
{
    memset(mapx, 0, sizeof(mapx));
    scanf("%d %d", &n, &m);
    char ch = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            ch = 0; 
            while (ch != '.' && ch != '*') ch = getchar();
            if (ch == '.')
            { 
                mapx[i][j] = 1; 
                endx = i; 
                endy = j; 
            }
        }
    for (int i = 0; i <= 25; i++) bits[i] = (i << 1);
    cnt = 0;
    pre = 1;
}

inline void hash_add(int sta, long long int val)
{
    if (dp[cnt].count(sta) > 0)
    {
        dp[cnt][sta] += val;
    }
    else
    {
        dp[cnt][sta] = val;
    }
}

inline void DP()
{
    dp[cnt][0] = 1;
    int bit_control = (1 << ((m + 1) << 1)) - 1;

    for (int i = 1; i <= n; i++)
    {
        //new line
        swap(pre, cnt);
        dp[cnt].clear();
        for (auto k = dp[pre].begin(); k != dp[pre].end(); k++)
        {
            dp[cnt][(k->first << 2) & bit_control] = k->second;
        }

        for (int j = 1; j <= m; j++)
        {
            swap(pre, cnt);//rolling
            dp[cnt].clear();

            for (auto k = dp[pre].begin(); k != dp[pre].end(); k++)
            {
                //get previous state&answer
                int now_sta = k->first;
                long long int now_ans = k->second;

                //get current plugs
                int is_down = (now_sta >> bits[j]) % 4;
                int is_right = (now_sta >> bits[j - 1]) % 4;

                if (!mapx[i][j])//case 0
                {
                    if ((!is_down) && (!is_right)) 
                        hash_add(now_sta, now_ans);
                }
                else if ((!is_down) && (!is_right))//case 1
                {
                    if (mapx[i + 1][j] && mapx[i][j + 1])
                        hash_add(now_sta + (1 << bits[j - 1]) + 2 * (1 << bits[j]), now_ans);
                }
                else if ((!is_down) && is_right)//case 2
                {
                    if (mapx[i + 1][j]) 
                        hash_add(now_sta, now_ans);//go down
                    if (mapx[i][j + 1]) 
                        hash_add(now_sta - is_right * (1 << bits[j - 1]) + is_right * (1 << bits[j]), now_ans);//go right
                }
                else if (is_down && (!is_right))//case 3
                {
                    if (mapx[i][j + 1]) 
                        hash_add(now_sta, now_ans);//go right
                    if (mapx[i + 1][j]) 
                        hash_add(now_sta - is_down * (1 << bits[j]) + is_down * (1 << bits[j - 1]), now_ans);//go down
                }
                else if (is_down == 1 && is_right == 1)//case 4
                {
                    int count = 1;
                    for (int l = j + 1; l <= m; l++)
                    {
                        if ((now_sta >> bits[l]) % 4 == 1) 
                            count++;
                        else if ((now_sta >> bits[l]) % 4 == 2) 
                            count--;
                        if (!count)
                        {
                            hash_add(now_sta - (1 << bits[l]) - (1 << bits[j]) - (1 << bits[j - 1]), now_ans);
                            break;
                        }
                    }
                }
                else if (is_down == 2 && is_right == 2)//case 5
                {
                    int count = 1;
                    for (int l = j - 2; l >= 0; l--)
                    {
                        if ((now_sta >> bits[l]) % 4 == 1) 
                            count--;
                        else if ((now_sta >> bits[l]) % 4 == 2) 
                            count++;
                        if (!count)
                        {
                            //at bits[l], it change from 1 to 2
                            hash_add(now_sta - 2 * (1 << bits[j]) - 2 * (1 << bits[j - 1]) + (1 << bits[l]), now_ans);
                            break;
                        }
                    }
                }

                else if (is_down == 1 && is_right == 2)//case 6
                    hash_add(now_sta - 2 * (1 << bits[j - 1]) - (1 << bits[j]), now_ans);
                else if (is_right == 1 && is_down == 2)//case 7
                    if (i == endx && j == endy) 
                        all_ans += now_ans;
            }
        }
    }
}

int main()
{
    ini(); 
    DP();
    printf("%lld\n", all_ans);
    return 0;
}