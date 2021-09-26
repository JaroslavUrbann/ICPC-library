const ld EPS=1e-6;
bool eq(ld a, ld b) { return fabs(a-b) <= fabs(a+b) * EPS || fabs(a-b) < EPS; }

ld clmp(ld a,ld mn,ld mx){return min(mx,max(mn,a));}

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
//	bool operator==(P p) const { eq(x,p.x) && eq(y,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T dot(P a, P b) const { return (a-*this).dot(b-*this); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi], positive above y=0
	ld angle() const { return atan2(y, x); }
	// angle of two points when looking from this point [0, pi] (not tested)
	ld angle(P v,P w){return acos(clmp((*this).dot(v,w)/(v-*this).dist()/(w-*this).dist(),ld(-1.),ld(1.)));}
	// counter-clockwise angle from b to c when looking from a(not tested)
	ld orientedAngle(P b,P c){return (*this).cross(b,c)>=0?(*this).angle(b,c):2*M_PI-(*this).angle(b,c);}
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
	friend istream&operator>>(istream&is,P&p){return is>>p.x>>p.y;}
};
typedef Point<ll>Pl;
typedef Point<ld>Pd;
