typedef __uint128_t u128;
typedef __int128_t s128;
typedef uint64_t u64;
typedef int64_t s64;
 
namespace MillerRabin{
	u64 pm(u64 a,u64 b,u64 m){return b?u128(b&1?a:1)*pm(a*u128(a)%m,b>>1,m)%m:1;}
	// n-1 == 2^r * d
	// a^(n-1) = 1 mod n (if n is prime, little fermat therem)
	// (a^d - 1) * (a^d + 1) * ... * (a^(2^(r-2) * d) + 1) * (a^(2^(r-1) * d) + 1) = 0 mod n
	// n is prime => n has to divide one of these factors <=> one of these factors is equal to 0 mod n
	bool iscomposite(u64 n,u64 a,u64 d,int r){
		u64 x=pm(a,d,n);
		if(x==1)return false;
		for(int i=0;i<r;++i,x=u128(x)*x%n)
			if(x==n-1)
				return false;
		return true;
	}
	bool isprime(u64 n){
		if(n<2)return false;
		int r=0;
		u64 d=n-1;
		while(!(d&1))d/=2,++r;
		for(int a:{2,3,5,7,11,13,17,19,23,29,31,37})
			if(iscomposite(n,a,d,r))
				return a==n;
		return true;
	}
}
