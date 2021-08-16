// knuth optimization (from O(n^3) to O(n^2))
// dp[i][j] = w[i][j] + min(dp[i][k-1]+dp[k][j]) for all k: 1<k<=j
// dp[i][i] = 0
// w[i][j] (cost matrix) must satisfy quadrangle inequality:
// for all i: i<=i2<=j<=j2, w[i][j] + w[i2][j2] <= w[i][j2] + w[i2][j]
// and must be monotone on the lattice of intervals:
// for all [i,j] that are a subset of [i2,j2]: w[i][j] <= w[i2][j2]

// then for some reason it means that:
// dpK(i,j) <= dpK(i,j+1) <= dpK(i+1,j+1) where dpK is the biggest optimal k
// so you can calculate the dp in increasing t = i - j

// 1 indexing

const int N=5010;
ll dp[N][N],a[N],pref[N];
int dpk[N][N];
int n;

ll w(int i,int j){return pref[j]-pref[i-1];}

void solvedp(){
	partial_sum(a,a+n+1,pref); // a needs to be ll
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j)dp[i][j]=LLONG_MAX;
	for(int i=1;i<=n;++i)dpk[i][i]=i-1;
	for(int t=1;t<n;++t)
		for(int i=1,j=i+t;j<=n;++i,++j)
			for(int k=dpk[i][j-1]+(i==j-1);k<=dpk[i+1][j];++k)
				if(ll val=w(i,j)+dp[i][k]+dp[k+1][j];val<dp[i][j])
					dp[i][j]=val,dpk[i][j]=k;
}

