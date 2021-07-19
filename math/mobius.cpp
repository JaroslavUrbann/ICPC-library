#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// https://www.youtube.com/watch?v=_noJI8UkTq8
// MOBIUS FUNCTION
// mu(x) = 0 pokud x je dělitelný čtvercem
// 			= 1 pokud x má sudej počet prvočísel
// 			= -1 pokud x má lichej počet prvočísel
// (subsety s 2 stejnejma prvkama ignoruju, -1 pokud lichej počet prvků, +1 pokud sudej)
// dělá to takovou prvočíslovou inkluzi-exkluzi, řekněme že mám čísla 1...N, potom tim že udělám mu(i) * F(dělitel=i)
// kde F vyřizuje všechny čísla s dělitelem i, tak dělám inkluzi-exkluzi, protože 1 zahrne všechny dělitele 1,
// 2 odebere všechny dělitele dvojky, 3 odebere všechny dělitele dvojky, 6 zahrne všechny dělitele 2*3 (byly odebraný dvakrát).
// zbydou jenom prvky který maj dělitele jenom 1?

vector<int>muarr(int n){
	vector<int>comp(n);
	vector<int>mu(n);
	for(int i=2;i<n;++i)
		if(!comp[i]){
			++mu[i];
			for(int j=2*i;j<n;j+=i){
				comp[j]=true;
				++mu[j];
			}
			for(ll j=i*ll(i);j<n;j+=i*i)mu[j]=1e9;
		}
	for(int i=0;i<n;++i)
		if(mu[i]>=1e9)mu[i]=0;
		else mu[i]=1-2*(mu[i]&1);
	return mu;
}

// MOBIUS INVERSION
// f(n) = suma přes všechny dělitele n, d: g(d)
// =>
// g(n) = suma přes všechny dělitele n, d: f(d) * mu(n/d)
// 
// ! funguje to i při iteraci přes všechny čísla, nejen dělitele: (i bez floor, pro racionální čísla)
// f(n) = sum k=1..n: g(floor(n/k))
// =>
// g(n) = sum k=1..n: f(floor(n/k))*mu(d)
// 
// 
// řešit úlohy s tim je potřeba tak, že mám nějakou kvantitu kterou chci spočítat a rozhodnu
// se ji spočítat pro každýho dělitele zvlášť. Udělám prostě rozklad podle dělitelů, předem
// si zafixuju, že ten můj objekt má něco jako d, kde d je dělitel velkýho objektu.
// (rotace pizzy => každá pizza má minimální rotaci, minimální rotace je vždy dělitelem)
// 
// co když mám:
// f(n) = sum d=1..n: g(n/d)
// kde f(x) jde vypočítat rychle, a chci vypočítat g(10^12)
// g(n) = f(n) - sum d=2..n: g(n/d)
// tohle mi dává rekurzivní vzorec jak spočítat g(n), využiju toho že f(n) je jednoduchý a g(n/d) má jen sqrt(n) unikátních hodnot
// (protože floor(n/k)/d == floor(n/k/d)))
// takže získám všechny hodnoty n/d pro d>sqrt(n) a postupně s nima evaluuju tu funkci, což mě bude stát (sqrt(1) + sqrt(2) + ... + sqrt(sqrt(n)))
// pak získám všechny hodnoty n/d pro d<sqrt(n) a evaluování mě bude stát (sqrt(n/1) + sqrt(n/2) + ... + sqrt(n/sqrt(n)))
// (zintegrováním získám že obojí stojí n^(3/4))
// v Mob to kombinuju se sítem a stojí to míň

// THIS EXTREMELY BAD AND NEEDS TO BE REWORKED
// solves g(n) in ~ n^(2/3) * log(n)^(1/3) (341M for 10^12)
// provided that f(n) is easy to compute, g(0) = f(0) = 0 and
// f(n) = sum(g(n/i)) for i=1...n
// f(n-1) == sum(g((n-1)/i))
// df(n) = f(n) - f(n-1) = sum(dg(n/d)) [s.t. d|n] = sum(g(d))
// dg(n) = df(n) - sum(dg(d)) [d!=n, d|n] // sieve this
// g(n) = f(n) - sum(g(n/i)) for i=2...n // recursion this
const ll u=10000000;
array<ll,u>gs;
// 1e10 in 18s with u = 1e7, eeeh
template<class T>
struct Mob{
	ll n;
	unordered_map<ll,T>gb;
	Mob(ll n):n(n){
		for(int i=1;i<u;++i){
			gs[i]+=f(i)-f(i-1);
			for(int j=2*i;j<u;j+=i)gs[j]-=gs[i];
			gs[i]+=gs[i-1];
		}
	}
	T g(ll x){ // == sum of phi(i) up to x
		if(x<u)return gs[x];
		if(gb.count(x))return gb[x];
		int sqx=max(2,int(sqrt(x)));
		ll res=f(x);
		for(int i=2;i<sqx;++i)res-=g(x/i);
		while(sqx<=x&&x/sqx==x/(sqx-1))res-=g(x/sqx++);
		for(ll v=1;v<=x/sqx;++v)res-=(x/v-x/(v+1))*g(v);
		return res;
	}
	T f(ll x){
		return x*(x+1)/2;
	}
};


signed main(){
	ll n=ll(1e10);
	Mob<ll>mob(n);
	cerr<<u<<endl;
	cerr<<mob.g(n)<<endl;
}


// dirichlet convolution: (pro funkce kde df je N)
// (f*g)(n) = sum over divs: f(d) * g(n/d)
// zobecnění:
// (f*g*h)(n) = sum over all a*b*c=n: f(a) * g(b) * h(c)
// 
// je komutativní, asociativní
// 
// pozn: normální konvoluce je
// sum 0..n: f(i)*g(n-i)
// 
// je to prostě function-wide operace a funkce tvoří grupu, identita je: f: [n=1]
// když f: 1, tak inverze týhle funkce je mu, tj platí:
// (f*mu)(n) = [n=1]
// takže mobius inverze jen říká že když:
// f = g * 1
// =>
// g = f * mu
// 
// (prohodim první 2 funkce a invertuju tu třetí, parametry jsou vždycky (n) = (n/d) * (d))
