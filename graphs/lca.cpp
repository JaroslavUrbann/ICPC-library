template<typename T>
struct SparseTable{
	int n,p;
	vector<vector<T>>dp;
	vector<int>lg;
	SparseTable(vector<T>a={1}):n(a.size()),p(log2(n)+1),dp(p,vector<T>(n)),lg(n+1){
		dp[0]=a;
		for(int i=2;i<=n;++i)lg[i]=lg[i/2]+1;
		for(int i=1;i<p;++i)
			for(int j=0,j2=(1<<(i-1));j2<n;++j,++j2)
				dp[i][j]=T::uni(dp[i-1][j],dp[i-1][j2]);
	}
	// inclusive, exclusive
	T query(int l,int r){
		int x=lg[r-l];
		return T::uni(dp[x][l],dp[x][r-(1<<x)]);
	}
};

struct lcaq{
	int d,u;
	lcaq(int d=0,u=0):d(d),u(u){}
	static lcaq uni(lcaq&a,lcaq&b){return lcaq(min(a.d,b.d),a.d<b.d?a.u:b.u);}
};

// not compiled
struct LCA{
	int n;
	vector<vector<int>>g;
	vector<int>pos;
	vector<lcaq>tour;
	SparseTable<lcaq>st;
	LCA(int n):n(n),g(n),pos(n){}
	LCA(vector<vector<int>>&g):n(g.size()),g(g),pos(n){}
	void ae(int u,int v){
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void dfs(int u,int p,int d){
		pos[u]=tour.size();
		tour.push_back({d,u});
		for(auto v:g[u])if(v!=p){
			dfs(v,u,d+1);
			tour.push_back({d,u});
		}
	}
	void calc(int u=0){dfs(u,u,0);st=SparseTable<lcaq>(tour);}
	int query(int u,int v){return st.query(min(pos[u],pos[v]),max(pos[u],pos[v])+1).u;}
};
