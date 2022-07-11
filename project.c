#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include <string.h>
#include "dirent.h"
#include  <stdio.h>
#include  "color.h"
#include  <conio.h>

typedef struct Component {
	char name[100];//name of text_box
	char label[4];// yes\0, no\0
	char radio[4];//  yes\0, no\0
	char label_text[150];
	char user_txt[7500];
	char user_radio;
	int height;
	int width;
	int x;
	int y;
}Component;

typedef struct Arr_component {
	Component* arr;
	int size;
}Arr_component;


char dest_username[100];
char get_username[100];
char dir[1000][1000];

int where_x = -1;
int where_y = -1;
int position = 0;
int menu_num = 1;
int access = 0;
int mode = 1;
int len_dir;
int token;

CONSOLE_CURSOR_INFO     cursorInfo;
COORD coord;

Arr_component* array;

#include "functions.h"

////////////////////////////////////////////////////////////////////////////////
void menu() {

	position_cmd(0, 46)
		show(0)


		switch (menu_num)
		{
		case(1):
		{
			make_border();
			printf(BGblue);
			printf("\n");
			if (position == 0)
				printf(white"         Component        ");
			else printf(black"         Component        ");
			if (position == 1)
				printf(white"         save form        ");
			else printf(black"         save form        ");
			if (position == 2)
				printf(white"         run commands        ");
			else printf(black"         run commands        ");
			if (position == 3)
				printf(white"         exit        ");
			else printf(black"         exit        ");
			printf(white"            to navigate->a for left ,d for right");
			printf("\n%s", BGblack);
			reset_color
				break;
		}
		case(2):
		{
			make_border();
			printf(BGred);
			printf("\n");
			if (position == 0)
				printf(white"           make Component           ");
			else printf(black"           make Component           ");
			if (position == 1)
				printf(white"           edit Component           ");
			else printf(black"           edit Component           ");
			if (position == 2)
				printf(white"            back         ");
			else printf(black"            back         ");
			printf(white"                 to navigate->a for left ,d for right");
			printf("\n%s", BGblack);
			reset_color
				break;
		}
		case(3):
		{
			make_border();
			printf(BGyellow);
			printf("\n");
			if (position == 0)
				printf(blue "          fill         ");
			else printf(black"          fill         ");
			if (position == 1)
				printf(blue "          button         ");
			else printf(black"          button         ");
			if (position == 2)
				printf(blue "          authorization         ");
			else printf(black"          authorization         ");
			if (position == 3)printf(blue"          back         "); else printf(black"          back         ");
			printf(blue"           to navigate->a for left ,d for right");
			printf("\n%s", BGblack);
			reset_color
				break;
		}
		case(4):
		{
			make_border();
			printf(BGgreen);
			printf("\n");
			if (position == 0)
				printf(magenta"            add                ");
			else printf(black  "            add                ");
			if (position == 1)
				printf(magenta"            find               ");
			else printf(black  "            find               ");
			if (position == 2)
				printf(magenta"            back               ");
			else printf(black  "            back               ");
			printf(magenta"                     to navigate->a for left ,d for right");
			printf("\n%s", BGblack);
			reset_color
				break;
		}
		default:
			break;
		}
}


////////////////////////////////////////////////////////////////////////////////////////////////
int on_press() {
	FILE* file;
	FILE* information;
	int keyboard_press = 0;
	file = fopen(get_username, "rb+");
	menu();
	while (keyboard_press != 13)
	{
		keyboard_press = _getch();
		if (keyboard_press == 100 &&
			((menu_num == 1 && position < 3) ||
				(menu_num == 2 && position < 2) ||
				(menu_num == 3 && position < 3) ||
				(menu_num == 4 && position < 2)))
		{
			position++;
			menu();
		}
		if (keyboard_press == 97 && position > 0)
		{
			position--;
			menu();
		}
	}
	switch (menu_num)
	{
	case(1):
	{
		switch (position)
		{
		case(0):
		{
			if (access == 1)
			{
				menu_num = 2;
			}
			else {
				system("cls");
				printf(red"you are not authorized");
				Sleep(2000);
				system("cls");
			}
			break;
		}
		case(1):
		{
			if (access == 1)
			{
				system("cls");
				printf(green"your form has been saved");
				write_(file, 0);
				Sleep(2000);
				system("cls");
			}
			else {
				system("cls");
				printf(red"you are not authorized");
				Sleep(2000);
				system("cls");
			}
			break;
		}
		case(2):
		{
			menu_num = 3;
			break;
		}
		default:
		{
			exit(1);
		}
		}
		position = 0;
		return 0;
	}
	case(2):
	{

		switch (position)
		{
		case(0):
		{
			system("cls");
			txt_box(0);
			break;
		}
		case(1):
		{
			system("cls");
			txt_box(1);
			break;
		}
		case(2):
		{
			menu_num = 1;
			position = 0;
			return 0;
		}

		default:
			break;
		}
		position = 0;
		return 0;
	}
	case(3):
	{
		switch (position)
		{
		case(0):
		{
			system("cls");
			show(1)
				fill();
			break;
		}
		case(1):
		{
			menu_num = 4;
			break;
		}
		case(2):
		{
			show(1)
				int temp;
			system("cls");
			if (access == 1)
			{
				printf("you are already authorized");
			}
			else {
				printf("enter token:\n");
				scanf("%d", &temp);
				clearBuffer();
				if (temp == token)
				{
					access = 1;
					printf(green"you are now a admin of this form ");
				}
				else {
					printf(red"wrong token!!");
				}
			}
			Sleep(3000);
			system("cls");
			show(0)
				break;
		}
		case(3):
		{
			menu_num = 1;
			position = 0;
			return 0;
		}
		default:break;
		}
		position = 0;
		return 0;
	}
	case(4):
	{
		switch (position)
		{
		case(0):
		{
			system("cls");
			printf(green"\t   all of your information has been saved");
			Sleep(2000);
			information = fopen(get_username, "wb");
			write_(information, 1);
			system("cls");
			menu_num = 4;
			break;
		}
		case(1):
		{
			if (access == 1)
			{
				system("cls");
				find_keyword();
				system("cls");
			}
			else {
				system("cls");
				printf(red"you are not authorized");
				Sleep(2000);
				system("cls");
			}
			break;
		}
		case(2):
		{
			menu_num = 3;
			position = 0;
			return 0;
		}
		default:
			break;
		}
		return 0;
	}
	default:break;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
int navigation() {
	FILE* file;

	if (mode == 1)
	{
		array->size = 0;
	}
	if (mode == 2)
	{
		file = fopen(get_username, "rb");
		read_info(file);
	}
	if (mode == 3)
	{
		file = fopen(dest_username, "rb");
		read_info(file);
	}

	while (1)
	{
		view();
		on_press();
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	show(0)
		array = (Arr_component*)malloc(sizeof(Arr_component));
	array->arr = (Component*)malloc(100 * sizeof(Component));

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
	Sleep(5000);
	sign_in();
	system("cls");
	navigation();
	return 0;
}