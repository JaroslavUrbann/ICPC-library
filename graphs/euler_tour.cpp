// hamiltonian path is a path where each vertex is visited exactly once
// it is np complete

// euler (path / trail) = path which visits every edge exactly once
// not every graph has an eulerian path
// it also depends on which node you start on
// for it to exists, it has to hold that starting vertex has outdegree = indegree + 1
// and ending vertex has indegree = outdegree + 1
// and every other vertex has indegree = outdegree

// euler (tour / closed walk / circut / cycle) = same as path but you start & end at the same node
// you can begin it anywhere if know the graph has it (makes sense)
// if a graph has a eulerian tour, then it is called eulerian
// graph is eulerian iff every vertex has an even degree
// graph has to be connected as well, duh

// if there are 2*k vertices with odd degree, then there exists a covering of the graph
// with k paths. (add k edges to create a matching between these 2*k vertices, there exists
// an euler tour, by removing the edges one by one, it'll split into k paths)

// a subgraph is called eulerian, if each node has an even degree
// the space of all eulerian subgraphs is a vector space (1/0 for each edge)
// (multiplications is ez, addition works since: x + y == 0, for each u:
// a = edges coming from u in x, b = edges coming from u in y, c = common for both
// new degree of u is a-c + b-c = a+b - 2*c (even again => belongs to vector space))
// you can find the base by creating a spanning tree and creating a vector for each
// edge that isn't part of the spanning tree (edge + path in the spanning tree between the 2 nodes)
// obvsly linearly independent. All edges not in the spanning tree obvsly get covered,
// other edges are in the spanning tree, and since x (addition of base) + y (the subspace)
// belongs to vector space, there can't be any edges left from the spanning tree, so x + y == 0 == x - y.
// dim of the space is E - V + C where C is the number of components.

// Hierholzer's algorithm, works in O(E):
// just run dfs, it will get stuck in the first node, because all nodes have an even degree.
// to ensure that you visit all edges, just run the dfs again from some nodes that don't
// have all their outgoing edges visited.
// so essentially you're just doing basic dfs.

// check the requirements, don't rely on dfs to tell you if the graph is eulerian
// bad implementation, should use id system for O(1) deletion of edges.
// pay attention to multiple edges / directedness of the graph etc.
set<pair<int,int>>vis;
const int N=100100;
int n,m;
vector<int>g[N];
vector<int>res;

void dfs(int u){
	while(g[u].size()){
		while(g[u].size()&&vis.count({u,g[u].back()}))g[u].pop_back();
		if(g[u].size()){
			vis.insert({u,g[u].back()});
			vis.insert({g[u].back(),u});
			dfs(g[u].back());
		}
	}
	res.push_back(u);
}
