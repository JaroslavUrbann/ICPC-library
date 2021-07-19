// https://codeforces.com/blog/entry/68953
//
// O(n*log(n))
// you have a set of binary vectors and you want to get the base.

struct Base{
	static const int D=64;
	ll b[D];
	void add(ll v){
		for(int i=D-1;i>=0;--i)
			if(v&1ll<<i){
				if(!b[i]){b[i]=v;return;}
				v^=b[i];
			}
	}
};

// min(a[i],a[i]^v) is equivalent to xoring when v's most significant bit is present in a[i].
// 
// what I'm building here is a set of vectors where I only care about the biggest bit
// of each vector and all such bits are different.
// 
// all you need to prove is this:
// a[i] will be 0 => a[i] belongs to the vector space:
// 	xoring is the same as adding / subtracting one, so what you just did is a[i]+v1..=0, which is
// 	equal to v1..=a[i] (since -a[i] == a[i]).
// a[i] belongs to the vector space => will be 0.
// 	each vector in the base has a different msb, so when I xor a[i] and v, I have to because no other
// 	vector will remove that bit from a[i]. I also can't xor when it doesn't have the bit set, because again,
// 	no other vector going forward will remove it for me. So this algorithm is the only way to remove bits
// 	from a[i] and if it's in the base, it will be 0.
