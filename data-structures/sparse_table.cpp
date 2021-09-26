template<typename O>
struct SparseTable{
	using T=typename O::T;
	int n,p;
	vector<vector<T>>dp;
	vector<int>lg;
	SparseTable(vector<T>a={1}):n(a.size()),p(log2(n)+1),dp(p,vector<T>(n)),lg(n+1){
		dp[0]=a;
		for(int i=2;i<=n;++i)lg[i]=lg[i/2]+1;
		for(int i=1;i<p;++i)
			for(int j=0,j2=(1<<(i-1));j2<n;++j,++j2)
				dp[i][j]=O::uni(dp[i-1][j],dp[i-1][j2]);
	}
	// inclusive, exclusive
	T query(int l,int r){
		int x=lg[r-l];
		return O::uni(dp[x][l],dp[x][r-(1<<x)]);
	}
};

struct maxq{
	typedef ll T;
	static T uni(T a,T b){return max(a,b);}
};

struct minq{
	typedef ll T;
	static T uni(T a,T b){return min(a,b);}
};

struct gcdq{
	typedef ll T;
	static T uni(T a,T b){return __gcd(a,b);}
};

