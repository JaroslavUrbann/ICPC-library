// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/MCMF.h
/**
 * Description: Minimum-cost maximum flow, assumes no negative cycles. 
 	* It is possible to choose negative edge costs such that the first 
 	* run of Dijkstra is slow, but this hasn't been an issue in the past. 
 	* Edge weights $\ge 0$ for every subsequent run. To get flow through 
 	* original edges, assign ID's during \texttt{ae}.
 * Time: Ignoring first run of Dijkstra, $O(FM\log M)$ 
 	* if caps are integers and $F$ is max flow.
 * Source: GeeksForGeeks
 	* https://courses.csail.mit.edu/6.854/06/scribe/s12-minCostFlowAlg.pdf
 	* running time is only pseudo-polynomial; see https://codeforces.com/blog/entry/70740
 	* https://en.wikipedia.org/wiki/Johnson%27s_algorithm (to get non-negative weights)
 	* https://codeforces.com/contest/1316/submission/72472865 
 		* mango_lassi, min cost circulation w/ capacity scaling
 * Verification: https://codeforces.com/contest/164/problem/C
 	* https://codeforces.com/contest/316/problem/C2
 		* TLEs, don't use priority queue
 */

/*
reweighting technique:
if you assign vertices some random numbers, and to each edge add p[u]-p[v],
then all paths s->t will have the same distance + p[t]-p[s] (all p[x] get added and then subtracted...)

if you set p[x] to bellman ford dist from 0, then p[u]-p[v] > -e (otherwise p[u]+e < p[v])

if you have negative cycles, you have to find them and fill them with flow.
if you always find & fill the cycle with lowest average cost, it should work in (N*M)^2*log(N*M)
source: trust me bro

otherwise, ssp won't create negative cycles on its own.

*/

// literally just spams dijkstra + johnson re-weighting
struct MCMF{
	using F=ll;using C=ll;
	struct E{int v,rid;F flo,cap;C w;};
	int n;
	vector<C>p,dist;
	vector<pair<int,int>>pre;
	vector<vector<E>>g;
	MCMF(int _n):n(_n),p(n),g(n),dist(n),pre(n){}
	// one directional by default, maybe change 0 to cap idk
	void ae(int u,int v,F cap,C w){
		g[u].push_back({v,(int)g[v].size(),0,cap,w});
		g[v].push_back({u,(int)g[u].size()-1,0,0,-w});
	}
	bool path(int s,int t){
		const C inf=numeric_limits<C>::max();
		dist.assign(n,inf);
		priority_queue<pair<C,int>,vector<pair<C,int>>,greater<pair<C,int>>>q;
		q.push({dist[s]=0,s});
		while(q.size()){
			auto[d,u]=q.top();q.pop();
			if(d>dist[u])continue;
			for(auto[v,rid,flo,cap,w]:g[u]){
				if(flo<cap&&dist[v]>d+w+p[u]-p[v]){
					q.push({dist[v]=d+w+p[u]-p[v],v});
					pre[v]={u,rid};
				}
			}
		} // if costs are doubles, add EPS so you don't have negative cycle
		return dist[t]!=inf;
	}
	pair<F,C>calc(int s,int t){
		// maybe replace with spfa?
		for(int _=0;_<n;++_)
			for(int u=0;u<n;++u)
				for(auto[v,rid,flo,cap,w]:g[u])
					if(cap)p[v]=min(p[v],p[u]+w);
		F totflow=0;C totcost=0;
		while(path(s,t)){
			// some distances might become negative, so you have to change potentials
			for(int i=0;i<n;++i)p[i]+=dist[i];
			F df=numeric_limits<F>::max();
			for(int v=t;v!=s;v=pre[v].first){
				auto[u,rid]=pre[v];
				E&e=g[u][g[v][rid].rid];
				df=min(df,e.cap-e.flo);
			}
			totflow+=df;totcost+=(p[t]-p[s])*df;
			for(int v=t;v!=s;v=pre[v].first){
				auto[u,rid]=pre[v];
				E&re=g[v][rid];re.flo-=df;
				g[u][re.rid].flo+=df;
			}
		}
		return {totflow,totcost};
	}
};
