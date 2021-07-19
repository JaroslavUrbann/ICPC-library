struct Cir {
    Pt s;
    ld r;
		// gets point a degrees counter-clock-wise from x+ on the Cir
    Pt point(ld a)const{ return {s.x+cos(a)*r, s.y+sin(a)*r}; }  
		ld area(){return M_PI*r*r;}
    bool operator<(const Cir &a){ return r<a.r; }  
		friend ostream &operator<<(ostream &os, const Cir &a){ 
			os<<"s: "<<a.s<<", r: "<<fixed<<setprecision(4)<<a.r; return os; 
		}
};

// distance from center - radius
ld Cir_Line_distance(Cir &a, Line &b){
    return max(Line_Pt_distance(b, a.s)-a.r, ld(0));
}

int Cir_Line_intersection(Cir a, Line b, Pt &p1, Pt &p2){
    if(Cir_Line_distance(a, b)>0)return 0; // don't touch
    Pt dv = Line_Pt_closest_Pt(b, a.s);
    ld d = norm(dv-a.s);
    ld h = sqrt(a.r*a.r-d*d); // wow
    Pt n = scale_to(b.b-b.a, h);
    p1 = dv+n;
    p2 = dv-n;
    return 1+!(eq(p1.x, p2.x) && eq(p1.y, p2.y)); // returns the number of intersections
}

int Cir_Cir_intersection(Cir c1, Cir c2, Pt &p1, Pt &p2){
    Pt dp = c2.s - c1.s;
    ld d = norm(dp);
    if (d > (c1.r + c2.r) && !eq(d,c1.r+c2.r)) return 0; // do not touch
    if (d < abs(c2.r - c1.r) && !eq(d,c2.r-c1.r)) return 0; // one inside the other
		// dist from c1 to point that line between 2 points will go through
    ld a = ((c1.r*c1.r) - (c2.r*c2.r) + (d*d)) / (2.0 * d) ;
    Pt pp = c1.s+dp*(a/d);
    ld h = sqrt(c1.r*c1.r - a*a); // dist from midpoint to intersection
    Pt r = {-dp.y * (h/d), dp.x * (h/d)};
    p1 = pp + r;
    p2 = pp - r;
    if(p1==p2) return 1; // touching
    return 2; // proper intersection
}
