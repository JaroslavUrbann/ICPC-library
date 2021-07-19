// maybe rework to use id's instead of a set?
template<typename T>
struct CD{
	struct Node;
	struct Node{
		int id;
		set<Node*>e;
	};
	vector<Node>nodes;
	CD(int n):nodes(n){}
	void ae(int u,int v){
		nodes[u].e.insert(&nodes[v]);
		nodes[v].e.insert(&nodes[u]);
	}
	// gets size of graph u
	int getsz(Node*u,Node*p){
		int res=1;
		for(auto v:u->e)if(v!=p)res+=getsz(v,u);
		return res;
	}
	// finds a centroid
	int getc(Node*u,Node*p,Node**c,int n){
		int sz=1,mx=0;
		for(auto v:u->e)if(v!=p){
			int d=getc(v,u,c,n);
			mx=max(mx,d);
			sz+=d;
		}
		if(max(mx,n-sz)<=n/2)*c=u;
		return sz;
	}
	// solve problem for centroid
	T solvec(Node*c){ // c

	}
	// solves problem for a graph, call with &nodes[0]
	T solve(Node*u){
		Node*c;getc(u,u,&c,getsz(u,u));
		T res=solvec(c);
		for(auto v:c->e){
			v->e.erase(c);
			res+=solve(v);
		}
		return res;
	}
};

