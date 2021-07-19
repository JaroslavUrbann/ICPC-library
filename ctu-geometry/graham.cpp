// returns convex hull with points in clockwise order
// use int cross if points are ints!!
// use > (2x) if you want to keep colinear points
vector<Pt>graham(vector<Pt>a){
	int n=a.size();
	vector<Pt>res(2*n+10);
	sort(a.begin(),a.end(),[](const Pt&a,const Pt&b){
		return a.x<b.x||(a.x==b.x&&a.y<b.y);
	});
	int p=0;
	for(int i=0;i<n;++i){
		while(p>=2&&cross(res[p-2],a[i],res[p-1])>=0)--p;
		res[p++]=a[i];
	}
	for(int i=n-2,pp=p+1;i>=0;--i){
		while(p>=pp&&cross(res[p-2],a[i],res[p-1])>=0)--p;
		res[p++]=a[i];
	}
	res.resize(p);
	if(res.size()>1)res.pop_back();
	return res;
}
