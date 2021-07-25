// https://seokjin2.tistory.com/35 참고

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <conio.h> //콘솔창
#include <windows.h> //커서위치  
using namespace std;

#define T_X 20
#define T_Y 38
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

void gotoxy(int x, int y) { //커서이동
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

const int block1[4][4][4] = { 
	{
		{0,0,2,0},
		{0,0,2,0},
		{0,0,2,0},
		{0,0,2,0}
	},
	{
		{0,0,0,0},
		{0,0,0,0},
		{2,2,2,2},
		{0,0,0,0}
	},
	{
		{0,0,2,0},
		{0,0,2,0},
		{0,0,2,0},
		{0,0,2,0}
	},
	{
		{0,0,0,0},
		{0,0,0,0},
		{2,2,2,2},
		{0,0,0,0}
	},
};

const int block2[4][4][4] = {
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,0},
		{0,2,2,0},
		{0,0,0,0}
	},
};

const int block3[4][4][4] = {
	{
		{0,2,0,0},
		{0,2,0,0},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,2,2,2},
		{0,2,0,0},
		{0,0,0,0}
	},
	{
		{0,2,2,0},
		{0,0,2,0},
		{0,0,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,2,0},
		{2,2,2,0},
		{0,0,0,0}
	},
};

const int block4[4][4][4] = {
	{
		{0,0,0,0},
		{0,0,2,2},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,2,0,0},
		{0,2,2,0},
		{0,0,2,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,2,2},
		{0,2,2,0},
		{0,0,0,0}
	},
	{
		{0,2,0,0},
		{0,2,2,0},
		{0,0,2,0},
		{0,0,0,0}
	},
};

const int block5[4][4][4] = {
	{
		{0,0,0,0},
		{0,0,2,0},
		{0,2,2,2},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,2,0},
		{0,0,2,2},
		{0,0,2,0}
	},
	{
		{0,0,0,0},
		{0,2,2,2},
		{0,0,2,0},
		{0,0,0,0}
	},
	{
		{0,0,2,0},
		{0,2,2,0},
		{0,0,2,0},
		{0,0,0,0}
	},
};

class Block {
protected:
	int shape[4][4][4];  //rotate y x
	int x;
	int y;
	int rCnt;
public:
	int getShape(int rCnt, int x, int y) {
		return shape[rCnt][y][x];
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	int getRCnt() {
		return rCnt;
	}

	void down() {
		y--;
	}
	void left() {
		x--;
	}
	void right() {
		x++;
	}
	void rotate() {
		rCnt = (rCnt + 1) % 4;
	}

	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setRCnt(int rCnt) {
		this->rCnt = rCnt;
	}
	void setShape(int rCnt, int x, int y, int value) {
		this->shape[rCnt][y][x] = value;
	}
}; //block 부모 클래스

class Block1 : public Block {
public:
	Block1() { //처음 생성자
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				for (int l = 0;l < 4;l++) {
					shape[i][j][l] = block1[i][j][l];
				}
			}
		}
	}
};

class Block2 : public Block {
public:
	Block2() { //처음 생성자
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				for (int l = 0;l < 4;l++) {
					shape[i][j][l] = block2[i][j][l];
				}
			}
		}
	}
};

class Block3 : public Block {
public:
	Block3() { //처음 생성자
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				for (int l = 0;l < 4;l++) {
					shape[i][j][l] = block3[i][j][l];
				}
			}
		}
	}
};

class Block4 : public Block {
public:
	Block4() { //처음 생성자
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				for (int l = 0;l < 4;l++) {
					shape[i][j][l] = block4[i][j][l];
				}
			}
		}
	}
};

class Block5 : public Block {
public:
	Block5() { //처음 생성자
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				for (int l = 0;l < 4;l++) {
					shape[i][j][l] = block5[i][j][l];
				}
			}
		}
	}
};

class game {
private:
	int x;
	int y;
	Block* block;
	vector<vector<int>> table;
public:
	game(int x, int y) { //생성자
		this->x = x;
		this->y = y;
		this->block = nullptr;
		for (int i = 0;i < y;i++) {
			vector<int> tmp;
			for (int j = 0;j < x;j++) {
				tmp.push_back(0);
			}
			table.push_back(tmp);
		}
		
		//틀 그리기
		for (int i = 0;i < x;i++) { //가로
			table[0][i] = 1;
			table[y - 1][i] = 1;
		}
		for (int i = 1;i < y - 1;i++) { //세로
			table[i][0] = 1;
			table[i][x - 1] = 1;
		}
		//바닥 감지
		for (int i = 1;i < x - 1;i++) {
			table[y - 1][i] = 4;
		}
	}


};




