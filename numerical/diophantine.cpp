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
