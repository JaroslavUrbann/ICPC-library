// slightly tested
// creates a dfs tree and if at least one of my children doesn't have a backedge
// that goes above me, I'm an articulation point
// special case for root ofc
struct Articulations{
	int n;
	vector<vector<int>>g;
	vector<int>low,in,res;
	Articulations(int n):n(n),g(n),low(n),in(n){}
	void ae(int u,int v){
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int dfs(int u,int p,int t){
		low[u]=1e9;in[u]=t;
		int notart=1,nonb=0;
		for(auto v:g[u])if(v!=p){
			if(in[v])low[u]=min(low[u],in[v]); // backedge
			else{
				++nonb;
				int lw=dfs(v,u,t+1);
				notart&=lw<t;
				low[u]=min(low[u],lw);
			}
		}
		if((u&&!notart)||(!u&&nonb>1))res.push_back(u);
		return low[u];
	}
	vector<int>calc(){dfs(0,0,1);return res;}
};
