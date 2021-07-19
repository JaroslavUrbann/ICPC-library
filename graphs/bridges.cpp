// creates a dfs tree and those edges to children that don't have a backedge
// that goes above me are bridges
struct Bridges{
	int n;
	vector<vector<int>>g;
	vector<int>low,in;
	vector<pair<int,int>>res;
	Bridges(int n):n(n),g(n),low(n),in(n){}
	void add_edge(int u,int v){
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int dfs(int u,int p,int t){
		low[u]=1e9;in[u]=t;
		for(auto v:g[u])if(v!=p){
			if(in[v])low[u]=min(low[u],in[v]); // backedge
			else{ // child
				int lw=dfs(v,u,t+1);
				if(lw>t)res.push_back({u,v});
				low[u]=min(low[u],lw);
			}
		}
		return low[u];
	}
	// u,v (shrug emoji) (might be in wrong order)
	vector<pair<int,int>>calc(){dfs(0,0,1);return res;}
};
