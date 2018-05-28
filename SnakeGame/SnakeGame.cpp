// SnakeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool g_GameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;			//For movement, fruit spawn location and score
int tailX[100], tailY[100];					//Using array to store the previoud node of the preceding piece of the snake
int nTail;

enum eDirection
{
	STOP = 0, LEFT, RIGHT, UP, DOWN
};

eDirection dir;

void Setup() {
	g_GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");

	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if(!print)
				cout << " ";
			}

			if (j == width - 1) {
				cout << "#";
			}
		}
		cout<<endl;
	}
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			g_GameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		return;
	}

	if (x > width || x < 0 || y > height || y<0) {
		g_GameOver = true;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x&&tailY[i] == y) {
			g_GameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();
	while (!g_GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}

    return 0;
}

