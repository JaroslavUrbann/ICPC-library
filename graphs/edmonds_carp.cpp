// very basic, use dinitz most of the time
// E^2 * V
// you don't need to add backwards edges with a directed graph
// (only edges with forward flow have a backwards capacity,
// so useful backwards edges will get added automatically)
template<typename T>
T EdmondsCarp(vector<unordered_map<int,T>>g,int s,int t){
	vector<int>p;
	auto bfs=[&](){
		p.assign(g.size(),-1);p[s]=s;
		queue<int>q;q.push(s);
		while(q.size()&&p[t]==-1){
			int u=q.front();q.pop();
			for(auto [v,w]:g[u])if(p[v]==-1&&w){
				p[v]=u;
				q.push(v);
			}
		}
		return ~p[t];
	};
	T res=0;
	while(bfs()){
		T mn=is_same<T,int>::value?INT_MAX:LLONG_MAX;
		for(int u=t;p[u]!=u;u=p[u])mn=min(mn,g[p[u]][u]);
		for(int u=t;p[u]!=u;u=p[u]){
			g[p[u]][u]-=mn;
			g[u][p[u]]+=mn;
		}
		res+=mn;
	}
	return res;
}
