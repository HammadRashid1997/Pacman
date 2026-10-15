#include <iostream>
#include <map>
#include <ctime>
#include <string>

#ifdef _WIN32
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

using namespace std;

void gotoxy(short x, short y)
{
	cout << "\033[" << (x + 1) << ";" << (y + 1) << "H";
}

#ifndef _WIN32
int getch(void)
{
	int ch;
	struct termios oldt, newt;
	if (tcgetattr(STDIN_FILENO, &oldt) != 0)
	{
		return EOF;
	}
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0)
	{
		return EOF;
	}
	ch = getchar();
	if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) != 0)
	{
		return EOF;
	}
	return ch;
}
#endif

void clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	cout << "\033[2J\033[H";
#endif
}

void Food(char map[14][24]) {
	for (int a = 0; a < 14; a++) {
		for (int b = 0; b < 24; b++) {
			if (map[a][b] == ' ') {
				if ((b % 2 == 1) && (a % 2 == 1)){
					map[a][b] = '.';
				}
			}
		}
	}
}

void display_Map(char map[14][24]) {
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 24; j++) {
			cout << map[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	int score = 0;
	char character;
	char map[14][24] =
		{
			"_______________________",
			"|                     |",
			"| +-------+ +-------+ |",
			"| |--+----+ +----+--| |",
			"| |--|   Hammad  |--| |",
			"| |__| +-------+ |__| |",
			"|      | ----- |      |",
			"| +--+ +-------+ +--+ |",
			"| |--|   Rashid  |--| |",
			"| |--+----+ +----+--| |",
			"| |-------+ +-------| |",
			"|                     |",
			"+---------GAME--------+",
	};
	cout << "PAC-MAN " << endl;
	clearScreen();
	Food(map);
	display_Map(map);
	int Cx = 11, Cy = 21;
	int E1x = 1, E1y = 21;
	srand(time(0));
	for (int x = 0; x < 5000; x++) {
		int count = rand() % 4 + 1;
		character = getch();
		if (character == 's') {
			if (map[Cx + 1][Cy] == ' ' || map[Cx + 1][Cy] == '.') {
				Cx++;
			}
		}
		if (character == 'w') { 
			if (map[Cx - 1][Cy] == ' ' || map[Cx - 1][Cy] == '.') {
				Cx--;
			}
		}
		if (character == 'a') {
			if (map[Cx][Cy - 1] == ' ' || map[Cx][Cy - 1] == '.') {
				Cy--;
			}
		}
		if (character == 'd') {
			if (map[Cx][Cy + 1] == ' ' || map[Cx][Cy + 1] == '.') {
				Cy++;
			}
		}
		if (count == 1) {
			if (map[E1x + 1][E1y] == ' ' || map[E1x + 1][E1y] == '.') {
				E1x++;
			}
		}
		if (count == 2) {
			if (map[E1x - 1][E1y] == ' ' || map[E1x - 1][E1y] == '.') {
				E1x--;
			}
		}
		if (count == 3) {
			if (map[E1x][E1y - 1] == ' ' || map[E1x][E1y - 1] == '.') {
				E1y--;
			}
		}
		if (count == 4) {
			if (map[E1x][E1y + 1] == ' ' || map[E1x][E1y + 1] == '.') {
				E1y++;
			}
		}
		if (map[Cx][Cy] == '.') {
			score++;
			map[Cx][Cy] = ' ';
		}
		clearScreen();
		display_Map(map);
		gotoxy(Cx, Cy);
		cout << "H" << endl;
		gotoxy(E1x, E1y);
		cout << "@";
		gotoxy(14, 2);
		cout << "Score " << score << endl;
		if (score == 32) {
			clearScreen();
			cout << "You Win. Hurrah!!!! " << endl;
		}
		else if (Cx == E1x && Cy == E1y) {
			clearScreen();
			cout << "You lose " << endl;
			cout << "Your score is: " << score << endl;
		}
	}
}
