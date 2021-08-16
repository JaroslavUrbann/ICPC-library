/*
bloom filters (aka set for hashes):
just create a bitset and turn on kth bit if you want to insert a string with hash k
- can't remove strings
- there should be multiple hashes for one string (about m/n where m = table size, n = number of inserted strings)
*/

// https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/HashRange%20(14.2).h
const int MOD=998244353;
using H = array<int,2>; // bases not too close to ends 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> BDIST(0.1*MOD,0.9*MOD);
const H base{BDIST(rng),BDIST(rng)};

H makeH(char c) { return {c,c}; }
/// const T ibase = {(int)inv(mi(base[0])),(int)inv(mi(base[1]))};
H operator+(H l, H r) { 
	for(int i=0;i<2;++i) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
	return l; }
H operator-(H l, H r) { 
	for(int i=0;i<2;++i) if ((l[i] -= r[i]) < 0) l[i] += MOD;
	return l; }
H operator*(H l, H r) { 
	for(int i=0;i<2;++i) l[i] = (ll)l[i]*r[i]%MOD;
	return l; }
H& operator+=(H& l, H r) { return l = l+r; }
H& operator-=(H& l, H r) { return l = l-r; }
H& operator*=(H& l, H r) { return l = l*r; }
ostream&operator<<(ostream&s,H h){return s<<"("<<h[0]<<", "<<h[1]<<")";}

H gpw(int i){
	static vector<H>pows{{1,1}};
	while(pows.size()<=i)pows.push_back(pows.back()*base);
	return pows[i];
}

// only reasonable sizes, otherwise use modpow instead of gpw
// was noticeably slower than doing concatenations manually
// (maybe it was keeping sz, didn't need it in that problem)
struct HR{
	int sz;H h;
	HR(char c=0):sz(!!c),h(makeH(c)){}
};
HR operator+(HR a,HR b){b.h+=gpw(b.sz)*a.h,b.sz+=a.sz;return b;}
HR&operator+=(HR&a,HR b){return a=a+b;}
bool operator==(HR a,HR b){return tie(a.sz,a.h)==tie(b.sz,b.h);}
ostream&operator<<(ostream&s,HR a){return s<<"size: "<<a.sz<<", hash: "<<a.h;}

struct HashRange {
	string S; vector<H> cum{{}};
	void add(char c) { S += c; cum.push_back(base*cum.back()+makeH(c)); }
	void add(string s) { for(auto c:s) add(c); }
	H hash(int l, int r) { return cum[r]-gpw(r-l)*cum[l]; }
	/**int lcp(HashRange& b) { return first_true([&](int x) { 
		return cum[x] != b.cum[x]; },0,min(sz(S),sz(b.S)))-1; }*/
};
