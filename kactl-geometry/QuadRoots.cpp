// no catastrophic cancellation when calculating b-sqrt(disc)
int quadRoots(ld a,ld b,ld c,pair<ld,ld>&out){
	assert(a); // check with EPS?
	ld d=b*b-4*a*c;
	if(d<0)return 0; // change to -EPS ?
	ld sum=(b>=0)?-b-sqrt(d):-b+sqrt(d);
	out={sum/2/a,sum?2*c/sum:0};
	return 1+(d>0); // change to EPS?
}
