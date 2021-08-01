// https://seokjin2.tistory.com/35 참고

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include <conio.h>
using namespace std;

#define T_X 20
#define T_Y 40
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

enum state {
	EMPTY,
	WALL,
	BLOCK,
	TOUCH,
	FLOOR
};

void CursorView(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void gotoxy(int x, int y) {
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

//block 부모 클래스
class Block { 
protected:
	int shape[4][4][4]; // rotate x y
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
		y++;
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
};

class Block1 : public Block {
public:
	Block1() {
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				for (int l = 0; l < 4; l++)
					shape[i][j][l] = block1[i][j][l];
		}
	}
};

class Block2 : public Block {
public:
	Block2() {
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				for (int l = 0; l < 4; l++)
					shape[i][j][l] = block2[i][j][l];
		}

	}
};

class Block3 : public Block {
public:
	Block3() {
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				for (int l = 0; l < 4; l++)
					shape[i][j][l] = block3[i][j][l];
		}

	}
};

class Block4 : public Block {
public:
	Block4() {
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				for (int l = 0; l < 4; l++)
					shape[i][j][l] = block4[i][j][l];
		}

	}
};

class Block5 : public Block {
public:
	Block5() {
		x = T_X / 2;
		y = 1;
		rCnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				for (int l = 0; l < 4; l++)
					shape[i][j][l] = block5[i][j][l];
		}

	}
};

class backup {
public:
	static void updateBlock(Block* source, Block& backupBlock) {
		backupBlock.setX(source->getX()); 
		backupBlock.setY(source->getY()); 
		backupBlock.setRCnt(source->getRCnt());
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					backupBlock.setShape(i, j, k, source->getShape(i, j, k)); // 블럭의 모양 백업
				}
			}
		}
	}
	static void updateTable(vector<vector<int> >& source, vector<vector<int> >& backupTable) {
		backupTable.resize(source.size(), vector<int>(source.size())); // 기존 table의 크기만큼 2차원 벡터 크기 할당
		copy(source.begin(), source.end(), backupTable.begin());
	}
};

class game {
private:
	int x;
	int y;
	Block* block;
	vector<vector<int>> table;
public:
	game(int x, int y) {
		this->x = x;
		this->y = y;
		this->block = nullptr;
		for (int i = 0; i < y; i++) {
			vector<int> tmp;
			for (int j = 0; j < x; j++) {
				tmp.push_back(0);
			}
			table.push_back(tmp);
		}

		//틀 그리기
		for (int i = 0; i < x; i++) { //가로
			table[0][i] = WALL;
			table[y - 1][i] = WALL;
		}
		for (int i = 1; i < y - 1; i++) { //세로
			table[i][0] = WALL;
			table[i][x - 1] = WALL;
		}
		//바닥 감지
		for (int i = 1; i < x - 1; i++) {
			table[y - 1][i] = FLOOR;
		}
	}

	void drawTable() {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (table[i][j] == WALL || table[i][j] == FLOOR)
					cout << "▩";
				else if (table[i][j] == BLOCK || table[i][j] == TOUCH)
					cout << "■";
				else
					cout << "  ";
			}
			cout << '\n';
		}
	}

	void createBlock() {
		srand((unsigned int)time(NULL));
		int sel = rand() % 5 + 1;
		switch (sel) {
		case 1:
			block = new Block1();
			break;
		case 2:
			block = new Block2();
			break;
		case 3:
			block = new Block3();
			break;
		case 4:
			block = new Block4();
			break;
		case 5:
			block = new Block5();
			break;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int y = j + block->getY();
				int x = i + block->getX();
				table[y][x] = block->getShape(block->getRCnt(), i, j);
			}
		}
	}

	void move(int direct) {
		Block backupB;
		vector<vector<int>> backupT;
		backup::updateBlock(block, backupB);
		backup::updateTable(table, backupT);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + block->getY();
				int X = i + block->getX();
				if (table[Y][X] == BLOCK) //블럭 테이블에서 삭제
					table[Y][X] = EMPTY;
			}
		}
		if (direct == DOWN) {
			block->down();
		}
		else if (direct == LEFT) {
			block->left();
		}
		else if (direct == RIGHT) {
			block->right();
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + block->getY();
				int X = i + block->getX();
				int blockValue = block->getShape(block->getRCnt(), i, j);
				if (blockValue != BLOCK) continue;
				if (table[Y][X] == EMPTY) table[Y][X] = blockValue;
				else if (table[Y][X] == WALL) {
					copy(backupT.begin(), backupT.end(), table.begin());
					block->setX(backupB.getX());
					block->setY(backupB.getY());
					return;
				}
				else if (table[Y][X] == TOUCH) {
					copy(backupT.begin(), backupT.end(), table.begin());
					block->setX(backupB.getX());
					block->setY(backupB.getY());
					if (direct == DOWN) {
						build();
						createBlock();
					}
					return;
				}
				else if (table[Y][X] == FLOOR) {
					copy(backupT.begin(), backupT.end(), table.begin());
					block->setX(backupB.getX());
					block->setY(backupB.getY());
					if (direct == DOWN) {
						build();
						createBlock();
					}
					return;
				}
			}
		}
	}

	void build() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + block->getY();
				int X = i + block->getX();
				int blockValue = block->getShape(block->getRCnt(), i, j);
				if (blockValue != BLOCK) continue;
				table[Y][X] = TOUCH;
			}
		}
	}

	void rotateBlock() {
		Block backupB;
		vector<vector<int>> backupT;
		backup::updateBlock(block, backupB);
		backup::updateTable(table, backupT);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + block->getY();
				int X = i + block->getX();
				if (table[Y][X] == BLOCK) //블럭 테이블에서 삭제
					table[Y][X] = EMPTY;
			}
		}
		block->rotate();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int Y = j + block->getY();
				int X = i + block->getX();
				int blockValue = block->getShape(block->getRCnt(), i, j);
				if (blockValue != BLOCK) continue;
				else if (blockValue == EMPTY)
					table[Y][X] = blockValue;
				else if (table[Y][X] == WALL || table[Y][X] == TOUCH || table[Y][X] == FLOOR) {
					copy(backupT.begin(), backupT.end(), table.begin());
					block->setRCnt(backupB.getRCnt());
					return;
				}
			}
		}
	}

	
};

class menu {
public:
	menu() {
		getchar();
		system("cls");
	}
};

class start {
private:
	game* g;
public:
	start() {
		g = new game(T_X, T_Y);
		g->createBlock();
		g->drawTable();
		while (1) {
			int sel;
			if (_kbhit()) {
				sel = _getch();
				if (sel == 224) {
					sel = _getch();
					switch (sel) {
					case UP:
						g->rotateBlock();
						break;
					case DOWN:
						g->move(DOWN);
						break;
					case LEFT:
						g->move(LEFT);
						break;
					case RIGHT:
						g->move(RIGHT);
						break;
					default:
						break;
					}
				}
			}
			gotoxy(0, 0);
			g->drawTable();
		}
	}
};

int main() {
	CursorView(false);
	game g(T_X, T_Y);
	//menu();
	start();
	getchar();
	return 0;
}