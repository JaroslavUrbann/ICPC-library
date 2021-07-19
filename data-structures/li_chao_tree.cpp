// convex hull trick is in micelaneous
// lines are represented as points [k,b] (y=kx+b)
// li chao tree maintains a segment-like tree structure
// where you can add lines in logN and ask for the smallest f(x)
// in logN (x<10^6, otherwise it would need to be implicit?)

// each vertex holds a line
// invariant: when you go from root to leaf (your x), one of the lines will provide the minimum f(x)
// when inserting a new line (nl) to a vertex with an old line (ol), one of the lines
// will be dominant in the whole left or right half, keep that line in the vertex,
// and send the other one recursively in the competitive interval (the one with a possible intersection).
// worse line will keep going into the competitive interval which proves invariant by induction.

// line is represented as a point
struct Line{ll k=0,b=1e18;};

ll f(Line l,ll x){return l.k*x+l.b;}

struct LiChaoTree{
	int logN;
	vector<Line>lines;
	LiChaoTree(int n):logN(pow(2,ceil(log2(n)))),lines(2*logN){}
	void addline(Line nl){addline(nl,0,logN,1);}
	void addline(Line nl,int l,int r,int idx){
		int m=(l+r)/2;
		bool lft=f(nl,l)<f(lines[idx],l);
		bool mid=f(nl,m)<f(lines[idx],m);
		if(mid)swap(lines[idx],nl); // ol is now the lower one in mid
		if(r-l==1)return;
		if(lft!=mid)addline(nl,l,m,2*idx); // ol is also lower on the right
		else addline(nl,m,r,2*idx+1); // ol is also lower on the left
	}
	ll get(int x){return get(x,0,logN,1);}
	ll get(int x,int l,int r,int idx){
		int m=(l+r)/2;
		ll y=f(lines[idx],x);
		if(r-l==1)return y;
		if(x<m)return min(y,get(x,l,m,2*idx));
		return min(y,get(x,m,r,2*idx+1));
	}
};


