/*
Searching all occurrences of one string of length n in another string length m in O(n + m) time
Searching for the largest common substring of two strings of lengths n and m (n ≥ m) in O((n + m·log(n))·log(m)) and O(n·log(m)) time
Finding the lexicographically minimal cyclic shift of a string of length n in O(n·log(n)) time
Sorting of all cyclic shifts of a string of length n in lexicographic order in O(n·log(n)2) time
Finding the number of sub-palindromes of a string of length n in O(n·log(n)) time
The number of substrings of string of length n that are cyclic shifts of the another string length m in O((n + m)·log(n)) time
The number of suffixes of a string of length n, the infinite extension of which coincides with the infinite extension of the given string for O(n·log(n)) (extension is a duplicate string an infinite number of times).
Largest common prefix of two strings length n with swapping two chars in one of them O(n·log(n))

bloom filters (aka set for hashes):
just create a bitset and turn on kth bit if you want to insert a string with hash k
- can't remove strings
- there should be multiple hashes for one string (about m/n where m = table size, n = number of inserted strings)
*/

// https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/HashRange%20(14.2).h
const int MOD=INT_MAX;
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
/// H& operator+=(H& l, H r) { return l = l+r; }
/// H& operator-=(H& l, H r) { return l = l-r; }
/// H& operator*=(H& l, H r) { return l = l*r; }

vector<H>pows{{1,1}};
struct HashRange {
	string S; vector<H> cum{{}};
	void add(char c) { S += c; cum.push_back(base*cum.back()+makeH(c)); }
	void add(string s) { for(auto c:s) add(c); }
	void extend(int len) { while (pows.size() <= len) pows.push_back(base*pows.back()); }
	H hash(int l, int r) { extend(r-l); // inclusive, exclusive
		return cum[r]-pows[r-l]*cum[l]; }
	/**int lcp(HashRange& b) { return first_true([&](int x) { 
		return cum[x] != b.cum[x]; },0,min(sz(S),sz(b.S)))-1; }*/
};
