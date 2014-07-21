/*
ID: khoatat2
LANG: C++
TASK: hamming
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
using namespace std;

ifstream fin("hamming.in");
ofstream fout("hamming.out");

int ham(int a, int b) {
	int cnt = 0, tmp = a ^ b;
	while(tmp) {
		cnt += tmp & 1;
		tmp >>= 1;
	}
	return cnt;
}

void hamming(int N, int B, int D) {
	bool* chosen = new bool[1 << B];
	memset(chosen, 0x1, 1<<B);
	
	for(int i = 0; i < (1<<B); i++) {
		if(! chosen[i]) continue;
		
		for(int j = i + 1; j < (1<<B); j++) {
			if(! chosen[j]) continue;
			
			if(ham(i, j) < D)
				chosen[j] = false;
		}
	}
	
	int n = 0, index = 0, per_line = 0;
	while(n < N && index < (1<<B)) {
		if(chosen[index]) {
			if(per_line == 9) {
				fout << index << endl;
				per_line = -0x1;
			} else if(n == N-1)
				fout << index << endl;
			else
				fout << index << " ";
			per_line++;
			n++;
		}
		index++;
	}
}

int main() {
	int N, B, D;
	fin >> N >> B >> D;
		
	hamming(N, B, D);
	
	return 0;
}