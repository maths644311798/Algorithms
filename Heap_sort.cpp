#include<iostream>
using namespace std;
int n, x[100000];
void check(int v, int len)
{
    int t, j, k;
    k = v * 2 + 1;
    if (k >= len) return;
    if (k + 1 >= len)
    {
        if (x[v] > x[k])
        {
            t = x[v];
            x[v] = x[k];
            x[k] = t;
        }
        return;
    }
    j = (x[k] < x[k + 1]) ? k : k + 1;
    if (x[v] > x[j])
    {
        t = x[v];
        x[v] = x[j];
        x[j] = t;
        check(j, len);
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = n >> 1; i >= 0; i--)check(i, n);
    while (n > 0)
    {
        cout << x[0] << ' ';
        x[0] = x[n - 1];
        --n;
        check(0, n);
    }
}