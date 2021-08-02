// v has to be the other node :(
struct E{
	int u,v,w;
};

// creates a dfs tree and those edges to children that don't have a backedge that goes above me are bridges
// ng contains a bridge tree that has bridges with old labels, so you have to use par[u] when using it 
// should work with self-loops and multi edges
// high constant & memory usage, but O(n+m)
struct BT{
	int n,c=0;
	vector<vector<E>>g,ng,inside;
	vector<int>par,low,dpt,vis;
	vector<E>bridges;
	BT(int n):n(n),g(n),par(n),low(n),dpt(n),vis(n){}
	void ae(E e){E oe=e;swap(oe.u,oe.v);
		g[e.u].push_back(e);
		g[e.v].push_back(oe);
	}
	void dfs2(int u,int f){
		ng.resize(c+1);inside.resize(c+1);
		vis[u]=1;par[u]=c;
		for(E e:g[u])if(e.v!=f){
			if(vis[e.v]&&par[e.v]!=c){E oe=e;swap(oe.u,oe.v);
				ng[c].push_back(e);
				ng[par[e.v]].push_back(oe);
			}else if(!vis[e.v])dfs2(e.v,f);
			if(vis[e.v]==1)inside[c].push_back(e);
		}
		vis[u]=2;
	}
	int dfs(int u,int p,int d){
		low[u]=dpt[u]=d;
		for(E e:g[u])if(e.v!=p){
			if(dpt[e.v])low[u]=min(low[u],dpt[e.v]);
			else{
				int lw=dfs(e.v,u,d+1);
				low[u]=min(low[u],lw);
				if(lw>d){
					bridges.push_back(e);
					dfs2(e.v,u);++c;
				}
			}
		}
		return low[u];
	}
	void calc(){//dfs(0,0,1);dfs2(0,-1);}
		for(int i=0;i<n;++i)if(!vis[i]){ // not tested
			dfs(i,i,1);
			dfs2(i,-1),++c;
		}
	}
};
