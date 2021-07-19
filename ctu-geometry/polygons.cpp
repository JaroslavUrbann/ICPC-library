typedef vector<Pt> Polygon;

// is point inside? 1 yes, 0 no, -1 border
int is_point_in_polygon(Pt p, Polygon &poly){
    ll n=poly.size(), wn=0;
    for(int i=0;i<n;++i){
        Pt &p2 = poly[(i+1)%n];
        if(is_point_on_segment(p, {poly[i], p2})) return -1;//pt on the border
        int k = dcmp(cross(p2-poly[i], p-poly[i])); // pt is left/right of border?
        int d1 = dcmp(poly[i].y-p.y);
        int d2 = dcmp(p2.y-p.y);
        if(k>0 && d1<=0 && d2>0) wn++;
        if(k<0 && d2<=0 && d1>0) wn--;
    }
    return wn;// wn=1 point is inside, 0 outisde
}

int is_point_in_polygon_clock(Pt p, Polygon &poly){
    ll n=poly.size();
    ld sum = 0;
    for(int i=0; i<n; ++i){
        sum += angle(poly[i]-p, poly[(i+1)%poly.size()]-p);
    }
    return !eq(sum, 0);
}

//cutpoly
//the polygon is split into three polygons, which end up in result
//result[0] is polygon on the left side of the line
//result[1] is polygon on the right side of the line
//result[2] are points of the polygon on the line (may not work)
ld cut_convex(vector<Pt> &poly, const Line&l, vector<Pt> result[3]){
    ll n=poly.size();
    Pt a=l.a;
    Pt b=l.b;
    vector<Pt> points;
    Pt p1=a, p2=b;
    ll cur, pre;
    for(int i=0; i<3; ++i)result[i].clear();
    if(n==0) return 0;  
    ld tempvec;  
    tempvec=vec(a, b, poly[0]);  
    if(EQ(tempvec, 0)) cur=2; else if(tempvec>0) cur=0; else cur=1;  
    for(int i=0; i<n; ++i){
        pre=cur;
        tempvec=vec(a, b, poly[(i+1)%n]);  
        if(EQ(tempvec, 0)) cur=2; else if(tempvec>0) cur=0; else cur=1;  
        if(cur==pre){  
            result[cur].push_back(poly[(i+1)%n]);
        }else{  
            p1=poly[i];   
            p2=poly[(i+1)%n];  
            Pt p=lines_intersection({p1, p2}, {a, b});
            points.push_back(p);
            result[pre].push_back(p);
            result[cur].push_back(p);
            result[cur].push_back(poly[(i+1)%n]);
        }  
    }  
    return points.size()<2 ? 0 : norm(points.front()-points.back());
}
///cutpoly
//correctness proof by AC on Feng Shui of https://codeforces.com/gym/101650

//shrinkpoly
//move each line of the convex clockwise polygon inside by the given distance
void shrink_poly(vector<Pt> &p, ld distance){
    ll N=p.size();
    vector<Line> L(N);
    for(int i=0; i<N; ++i){ L[i].a=p[i]; L[i].b=p[(i+1)%N]; }
    for(int i=0; i<N; ++i){
        Pt v=L[i].b-L[i].a;
        Pt rot=rotate(v, -M_PI/2); // move line to the right
        rot=toLen(rot, distance-EPS);
        L[i].a=L[i].a+rot;
        L[i].b=L[i].b+rot;
    }
    vector<Pt> q[3];
    for(int i=0; i<N; ++i){
        cutConvex(p, L[i], q);
        p=q[1];
    }
}
///shrinkpoly

//equalpolys
//check if polygons are the same up to translation and rotation
bool equalPolys(vector<Pt> &a, vector<Pt> &b){
    // not sure if this works in all cases, but it got an AC
    vector<ll> aa(2*a.size());
    vector<ll> bb(2*b.size());
    for(int i=0; i<a.size(); ++i){
        Pt &q=a[(i+0)%a.size()];
        Pt &w=a[(i+1)%a.size()];
        Pt &e=a[(i+2)%a.size()];
        aa[2*i  ]=vec(w-q, e-w)*dot(w-q, e-w);
        aa[2*i+1]=dot(w-q, w-q);
    }
    for(int i=0; i<b.size(); ++i){
        Pt &q=b[(i+0)%b.size()];
        Pt &w=b[(i+1)%b.size()];
        Pt &e=b[(i+2)%b.size()];
        bb[2*i  ]=vec(w-q, e-w)*dot(w-q, e-w);
        bb[2*i+1]=dot(w-q, w-q);
    }
    aa.resize(aa.size()*2);
    for(int i=0; i<aa.size()/2; ++i)aa[i+aa.size()/2]=aa[i];
    //return a.size()==b.size() && EQ(area(a), area(b)) && kmp(bb, aa);
    return false;
}
///equalpolys

//area
ld area(vector<Pt> &p){
    ll N=p.size();
    ld s=vec(p[N-1], p[0]);
    for(int i=0; i<N-1; ++i) s+=vec(p[i], p[i+1]);
    return fabs(s/2);
}
///area

//centroid
Pt centroid(vector<Pt> &p) {
    ll N=p.size();
    ld area = 0, tmp;
    Pt res = {0, 0};
    for (int i=0; i<N; ++i) {
        Pt a = p[i], b = p[(i + 1) % N];
        tmp = vec(a, b);
        area += tmp;
        res = res + (a + b) * tmp;
    }
    area /= 2;
    res = res / (area * 6);
    return res;
}
///centroid

// todo investigate
//The vector rotates theta clockwise to get the direction of the vector b
ld getRerotateAngle(Pt a, Pt b){
    ld tempa=angle(a, {1, 0});
    if(a.y<0) tempa=2*M_PI-tempa;
    ld tempb=angle(b, {1, 0});
    if(b.y<0) tempb=2*M_PI-tempb;
    return ((tempa-tempb)>0) ? tempa-tempb : tempa-tempb+2*M_PI;
}

double rotating_calipers(Pt *ch, int n) {
    int q=1;
    ld ans=0;
    ch[n]=ch[0];
    for(int p=0; p<n; ++p){
        Pt v=ch[p]-ch[p+1];
        while(vec(ch[q+1]-ch[p+1], v)>vec(ch[q]-ch[p+1], v))
            q=(q+1)%n;
        ans=max(ans, max(norm(ch[p]-ch[q]), norm(ch[p+1]-ch[q+1])));
    }
    return ans;
}



