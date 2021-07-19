// for offline use only, all operations are O(n) otherwise.
// that's why there isn't even implemented adding nodes
// query gives you k closest points, should be in log(n)
// nothing more than 1e9 will work (squaring)
// not tested
template<typename T>
struct KDTree{
	struct Pt;
	struct Pt{
		Pt *l,*r;
		vector<T>vals;
	};
	int n=0,d;
	vector<Pt>pts;
	KDTree(vector<vector<T>>vals):d(vals[0].size()),pts(vals.size()){
		build(vals,0,vals.size(),0);
	}
	// n*log^2(n), use median of 10 random points otherwise
	Pt* build(vector<vector<T>>&vals,int l,int r,int dep){
		if(l==r)return 0;
		if(l+1==r)return &(pts[n++]={0,0,vals[l]});
		sort(vals.begin()+l,vals.begin()+r,[&](auto x,auto y){
			return x[dep%d]<y[dep%d];
		});
		int m=(l+r)/2;
		return &(pts[n++]={build(vals,l,m,d+1),build(vals,m+1,r,d+1),vals[m]});
	}
	ll dist(const vector<T>&a,const vector<T>&b){
		vector<T>tmp;
		transform(a.begin(),a.end(),b.begin(),back_inserter(tmp),[](T x,T y){
			return (x-y)*(x-y);
		});
		return accumulate(tmp.begin(),tmp.end(),0ll);
	}
	void getclosest(priority_queue<pair<ll,Pt*>>&q,Pt*root,vector<T>&want,int dep,int k){
		if(root==0)return;
		Pt*nxt=root->l,*other=root->r;
		if(root->vals[dep%d]<want[dep%d])swap(nxt,other);
		getclosest(q,nxt,want,dep+1,k);
		ll rootdist=dist(root->vals,want);
		if(q.size()<k||rootdist<q.top().first){
			if(q.size()==k)q.pop();
			q.push({rootdist,root});
		}
		ll linedist=root->vals[dep%d]-want[dep%d];
		if(q.size()<k||linedist*linedist<=q.top().first)getclosest(q,other,want,dep+1,k);
	}
	vector<vector<T>>query(vector<T>pt,int k){
		priority_queue<pair<ll,Pt*>>q;
		getclosest(q,&pts[n-1],pt,0,k);
		vector<vector<T>>res(q.size());
		for(int i=int(res.size())-1;i>=0;--i)res[i]=q.top().second->vals,q.pop();
		return res;
	}
};
