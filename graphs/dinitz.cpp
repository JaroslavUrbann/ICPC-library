// creates bfs levels and spams multiple dfs that only go forward,
// each dfs finds a path and adds some flow, when you can't find more paths
// it does a new bfs and repeats
// works in O(V^2 * E), should be much faster though, probably like V*E idk
// use long long if the sum of all edges can be bigger than int
template<typename T>
struct Dinitz{
	int n;
	vector<pair<T,int>>e;
	vector<vector<int>>g;
	vector<int>cur,h;
	bool bfs(int s,int t){
		h.assign(n,0);h[s]=1;
		queue<int>q;q.push(s);
		while(q.size()&&!h[t]){
			int u=q.front();q.pop();
			for(auto i:g[u]){
				auto[c,v]=e[i];
				if(c&&!h[v]){
					h[v]=h[u]+1;
					q.push(v);
				}
			}
		}
		return h[t];
	}
	T dfs(int u,int t,T f){ // returns consumed capacity
		if(u==t)return f;
		T r=f; // remaining capacity to fill
		for(int&i=cur[u];i<g[u].size();++i){
			auto[c,v]=e[g[u][i]];
			if(c&&h[v]==h[u]+1){
				T fl=dfs(v,t,min(c,r));
				e[g[u][i]].first-=fl;
				e[g[u][i]^1].first+=fl;
				if(!(r-=fl))return f;
			}
		}
		return f-r;
	}
	T maxflow(int s,int t){ // can't call more than once
		T res=0;
		while(bfs(s,t)){
			cur.assign(n,0);
			while(T f=dfs(s,t,is_same<T,int>::value?INT_MAX:LLONG_MAX))res+=f;
		}
		return res;
	}
	// IF THEY WANT ID'S, JUST RETURN THE ID'S
	// YOU DON'T NEED TO CREATE AN EDGE STRUCT
	// (fill edges sequentially (official first) and return j/2)
	// have to call maxFlow first
	// returns u,v,cost, flow is going u->v
	// does a dfs and takes edges that are visited->unvisited
	vector<tuple<int,int,T>>mincut(int s){
		vector<bool>vis(n);
		function<void(int)>dfs=[&](int u){
			vis[u]=true;
			for(int i:g[u]){
				auto[c,v]=e[i];
				if(!vis[v]&&c>0)dfs(v);
			}
		};
		dfs(s);
		vector<tuple<int,int,T>>res;
		for(int i=0;i<n;++i)
			if(vis[i])
				for(auto j:g[i]){
					auto[c,v]=e[j];
					if(!vis[v])res.push_back({i,v,e[j^1].first/2}); // /2 if undirected
				}
		return res;
	}
	Dinitz(int n):n(n),g(n){}
	void ae(int u,int v,T c,T bc=0){ // bc = c if undirected
		g[u].push_back(e.size());
		e.push_back({c,v});
		g[v].push_back(e.size());
		e.push_back({bc,u});
	}
};
