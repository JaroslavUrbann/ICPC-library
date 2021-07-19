// topsort
bool kahn(vector<vector<int>>g,vector<int>&res){
	int n=g.size();
	vector<int>incnt(n);
	for(int u=0;u<n;++u)
		for(auto v:g[u])
			++incnt[v];
	queue<int>q;
	for(int u=0;u<n;++u)if(!incnt[u])q.push(u);
	while(q.size()){
		int u=q.front();q.pop();
		res.push_back(u);
		for(auto v:g[u])if(!--incnt[v])q.push(v);
	}
	return res.size()==n;
}

