// this is shit, because it's really slow, long and isn't any more powerful than
// the n*log^2(n) version. It's my first implementation and I didn't know you should
// do this with dsu for worse complexity but better constant factor. feel free to delete
// just remember that you can do everything with sqrt decomposition I guess...

// you have a graph and queries with deleting / adding edges and also an asking query
// that asks how many connected comonents there are / if nodes u,v are connected ...
// you solve it by sqrt decomposition:
// every sqrt(q) queries you rebuild the graph completely, but you don't use edges that
// are in the following block of size sqrt(q) (doesn't matter if they are added / deleted)
// then for each square you add up to sqrt edges so that it becomes the wanted graph
// (for example, on the square where you build the graph, you'll add all edges that will be deleted in
// the block, and each square after that you update the set of edges that you'll be adding)
// implementation is kind of messy and I think slow

// O(m*log(m) + m*sqrt(m))
// if type == ASK, u and v can be nonsense
// qq queries are in the form of u,v,t, there are 3 types
struct Q{int id,t;};

struct DC{
	const int ASK=0,ADD=1,DEL=2;
	int n,m,q,sqq,cn; // current number of nodes in compressed graph
	vector<Q>qs;
	vector<pair<int,int>>edges;
	vector<vector<int>>g;
	vector<int>p,vis;
	DC(int n,vector<tuple<int,int,int>>qq):n(n),q(qq.size()),sqq(sqrt(q)),g(n),p(n),vis(n){
		for(auto&[u,v,t]:qq)if(u>v)swap(u,v);
		for(auto[u,v,t]:qq)if(t!=ASK)edges.push_back({u,v});
		sort(edges.begin(),edges.end());
		edges.erase(unique(edges.begin(),edges.end()),edges.end());
		m=edges.size();
		for(auto[u,v,t]:qq)qs.push_back({int(lower_bound(edges.begin(),edges.end(),make_pair(u,v))-edges.begin()),t});
	}
	void addedge(int idx,int pars){
		auto[u,v]=edges[idx];
		if(pars)u=p[u],v=p[v];
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void deledges(int idx){
		auto[u,v]=edges[idx];
		g[p[u]].clear();
		g[p[v]].clear();
	}
	void dfsp(int u,int par){
		p[u]=par;
		for(auto v:g[u])if(p[v]!=par)dfsp(v,par);
	}
//	int dfsolve(int u){
//		vis[u]=true;
//		int res=0;
//		for(auto v:g[u])if(!vis[v])res+=dfsolve(v);
//		return res+1;
//	}
//	void dfsolve2(int u){
//		vis[u]=false;
//		for(auto v:g[u])if(vis[v])dfsolve2(v);
//	}
	vector<int>solve(){
		vector<int>ans,add;
		for(int i=0;i<q;++i){
			int l=i/sqq*sqq,r=min(q,(1+i/sqq)*sqq);
			if(i%sqq==0){ // rebuild graph
				add.assign(m,0);p.assign(n,-1);cn=0;
				for(int j=0;j<i;++j)if(qs[j].t!=ASK)add[qs[j].id]^=1;
				// 1 == add to graph, 2 == don't do shit, 3 == add to additional
				for(int j=r-1;j>=l;--j)if(qs[j].t!=ASK)add[qs[j].id]=2+(qs[j].t==DEL);
				for(int id=0;id<m;add[id]=max(add[id]-2,0),++id)if(add[id]==1)addedge(id,0);
				for(int u=0;u<n;++u)if(p[u]==-1)dfsp(u,cn++);
				for(auto&v:g)v.clear();
			}
			if(qs[i].t==ASK){ // question
				for(int j=l;j<r;++j)if(qs[j].t!=ASK&&add[qs[j].id])addedge(qs[j].id,1);
//				// you have a compressed graph that has up to n nodes, numbered 0..cn-1
//				// and up to sqrt(n) edges (non-ask queries in <l,r))
//				// p[u] is the parent node of each node in the graph
//				// you can do dfs from each node in <l,r) to get the number of comps in sqrt(n)
//				// or you can do dfs from a query node to know if they are connected in sqrt(n)
//				int res=cn;
//				for(int j=l;j<r;++j)
//					if(qs[j].t!=ASK){
//						auto[u,v]=edges[qs[j].id];
//						u=p[u],v=p[v];
//						if(!vis[u])res+=1-dfsolve(u);
//						if(!vis[v])res+=1-dfsolve(v);
//					}
//				for(int j=l;j<r;++j)
//					if(qs[j].t!=ASK){
//						auto[u,v]=edges[qs[j].id];
//						dfsolve2(p[u]);
//						dfsolve2(p[v]);
//					}
//				ans.push_back(res);
				for(int j=l;j<r;++j)if(qs[j].t!=ASK&&add[qs[j].id])deledges(qs[j].id);
			}else add[qs[i].id]^=1; // no question
		}
		return ans;
	}
};

