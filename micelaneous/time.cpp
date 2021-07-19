#include<bits/stdc++.h>
using namespace std;
using namespace chrono;

steady_clock::time_point bt,et;

signed main(){
	bt=steady_clock::now();
	while(1){
		et = steady_clock::now();
		// 1 second (account for writing output + length of one cycle)
		if(duration_cast<milliseconds>(et-bt).count()>800)break;
	}
}
