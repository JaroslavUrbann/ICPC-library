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
// you can find modulo inverse with extended euclid:
// a*x + m*y = 1, when you modulo m, you get a*x = 1 mod m
// gcd(a,m) = 1, otherwise inverse doesn't exist
// or a fast way: (check if gcd(a,m)==1 before)
ll inv(ll a,ll m){return (a%=m)==1?1:m-ll(inv(m,a))*m/a;}
