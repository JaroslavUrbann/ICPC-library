// mo's algorithm sorts queries by block of left idx and then by right idx
// and then adds/removes items to fill in the query range each time
// if you consider only l:
// each l goes at most sqrt(n) for each query (+n in total) so that is q*sqrt(n)
// if you consider only r:
// each r goes from left to right for each sqrt block, so that is n*sqrt(n)
// so in total (q+n)*sqrt(n)*O(add,remove)
// you can also play around with bsz
// if you timeout, it's because you're using log operations, do everything to get rid of them
// mo with updates O(n^1.666):
// normal mo, but the time moves from 0 to T (at time t you do all updates from time t)

struct query{int l,r,idx;}; //inclusive,exclusive

template<typename T>
struct Mo{
	const int n,bsz; // block size
	vector<T>a;
	Mo(vector<T>&a):n(a.size()),bsz(sqrt(n)),a(a){}
	void add(int idx){

	}
	void remove(int idx){

	}
	T get(){

	}
	vector<T>solve(vector<query>&queries){
		vector<T>res(queries.size());
		sort(queries.begin(),queries.end(),[&](query&a,query&b){
			if(a.l/bsz!=b.l/bsz)return a.l/bsz<b.l/bsz;	
			return (a.l/bsz)&1?a.r>b.r:a.r<b.r;
		});
		int l=0,r=0; //inclusive,exclusive
		for(auto q:queries){
			while(r<q.r)add(r++);
			while(q.l<l)add(--l);
			while(q.r<r)remove(--r);
			while(l<q.l)remove(l++);
			res[q.idx]=get();
		}
		return res;
	}
};
