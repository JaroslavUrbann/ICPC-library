// https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/MinCostMaxFlow.h

#include<bits/extc++.h>
const ll inf=numeric_limits<ll>::max()/4;

// NO DOUBLE EDGES / NEGATIVE CYCLES ALLOWED
// not tested
// O(E^2)
struct MCMF{
	int n;
	vector<vector<int>>ed,red;
	vector<vector<ll>>cap,flow,cost;
	vector<int>seen;
	vector<ll>dist,pi;
	vector<pair<int,int>>par;
	MCMF(int n):n(n),ed(n),red(n),cap(n,vector<ll>(n)),flow(cap),cost(cap),seen(n),dist(n),pi(n),par(n){}
	void ae(int u,int v,ll c,ll w){ // capacity, cost
		cap[u][v]=c;
		cost[u][v]=w;
		ed[u].push_back(v);
		ed[v].push_back(u);
	}
	void path(int s){
		fill(seen.begin(),seen.end(),0);
		fill(dist.begin(),dist.end(),inf);
		dist[s]=0;ll di;
		__gnu_pbds::priority_queue<pair<ll,int>>q;
		vector<decltype(q)::point_iterator>its(n);
		q.push({0,s});
		auto relax=[&](int i,ll c,ll w,int dir){
			ll val=di-pi[i]+w;
			if(c&&val<dist[i]){
				dist[i]=val;
				par[i]={s,dir};
				if(its[i]==q.end())its[i]=q.push({-dist[i],i});
				else q.modify(its[i],{-dist[i],i});
			}
		};
		while(!q.empty()){
			s=q.top().second;q.pop();
			seen[s]=1;di=dist[s]+pi[s];
			for(int i:ed[s])if(!seen[i])relax(i,cap[s][i]-flow[s][i],cost[s][i],1);
			for(int i:red[s])if(!seen[i])relax(i,flow[i][s],-cost[i][s],0);
		}
		for(int i=0;i<n;++i)pi[i]=min(pi[i]+dist[i],inf);
	}
	pair<ll,ll>calc(int s,int t){
		ll totflow=0,totcost=0;
		while(path(s),seen[t]){
			ll fl=inf;
			for(int p,r,x=t;tie(p,r)=par[x],x!=s;x=p)fl=min(fl,r?cap[p][x]:flow[x][p]);
			totflow+=fl;
			for(int p,r,x=t;tie(p,r)=par[x],x!=s;x=p)
				if(r)flow[p][x]+=fl;
				else flow[x][p]-=fl;
		}
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				totcost+=cost[i][j]*flow[i][j];
		return {totflow,totcost};
	}
	// if there are negative costs, call this before maxflow
	void setpi(int s){
		fill(pi.begin(),pi.end(),inf);pi[s]=0;
		int it=n,ch=1;ll v;
		while(ch--&&it--)
			for(int i=0;i<n;++i)if(pi[i]!=inf)
				for(int to:ed[i])if(cap[i][to])
					if((v=pi[i]+cost[i][to])<pi[to])
						pi[to]=v,ch=1;
		assert(it>=0); // negative cost cycle found
	}
};

