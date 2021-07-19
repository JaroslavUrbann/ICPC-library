struct Line {
	Pt a, b;
	bool operator<(Line &l){ // sort by counter-clock-wise degree from the x+
		Pt v=b-a, w=l.b-l.a;
		return atan2(v.y, v.x) < atan2(w.y, w.x);
	}
	friend ostream &operator<<(ostream &os, const Line &a){ 
		os<<"Line: "<<a.a<<" -> "<<a.b; return os; 
	}
	bool operator=(Line other){
		return eq(cross(b-a, other.b-other.a), 0) && eq(oriented_angle(b-a), oriented_angle(other.b-other.a));
	}
};

// cross is area under line and point (forming a rhomboid) divided by line sz. is dist.
ld Line_Pt_distance(Line l, Pt p){ return abs(cross(p-l.a, l.b-l.a)/norm(l.b-l.a)); }

// check if lines have exactly 1 point of intersection
bool Line_Line_intersect(Line a,Line b){return cross(a.x-a.y,b.x-b.y);}

// both d1 and d2 are collinear to their lines
// a1 and a2 are starting points of the lines
// x is cross product
// p: res=a1+t*d1
// q: (res-a2)xd2=0
// (a1-t*d1-a2)xd2 => t=((a2-a1)xd2)/(d1xd2)
Pt Line_Line_intersection(Line p, Line q){
	Pt d1=p.b-p.a;
	Pt d2=q.b-q.a;
	ld t=cross(q.a-p.a,d2)/cross(d1,d2);
	return p.a+d1*t;
}

// creates line normal to a going through b
Pt Line_Pt_closest_Pt(Line a, Pt b){
	return Line_Line_intersection(a, {b, b+normal(a.b-a.a)});
}
