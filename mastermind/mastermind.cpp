#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>

#include "engine.h"
#include "topten.h"
#include "variables.h"

using namespace std;

int attempt = 1, scoreField = 1;
string nmPrevious;
vector<TopTen> competitors;
Engine engine;

int getkey();
void write(int x, int y, char* t, int color);
void backspacePressed(char* s, int Data[]);
void keyPressed(char* s, int Data[]);
void writeScores(vector<TopTen> competitors);
void drawDataRow(string name, int position, int score, int flag);
void initCombination();
void drawMenuItem(string title, int xPos, int yPos, bool selected, int error = NO_ERROR);
void init();
void insertNM();

void showCursor(int hide)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = hide;
	SetConsoleCursorInfo(consoleHandle, &info);
}

string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

char* allocateChar(int n) // napravi okvir za ime
{
	unsigned int i, j, Length;
	char* p;
	char s[] = " ";

	Length = strlen(s);
	p = new char[Length * n + 1];
	for (i = 0; i < n; i++) {
		for (j = 0; j < Length; j++) 
			*p++ = s[j];
	}
	*p = 0;
	return (p - (Length * n));
}

void setcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return;
}

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

//crta naslovnu sekciju u aplikaciji
void drawTitle()
{
	//0-79
	//koordinate odakle crta konzola
	int conX = 0;
	int conY = 0;
	gotoxy(conX, conY);

	setcolor(CYAN);
	cout << (char)TL;
	for (int i = 0; i < 78; i++)
		cout << (char)HL;
	cout << (char)TR << endl;

	conY++;
	gotoxy(conX, conY);
	cout << (char)VL;
	
	for (int i = 0; i < 27; i++) {
		setcolor(BACKGROUND_RED);
		cout << " ";
	}	

	for (int i = 0; i < 25; i++)
		setcolor(113);
	for (int i = 0; i < 5; i++)
		cout << " ";
	cout << "Master of Mind";
	
	for (int i = 0; i < 5; i++)
		cout << " ";

	for (int i = 0; i < 27; i++) {
		setcolor(BACKGROUND_RED);
		cout << " ";
	}

	setcolor(CYAN);
	conY++;
	gotoxy(conX, conY);
	cout << (char)BL;
	for (int i = 0; i < 78; i++)
		cout << (char)HL;
	
	conX = 79;
	conY = 1;
	gotoxy(conX, conY);
	cout << (char)VL;
	conY++;
	gotoxy(conX, conY);
	cout << (char)BR << endl;
}

void insertScore(int score, int attempt)
{
	int x = attempt * 2 + 1;
	int y = 7;

	gotoxy(x, y);
	setcolor(BACKGROUND_GREEN_WHITE);

	cout << score;
}

//crta score u aplikaciji
void drawScore()
{
	int conX = 2;
	int conY = 6;

	gotoxy(conX, conY);

	setcolor(YELLOW);

	cout << (char)TL << (char)HL << (char)T << (char)HL << (char)T << (char)HL << (char)T << (char)HL << (char)T << (char)HL << (char)TR;
	conY++;
	gotoxy(conX, conY);

	cout << (char)VL << "S" << (char)VL << "c" << (char)VL << "o" << (char)VL << "r" << (char)VL << "e" << (char)VL;
	
	conY++;
	gotoxy(conX, conY);
	cout << (char)BL << (char)HL << (char)TT << (char)HL << (char)TT << (char)HL << (char)TT << (char)HL << (char)TT << (char)HL << (char)BR;
}

//crta data u aplikaciji
void drawNumberSection(int conX, int conY, int dimX, int dimY, string text)
{
	setcolor(YELLOW);
	gotoxy(conX, conY);

	cout << (char)TL;
	for (int i = 0; i < dimX - 2; i++)
		cout << (char)HL;
	cout << (char)TR;
	
	conY++;
	gotoxy(conX, conY);

	cout << (char)VL;
	setcolor(96);
	cout << " " << text << " ";
	setcolor(YELLOW);
	cout << (char)VL;
	conY++;
	gotoxy(conX, conY);

	cout << (char)RT;
	for (int i = 0; i < dimX - 2; i++)
		cout << (char)HL;
	cout << (char)LT;
	conY++;

	for (int i = 0; i < dimY - 4; i++)
	{
		gotoxy(conX, conY);
		conY++;
		cout << (char)VL;
		for (int i = 0; i < dimX - 2; i++)
			cout << " ";
		cout << (char)VL;
	}

	gotoxy(conX, conY);
	
	cout << (char)BL;
	for (int i = 0; i < dimX - 2; i++)
		cout << (char)HL;
	cout << (char)BR;
}

//crta zuti okvir oko aplikacije
void drawGameBorder()
{
	int conX = 0;
	int conY = 4;
	int conXR = 79;

	setcolor(YELLOW);
	gotoxy(conX, conY);
	cout << (char)TL;
	for (int i = 0; i < 78; i++)
		cout << (char)HL;
	cout << (char)TR << endl;

	conX = 0;
	conY = 5;

	for (int i = 0; i < 15; i++)
	{
		gotoxy(conX, conY);
		cout << (char)VL;
		gotoxy(conXR, conY);
		cout << (char)VL << endl;
		conY++;
	}

	cout << (char)BL;
	for (int i = 0; i < 78;i++)
		cout << (char)HL;

	cout << (char)BR << endl;

	drawScore();
	drawNumberSection(15,6,8,13, "Data");
	drawNumberSection(27, 6, 6, 13, "nm");
}

//salje se broj koji je racunar predlozio i broj pokusaja (krece se od 1)
void computerGuess(string number)
{
	int x = 17; 
	int y = attempt + 8;

	gotoxy(x, y);
	setcolor(WHITE);
	cout << number;
}

int keyControl(char* s, int x, int y, int color, int polje) // unos imena
{
	int len, Data[5];
	len = strlen(s); 

	if (!len) 
		return 0;

	Data[2] = len - 1;

	if (isspace(s[Data[2]])) 
		Data[4] = 9; 
	else 
		Data[4] = 1;

	Data[0] = 0;

	while (Data[0] < len) {
		if (Data[4]) {
			write(x, y, s, color);
			if (Data[4] == 9) {
				while (isspace(s[Data[2]]) && Data[2] > 0) 
					Data[2]--;
				if (!isspace(s[Data[2]])) 
					Data[2]++;
			}
			Data[4] = 0;
		}
		gotoxy(x + Data[0], y);

		switch (Data[3] = getkey()) {
			case HOMEKEY:
				Data[0] = 0;
				break;
			case ENDKEY:
				Data[0] = Data[2];
				break;
			case LEFTKEY:
				if (polje == 3)
					return LEFTKEY;
				if (--Data[0] < 0) 
					Data[0] = 0;
				break;
			case RIGHTKEY:
				if (polje == 3)
					return RIGHTKEY;
				if (++Data[0] == len) 
					Data[0]--;
				break;
			case PGDNKEY: case TAB:
				return PGDNKEY;
			case PGUPKEY:
				return PGUPKEY;
			case UPKEY: case DOWNKEY: case CTRLHOMEKEY: case CTRLENDKEY:
				return Data[3];
			case ESC:
				exit(0);
			case CR:
				return CR;
			case BS:  
				backspacePressed(s, Data);  
				break;
			case DELKEY: 
				backspacePressed(s, Data); 
				break;
			default:
				if (polje == 3)
					continue;

				if (polje != 1)
					keyPressed(s, Data);
				else
					if (Data[3] > 47 && Data[3] < 58) {
						keyPressed(s, Data);
					}
					else
					{
						s[Data[0] - 1] = *" ";
						Data[4] = 0;
					}
				break;
		}
	}
	write(x, y, s, color);
	return CR;
}

void lowerSectionControl(int error) {
	int x = 85, y = 20;
	int ind = 0; // 0 - New, 1 - Ignore, 2 - Exit

	showCursor(FALSE);
	
	drawMenuItem(" New", 0, 21, true);

	if (error) {
		drawMenuItem("Ignore", 28, 21, false, ERROR);
	}

	char *s = allocateChar(1);
	int returnValue;

	while (1) {
		returnValue = keyControl(s, x, y, WHITE, 3);

		if (returnValue == PGUPKEY) {
			engine = Engine();
			init();
		}
		else if (returnValue == RIGHTKEY && ind == 0) {
			drawMenuItem(" New", 0, 21, false);

			if (error) {
				drawMenuItem("Exit", 55, 21, true);
				ind = 2;
			}
			else {
				drawMenuItem("Ignore", 28, 21, true);
				ind = 1;
			}
		}
		else if (returnValue == RIGHTKEY && ind == 1) {
			drawMenuItem("Ignore", 28, 21, false);
			drawMenuItem("Exit", 55, 21, true);
			ind = 2;
		}
		else if (returnValue == RIGHTKEY && ind == 2) {
			drawMenuItem("Exit", 55, 21, false);
			drawMenuItem(" New", 0, 21, true);
			ind = 0;
		}
		else if (returnValue == LEFTKEY && ind == 0) {
			drawMenuItem(" New", 0, 21, false);
			drawMenuItem("Exit", 55, 21, true);
			ind = 2;
		}
		else if (returnValue == LEFTKEY && ind == 2) {
			drawMenuItem("Exit", 55, 21, false);

			if (error) {
				drawMenuItem(" New", 0, 21, true);
				ind = 0;
			}
			else {
				drawMenuItem("Ignore", 28, 21, true);
				ind = 1;
			}
		}
		else if (returnValue == LEFTKEY && ind == 1) {
			drawMenuItem("Ignore", 28, 21, false);
			drawMenuItem(" New", 0, 21, true);
			ind = 0;
		}
		else if (returnValue == CR) {
			if (ind == 0) {
				engine = Engine();
				init();
			}
			else if (ind == 1) {
				insertNM();
			}
			else if (ind == 2) {
				exit(1);
			}
		}
	}
}

//saljemo koji je pokusaj u pitanju
void insertNM()
{
	showCursor(TRUE);

	int x = 29;
	int y = attempt + 8;
	int score;

	if (attempt > 1) //menjamo boju pokusaju iznad, a novi stavljamo da je crvene boje
	{
		y--;
		gotoxy(x, y);
		setcolor(WHITE);
		cout << nmPrevious;
		y++;
	}
	setcolor(BACKGROUND_RED_WHITE);
	gotoxy(x, y);
	cout << "  ";

	gotoxy(x, y);

	do {
		char* nm = allocateChar(2);
		int returnValue = keyControl(nm, x, y, BACKGROUND_RED_WHITE, 1);

		if (returnValue == PGDNKEY) {
			lowerSectionControl(NO_ERROR);
		}

		nmPrevious = nm;

		if (nm[0] < nm[1]) {
			gotoxy(x, y);
		}
		else if (nm[1] == '4') {
			score = engine.dajScore();
			insertScore(score, scoreField);
			scoreField++;

			engine.restart();

			if (scoreField == 6) {
				int finalScore = engine.dajUkupniScore();
				int position = findPosition(competitors, finalScore);
				drawDataRow("", position, finalScore, INSERT_NAME);
				writeScores(competitors);
				scoreField = 1;
				drawScore();
				lowerSectionControl(ERROR);
			}

			attempt = 1;

			drawNumberSection(15, 6, 8, 13, "Data");
			drawNumberSection(27, 6, 6, 13, "nm");
			initCombination();

			break;
		}
		else {
			engine.redukujListu(nm[0] - '0', nm[1] - '0');

			attempt++;
			initCombination();
		}
	} while (1);
}

void drawMenuItem(string title, int xPos, int yPos, bool selected, int error)
{
	int conX = xPos;
	int conY = yPos;
	int conXR = conX + 24;
	conY++;
	gotoxy(conX, conY);

	if (error) {
		setcolor(GRAY);
	}	
	else {
		setcolor(YELLOW);
	}

	cout << (char)DTL;
	for (int i = 0; i < 23; i++)
		cout << (char)DHL;
	cout << (char)DTR;

	conY++;
	gotoxy(conX, conY);
	cout << (char)DVL;

	gotoxy(conXR, conY);
	conY++;
	cout << (char)DVL;

	gotoxy(conX, conY);

	cout << (char)DBL;
	for (int i = 0; i < 23; i++)
		cout << (char)DHL;
	cout << (char)DBR;

	int length = 25;
	int wordLength = title.length();
	
	conY = yPos + 2;
	int pom = (length - wordLength) / 2;
	
	if (selected) {
		conXR = xPos + 1;
		gotoxy(conXR, conY);
		setcolor(49);
		for (int i = 0; i < pom - 1; i++)
			cout << " ";
		cout << title;
		for (int i = 0; i < pom; i++)
			cout << " ";
	}
	else {
		conXR = xPos + 1;
		gotoxy(conXR, conY);

		if (error) {
			setcolor(GRAY);
		}
		else {
			setcolor(CYAN);
		}

		for (int i = 0; i < pom - 1; i++)
			cout << " ";
		cout << title;
		for (int i = 0; i < pom; i++)
			cout << " ";
	}
}

//ova funkcija crta prazne redove pre i posle tabele top10
void drawEmptyRow(int y)
{
	int x = 38;
	gotoxy(x, y);

	setcolor(BACKGROUND_WHITE);
	for (int i = 0; i < 18; i++)
		cout << " ";

	setcolor(BACKGROUND_YELLOW);
	for (int i = 0; i < 18; i++)
		cout << " ";
}

void drawRow(int position)
{
	int x = 38;
	int y = position + 7;
	gotoxy(x, y);

	//bela pozadina levo
	setcolor(BACKGROUND_WHITE);
	for (int i = 0; i < 15; i++)
		cout << " ";

	if (position == 10) {
		cout << position << " ";
		setcolor(BACKGROUND_YELLOW);
		cout << " " << position;
	}
	else{
		cout << "0" << position << " ";
		setcolor(BACKGROUND_YELLOW);
		cout << " 0" << position;
	}

	//zuta pozadina desno
	for (int i = 0; i < 12; i++)
		cout << " ";
	
	cout << "50 ";
}

//funkcija formatira ime korisnika 
void textFormatting(char* name)
{
	int n = strlen(name);
	for (int i = 0; i < n; i++)
	{
		if (name[i] >= '0' && name[i] <= '9')
		{
			for (int j = i; j < n - 1; j++)
			{
				name[j] = name[j + 1];
			}
			n--;
			i--;
		}
	}

	name[0] = toupper(name[0]);
	for (int i = 1; i < n; i++)
	{
		if (name[i] <= 'Z' && name[i] >= 'A')
			name[i] = tolower(name[i]);

	}
	name[n - 1] = '\0';
}

//ako se citaju pocetni podaci iz baze, funkciji treba da se prosledi flag 0
//u tom slucaju on nece da zahteva da se unese ime
//ako se ostvari novi skor koji treba da se upise onda je flag 1
//tada funkcija bi trebalo da trazi ime da se unese i da to ime upise na odgovarajucu poziciju
//ako se ne unese ime ostaje Unsigned
//cifre u imenu se NE RACUNAJU preskacu se
void drawDataRow(string name, int position, int score, int flag)
{
	int x = 38;
	int xR = 71;
	int y = position + 7;
	int returnValue = 0;
	//ispis score
	gotoxy(xR, y);
	setcolor(BACKGROUND_YELLOW);
	if (score < 10)
	{
		cout << "0" << score;
	}
	else
	{
		cout << score;
	}

	if (flag)
	{
		setcolor(BACKGROUND_YELLOW);

		//ovaj deo nema ime
		//unos imena sa tastarure
		//+1 zbog razmaka na pocetku
		gotoxy(x + 1, y);
		for (int i = 0; i < 13; i++)
			cout << " ";

		gotoxy(x + 1, y);
		//maksimum je 13 karaktera
		//getchar do entera ili do 13 karaktera
		char* newName = allocateChar(10);
		returnValue = keyControl(newName, x+1, y, BACKGROUND_YELLOW, 0);

		if (newName[0] == ' ')
		{
			name = "Unsigned";
		}
		else
		{
			textFormatting(newName);
			name = convertToString(newName, strlen(newName));
		}

		TopTen competitor;
		competitor.name = name;
		competitor.score = score;
		insertSorted(competitors, competitor);
		writeScores(competitors);
		updateScoresInFile(competitors);
	}

	//ispis imena
	setcolor(BACKGROUND_WHITE);
	gotoxy(x, y);
	cout << " " << name << " ";

	int nameLength = name.length();
	int n = 13 - nameLength;

	for (int i = 0; i < n; i++)
		cout << " ";

	if (returnValue == PGDNKEY)
		lowerSectionControl(NO_ERROR);
}

void drawInitTable()
{
	//18 + 18 po x
	//13 po y ( table header, prazan red, top10, prazan red)

	int conX = 38;
	int conY = 6;

	gotoxy(conX, conY);
	setcolor(BACKGROUND_YELLOW);
	cout << " Author:";
	for (int i = 0; i < 10; i++)
		cout << " ";

	setcolor(BACKGROUND_WHITE);
	cout << " Mirko Lepovic";
	for (int i = 0; i < 4; i++)
		cout << " ";

	//prazan red   (38,7)
	conY++;  
	drawEmptyRow(conY);
	
	//prvo mesto u tabeli, prvi red (38,8)
	conY++;
	gotoxy(conX, conY);

	for (int i = 0; i < 10; i++) {
		drawRow(i + 1);
	}

	//prazan red   (38,18)
	conY = 18;
	drawEmptyRow(conY);
}

void writeScores(vector<TopTen> competitors) {
	for (int i = 0; i < competitors.size(); i++) {
		drawDataRow(competitors[i].name, i + 1, competitors[i].score, READ_FROM_FILE);
	}
}

int getkey()  // pritisak dugmeta
{
	int c, key;
	char ch = _getch();

	if (ch == 224) {
		ch = _getch();
	}

	key = (c = ch) > 0 ? c : 256 + ch;

	return key;
}

void write(int x, int y, char* t, int color) {
	gotoxy(x, y);

	setcolor(color);
	cout << t;
}

void backspacePressed(char* s, int Data[]) // pritisni backspace
{
	if (!Data[0]) 
		return;  
	
	if (Data[0]-- > Data[2]) 
		return;

	Data[4] = 1; 
	Data[1] = Data[2];

	memmove(&s[Data[0] + 1], &s[Data[0]], Data[1] - Data[0]);

	s[Data[1]] = ' ';

	if (s[Data[2]] == ' ') 
		Data[4] = 9;

	return;
}

void keyPressed(char* s, int Data[]) // pritisni dugme ili slovo
{
	if (Data[3] < ' ' || Data[3] > 'z') 
		return;

	Data[3] = tolower(Data[3]);
	Data[1] = Data[0];

	if (Data[2] <= Data[0]) {
		s[Data[0]] = Data[3];
		Data[0]++;
		if (s[Data[1]] != ' ') {
			Data[2] = Data[0]; 
			Data[4] = 1;
		}
		return;
	}

	Data[4] = 1; 
	Data[1] = Data[2];
	memmove(&s[Data[0]], &s[Data[0] + 1], Data[1] - Data[0]);

	s[Data[0]] = Data[3];
	Data[0]++; 
	Data[2]++; 
	int len = strlen(s);

	if (Data[2] < len) 
		return;

	Data[2]--;

	if (isspace(s[Data[2]])) 
		Data[4] = 9;

	return;
}

void init()
{
	attempt = 1;
	scoreField = 1;

	drawTitle();
	drawGameBorder();
	drawInitTable();

	drawMenuItem(" New", 0, 21, false); 
	drawMenuItem("Ignore", 28, 21, false);
	drawMenuItem("Exit", 55, 21, false);

	writeScores(competitors);
	initCombination();
}

void initCombination() {
	char combinationChar[6];
	strcpy_s(combinationChar, engine.dajKombinaciju());
	string combination = convertToString(combinationChar, strlen(combinationChar));

	if (combination == "error") {
		lowerSectionControl(ERROR);
	}

	computerGuess(combination);
	insertNM();
}

int main()
{
	//int ch = 0;
	//while (ch != 0x1B)  // exit on ESC
	//{
	//	ch = _getch();
	//	printf("%02X (%d)\n", ch, ch);
	//}

	readFile(competitors);
	engine = Engine();
	init();
}
