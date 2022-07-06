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




int position = 0;
int menu_num = 1;

COORD coord;
CONSOLE_CURSOR_INFO     cursorInfo;
FILE* view;

char dir[1000][1000];
char get_username[100];
int len_dir;

typedef struct Commponent {
	char name[100];//name of text_box
	char label[4] ;// yes\0, no\0
	char radio[4];//  yes\0, no\0
	char user_label[150];
	char user_txt[7500];
	char user_radio = 'f';
	int hight ;
	int width ;
	int x ;
	int y ;
}Commponent;

typedef struct arr_commponent {
	Commponent* arr;
	int size;
}arr_commponent;

typedef struct user_data {
	char name[100];
	char string[10000];
}user_data;

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
		
		position_cmd(0, 45)
		show(0)
		

		switch (menu_num)
		{
		case(1): {
			make_border();
			printf( BGblue);
			printf("\n");
			if (position == 0)printf(white"                       Component           "); else printf(black"                       Component           ");
			if (position == 1)printf(white"                    run commands          "); else printf(black"                    run commands          ");
			if (position == 2)printf(white"          exit          "); else printf(black"          exit          ");
			printf(white"     to navigate->a for left ,d for right");
			printf("\n%s\n%s",BGwhite, BGblack);
			break;
		}
		case(2):{
			make_border();
			printf(BGred);
			printf("\n");
			if (position == 0)printf(white"           make Component           "); else printf(black"           make Component           ");
			if (position == 1)printf(white"           edit Component           "); else printf(black"           edit Component           ");
			if (position == 2)printf(white"            back         "); else printf(black"            back         ");
			printf(white"                 to navigate->a for left ,d for right");
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
			if (position == 0)printf(white"        make text box          "); else printf(black"        text box          ");
			if (position == 1)printf(white"        edit text box          "); else printf(black"        label          ");
			if (position == 2)printf(white"          back         "); else printf(black"          back         ");
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
		if (keyboard_press == 100 && ((menu_num == 1 && position < 2) || (menu_num == 2 && position < 2) || (menu_num == 3 && position < 2) || (menu_num == 4 && position < 5))) {
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
			if (position == 2) { exit(1); }
			menu_num = position + 2;
			position = 0;
			return 0;
		}
		case(2): {
			
			if (position == 2) { menu_num = 1; position = 0; return 0; }
		
			if (position == 0)
			{ 
				system("cls");
				txt_box(0);
			}
			if (position == 1) {
				system("cls");
				txt_box(1);
			}
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
	/*char ch;
	rewind(file);
	system("cls");
	show(0)
	position_cmd(0, 0)
	ch = fgetc(file);
	while (ch != EOF) {
		printf(white"%c", ch);
		ch = fgetc(file);
	} */
	char info_dir[100] = "./info/";
	strcat(info_dir, get_username);
	file = fopen(info_dir, "r+");
	arr_commponent* array = read_info(file);
	
	for (size_t i = 0; i < array->size; i++)
	{
		int k = 0;
		position_cmd((array->arr + i)->x - 1, (array->arr + i)->y);
		if (((array->arr + i)->radio)[0] == 'y' && (array->arr+i)->user_radio == 't') {printf(green"O");}
		else if (((array->arr + i)->radio)[0] == 'y'){ printf(white"O"); }
		position_cmd((array->arr + i)->x, (array->arr + i)->y);
		while (k <= (array->arr + i)->width + 1) { printf(white"-"); k++; }
		k = 1;
		while (k <= (array->arr + i)->hight) {
			position_cmd((((array->arr + i)->x + 1) + (array->arr + i)->width), ((array->arr + i)->y) + k)
				printf(".");
			k++;
		}
		k = 1;
		while (k <= (array->arr + i)->hight)
		{
			position_cmd(((array->arr + i)->x), ((array->arr + i)->y) + k)
				printf(".");
			k++;
		}
		k = 0;
		position_cmd(((array->arr + i)->x), ((array->arr + i)->y) + (array->arr + i)->hight + 1)
			while (k <= (array->arr + i)->width + 1) { printf("-"); k++; }
	}
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
	
	show(0)
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