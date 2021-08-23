#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/CRT.h

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}

// please prove why is there a exactly one solution mod lcm(m1,m2..)

// linear congruence equation:
// ax = b mod m
// if a and m are coprime, then just find the inverse of a,
// and multiply it by b (can do so with extended euclid ax + bm = 1)
// if not coprime, then divide everything by gcd(a,m)
// if b isn't divisible by gcd(a,m), then there is no solution

// how to solve:
// x = a1 mod m1  (x = a1 + k1*m1)
// x = a2 mod m2  (x = a2 + k2*m2)
// just add them together:
// a1 + k1*m1 = a2 + k2*m2
// m1*k1 - m2*k2 = a2-a1  (solve it with extended euclid)
// then you can get x by substituting. all solutions are x = x0*lcm(m1,m2)

// for more congruences, just merge them one by one
// right now you have x = s mod lcm(m1,m2)

// if you get overflow you have to think about how lcm is computed etc.

// finds x,y for a*x + b*y = gcd(a,b)
// should work for negative numbers as well
ll gcd(ll a,ll b,ll&x,ll&y){
	if(!b){
		x=1;y=0;
		return a;
	}
	ll x1,y1;
	ll d=gcd(b,a%b,x1,y1);
	// I know: b*x1 + (a%b)*y1 = d
	// want to know: a*? + b*? = d
	// b*x1 + (a-(a/b)*b)*y1 = d
	// b*x1 + a*y1 - (a/b)*b*y1 = d
	// b*(x1-(a/b)*y1) + a*y1 = d
	x=y1;
	y=x1-(a/b)*y1;
	return d;
}

// if you want all solutions, then just add a*(b/g) - b*(a/g) = 0 (lcm)
// so add (b/g) to x and -(a/g) to y
bool solve_diophantine(ll a,ll b,ll c,ll&x,ll&y,ll&g){
	if(!a&&!b){
		x=y=g=0;
		return !c;
	}
	g=gcd(a,b,x,y);
	x*=c/g;
	y*=c/g;
	return !(c%g);
}

void normalize(ll&a,ll&m){a%=m;a=(a+m)%m;}

const int N=100;
ll a[N],m[N];

signed main(){
	int n;cin>>n;
	for(int i=0;i<n;++i)cin>>a[i]>>m[i],normalize(a[i],m[i]);
	ll res=a[0];
	ll lcm=m[0];
	// I have res = a[0] % m[0]
	for(int i=1;i<n;++i){
		// I have res = a[i] % m[i]
		// want to solve:
		// res + x*lcm = a[i] + y*m[i]
		// lcm*x - m[i]*y = a[i]-res
		ll a1=lcm,b1=-m[i],c1=a[i]-res,x,y,g;
		if(!solve_diophantine(a1,b1,c1,x,y,g)){cout<<"No solution\n";return 0;}
		res=a[i]+y*m[i];
		lcm=lcm*(m[i]/__gcd(lcm,m[i]));
		normalize(res,lcm);
	}
	cout<<res<<" "<<lcm<<endl;
}
