/*
sum of i, i^2, i^3
n(n+1)/2
n(n+1)(2n+1)/6
n^2(n+1)^2/4

maximum area of polygon with 4 sides:
sqrt((s-a)(s-b)(s-c)(s-d))

fibonacci:
k=(n+1)//2
if even: f(n) = (2*f(k-1)+f(k)) * f(k)
if odd: f(n) = f(k) * f(k) + f(k-1) * f(k-1)
*/
const ll mod=1e9+7;
unordered_map<ll,ll>fib;
// only log(n) for some reason
ll getfib(ll n){
	if(fib.count(n))return fib[n];
	if(n<2)return fib[n]=n;
	ll km=getfib((n+1)/2-1),k=getfib((n+1)/2);
	if(n&1)return fib[n]=(k*k+km*km)%mod;
	return fib[n]=(2*km+k)*k%mod;
}
/*
n = sum over all divisors of n: phi(d)

birthday paradox approximation:
p(n) = n^2 / 2 / H
p(n) = pravděpodobnost 2 stejnejch prvků při vyzkoušení n vstupů
H = počet různejch výstupů funkce f
=> n ~ sqrt(2 * H * p(n))
dosadim p(n) jako pravděpodobnost kolize kterou chci a vyjde mi maximální počet vstupů který můžu mít
pokud chci očekávanej počet prvků, než najdu kolizi, tak to je cca.
E(n) = 1.25*sqrt(H)

wilson's theorem:
p is prime iff: (p-1)! = -1 (mod p)

calculating inverse of all numbers in linear time
řekněme že chci spočítat inv[i], vim že:
m = a*i + b (mod m)
0 = a + b*inv[i] (mod m)
-a*inv[b] = inv[i] (mod m)
// b je by definition menší než i, takže ez
*/
inv[1] = 1;
for(int i = 2; i < m; ++i)
    inv[i] = m - (m/i) * inv[m%i] % m;
/*

number of ways to assign permutation to tree s.t. it becomes heap-like:
n!/(a*b*c*d...) // where n is the tree size and a,b,c,.. are subtree sizes
// easy recursive formula + a lot of cancelling of terms (start with binary heap tree)

Chicken McNugget Theorem
for all n,m:
all multiples of gcd(m,n) greater than lcm(m,n)-m-n are representable as x*m + y*n
for some positive integers x,y. (especially nice if n and m are coprime)

number of trees with n (labeled) vertices: n^(n-2) (prufer code)
number of binary search trees (unlabeled) (left vs right child matters): (2n)!/(n+1)!/n!


*/
