/*
Montgomery multiplication

calculating a*b mod n is slow, bcs modulo is slow.
so you transfrom a and b to a space where multiplication is fast.

r = 2^m, st. gcd(r,n) == 1

x_m = x * r mod n

a_m * b_m = a * b * r^2 mod m
=>
need to be able to calculate x * r^-1 mod n fast
st. the result is already moduled by n.

=> montgomery reduction
calculate inverse by extended euclid: r * r^-1 + n * n' = 1
x * r^-1 = x * r * r^-1 / r = x * (1 - n * n') / r
= ((l * r - x * n') * n + x) / r mod n
by changing l, you can basically change the result of the multiplication x * n'
by a multiple of r, so you can also calculate it modulo r.
let's say q = - x * n' mod r,
q * n < r * n, so q * n / r will be very close to n, you can just check & subtract n once

so overall, you don't need to use %n and that's about it (/r is just a bit shift).

not as practical tbh
*/

typedef __uint128_t u128;
typedef __int128 s128;
typedef uint64_t u64;

struct u256{
	u128 lo,hi;
	static u128 HI(u128&x){return x>>64;}
	static u128 LO(u128&x){return u64(x);}
	static u256 mul(u128 x,u128 y){
		u128 t1=LO(x)*LO(y);
		u128 t2=HI(x)*LO(y)+HI(y)*LO(x);
		return{(t2<<64)+LO(t1),HI(x)*HI(y)+HI(t2)};
	}
	u256(u128 lo=0,u128 hi=0):lo(lo),hi(hi){}
};

struct Montgomery{
	u128 mod,inv,r2;
	Montgomery(u128 n=1):mod(n),inv(1),r2(-n%n){ // r-n == r mod n
		for(int i=0;i<7;++i)inv*=2-n*inv; // a*x = 1 mod 2^k  =>  a*x*(2-a*x) = 1 mod 2^2k
		for(int i=0;i<4;++i,r2-=r2>=mod?mod:0)r2<<=1; // r * 2^4
		for(int i=0;i<5;++i)r2=mul(r2,r2); // (r * 2^4)^2^5 = r * 2^128 (r^2 in normal space) mod n
	}
	u128 reduce(u256 x){
		u128 q=x.lo*inv;
		s128 a=x.hi+u256::mul(q,mod).hi;
		if(a<0)a+=mod;
		return a;
	}
	u128 init(u128 x){return mul(x,r2);}
	u128 mul(u128 a,u128 b){return reduce(u256::mul(a,b));} // a,b are in montgomery space
};
