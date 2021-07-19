// berge's lemma:
// maximum matching <=> matching has no augmenting path
// =>: ez
// <=:
// let's have M and M' on the same graph where M' has more edges.
// G = M xor M', each vertex has max. degree of 2, so G's connected components have 1 of 3 forms:
// 1) isolated vertex
// 2) alternating path between edges from M and from M'
// 3) even length circle with alternating edges of M and M'
// because M' has more edges, there has to be at least 1 path where there are
// more edges from M', which is exactly the augmenting path for M which we were searching for.
// so you can just keep finding augmenting paths and you're good.

// konig's theorem:
// sz of minimum vertex cover on bipartite graph = sz of maximum matching
// let M be the matching, no vertex can cover more than 1 edge of M, so if we construct MVC of size |M|
// it will be optimal: U = unmatched vertices in L, Z = U u (vertices that connect to U via an alternating path)
// (matched vertex = has 1 edge matched)
// K = (L \ Z) u (R n Z)   // right side is: matched vertices - those that don't connect to any unmatched ones
// 												 // left side is: matched vertices - vertices that connect to R that connect to an unmatched node in L
// so you from the matchings, you keep in R those which connect to an unmatched node in L and you keep in L those
// who's right side you didn't keep
// this set covers all edges, let's look at all cases:
// 	if e's right node is matched and doesn't connect to any unmatched nodes, e's left node is matched (look up)
//  if e's right node is unmatched, it means that it doesn't lie in an alternating path, so it's in the left part

// maximum independent set = n - minimum vertex cover
// minimum weight vertex cover = max flow through bipartite graph, where mid edges are inf, and other edges are the cost of the node
// - extract by taking all nodes on the left that are capped, and then all on right that are capped & don't have an edge to a taken node.
// - didn't take any flow twice, no nodes are adjacent, 
// - doesn't work, how to extract???

// bipartite matching
// N * M (but on random graphs it's like very fast, easily passes random N=50,000,M=150,000)
// kunh's algorithm:
// just keep finding augmenting paths with dfs.
// when you find an augmenting path for a vertex, you don't need to check that vertex again,
// because once a vertex is saturated, then it won't be unsaturated by finding new augmenting paths.
// IF YOU GET TLE, TRY FORCING THE LEFT PART TO BE SMALLER
struct Kunh{
	int n,m;
	vector<int>vis,ma,mb;
	vector<vector<int>>g;
	bool dfs(int u){
		if(vis[u])return false;
		vis[u]=true;
		for(int i=0;i<2;++i)
			for(auto v:g[u])
				if((!i&&mb[v]==-1)||(i&&dfs(mb[v]))){
					mb[v]=u;
					ma[u]=v;
					return true;
				}
		return false;
	}
	int maxbpm(){
		int res=0;
		for(bool cont=true;cont;){
			cont=false;
			vis.assign(n,0);
			for(int i=0;i<n;++i)if(ma[i]==-1&&dfs(i)){
				cont=true;
				++res;
			}
		}
		return res;
	}
	// minimum vetex cover, matching has to be filled
	// using konigs theorem & its constructive proof from wikipedia
	// O(n)
	vector<int>minvc(){ // 0..n-1 if vertex is from L, n..n+m-1 otherwise
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
	Kunh(int n,int m):n(n),m(m),g(n),ma(n,-1),mb(m,-1){}
	void ae(int u,int v){g[u].push_back(v);}
};
