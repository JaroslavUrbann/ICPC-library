// kunh was faster a few times, it is shorter,
// but has an n^2 countertest iirc and could be slow when left part is larger
// bipartite matching
// sqrt(N) * M
// does bfs from unmatched nodes while alternating edges between
// unmatched, matched, ... stops when it finds and unmatched node
// (has to be on the right side). then it does dfses on the created
// graph (finds alternating paths). repeats everything.
struct HK{
	// minimum vetex cover, matching has to be filled
	// using konigs theorem & its constructive proof from wikipedia
	vector<int>minvc(){ // [0,n-1] if vertex is from left part, [n,n+m-1] otherwise
		queue<int>q;
		vector<bool>Z(n+m);
		for(int i=0;i<n;++i)
			if(ma[i]==-1){
				for(auto v:g[i]){
					if(!Z[mb[v]])q.push(mb[v]);
					Z[v+n]=Z[mb[v]]=true;
				}
				Z[i]=true;
			}
		while(q.size()){
			int u=q.front();q.pop();
			for(auto v:g[u])if(mb[v]!=u){
				if(!Z[mb[v]])q.push(mb[v]);
				Z[v+n]=Z[mb[v]]=true;
			}
		}
		vector<int>res;
		for(int i=0;i<n+m;++i)if(Z[i]==(i>=n))res.push_back(i);
		return res;
	}
	int n,m;
	vector<int>ma,mb,dist; // n is a dummy node
	vector<vector<int>>g;
	bool bfs(){
		dist.assign(n+1,INT_MAX);
		queue<int>q;
		for(int i=0;i<n;++i)
			if(ma[i]==-1){
				q.push(i);
				dist[i]=0;
			}
		while(q.size()){
			int u=q.front();q.pop();
			if(u==n)break;
			for(auto v:g[u])if(dist[mb[v]]==INT_MAX){
				dist[mb[v]]=dist[u]+1;
				q.push(mb[v]);
			}
		}
		return dist[n]!=INT_MAX;
	}
	bool dfs(int u){
		if(u==n)return true;
		for(auto v:g[u])if(dist[mb[v]]==dist[u]+1&&dfs(mb[v])){
			mb[v]=u;
			ma[u]=v;
			return true;
		}
		dist[u]=INT_MAX;
		return false;
	}
	int maxbpm(){
		int res=0;
		while(bfs())
			for(int i=0;i<n;++i)
				res+=ma[i]==-1&&dfs(i);
		return res;
	}
	HK(int n,int m):n(n),m(m),ma(n,-1),mb(m,n),g(n){}
	void ae(int u,int v){g[u].push_back(v);}
};
