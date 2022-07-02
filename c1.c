#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include <stdlib.h> 
#include <string.h>
#include  <ctype.h>
#include  <stdio.h>
#include  "color.h"
#include "dirent.h"
#include  <conio.h>
#include   <math.h>
#include   <time.h>



int position = 0;
int menu_num = 1;

COORD coord;
CONSOLE_CURSOR_INFO     cursorInfo;
FILE* view;
char dir[1000][1000];
int len_dir;

typedef struct Commponent {
	char name[100];
	char label[4];
	char radio[5];
	int hight;
	int weidth;
	int x;
	int y;
}Commponent;

#include "functions.h"
#define maxsize 200

////////////////////////////////////////////////////////////////////////////////////////////////
 void change_line(int n) {
	for (size_t i = 0; i < n; i++)
	{
		printf("\n");
	}
 }
	 void menu() {
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = 0;
		//coord.X = 20;
		coord.Y = 45;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		switch (menu_num)
		{
		case(1): {
			make_border();
			printf( BGblue);
			printf("\n");
			if (position == 0)printf(white"      make form          "); else printf(black"      make form          ");
			if (position == 1)printf(white"        save and edit          "); else printf(black"        save and edit          ");
			if (position == 2)printf(white"        run commands          "); else printf(black"        run commands          ");
			if (position == 3)printf(white"          exit          "); else printf(black"          exit          ");
			printf(white" to navigate->a for left ,d for right   ");
			printf("\n%s\n%s",BGwhite, BGblack);
			break;
		}
		case(2):{
			make_border();
			printf(BGred);
			printf("\n");
			if (position == 0)printf(white"        text box          "); else printf(black"        text box          ");
			if (position == 1)printf(white"        label          "); else printf(black"        label          ");
			if (position == 2)printf(white"    Radio button          "); else printf(black"    Radio button          ");
			if (position == 3)printf(white"          back         "); else printf(black"          back         ");
			printf(white"      to navigate->a for left ,d for right          ");
			printf("\n%s\n%s", BGwhite, BGblack);
			break;
		}
		case(3): {
			make_border();
			printf(BGyellow);
			printf("\n");
			if (position == 0)printf(white"                 save                 "); else printf(black"                 save                 ");
			if (position == 1)printf(white"                 edit                 "); else printf(black"                 edit                 ");
			if (position == 2)printf(white"        back         "); else printf(black"        back         ");
			printf(white"      to navigate->a for left ,d for right           ");
			printf("\n%s\n%s", BGwhite, BGblack);
			break;
		}
		case(4): {
			make_border();
			printf(BGgreen);
			printf("\n");
			if (position == 0)printf(white"        text box          "); else printf(black"        text box          ");
			if (position == 1)printf(white"        label          "); else printf(black"        label          ");
			if (position == 2)printf(white"          button          "); else printf(black"          button          ");
			if (position == 3)printf(white"          back         "); else printf(black"          back         ");
			printf(white"      to navigate->a for left ,d for right          ");
			printf("\n%s\n%s", BGwhite, BGblack);
			break;
		}
		default:
			break;
		}
	
	
	 }
	 
	 
////////////////////////////////////////////////////////////////////////////////////////////////
int on_press() {
	int keyboard_press = 0;
	menu();
	while (keyboard_press != 13) {
		keyboard_press = _getch();
		if (keyboard_press == 100 && ((menu_num == 1 && position < 3) || (menu_num == 2 && position < 3) || (menu_num == 3 && position < 2) || (menu_num == 4 && position < 5))) {
			position++;
			menu();
		}
		if (keyboard_press == 97 && position > 0) {
			position--;
			menu();
		}

	}
	switch (menu_num)
	{
		case(1): {
			if (position == 3) { exit(1); }
			menu_num = position + 2;
			position = 0;
			return 0;
		}
		case(2): {
			
			if (position == 3) { menu_num = 1; position = 0; return 0; }
		
			if (position == 1)
			{ 
				system("cls");
				//txt_box();
			}
			//menu_num = position + 2;
			position = 0;
			return 0;
		}
		case(3): {
			if (position == 2) { menu_num = 1; position = 0; return 0; }
			menu_num = position + 2;
			position = 0;
			return 0;
		}
		
		default:break;
	}

	}
////////////////////////////////////////////////////////////////////////////////////////////////
void view_(FILE* file) {
	char ch;
	rewind(file);
	system("cls");
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = 0;
	coord.Y = 0;
	coord.X = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	do {
		ch = fgetc(file);
		printf(white"%c", ch);
	} while (ch != EOF);
}
////////////////////////////////////////////////////////////////////////////////////////////////
int navigation() {
	while (1)
	{
		view_(view);
		on_press();
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	len_dir = readdir_(dir);
	system("mode con:cols=150 lines=50");
	printf(green R"EOF(

	
			  _____   U  ___ u   ____     __  __        __  __      _       _  __  U _____ u   ____     
			 |" ___|   \/"_ \/U |  _"\ uU|' \/ '|u    U|' \/ '|uU  /"\  u  |"|/ /  \| ___"|/U |  _"\ u  
			U| |_  u   | | | | \| |_) |/\| |\/| |/    \| |\/| |/ \/ _ \/   | ' /    |  _|"   \| |_) |/  
			\|  _|/.-,_| |_| |  |  _ <   | |  | |      | |  | |  / ___ \ U/| . \\u  | |___    |  _ <    
			 |_|    \_)-\___/   |_| \_\  |_|  |_|      |_|  |_| /_/   \_\  |_|\_\   |_____|   |_| \_\   
			 )(\\,-      \\     //   \\_<<,-,,-.      <<,-,,-.   \\    >>,-,>> \\,-.<<   >>   //   \\_  
			(__)(_/     (__)   (__)  (__)(./  \.)      (./  \.) (__)  (__)\.)   (_/(__) (__) (__)  (__) 
					              welcome to form maker2000
)EOF");
	Sleep(10);
	view = sign_in();
	system("cls");
	navigation();

	return 0;
}