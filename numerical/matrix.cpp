using T=int;
using Mat=vector<vector<T>>;

Mat makeMat(int r,int c){return Mat(r,vector<T>(c));}
Mat makeId(int n){
	Mat m=makeMat(n,n);
	for(int i=0;i<n;++i)m[i][i]=1;
	return m;
}

Mat operator+=(Mat&a,const Mat&b){
	for(int i=0;i<a.size();++i)
		for(int j=0;j<a[0].size();++j)
			a[i][j]+=b[i][j];
	return a;
}

Mat operator+(Mat a,const Mat&b){return a+=b;}

Mat operator*(const Mat&a,const Mat&b){
	int x=a.size(),y=a[0].size(),z=b[0].size();
	Mat c=makeMat(x,z);
	for(int i=0;i<x;++i)
		for(int j=0;j<y;++j)
			for(int k=0;k<z;++k)
				c[i][k]=(c[i][k]+ll(a[i][j])*b[j][k])%mod;
	return c;
}

Mat operator^(Mat m,ll p){
	Mat res=makeId(m.size());
	for(;p;p>>=1,m=m*m)if(p&1)res=res*m;
	return res;
}

ostream&operator<<(ostream&os,const Mat&a){
	for(int i=0;i<a.size();++i,os<<endl)
		for(int j=0;j<a[0].size();++j)	
			os<<a[i][j]<<" ";
	return os;
}
