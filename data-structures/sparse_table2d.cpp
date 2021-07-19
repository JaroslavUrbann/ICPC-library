// if there is like a million queries, you should actually use precomputed log
template<typename T>
struct SparseTable2D{
	int n,m,p,q;
	vector<vector<vector<vector<T>>>>dp; // p,q,n,m
	SparseTable2D(vector<vector<T>>a):n(a.size()),m(a[0].size()),p(log2(n)+1),q(log2(m)+1),
	dp(p,vector<vector<vector<T>>>(q,vector<vector<T>>(n,vector<T>(m)))){
		dp[0][0]=a;
		for(int i=1;i<p;++i) // computes all rectangles of shape (2^i, 1) (everything for j==0)
			for(int y=0,y2=(1<<(i-1));y2<n;++y,++y2)
				for(int x=0;x<m;++x)
					dp[i][0][y][x]=max(dp[i-1][0][y][x],dp[i-1][0][y2][x]);
		for(int i=0;i<p;++i) // computes everything else
			for(int j=1;j<q;++j)
				for(int y=0;y<n;++y)
					for(int x=0,x2=(1<<(j-1));x2<m;++x,++x2)
						dp[i][j][y][x]=max(dp[i][j-1][y][x],dp[i][j-1][y][x2]);
	}
	// inclusive, exclusive
	// y1<y2, x1<x2
	T query(int y1,int x1,int y2,int x2){
		int i=log2(y2-y1);
		int j=log2(x2-x1);
		return max({dp[i][j][y1][x1],
								dp[i][j][y2-(1<<i)][x1],
								dp[i][j][y1][x2-(1<<j)],
								dp[i][j][y2-(1<<i)][x2-(1<<j)]});
	}
};

