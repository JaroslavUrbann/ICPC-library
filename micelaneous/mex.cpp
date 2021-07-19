// *nim is in math*
// find mex with updates:
// maintain 2 sets, one with the current numbers and one with the complement.
// result is the minimum element from the complement set

// find mex in some range of an array:
// sort queries by r, answer queries with parameter l.
// create a support array where a_r[i]=x means that:
// when considerinng the first r elements, the last occurence of element i was at index x.
// initialize the segment tree with -1 and update it going left to right while answering queries offline.
// segment tree will tell you minimum element and we are searching for prefix for which holds that
// min of all elements on the prefix is >= l (therefore all elements are inside the subarray <l,r))
// if you want updates, then you do a 3D Mo, where time variable only moves forwards
// and block size is n^(2/3) (no idea how it works lmao)

// not tested
// maintains multiset that can answer mex queries for arbitrary x
template<class T>
struct Mex{
	map<T,int>in;
	set<T>out; // x \in out <=> x \notin in && x-1 \in in
	void add(T x){
		if(!in[x]++){
			out.erase(x);
			if(!in.count(x+1))out.insert(x+1);
		}
	}
	void del(T x){
		if(!--in[x]){
			out.erase(x+1);
			auto it=in.erase(in.find(x));
			if(it!=in.begin()&&prev(it)->first==x-1)out.insert(x);
		}
	}
	T mex(T x=0){return in.count(x)?*out.lower_bound(x):x;}
};
