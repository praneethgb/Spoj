#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

#define PB push_back
#define LL long long
#define SZ(x) int(x.size())
#define ALL(x) x.begin(),x.end()
#define FOR(a,b) for(int a=0;a<b;a++)
#define CLR(a,b) memset(a,b,sizeof(a))

using namespace std;

#define infile "a.in"
#define outfile "a.out"

#define maxn 11
#define maxlen 11000
#define P 7774777

typedef LL h_type;

int n;
char s[maxn][maxlen];
h_type h[maxn][maxlen];
h_type ppow[maxlen];
int len[maxn];

inline h_type calc(int i, int j1, int j2)
{
	if (j1 == 0)
		return h[i][j2];
	return h[i][j2] - h[i][j1-1] * ppow[j2-j1+1];
}

bool check(int q)
{
	vector<h_type> v;

	for (int i = 0; i < n; i++)
	{
		vector<pair<h_type, int> > u;
		for (int j = 0; j + q <= len[i]; j++)
			u.PB(make_pair(calc(i, j, j+q-1), j));
		sort(u.begin(), u.end());
		int k = u.size();
		for (int j = 0; j < k; j++)
		{
			int l = j;
			while (l+1 < k && u[l].first == u[l+1].first) l++;
			if (u[j].second + q <= u[l].second)
				v.PB(u[j].first);
			j = l;
		}
	}

	sort(v.begin(), v.end());
	int vs = v.size();
	int cnt = 0;
	for (int i = 0; i < vs; i++)
	{
		if (i > 0 && v[i] == v[i-1])
			cnt++;
		else
			cnt = 1;
		if (cnt == n)
			return true;
	}
	return false;
}

void solvecase()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s[i]);
		len[i] = strlen(s[i]);
	}

	for (int i = 0; i < n; i++)
	{
		h_type t = 0;
		for (int j = 0; j < len[i]; j++)
		{
			t = t * P + s[i][j];
			h[i][j] = t;
		}
	}
	ppow[0] = 1;
	for (int i = 1; i < maxlen; i++)
		ppow[i] = ppow[i-1] * P;

	int r = len[0] / 2;
	for (int i = 1; i < n; i++)
		r = min(r, len[i] / 2);
	r++;
	int l = 0;

	while (l+1 < r)
	{
		int m = (l+r)/2;
		if (check(m))
			l = m;
		else
			r = m;
	}

	printf("%d\n", l);
}

void solve() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) solvecase();
}

int main() {
	//freopen(infile, "rt", stdin);
	//freopen(outfile, "wt", stdout);
	solve();
	return 0;
}
