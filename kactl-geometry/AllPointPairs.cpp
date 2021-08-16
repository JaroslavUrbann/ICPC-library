// was made for long longs
// goes through all pairs of points, calls f(int i,vec<P>&pts)
// pts will be sorted by their distance from the line going through pts[i],pts[i+1]
// collinear points will be to the left and to the right of i
template<class P,class F>
void allPointPairs(vector<P>pts,F f){
	int n=pts.size();
	vector<int>pos(n);
	iota(pos.begin(),pos.end(),0);
	sort(pts.begin(),pts.end());
	struct E{P v;int i,j;};
	vector<E>evs(n*(n-1)/2);
	for(int p=0,i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
			evs[p++]={pts[j]-pts[i],i,j};
	sort(evs.begin(),evs.end(),[&](E&a,E&b){
		if(!a.v.cross(b.v))return tie(pts[b.j],pts[b.i])<tie(pts[a.j],pts[a.i]);
		return a.v.cross(b.v)>0;
	});
	for(auto[v,i,j]:evs)f(pos[i],pts),swap(pts[pos[i]],pts[pos[j]]),swap(pos[i],pos[j]);
}

