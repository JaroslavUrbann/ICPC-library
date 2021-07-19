
// typical dfs order array, nodes appearing twice should not be counted
// + count lca separately if different subtrees

struct query{int u,v,idx;}; //inclusive,exclusive

// not compiled
// probably don't do this tbh and just do n^2 without cache misses
// array is 2 times longer when doing mo on a tree
template<typename T>
struct MoTree{
	const int n,ln,bsz=450; // block size
	vector<vector<int>>g,p;
	vector<T>vals,in,out,a;
	Mo(vector<T>&vals):n(a.size()),ln(log2(n)+1),g(n),p(n,vector<int>(ln)),vals(vals),in(n),out(n),a(2*n){}
	void ae(int u,int v){
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void add(int idx){
		
	}
	void del(int idx){

	}
	T get(){

	}
	void dfs(int u,int par,int d,int&tim){
		a[in[u]=tim++]=u;
		p[u][0]=par;
		for(int j=1;j<ln;++j)p[u][j]=p[p[u][j-1]][j-1];
		for(auto v:g[u])if(v!=p)dfs(v,u,d+1,tim);
		a[out[u]=tim++]=u;
	}
	bool isp(int u,int v){return in[u]>=in[v]&&out[u]>=out[v];}
	int lca(int u,int v){
		if(isp(u,v))return u;
		if(isp(v,u))return v;
		for(int j=ln-1;j>=0;--j)if(!isp(p[u][j],v))u=p[u][j];
		return p[u][0];
	}
	vector<T>solve(vector<query>&queries){
		int tim=0;dfs(0,0,0,tim);
		for(auto&[u,v,i]:queries)if(in[u]>in[v])swap(u,v);
		vector<T>res(queries.size());
		sort(queries.begin(),queries.end(),[&](query&x,query&y){
			if(in[x.u]/bsz!=in[y.u]/bsz)return in[x.u]<in[y.u];	
			return (in[x.u]/bsz)&1?in[x.u]>in[y.u]:in[x.u]<in[y.u];
		});
		int l=0,r=0; //inclusive,exclusive
		for(auto[u,v,i]:queries){
			while(r<in[v]+1)add(r++);
			while(in[u]<l)add(--l);
			while(in[v]+1<r)del(--r);
			while(l<in[u])del(l++);
			int lcpos=in[lca(u,v)];
			if(lcpos!=in[u])add(lcpos);
			res[i]=get();
			if(lcpos!=in[u])del(lcpos);
		}
		return res;
	}
};
