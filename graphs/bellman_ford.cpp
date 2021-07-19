// <= -inf - reached by negative cycle
// >= inf - not reachable at all
// if working with general graph (no s), parent links stop working,
// only some paths end up in a cycle, some end with with -1,
// some can even end up in a cycle that isn't negative.
// you have to specifically pick out a vertex that was updated
// in the last iteration of the first run (don't even do the second run)
// the parent chain of that vertex will form a negative cycle
struct BF{
	const ll inf=1e18;
	int n;
	vector<vector<pair<int,int>>>g;
	vector<ll>p,d,r; // parent, distance, reachable
	BF(int n):n(n),g(n),p(n),d(n,2*inf),r(n){}
	void ae(int u,int v,int w){g[u].push_back({w,v});} // one directional by default
	void calc(int s){
		queue<int>q;q.push(s);
		while(q.size()){
			int u=q.front();q.pop();r[u]=true;
			for(auto[w,v]:g[u])if(!r[v])q.push(v);
		}
		d[0]=0;
		for(int it=0;it<n;++it)
			for(int u=0;u<n;++u)if(r[u])
				for(auto[w,v]:g[u])if(d[u]+w<d[v]){
					d[v]=d[u]+w;
					p[v]=u;
				}
		for(int it=0;it<n;++it)
			for(int u=0;u<n;++u)if(r[u])
				for(auto[w,v]:g[u])if(d[u]+w<d[v])
					d[v]=-2*inf;
	}
};
