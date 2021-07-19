// euler totient function (phi)
// it's the number of numbers in {1..n} that are coprime with n
// a^phi(p) mod p = 1 (if a and p are coprime
// phi(p^k) = p^k - p^(k-1)

// sqrt(n)
// phi(x) = phi(p1^f) * phi(p2^g) ...
// phi(x) = (p1^f - p1^(f-1)) * (p2^g - p2^(g-1)) ...
// phi(x) = p1^f * (1 - 1/p1) * p2^f * (1 - 1/p2) ...
// phi(x) = n * (1 - 1/p1) * (1 - 1/p2) ...
ll phi(ll x){
	ll res=x;
	for(ll i=2;i*i<=x;++i)
		if(x%i==0){
			while(x%i==0)x/=i;
			res-=res/i;
		}
	if(x>1)res-=res/x;
	return res;
}

// phi(n) = n * (1 - 1/p1) * (1 - 1/p2) ...
// phiarr1(n) = n
// phiarr2(n) = n * (1 - 1/p1) = n - n/p1 = phiarr1(n) - phiarr1(n)/p1
// ...
vector<int>phiarr(int n){
	vector<int>phi(n+1);
	iota(phi.begin(),phi.end(),0);
	for(int i=2;i<=n;++i)
		if(phi[i]==i)
			for(int j=i;j<=n;j+=i)
				phi[j]-=phi[j]/i;
	return phi;
}

// formula:
// n = sum over all divisors of n: phi(d)
// 
// proof:
// 	consider the set {1,..,n}, each of these numbers has a gcd with n (d), which is a factor of n
// 	pro každý d je v tomhle array phi(n/d) čísel pro který platí, že gcd(num,n) == d
// 	(protože d chci vynásobit jen číslama 1...n/d a zároveň gcd(n,d*num) musí být jen d).
// 	Takže basically pro každýho dělitele n ve tvaru n/d jsem našel phi(d) prvků ze setu {1,..,n},
// 	který jsou všechny disjunktní (n/d je gcd(num,n)) a pokryjou všechny ty čísla (kažný num má nějaký gcd s n).
