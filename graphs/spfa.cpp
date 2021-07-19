// the fact that there is a negative cycle doesn't mean that it is on the path s->t!
// O(m) on average, O(n*m) counter testcase (also slow when negative cycles are present)
// use normal bf for any negative cycle stuff
pair<bool,vector<ll>>spfa(vector<vector<pair<int,int>>>&g,int s){
	int n=g.size();
	vector<ll>d(n,LLONG_MAX);
	vector<int>len(n),inq(n);
	queue<int>q;
	d[s]=0;q.push(s);inq[s]=true;
	while(q.size()){
		int u=q.front();q.pop();
		inq[u]=false;
		for(auto[w,v]:g[u])if(d[u]+w<d[v]){
			d[v]=d[u]+w;
			len[v]=len[u]+1;
			if(len[v]==n)return{0,{}};
			if(!inq[v])q.push(v);
			inq[v]=true;
		}
	}
	return {1,d};
}
