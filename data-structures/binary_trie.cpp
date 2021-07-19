// trie is in strings
// not tested
struct BinaryTrie{
	const int D=2,M=63;
	int cmx=0;
	vector<vector<int>>nxt;
	BinaryTrie(){addnode();}
	int addnode(){
		nxt.push_back(vector<int>(2,-1));
		return cmx++;
	}
	void add(ll num){
		int u=0;
		for(int i=M-1;i>=0;--i){
			int lr=!!(num&1ll<<i);
			if(nxt[u][lr]==-1)nxt[u][lr]=addnode();
			u=nxt[u][lr];
		}
	}
	ll fmax(ll num){ // max xor
		ll u=0,res=0;
		for(int i=M-1;i>=0;--i){
			int lr=!(num&1ll<<i);
			if(nxt[u][lr]==-1){
				assert(~nxt[u][!lr]);
				u=nxt[u][!lr];
			}else{
				res|=1<<i;
				u=nxt[u][lr];
			}
		}
		return res;
	}
};
