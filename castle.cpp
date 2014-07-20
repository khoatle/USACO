/*
ID: khoatat2
LANG: C++
TASK: castle
*/


#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;

int M, N;
int** castle;

#define WEST  1
#define NORTH 2
#define EAST  4
#define SOUTH 8

#define NOT_VISITED 0


ifstream fin("castle.in");
ofstream fout("castle.out");

template<class T> string toString(T n){ostringstream ost;ost<<n;ost.flush();return ost.str();}

int num_rooms = 0;

int** visited;

map<int, int> size_of_room;

bool wall_west(int row, int col) {
	return castle[row][col] % 2 != 0;
}

bool wall_north(int row, int col) {
	int n = (castle[row][col] % 2 == 0)? castle[row][col] : castle[row][col] - 1;
	if(n >= 8) n -= 8;
	if(n >= 4) n -= 4;
	
	return n == 2;
}

bool wall_east(int row, int col) {
	int n = castle[row][col];
	if(n >= 8) n -= 8;
	return n >= 4 && n < 8;
}

bool wall_south(int row, int col) {
	return castle[row][col] >= 8;
}

int fill(int row, int col, int number) {
	if(row < 0 || row >= N || col < 0 || col >= M || visited[row][col])
		return 0;
	
	int cnt = 1;
	visited[row][col] = number;
	if(! wall_west(row, col)) 
		cnt += fill(row, col - 1, number);
	if(! wall_north(row, col)) 
		cnt += fill(row - 1, col, number);
	if(! wall_east(row, col))
		cnt += fill(row, col + 1, number);
	if(! wall_south(row, col))
		cnt += fill(row + 1, col, number);
	
	return cnt;
}

void test_wall(int row, int col) {
	string str = "";
	if(wall_west(row, col)) 
		str += "west "; 
	if(wall_north(row, col)) 
		str += "north ";
	if(wall_east(row, col))
		str += "east ";
	if(wall_south(row, col))
		str += "south ";
	cout << str << endl;
}

void fill_rooms() {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if(! visited[i][j]) {
				int s = size_of_room.size();
				int room_size = fill(i, j, s + 1);
				size_of_room[size_of_room.size() + 1] = room_size;
			}
		}
	}
}

void second_pass() {
	int m = -1;
	int prev_i, prev_j;
	string result = "";
	for(int j = 0; j < M; j++) {
		for(int i = 0; i < N; i++) {
			for(int dir_c = 0; dir_c < 2; dir_c++) {
				for(int dir_r = -1; dir_r < 1; dir_r++) {
					if(abs(dir_r + dir_c) == 1 && i + dir_r >= 0 && i + dir_r < N && j + dir_c >= 0 && j + dir_c < M) {
						if(visited[i + dir_r][j + dir_c] != visited[i][j]) {
							if(m <= size_of_room[visited[i + dir_r][j + dir_c]] + size_of_room[visited[i][j]]) {
								if(m == size_of_room[visited[i + dir_r][j + dir_c]] + size_of_room[visited[i][j]]) {
									if(j > prev_j) continue;
									else if(i == prev_i && dir_c == 1) continue;
								}
								
								m = size_of_room[visited[i + dir_r][j + dir_c]] + size_of_room[visited[i][j]];
								prev_i = i;
								prev_j = j;
								result = toString(i + 1) + " " + toString(j + 1);
								if(dir_r == 1) result += " S";
								else if(dir_r == -1) result += " N";
								else if(dir_c == 1) result += " E";
								else result += " W";
							}
						}
					}
				}
			}
		}
	}
	fout << m << endl;
	fout << result << endl;
	
}

int main() {
	
	fin >> M >> N;
	castle = new int*[N];
	for(int i = 0; i < N; i++)
		castle[i] = new int[M];
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			fin >> castle[i][j];
	visited = new int*[N];
	for(int i = 0; i < N; i++) {
		visited[i] = new int[M];
		for(int j = 0; j < M; j++)
			visited[i][j] = NOT_VISITED;
	}
	
	for(int i = 0; i < N; i++)
		memset(visited[i], 0, M * sizeof(int));

	// test_wall(0, 0);
	// cout << fill(0, 0) << endl;

	fill_rooms();
	fout << size_of_room.size() << endl;
	int m = -1;
	for(map<int, int>::iterator it = size_of_room.begin(); it != size_of_room.end(); it++)
		m = max(it->second, m);
	
	fout << m << endl;
	second_pass();
	// for(int i = 0 ; i < N; i++) {
	// 	for(int j = 0; j < M; j++) {
	// 		if(visited[i][j])
	// 			cout << "*";
	// 		else
	// 			cout << "-";
	// 	}
	// 	cout << endl;
	// }
	
	return 0;
}