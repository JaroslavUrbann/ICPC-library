const ld EPS=1e-6;

int dcmp(ld x){return abs(x)<EPS?0:(x<0?-1:1);}

// absolute comparison at the end makes the equality easier
bool eq(ld a, ld b) { return abs(a-b) <= abs(a+b) * EPS || abs(a-b) < EPS; }

struct Pt{
	ld x, y;
	// or return x < p.x-EPS || eq(x, p.x) && y < p.y-EPS);
	Pt operator+(const Pt &p){ return{x+p.x, y+p.y}; }
	Pt operator-(const Pt &p){ return{x-p.x, y-p.y}; }
	Pt operator-(){ return{-x, -y}; }
	Pt operator*(ld d){ return {x*d, y*d}; }
	Pt operator/(ld d){ return {x/d, y/d}; }
	friend ostream &operator<<(ostream &os, const Pt &a){ os<<'['<<a.x<<", "<<a.y<<']'; return os; }
	friend istream &operator>>(istream &is, Pt &a){ is>>a.x>>a.y; return is; }
};
bool operator==(const Pt &a, const Pt &b){ return eq(a.x, b.x) && eq(a.y, b.y); }
bool operator!=(const Pt &a, const Pt &b){ return !(a==b); }
// for sorting (has to be really low-cost)
bool operator<(const Pt &a,const Pt &b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
// for casual usage
//bool operator<(const Pt &a,const Pt &b){ 
//	if(a==b)return false;
//	if(eq(a.x,b.x))return a.y<b.y;
//	return a.x<b.x;
//}

ld triangle_area(Pt a,Pt b,Pt c){return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);}
bool collinear(Pt a,Pt b,Pt c){return !dcmp(triangle_area(a,b,c));}

struct pair_hash {
    inline std::size_t operator()(const Pt & v) const {
        return (ll(v.x)*31+v.y)%ll(1e9+7);
    }
};


ld cross(Pt a, Pt b){ return b.x*a.y-b.y*a.x; } // is a to the left of b? (+1)
ld cross(Pt a, Pt b, Pt c){ return cross(b-a, c-a); } // is b to the left of c? (starting from a) (+1)

// do a and b point in the same direction? (+1)
// are they perpendicular? (0)
ld dot(Pt a, Pt b){ return a.x*b.x+a.y*b.y; }

// size of a
ld norm(Pt a){ return hypot(a.x, a.y); }

// dot product je projekce jednoho vektoru na druhej, která je vynásobená délkou druhýho
// když si druhej vektor představíš jako x=1,y=0, tak je to čistě arccos(prilehla/prepona)
// /norm(b) z toho udělá čistě projekci a pak to je prilehla(=projekce)/prepona(=norm(a))
// outputs values in <0,pi>, so always positive and < 180 degrees
ld angle(Pt a, Pt b){ return acos(dot(a, b)/norm(a)/norm(b)); }

// angle from x+ axis ([1,1]=45deg, [1,-1]=-45deg)
// sorts quadrants: 3,4,1,2 (ld,rd,ru,lu)
ld oriented_angle(Pt v){ return atan2(v.y, v.x); }

// if a is x+ axis, above x is (0,180), below is (0,-180), 0 is when very close to x+
// imagine stepping from a to b on a unit circe, going right = 90, left = -90
ld oriented_angle(Pt a,Pt b){return atan2(cross(b,a),dot(b,a));}

// make the vector length something while keeping proportions
Pt scale_to(Pt a, ld res){ return a*res/norm(a); }

// counter-clock-wise rotation
Pt rotate(Pt a, ld rad){ return {a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad)}; }

ld Pt_Pt_distance(Pt a, Pt b){ return norm(b-a); }

// polar coordinates have (length of vector, counter-clock-wise angle from x+)
Pt fromPolar(ld len, ld ang){ return {len*cos(ang), len*sin(ang)}; }

// 360deg = 2pi (in rad)
ld d2r(ld deg){ return deg/180*M_PI; }
ld r2d(ld deg){ return deg*180/M_PI; }

// perpendicular vector of unit length
Pt normal(Pt a){ ld n=norm(a); return {-a.y/n, a.x/n}; }
