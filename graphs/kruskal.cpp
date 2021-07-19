// if you want spanning tree on graph complement (not minimal):
// keep all unvisited vertices in a set S and do a bfs,
// at each step traverse all the nodes in S, if you have an edge to them,
// skip them, otherwise remove them and push them into the queue
// (n+m)logn because you will do at most m skips and n removals.
// or
// take the vertex with the smallest degree, all the vertices not connected to
// it form a component (compress it's edges to 1 vertex), now you have k vetices
// run k^2 algorithm to make the spanning tree (O(k^2) = O(m^2/n^2) = O(m/n^2 * m) = O(m))

// proper dsu
vector<int>p,sz;

int find(int u){return p[u]==u?u:p[u]=find(p[u]);}

void uni(int u,int v){
	u=find(u);v=find(v);
	if(u!=v){
		if(sz[u]>sz[v])swap(u,v);
		p[u]=p[v];
		sz[v]+=sz[u];
	}
}
// proper dsu


struct edge{
	int f,t;
	ll w;
	bool operator<(const edge&a)const{return w<a.w;}
};

// g has to be {weight, to}
// change input to edges if it's convenient
vector<edge>kruskal(vector<vector<pair<ll,int>>>&g){
	int n=g.size();
	vector<edge>edges;
	for(int i=0;i<n;++i)
		for(auto e:g[i])
			edges.push_back({i,e.second,e.first});
	sort(edges.begin(),edges.end());
	sz.assign(n,0);
	p.resize(n);iota(p.begin(),p.end(),0);
	vector<edge>res;
	for(auto e:edges)
		if(find(e.f)!=find(e.t)){
			uni(e.f,e.t);
			res.push_back(e);
		}
	return res;// edges of spaning tree
}
