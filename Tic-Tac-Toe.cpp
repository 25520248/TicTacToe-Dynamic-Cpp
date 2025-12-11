/*
* Project: Console Gomoku (Caro) with AI Bot
* Author: Công Danh
* Date: Dec 2025
* Language: C++
* Description: A dynamic board Gomoku game using Heuristic algorithm.
*/
#include<iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
using namespace std;
struct moveforbot {
	int length;
	int blocked;
	moveforbot operator+(const moveforbot& other) {
		moveforbot result{ 0,0 };
		result.length = length + other.length;
		result.blocked = blocked + other.blocked;
		return result;
	}
	bool operator<(const moveforbot& other) {
		if (blocked != other.blocked)return blocked > other.blocked;
		else return length < other.length;
	}
};
void soRt_moveforbot(moveforbot a[], int n) {
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] < a[j])swap(a[j], a[i]);
		}
	}
}
void firstmove(char& turn) {
	int move = rand() % 2;
	turn = (move ? 'X' : 'O');
}
char** createboard(int n) {
	char** board = new char* [n];
	for (int i = 0; i < n; i++) {
		board[i] = new char[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			board[i][j] = ' ';
		}
	}
	return board;
}
void sizeofboard(int& n) {
	do
	{
		cout << "Choose the size of the board (3-20)\n";
		cin >> n;
		if (n >= 3 && n <= 20)break;
		else cout << "Invalid size!\n";
	} while (1);
}
void deleteboard(char** board, int n) {
	for (int i = 0; i < n; i++) {
		delete[] board[i];
	}
	delete[] board;
}
void thecurrentboard(char** board, int n) {
	cout << setw(3) << ' ';
	for (int i = 1; i <= n; i++) {
		if (i < 10 && i != 0)cout << "  " << i << ' ';
		else if (i >= 10)cout << " " << i << ' ';
	}
	cout << endl << setw(3) << ' ';
	for (int i = 0; i < n; i++) {
		cout << "+---";
	}
	cout << "+\n";
	for (int i = 0; i < n; i++)
	{
		cout << setw(3) << i + 1;
		for (int j = 0; j < n; j++)
		{
			cout << "| " << board[i][j] << ' ';
		}
		cout << "|\n" << setw(3) << ' ';
		for (int j = 0; j < n; j++) {
			cout << "+---";
		}
		cout << '+' << endl;
	}
}
struct Move {
	char symbol;
	int row;
	int column;
};
void movehistory(int count, const Move a[]) {
	int i = ((count >= 10) ? count - 10 : 0);
	for (; i < count; i++) {
		cout << a[i].symbol << ' ' << a[i].row << ' ' << a[i].column << endl;
	}
}
int symbolcounting(int deltarow, int deltacol, char** board, const Move a, int n) {
	int count = 0, i = a.row, j = a.column, k = 1;
	while (k < 5)
	{
		i += deltarow;
		j += deltacol;
		if (i > n || i < 1 || j < 1 || j>n || board[i - 1][j - 1] != a.symbol)return count;
		else if (board[i - 1][j - 1] == a.symbol)count++;
		++k;
	}
	return count;
}
int checkwin(char** board, int n, const Move a[], int movecount) {
	int m, count = 1;
	if (n >= 5)m = 5;
	else m = n;
	if (movecount == 0)return 0;
	if ((symbolcounting(0, -1, board, a[movecount - 1], n) + symbolcounting(0, 1, board, a[movecount - 1], n) + 1 >= m) ||
		(symbolcounting(1, 0, board, a[movecount - 1], n) + symbolcounting(-1, 0, board, a[movecount - 1], n) + 1 >= m) ||
		(symbolcounting(-1, 1, board, a[movecount - 1], n) + symbolcounting(1, -1, board, a[movecount - 1], n) + 1 >= m) ||
		(symbolcounting(1, 1, board, a[movecount - 1], n) + symbolcounting(-1, -1, board, a[movecount - 1], n) + 1 >= m))
		return 1;
	else return 0;
}
int playerinteraction() {
	char respond;
	cout << "R:Replay\nM:Menu\nB:Back to game\n";

	while (1)
	{
		cin >> respond;
		if (respond == 'B' || respond == 'b') return 0;
		else if (respond == 'M' || respond == 'm')return 1;
		else if (respond == 'R' || respond == 'r')return 2;
		else continue;
	}
}
int entermove(char** board, char& turn, int n, Move a[], int count) {
	int column = 0, row = 0;
	while (1) {
		cin >> row;
		if (column == -1 || row == -1) {
			int l = playerinteraction();
			if (l == 0) {
				system("cls");
				thecurrentboard(board, n);
				continue;
			}
			else return l;
		}
		cin >> column;
		if (row > n || column > n || row <= 0 || column <= 0) {
			cout << "Invalid move! You are playing a " << n << "x" << n << " game!\n";
		}
		else
		{
			if (board[row - 1][column - 1] == ' ') {
				if (turn == 'X') {
					a[count].symbol = 'X'; a[count].column = column; a[count].row = row;
					turn = 'O'; board[row - 1][column - 1] = 'X';
					break;
				}
				else {
					a[count].symbol = 'O'; a[count].column = column; a[count].row = row;
					turn = 'X'; board[row - 1][column - 1] = 'O';
					break;
				}
			}
			else cout << "Invalid move!Square is not empty\n";
		}
	}
	return 0;
}

moveforbot symbolcountingforbot(int deltarow, int deltacol, char** board, const Move a, int n) {
	moveforbot move1{ 0,0 };
	int i = a.row, j = a.column, k = 1;
	while (k < 5)
	{
		i += deltarow;
		j += deltacol;
		if (i > n || i < 1 || j < 1 || j>n || board[i - 1][j - 1] != a.symbol)
		{
			if (i > n || i < 1 || j < 1 || j>n || board[i - 1][j - 1] != ' ')move1.blocked++;
			break;
		}
		else if (board[i - 1][j - 1] == a.symbol)move1.length++;
		++k;
	}
	return move1;
}
int scorecalculating(char botturn, char** board, const Move a, int n, int movecount) {
	if (movecount == 0)return 10;
	Move b = a; b.symbol = ((botturn == 'X') ? 'O' : 'X');
	int m;
	moveforbot count[4] =
	{
		symbolcountingforbot(0, -1, board, a, n) + symbolcountingforbot(0, 1, board, a, n),
		symbolcountingforbot(1, 0, board, a, n) + symbolcountingforbot(-1, 0, board, a, n),
		symbolcountingforbot(-1, 1, board, a, n) + symbolcountingforbot(1, -1, board, a, n),
		symbolcountingforbot(1, 1, board, a, n) + symbolcountingforbot(-1, -1, board, a, n)
	},
		countopp[4] =
	{
		symbolcountingforbot(0, -1, board, b, n) + symbolcountingforbot(0, 1, board, b, n),
		symbolcountingforbot(1, 0, board, b, n) + symbolcountingforbot(-1, 0, board, b, n),
		symbolcountingforbot(-1, 1, board, b, n) + symbolcountingforbot(1, -1, board, b, n),
		symbolcountingforbot(1, 1, board, b, n) + symbolcountingforbot(-1, -1, board, b, n)
	};
	soRt_moveforbot(count, 4);
	soRt_moveforbot(countopp, 4);
	if (n >= 5)m = 5;
	else m = n;
	if (count[0].blocked == 2 || countopp[0].blocked == 2)return 0;
	else
	{
		if (count[0].length == m - 1)return 10000;
		else if (countopp[0].length == m - 1)return 900;
		else if (count[0].length == m - 2)return 700;
		else if (countopp[0].length == m - 2 && countopp[0].blocked == 0)return 600;
		else if (countopp[0].length == m - 2)return 500;
		else if (count[0].length >= m - 3)return 150;
		else if (count[0].length >= m - 4)return 50;
	}
	return 10;
}
int botmove(char botturn, char** board, char& turn, int n, Move a[], int count) {
	int row = rand() % n + 1, column = rand() % n + 1, maxscore = -1,
		tested[20][20]{ 0 },
		delcol[8] = { -1,0,1,-1,1,-1,0,1 },
		delrow[8] = { -1,-1,-1,0,0,1,1,1 };
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 8; j++) {
			int currentscore = -1,
				newrow = a[i].row + delrow[j],
				newcol = a[i].column + delcol[j];
			if (newrow <= n && newrow > 0 && newcol <= n && newcol > 0 &&
				board[newrow - 1][newcol - 1] == ' ' && tested[newrow - 1][newcol - 1] == 0) {
				Move b;
				b.row = newrow; b.column = newcol; b.symbol = botturn;
				currentscore = scorecalculating(botturn, board, b, n, count);
				tested[newrow - 1][newcol - 1] = 1;
				if (currentscore > maxscore) {
					maxscore = currentscore;
					row = newrow;
					column = newcol;
				}
			}
		}
	}
	a[count].symbol = botturn; a[count].column = column; a[count].row = row;
	board[row - 1][column - 1] = botturn;
	turn = ((botturn == 'X') ? 'O' : 'X');
	return 0;
}

int main() {
	system("cls");
	srand(time(0));
	while (1) {
		cout << "TIC-TAC-TOE\n1.PvP\n2.PvE\n3.Exit\n";
		int choice, n = 0, gamecommand = 0;
		char turn = 'O', botturn = 'X';
		cin >> choice;
		if (choice == 3) return 0;
		sizeofboard(n);
		if (choice == 2) {
			cout << "Choose your side: X or O? ";
			cin >> turn;
			botturn = ((turn == 'X') ? 'O' : 'X');
		}
		do {
			firstmove(turn);
			int movecount = 0;
			char** board = createboard(n);
			Move history[400]; ;
			while (1) {
				gamecommand = 0;
				system("cls");
				cout << "It's " << turn << "'s turn\n";
				cout << "Input format:[Row] [Column]\nPress 'R' to Replay, 'M' to go back to menu, '-1' to pause game\n";
				thecurrentboard(board, n);
				movehistory(movecount, history);
				int ketqua = checkwin(board, n, history, movecount);
				if (ketqua) {
					cout << history[movecount - 1].symbol << " wins!\n";
					break;
				}
				else if (movecount == n * n) {
					cout << "Draw!\n";
					break;
				}
				int result = 0;
				if (choice == 2 && turn == botturn)
					result = botmove(botturn, board, turn, n, history, movecount);
				else
					result = entermove(board, turn, n, history, movecount);
				if (result == 1) {
					gamecommand = 1;
					break;
				}
				else if (result == 2) {
					gamecommand = 2;
					break;
				}
				movecount++;
			}
			deleteboard(board, n);
			if (gamecommand == 1)break;
			else if (gamecommand == 0) {
				int l;
				l = playerinteraction();
				if (l == 1) break;
			}
		} while (1);
	}
	return 0;
}