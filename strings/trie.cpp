// not tested
struct Trie{
	const int D=2,F='0';
	int cmx=0;
	vector<vector<int>>nxt;
	Trie(){addnode();}
	int addnode(){
		nxt.push_back(vector<int>(D,-1));
		return cmx++;
	}
	void add(string&s){
		int u=0;
		for(auto c:s){
			c-=F;
			if(nxt[u][c]==-1)nxt[u][c]=addnode();
			u=nxt[u][c];
		}
	}
};

