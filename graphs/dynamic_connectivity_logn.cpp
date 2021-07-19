// you have a graph and queries where you add / delete edges / ask a question about connectivity
// you can ask questions that can be answered with a dsu.
// you do a divide and conquer and always add all edges that have been added before and won't be
// changed in the current segment in any way. You do this recursively and you'll magically get
// to a a leaf where you'll have a dsu with the exact edges that it should have.
// q * log^2(q) - it won't be better if you do it in q * log(q) (with graph compression and dfs)
// use unordered_map if you want to speed it up
struct DC{
	const int ASK=0,ADD=1,DEL=2;
	map<pair<int,int>,int>mp;
	vector<int>o,u,v,t,ans; // other occurence of that edge, u-v, type of query, just answers
	RollBackDSU dsu;
	DC(int n):dsu(n){}
	void addq(int tp,int a,int b){
		if(a>b)swap(a,b);
		o.push_back(0);
		if(tp!=ASK){
			if(mp.count({a,b})){
				o.back()=mp[{a,b}];
				o[o.back()]=o.size()-1;
				mp.erase({a,b});
			}else mp[{a,b}]=o.size()-1;
		}
		u.push_back(a);
		v.push_back(b);
		t.push_back(tp);
	}
	void solve(int l,int r){
		if(l+1==r){
			if(t[l]==ASK)ans.push_back(dsu.c);
			return;
		}
		int m=l+r>>1,now=dsu.time();
		// adds edges that that were added before <l,m) and removed in <m,r)
		for(int i=m;i<r;++i)if(t[i]!=ASK&&o[i]<l)dsu.uni(u[i],v[i]);
		solve(l,m);
		dsu.rollback(now);
		// adds edges that that were added in <l,m) and removed after <m,r)
		for(int i=l;i<m;++i)if(t[i]!=ASK&&o[i]>=r)dsu.uni(u[i],v[i]);
		solve(m,r);
		dsu.rollback(now);
	}
	vector<int>calc(){
		for(auto[p,idx]:mp){ // removes all edges so additions / removals are in pairs
			t.push_back(DEL);
			o[idx]=o.size();
			o.push_back(idx);
			u.push_back(p.first);
			v.push_back(p.second);
		}
		mp.clear();
		if(o.empty())return{};
		solve(0,o.size());
		return ans;
	}
};
