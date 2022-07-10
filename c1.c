#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include <stdlib.h> 
#include <string.h>
#include "dirent.h"
#include  <ctype.h>
#include  <stdio.h>
#include  "color.h"
#include  <conio.h>


typedef struct Commponent {
	char name[100];//name of text_box
	char label[4];// yes\0, no\0
	char radio[4];//  yes\0, no\0
	char user_label[150];
	char user_txt[7500];
	char user_radio;
	int hight;
	int width;
	int x;
	int y;
}Commponent;

typedef struct Arr_commponent {
	Commponent* arr;
	int size;
}Arr_commponent;

typedef struct text{
	char arr[7500];
	int x;
	int y;
	
}Text;

typedef struct Arr_text {
	Text* arr;
	int size;
}Arr_text;

char get_username[100];
char dir[1000][1000];

int where_x = -1;
int where_y = -1;
int position = 0;
int menu_num = 1;
int mode = 1;
int len_dir;


CONSOLE_CURSOR_INFO     cursorInfo;
COORD coord;


Arr_commponent* array;
Arr_text* goto_text;


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
			if (position == 0)printf(white"      Component      "); else printf(black"      Component      ");
			if (position == 1)printf(white"      save form      "); else printf(black"      save form      ");
			if (position == 2)printf(white"      run commands      "); else printf(black"      run commands      ");
			if (position == 3)printf(white"      where is?      "); else printf(black"      where is?      ");
			if (position == 4)printf(white"      exit      "); else printf(black"      exit      ");
			printf(white"           to navigate->a for left ,d for right");
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
			if (position == 0)printf(blue"           fill          "); else printf(black"           fill          ");
			if (position == 1)printf(blue"           goto          "); else printf(black"           goto          ");
			if (position == 2)printf(blue"           button        "); else printf(black"           button        ");
			if (position == 3)printf(blue"           back          "); else printf(black"           back          ");
			printf(blue"              to navigate->a for left ,d for right");
			printf("\n%s\n%s", BGwhite, BGblack);
			break;
		}
		case(4): {
			make_border();
			printf(BGgreen);
			printf("\n");
			if (position == 0)printf(magenta"      add          "); else printf(black"      add          ");
			if (position == 1)printf(magenta"      find         "); else printf(black"      find         ");
			if (position == 2)printf(magenta"      edit         "); else printf(black"      edit         ");
			if (position == 3)printf(magenta"      remove       "); else printf(black"      remove       ");
			if (position == 4)printf(magenta"      back         "); else printf(black"      back         ");
			printf(magenta"                   to navigate->a for left ,d for right");
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
	FILE* file;
	char info_dir[100] = "./info/";
	strcat(info_dir, get_username);
	file = fopen(info_dir, "rb+");
	menu();
	while (keyboard_press != 13) {
		keyboard_press = _getch();
		if (keyboard_press == 100 && ((menu_num == 1 && position < 4) || (menu_num == 2 && position < 2) || (menu_num == 3 && position < 3) || (menu_num == 4 && position < 4))) {
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
			switch (position)
			{
			case(0): {menu_num = 2; break; }
			case(1): {system("cls"); printf(green"your form has been saved"); write_(file,0); Sleep(1000);system("cls"); break; }
			case(2): {menu_num = 3; break; }
			case(3): {system("cls"); show(1) printf("x and y with white space:\n"); scanf("%d %d", &where_x, &where_y); clearBuffer(); system("cls"); show(0); break; }
			default:{exit(1);}
			}
			position = 0;
			return 0;
		}
		case(2): {

			switch (position)
			{
			case(0): {
				system("cls");
				txt_box(0); break;
			}
			case(1): {
				system("cls");
				txt_box(1); break;
			}
			case(2): {menu_num = 1; position = 0; return 0; }

			default:
				break;
			}


			position = 0;
			return 0;
		}
		case(3): {
			switch (position)
			{
			case(0): {
				system("cls");
				show(1)
				fill(); break;
			}
			case(1):{
				show(1)
				goto_();
				system("cls"); break;
			}
			case(2): {menu_num = 4; break; }
			case(3): {menu_num = 1; position = 0; return 0; }

			default:
				break;
			}



			position = 0;
			return 0;
			
		}
		case(4): {
			
			switch (position)
			{
			case(0): {system("cls"); printf(green"\t   all of your information has been saved"); Sleep(1000);
				FILE* information;
				information = fopen(get_username, "wb");
				write_(information, 1);
				system("cls");
				menu_num = 4;
				break;
			}
			case(2): {system("cls"); edit(); break; }
			case(3): {system("cls"); remove_(); break; }
			case(4):{menu_num = 3; position = 0; return 0; }
			
			default:
				break;
			}
			return 0;
		}
		
		default:break;
	}

	}
////////////////////////////////////////////////////////////////////////////////////////////////
void view_() {
	int k = 0;
	
	for (int i = 0; i < array->size; i++)
	{
		
		int temp = 1;
		int coord_y = (array->arr + i)->y + 3;
		position_cmd((array->arr + i)->x , (array->arr + i)->y);
		if (((array->arr + i)->radio)[0] == 'y' && (array->arr + i)->user_radio == 't') { printf(green"O "); }
		else if (((array->arr + i)->radio)[0] == 'y') { printf(white"O "); }
		else printf(" ");
		if ((array->arr + i)->label[0] == 'y') {
			while (k < (array->arr + i)->width && ((array->arr + i)->user_label[k] != '\0') && (array->arr + i)->user_label[k] != '|') {
				printf("%c", (array->arr + i)->user_label[k]); k++;
			}
		}
		position_cmd((array->arr + i)->x, (array->arr + i)->y+1);
		k = 0;
		while (k <= (array->arr + i)->width + 1) { printf(white"-"); k++; }
		k = 1;
		while (k <= (array->arr + i)->hight) {
			position_cmd((((array->arr + i)->x + 1) + (array->arr + i)->width), ((array->arr + i)->y+1) + k)
				printf(".");
			k++;
		}
		k = 1;
		while (k <= (array->arr + i)->hight)
		{
			position_cmd(((array->arr + i)->x), ((array->arr + i)->y+1) + k)
				printf(".");
			k++;
		}
		k = 0;
		position_cmd(((array->arr + i)->x), ((array->arr + i)->y) + (array->arr + i)->hight + 2)
			while (k <= (array->arr + i)->width + 1) { printf("-"); k++; }
		position_cmd((array->arr + i)->x+1, (array->arr + i)->y+2);
		k = 0;
		while (k < ((array->arr + i)->width * (array->arr + i)->hight) && (array->arr + i)->user_txt[k] != '\0') {
			if ((array->arr + i)->user_txt[k] == '\n'|| (temp% ((array->arr + i)->width+1) == 0)) { 
				position_cmd((array->arr + i)->x + 1, coord_y); coord_y++;  temp = 1; }
			if (coord_y > (coord_y+(array->arr + i)->hight)) { break; }
			if ((array->arr + i)->user_txt[k] != '\n' && (array->arr + i)->user_txt[k]!='|') {
				printf("%c", (array->arr + i)->user_txt[k]); temp++;
			}
			k++;
		}

	}
	for (int i = 0; i < goto_text->size; i++) {
		k = 0;
		int border = 0;
		int coord_x = (goto_text->arr + i)->x;
		int coord_y = (goto_text->arr + i)->y;
		position_cmd(coord_x, coord_y);
		while ((goto_text->arr + i)->arr[k] != '\0') {
			if (coord_x+border >= 150 || (goto_text->arr + i)->arr[k] == '\n') {
				coord_y++;
				position_cmd(coord_x, coord_y);
				border = 0;
		}
			if (coord_y >= 45) { break; }
			if ((goto_text->arr + i)->arr[k] != '\n') {
				printf(white"%c", (goto_text->arr + i)->arr[k]);
			}
			k++;
			border++;
		}
	}
	if (where_x>=0 && where_y>=0)
	{
		position_cmd(where_x, where_y);
		printf(red"X");
		where_x = -1;
		where_y = -1;
	}


}
////////////////////////////////////////////////////////////////////////////////////////////////
int navigation() {
	FILE* file;
	char info_dir[100] = "./info/";
	if (mode == 1) { array->size = 0; goto_text->size = 0; }
	if(mode==2){
		strcat(info_dir, get_username);
		file = fopen(info_dir, "rb"); 
		read_info(file,0);
	}
	if(mode==3){
		file = fopen(get_username, "rb");
		read_info(file,1); }
	
	
	while (1)
	{
		view_();
		on_press();
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	show(0)
	array = (Arr_commponent*)malloc(sizeof(Arr_commponent));
	array->arr = (Commponent*)malloc(100 * sizeof(Commponent));
	goto_text = (Arr_text*)malloc(sizeof(Arr_text));
	goto_text->arr = (Text*)malloc(100 * sizeof(Text));

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
	sign_in();
	system("cls");
	navigation();

	return 0;
}