#include<iostream>
#include<cstring>
using namespace std;

string T, P;
int pi[1000];

void ComputePrefixFunction(const string& P)
{
	int m = P.length();
	pi[0] = -1;
	int k = -1;
	for (int q = 1; q < m; ++q)
	{
		while (k >= 0 && P[k + 1] != P[q]) k = pi[k];
		if (P[k + 1] == P[q]) ++k;
		pi[q] = k;
	}
}

void KMP_Matcher(const string& T, const string& P)
{
	int n = T.length(), m = P.length();
	ComputePrefixFunction(P);
	int q = -1;
	for (int i = 0; i < n; ++i)
	{
		while (q >= 0 && P[q + 1] != T[i]) q = pi[q];
		if (P[q + 1] == T[i]) ++q;
		if (q == m - 1)
		{
			cout << i - m + 1 << '\n';
			q = pi[q];
		}
	}
}

int main()
{
	cin >> T >> P;
	KMP_Matcher(T, P);
	return 0;
}