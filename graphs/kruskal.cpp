// if you want spanning tree on graph complement (not minimal):
// keep all unvisited vertices in a set S and do a bfs,
// at each step traverse all the nodes in S, if you have an edge to them,
// skip them, otherwise remove them and push them into the queue
// (n+m)logn because you will do at most m skips and n removals.
// or
// take the vertex with the smallest degree, all the vertices not connected to
// it form a component (compress it's edges to 1 vertex), now you have k vetices
// run k^2 algorithm to make the spanning tree (O(k^2) = O(m^2/n^2) = O(m/n^2 * m) = O(m))

using W=ll;
struct E{int u,v;W w;};
struct Kruskal{
	int n;
	vector<int>par;
	vector<E>eds;
	Kruskal(int n):n(n),par(n,-1){}
	void ae(int u,int v,W w){eds.push_back({u,v,w});}
	int getp(int u){return par[u]<0?u:par[u]=getp(par[u]);}
	vector<E>calc(){
		sort(eds.begin(),eds.end(),[&](E&a,E&b){return a.w<b.w;});
		vector<E>res;
		for(auto[u,v,w]:eds)if(int pu=getp(u),pv=getp(v);pu!=pv){
			if(par[pu]<par[pv])swap(pu,pv);
			par[pv]+=par[pu],par[pu]=pv;
			res.push_back({u,v,w});
		}
		return res;
	}
};
