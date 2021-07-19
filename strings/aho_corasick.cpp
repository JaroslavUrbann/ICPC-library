// not really tested
// if you want the shortest matching word, reverse all input
struct AhoCorasick{
	static const int A=26,F='A'; // DON'T FORGET TO CHANGE F
	struct Node{
		int nxt[A],p,c,l=0,w=0,m=0; // parent, char, link, closest suffix with word, matches
		vector<int>ids; // ids of full strings ending here (||>1 iff there are 2 same strings)
		Node(int p=0,int c=0):p(p),c(c){memset(nxt,-1,sizeof(nxt));}
	};
	vector<Node>t={Node()};
	void add(string&s,int id){
		int u=0;
		for(auto c:s){
			c-=F;
			if(t[u].nxt[c]==-1){
				t[u].nxt[c]=t.size();
				t.push_back(Node(u,c));
			}
			u=t[u].nxt[c];
		}
		t[u].ids.push_back(id);
	}
	AhoCorasick(vector<string>&pats){
		for(int i=0;i<pats.size();++i)add(pats[i],i);
		queue<int>q;
		// at each step I know my link, but don't know my nxts
		for(q.push(0);q.size();q.pop()){
			int u=q.front();
			t[u].w=t[u].ids.size()?u:t[t[u].l].w;
			for(int i=0;i<A;++i){
				int&v=t[u].nxt[i],x=(!!u)*t[t[u].l].nxt[i]; // nxt node, -||- for my longest suffix
				if(~v)t[v].l=x,q.push(v);
				else v=x;
			}
		}
	}
};
