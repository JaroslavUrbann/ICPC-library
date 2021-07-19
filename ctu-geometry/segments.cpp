struct Segment{
	Pt a, b;
	// sort by first point and then by second point (whatever that means)
	bool operator<(const Segment &q){return a!=q.a ? a<q.a : b<q.b; }
	bool operator==(const Segment &q){return (a==q.a&&b==q.b)||(a==q.b&&b==q.a); }
	friend ostream &operator<<(ostream &os, const Segment &a){ 
		os<<"Segment : "<<a.a<<" -> "<<a.b; return os; 
	}
};

// doesn't work for collinear segments
bool Segment_Segment_intersect(Segment s, Segment t){
	// s is between ta and tb
	ld c1=cross(s.b-s.a, t.a-s.a), c2=cross(s.b-s.a, t.b-s.a);
	// t is between sa and sb
	ld c3=cross(t.b-t.a, s.a-t.a), c4=cross(t.b-t.a, s.b-t.a);
	return dcmp(c1)!=dcmp(c2) && dcmp(c3)!=dcmp(c4);
}

Pt Segment_Segment_intersect_Pt(Segment s, Segment t){
	Pt d1=s.b-s.a;
	Pt d2=t.b-t.a;
	ld tt=cross(t.a-s.a,d2)/cross(d1,d2);
	return s.a+d1*tt;
}

ld Segment_Pt_distance(Segment s, Pt p){
	Pt v1=s.b-s.a, v2=p-s.a, v3=p-s.b;
	if(dcmp(dot(v1, v2))<0) return norm(v2); // closer to a
	if(dcmp(dot(v1, v3))>0) return norm(v3); // closer to b
	return fabs(cross(v1, v2))/norm(v1); // closer to line
}

// didn't really work last time, watch out
// including endpoints, put <0 if endpoints not included
bool is_Pt_on_Segment(Pt p, Segment s){
	// is on line and is between points
	return dcmp(cross(s.a-p, s.b-p))==0 && dcmp(dot(s.a-p, s.b-p))<=0;
}

Pt Segment_Pt_closest_Pt(Segment s, Pt p){
	Pt v1=s.b-s.a, v2=p-s.a, v3=p-s.b;
	if(dcmp(dot(v1, v2))<0) return s.a; // closer to a
	if(dcmp(dot(v1, v3))>0) return s.b; // closer to b
	return Segment_Segment_intersect_Pt(s, {p,normal(s.b-s.a)+p}); // closer to line
}
