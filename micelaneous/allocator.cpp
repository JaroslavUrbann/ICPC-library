// https://github.com/kth-competitive-programming/kactl/blob/main/content/various/SmallPtr.h

// ~ 470 MB, change accordingly
static char buf[450<<20];
void*operator new(size_t s){
	static size_t i=sizeof(buf);
	assert(s<i);
	return (void*)&buf[i-=s];
}
void operator delete(void*){}

// 32 bit ptr for saving memory
template<class T>
struct P{
	unsigned i;
	P(T*p=0):i(p?unsigned((char*)p-buf):0){}
	T&operator*()const{return*(T*)(buf+i);}
	T*operator->()const{return&**this;}
	T&operator[](int a)const{return(&**this)[a];}
	explicit operator bool()const{return i;};
};
