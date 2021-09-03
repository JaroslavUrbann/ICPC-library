// li-chao tree is in data structures
// convex hull trick
// if there is an obvious n^2 dp that can be represented as dp[i] = min(f(i,j))
// where f(i,j) is a linear function that is parametrized by j and has an input i.
// you can take these linear functions and do a convex hull and find the minimal
// value in logn. You can do this in nsqrt(n) by rebuilding the whole convex hull
// every sqrt(n) lines.
// points in this convex hull aren't the intersections, but the lines themselves,
// parametrized by [k,b] (y=kx+b).
// so you want to find the point with the smallest dot product with the point [x,1].
// if you consider all possible [x,1] (even negative x), you can easily see that
// the points with the smallest dot product will create a cup-like convex hull.
// Imagine normal vectors (vecs) that go from the pairs of points next to each
// other on the hull. The point with the smallest dot product will be the one
// which is adjacent to the normal vectors with the next smallest & the next biggest
// angle when sorted. It's because you can imagine a perpendicular
// line from the tip of [x,1]. All vectors on this line will have the same
// dot product with me, and this point will be the one to touch the line first
// if I move the line from the bottom to the top.

// this implementation requires that lines are added monotonically with k
// if you can't satisfy that property, use li chao tree.

typedef __int128 I;
// line is represented as a point
struct Line{I k=0,b=LLONG_MAX;};
Line operator-(const Line&a,const Line&b){return {a.k-b.k,a.b-b.b};}

// positive if b is to the left of a
I cross(const Line&a,const Line&b){return a.k*b.b-a.b*b.k;}

I f(const Line&l,I x){return l.k*x+l.b;}

// NOT REALLY TESTED FOR DECREASING / BOTH
// deque uses too much memory, if you're using this struct way too much,
// & you're poping/pushing from just one side, use vector instead
// if you push front, use the pushing back side and just change <= to >=
// and then also change cross(a,b)>0 to cross(a,b)<0
struct CHT{
	deque<Line>hull,vecs; // hull pts, normal vectors to the connections between points
	void addline(Line l){
		if(hull.size()){
			// adding from left to right
			if(auto [k,b]=hull.back();l.k>k||(l.k==k&&l.b<b)){
				while(vecs.size()&&cross(hull[hull.size()-2]-l,hull.back()-l)<=0){
					hull.pop_back();
					vecs.pop_back();
				}
				vecs.push_back({-(hull.back().b-l.b),hull.back().k-l.k});
				hull.push_back(l);
			}else if(auto [k,b]=hull.front();l.k<k||(l.k==k&&l.b<b)){
				while(vecs.size()&&cross(hull[1]-l,hull[0]-l)>=0){
					hull.pop_front();
					vecs.pop_front();
				}
				vecs.push_front({-(hull[0].b-l.b),hull[0].k-l.k});
				hull.push_front(l);
			}// don't put assert here, it can pass if (l.k==k&&l.b>=b) (useless line)
		}else hull.push_back(l);
	}
	I get(I x){assert(hull.size());
		// (imagine normal vectors sorted): if >, all vecs to the right are smaller.
		auto it=lower_bound(vecs.begin(),vecs.end(),Line{x,1},[&](const Line&a,const Line&b){
			return cross(a,b)<0;
		});
		return f(hull[it-vecs.begin()],x);
	}
};
