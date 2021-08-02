// not really tested
template<class P>
bool isConvex(vector<P>a,bool strict){
	bool pos=false,neg=false,col=false;
	for(int i=0,n=a.size();i<n;++i){
		auto o=a[i].cross(a[(i+1)%n],a[(i+2)%n]);
		if(o>0)pos=true; // EPS
		else if(o<0)neg=true; // -EPS
		else col=true;
	}
	return (!strict||!col)&&(!pos||!neg);
}

