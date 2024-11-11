/**
   @file Ordenación divide y vencerás
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

bool DyV (vector<int> v, int start, int end, bool found) {

	if (end>start && !found) {
		int m=(end+start)/2;
		found = DyV(v, start, m, found);
		if (!found)
			found = DyV(v, m+1, end, found);
	}
	else if (v[start]==start) {
		cout << start << endl;
		found =true;
		//exit(0);
	}
	
	return found;
}

int main(int argc, char*argv[]) {
	
	int n=atoi(argv[1]);
	int v[10];
	v[0]=1;
	v[1]=1;
	v[2]=5;
	v[3]=6;
	v[4]=7;
	
	DyV(v, 0, 4, false);
	
	for (int i=0; i<10; i++) {
		v[i]=4;
	}
	DyV(v, 0, 9, false);
}
