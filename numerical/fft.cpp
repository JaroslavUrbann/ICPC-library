// if you can't figure it out, try reversing one of the polynoms
// visualization:
//      |0|1|2|3|4|5|6|7|8|
//  |5|4|3|2|1|0|
// move left vector by 1 position each time, take products of each pair and sum them together, you'll get the ith result
// https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FastFourierTransform.h
// todo: - how to do 2d fft? - fft for circular convolution

typedef double db;
typedef complex<dp> C;
 
void fft(vector<C>&a){
	int n=a.size(),L=31-__builtin_clz(n);
	static vector<complex<ld>>R(2, 1);
	static vector<C>rt(2, 1);
	for(static int k=2;k<n;k<<=1){
		R.resize(n);rt.resize(n);
		auto x=polar(1.L, acos(-1.L)/k);
		for(int i=k;i<2*k;++i)rt[i]=R[i]=i&1?R[i/2]*x:R[i/2];
	}
	vector<int>rev(n);
	for(int i=0;i<n;++i)rev[i]=(rev[i/2]|(i&1)<<L)/2;
	for(int i=0;i<n;++i)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int k=1;k<n;k*=2)
		for(int i=0;i<n;i+=2*k)
			for(int j=0;j<k;++j){
				C z=rt[j+k]*a[i+j+k];
				a[i+j+k]=a[i+j]-z;
				a[i+j]+=z;
			}
}
 
// round before converting to int
vector<db>conv(const vector<db>&a,const vector<db>&b){
	vector<db>res(a.size()+b.size()-1);
	int L=32-__builtin_clz(res.size()),n=1<<L;
	vector<C>in(n),out(n);
	copy(a.begin(),a.end(),in.begin());
	for(int i=0;i<b.size();++i)in[i].imag(b[i]);
	fft(in);
	for(C&x:in)x*=x;
	for(int i=0;i<n;++i)out[i]=in[-i&(n-1)]-conj(in[i]);
	fft(out);
	for(int i=0;i<res.size();++i)res[i]=imag(out[i])/(4*n);
	return res;
}
