// https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
// https://alan20210202.github.io/2020/08/07/FWHT/
// https://raw.githubusercontent.com/IvanAli/logical-convolutions/main/logical_convolutions.pdf
// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastSubsetTransform.h
// instead of a+b=c in the exponent, it's a&b=c etc.
// if you want 2d, just use poly & a[i]*=b[i] would be normal fwhd

template<class T>
void fwhd(vector<T>&a,bool inv=0){
	#define mp(x,y) make_pair(x,y)
	for(int n=a.size(),step=1;step<n;step<<=1)
		for(int i=0;i<n;i+=step<<1)
			for(int j=i;j<i+step;++j){
				T&u=a[j],&v=a[j+step];tie(u,v)=
				// inv?mp(v-u,u):mp(v,u+v); // and
				// inv?mp(v,u-v):mp(u+v,u); // or
//				 mp(u+v,u-v); // xor
			}
//	 if(inv)for(T&x:a)x/=a.size(); // xor
}

// NEEDS TO BE 2^N (and include space for new items)
template<class T>
vector<T>conv(vector<T>a,vector<T>b){
	fwhd(a);fwhd(b);
	for(int i=0;i<a.size();++i)a[i]*=b[i];
	fwhd(a,1);return a;
}

