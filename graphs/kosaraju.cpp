// finding strong components
// first do topological sort using dfs (sink first)
// reverse the graph
// go from the original source (so last element) and do dfs again and see how far you can get.
// when I visit a node, I know that it can get to me (obviously).
// And I also know that I can get to it, because either I was opened first 
// and I am the parent of that node, or I was opened second, but then
// the node would be my parent and I would be closed first (which I'm not).
struct Kosaraju{
	int n,k=0;
	vector<vector<vector<int>>>g;
	vector<vector<int>>vis;
	vector<int>sorted,p;
	Kosaraju(int n):n(n),g(n,vector<vector<int>>(2)),vis(n,vector<int>(2)),p(n){}
	void ae(int u,int v){
		g[u][0].push_back(v);
		g[v][1].push_back(u);
	}
	void dfs(int u,int r){
		if(vis[u][r])return;
		vis[u][r]=true;
		for(auto v:g[u][r])dfs(v,r);
		if(!r)sorted.push_back(u);
		else p[u]=k;
	}
	// res[u] = id of parent component [0,k-1]
	vector<int>getp(){
		for(int i=0;i<n;++i)dfs(i,0);
		for(int i=n-1;i>=0;--i)
			if(!vis[sorted[i]][1]){
				dfs(sorted[i],1);
				++k;
			}
		return p;
	}
	// graph with compressed sccs
	vector<vector<int>>getg(){
		vector<int>p=getp();
		vector<vector<int>>res(k);
		for(int u=0;u<n;++u)
			for(auto v:g[u][0])
				if(p[u]!=p[v])
					res[p[u]].push_back(p[v]);
		for(int u=0;u<k;++u){
			sort(res[u].begin(),res[u].end());
			res[u].erase(unique(res[u].begin(),res[u].end()),res[u].end());
		}
		return res;
	}
};
