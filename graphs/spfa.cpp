// the fact that there is a negative cycle doesn't mean that it is on the path s->t!
// O(m) on average, O(n*m) counter testcase (also slow when negative cycles are present)
// use normal bf for any negative cycle stuff
template<class T>
struct SPFA{
	int n;
	vector<vector<pair<int,int>>>g;
	vector<T>d;
	vector<int>len,inq;
	SPFA(int n):n(n),g(n){}
	void ae(int u,int v,T w){g[u].push_back({w,v});}
	void calc(int s){
		d.assign(n,numeric_limits<T>::max());
		len.assign(n,0);inq=len;
		queue<int>q;d[s]=0;q.push(s);inq[s]=true;
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
		return{1,d};
	}
};
