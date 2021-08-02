// https://vlecomte.github.io/cp-geo.pdf
// adding n integers with log(n)*EPS theoretical relative error bound
// (error of adding 2 integers is about (max(k1,k2)+1)*EPS, where k1*EPS is relative error of a[1])
// ONLY USE WITH NON-NEGATIVE INTEGERS
struct stableSum{
	int n=0;
	vector<ld>v,pref{0};
	void operator+=(ld a){
		for(int s=++n;s&1^1;s>>=1,v.pop_back(),pref.pop_back())a+=v.back();
		v.push_back(a);
		pref.push_back(pref.back()+1);
	}
	ld val(){return pref.back();}
};
