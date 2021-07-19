/*
Pollard rho

how to actually find collisions with birthday paradox?
you would have to keep all found numbers in a set and query whether you
already have a new given number. O(sqrt(N) * log2(sqrt(N)))

pollard rho chooses a random function N->N, and a starting point
and creates a sequence x, f(x), f(f(x)), ...
the sequence starts repeating in O(sqrt(N)) steps if the function is random enough

you can keep two pointers, one going forward by one step and the other one by two,
they will eventually meet when running on the loop, since they can't jump
over each other. O(sqrt(N))

pollard uses
f(x) = x*x + c mod p
where p is the first prime bigger than n

factorization:
notice that when p is a factor of n, ((x mod n) mod p) == (x mod p)
so you can do rho algorithm and instead of checking for xi == xj mod n,
you can check xi == xj mod p, where p is a divisor of n. (still useless)
but then that means that gcd(xi-xj,n) == p (or some multiple of p).
so if n has some non-trivial divisor p, then you'll find some xi,xj st. gc != 1
on average sooner than finding xi == xj. since p is at most sqrt(N), it will be in about N^(1/4)

*/

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

#define uid(a, b) uniform_int_distribution<u64>(a, b)(gen)
mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
 
struct Factorizer{
	static const int N=1000100;
	array<int,N>sieve;
	unordered_map<ll,int>primes;
	Factorizer(){
		for(int i=2;i<N;++i)if(!sieve[i])
			for(int j=i;j<N;j+=i)sieve[j]=i;
	}
	void rho(u64 n){
		if(n<N){fsmall(n);return;}
		if(MillerRabin::isprime(n)){++primes[n];return;}
		auto f=[&](u64 x,u64 c){return (u128(x)*x+c)%n;};
		auto diff=[&](u64 x,u64 y){return x>y?x-y:y-x;};
		u64 x=uid(1,n-1),y=x,d=1,c=uid(0,n-1);
		while(d==1){
			x=f(x,c);y=f(f(y,c),c);
			d=__gcd(diff(x,y),n);
		}
		rho(d);rho(n/d);
	}
	void fsmall(int n){for(;n>1;n/=sieve[n])++primes[sieve[n]];}
	void divsr(unordered_map<ll,int>::iterator it,ll num,vector<ll>&res){
		if(it==primes.end()){res.push_back(num);return;}
		for(int i=0;i<=it->second;++i,num*=it->first)divsr(next(it),num,res);
	}
	// all divisors of n (not sorted, about n^1/3)
	vector<ll>divs(u64 n){fact(n);
		vector<ll>res;divsr(primes.begin(),1,res);
		return res;
	}
	// (prime, exponent)
	unordered_map<ll,int>fact(u64 n){primes.clear();rho(n);return primes;}
};

/*
opencup saratov problem F
divisor propagation dp:
given number N, you have some cnt_d associated with each divisor d of N.
and you want to propagate cnt_d to each divisor of d, for each d.
how much is the final cnt_x, cnt_y, ...?

let's say cnt_N = 1, and cnt_else = 0. You want cnt_d = 1 for each d at the end.
first add 1 to all divisors where p1 is anything and p_other are full.
then add 1 to all divisors where p1 and p2 are anything and p_other are full.
*/
