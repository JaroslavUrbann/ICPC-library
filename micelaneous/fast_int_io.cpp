const int MAXSIZE = 1 << 18 | 1;
char buff[MAXSIZE], *p1, *p2;

inline int Gc() {
	return p1 == p2 &&
		(p2 = (p1 = buff) + fread(buff, 1, MAXSIZE, stdin), p1 == p2)? EOF: *p1++;
}
template<typename T> inline void read(T& x) {
	x = 0; int f = 0, ch = Gc();
	while (!isdigit(ch)) f |= ch == '-', ch = Gc();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = Gc();
	if (f) x = -x;
}

// watch out for int
inline void write(register int x){
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10^48);
}
