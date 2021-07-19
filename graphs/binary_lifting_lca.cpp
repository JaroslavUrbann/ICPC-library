// probably could be used for querying sum along a path on tree
// (with updates -> use euler walk or HLD for non-reversible operation (max))
const int N=200100,logN=ceil(log2(N));
int up[N][logN];
int tin[N],tout[N],d[N];
int n,timer;
vector<int>g[N];

void dfs(int u,int p,int depth){
	tin[u]=++timer;
	d[u]=depth;
	up[u][0]=p;
	for(int i=1;i<logN;++i)up[u][i]=up[up[u][i-1]][i-1];
	for(auto v:g[u])if(v!=p)dfs(v,u,depth+1);
	tout[u]=++timer;
}

bool isanc(int u,int v){return tin[u]<=tin[v]&&tout[u]>=tout[v];}

int lca(int u,int v){
	if(isanc(u,v))return u;
	if(isanc(v,u))return v;
	// jumps with u until it barely is the ancestor of v
	for(int i=logN-1;i>=0;--i)
		if(!isanc(up[u][i],v))
			u=up[u][i];
	return up[u][0];
}

// jumps up min(depth[u],x) from u
int jumpx(int u,int x){
	for(int i=logN-1;i>=0;--i)
		if((1<<i)&x)
			u=up[u][i];
	return u;
}
