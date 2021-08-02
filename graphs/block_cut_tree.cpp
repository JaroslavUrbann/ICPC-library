// v has to be the other node :(
struct E{
	int u,v;
};

// IF DOING QUERIES THEN READ ALL OF THIS
// should work with self-loops, multi edges and multiple components (not tested on any of these)
// high constant & memory usage, but O(n+m)
// use isart[par[u]] for arts, to get all components u belongs to, use ng[par[u]]
// parent component of each art is the last entry in ng[par[u]]
// use them if updating nodes, and add 1 node above lcm when querying
// (only when the lcm is a component), careful that if root is an art, 
// you shouldn't use its parent component (it doesn't have any)
// there can be n-2 arts, and n-1 comps at the same time
// root is guaranteed to be 0
struct BCT{
	int n,c=1;
	vector<vector<E>>g,inside;
	vector<vector<int>>ng;
	vector<int>par,low,dpt,vis,isart;
	BCT(int n):n(n),g(n),inside(2*n),ng(2*n),par(n,-1),low(n),dpt(n),vis(n),isart(2*n){}
	void ae(E e){E oe=e;swap(oe.u,oe.v);
		g[e.u].push_back(e);
		g[e.v].push_back(oe);
	}
	void nae(int u,int v){
		ng[u].push_back(v);
		ng[v].push_back(u);
	}
	void dfs2(int u,int f,int cc){
		vis[u]=true;
		if(~par[u])nae(par[u],cc);
		else par[u]=cc;
		for(E e:g[u])if(e.v!=f&&!vis[e.v]){
			inside[cc].push_back(e);
			dfs2(e.v,f,cc);
		}
	}
	int dfs(int u,int p,int d){
		low[u]=dpt[u]=d;
		int pv=-1;
		for(E e:g[u])if(e.v!=p){
			if(dpt[e.v])low[u]=min(low[u],dpt[e.v]);
			else{
				int lw=dfs(e.v,u,d+1);
				low[u]=min(low[u],lw);
				if(lw>=d&&(d!=1||~pv)){
					if(par[u]==-1){
						isart[par[u]=(u?c++:0)]=true;
						if(d==1){dfs2(pv,u,c);nae(par[u],c++);}
					}
					dfs2(e.v,u,c);nae(par[u],c++);
				}
				pv=e.v;
			}
		}
		if(d==1&&par[u]==-1)dfs2(u,-1,u?c++:0);
		return low[u];
	}
	void calc(){for(int i=0;i<n;++i)if(!vis[i])dfs(i,i,1);}
};

