// proper dsu
// random dsu is about 8s, size dsu is about 2.6s (https://codeforces.com/blog/entry/47402)
struct DSU{
	int cmp;
	vector<int>p; // -size if self, parent otherwise
	DSU(int n):cmp(n),p(n,-1){}
	int find(int u){return p[u]<0?u:p[u]=find(p[u]);}
	int size(int u){return -p[find(u)];}
	bool same(int u,int v){return find(u)==find(v);}
	int comps(){return cmp;}
	void uni(int u,int v){
		u=find(u),v=find(v);
		if(u!=v){
			if(size(u)>size(v))swap(u,v);
			p[v]+=p[u];
			p[u]=v;
			--cmp;
		}
	}
};
