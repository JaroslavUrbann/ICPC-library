// Regular Polygon
// r = cr = circumradius (distance from center to point)
// s = side
// a = apothem = distance from center to a side ( = incircle radius)
// p = perimeter
ld cr(ld s,int n){return s/2/sin(M_PI/n);}
ld cr(ld a,int n){return a/cos(M_PI/n);}
ld area(ld p,ld a){return p*a/2;}
ld area(ld s,int n){return n*s*s/tan(M_PI/n)/4;}
ld apothem(ld r,int n){return r*cos(M_PI/n);}
ld side(ld r,int n){return r*2*sin(M_PI/n);}

// Circle
// the angle that you're observing a circle from when you're d units away
ld angle(ld r,ld d){return 2*asin(r/d);}

// Cosine rule (2 sides of a triangle and angle between them => third side)
ld cosc(ld a,ld b,ld g){return sqrt(a*a+b*b-2*a*b*cos(g));}
ld cosg(ld a,ld b,ld c){return acos(max(ld(-1),min(ld(1),(a*a+b*b-c*c)/2/a/b)));}
