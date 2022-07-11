#define reset_color printf(white);
//////////////////////////////////////////////// 
#define show(x) \
cursorInfo.bVisible = x;\
cursorInfo.dwSize = 100;\
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
////////////////////////////////////////////////set console cursor visibility
#define position_cmd(x,y) \
coord.X = x;\
coord.Y = y;\
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
////////////////////////////////////////////////set console cursor position
#define available_text_box printf(cyan"\nthere are %d component available\n", array->size);\
for (int j = 0; j < array->size; j++)\
{\
	Component* comp = (array->arr+j);\
	printf("name=%s \t", comp->name);\
\
	if(comp->label[0] == 'y'){\
		printf("label=%.10s",comp->label_text);	\
	}else{\
		printf("label=NONE!!     ");\
	}\
\
	printf("\tradio_Box=%s \tX=%d \tY=%d \thight=%d \twidth=%d\n",comp->radio,\
        comp->x, comp->y,\
		comp->height , comp->width);\
}\
////////////////////////////////////////////////print all available component

void make_border() {
	for (int i = 0; i < 15; i++)
	{
		printf(magenta"----------");
	}
	printf(black"\n");

}

void clearBuffer() {
	// clearing scanf buffer 
	char c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

/////////////////////////////////////////////// read directory
int readdir_(char dir[][1000])
{
	DIR* folder;
	int files = 0;
	struct dirent* entry;
	folder = opendir(".");
	while ((entry = readdir(folder)))
	{
		strcpy(dir[files], entry->d_name);
		files++;
	}
	closedir(folder);
	return   files++;
}

/////////////////////////////////////////////// get component from file
void read_info(FILE * file) {
	int i = 0;
	rewind(file);
	fread(&token, sizeof(int), 1, file);
	fread(&array->size, sizeof(int), 1, file);
	while (i < array->size)
	{
		fread(&array->arr[i], sizeof(Component), 1, file);
		i++;
	}
	fclose(file);
}

//////////////////////////////////////////////// change view in find button
void change_form(char name[]) {
	FILE* file;
	file = fopen(name, "rb");
	read_info(file);
}

/////////////////////////////////////////////// write component info into file
void write_(FILE * file, int mode) {
	Component* temp = (Component*)malloc(100 * sizeof(Component));
	Component* comp;

	rewind(file);
	fwrite(&token, sizeof(int), 1, file);
	fwrite(&array->size, sizeof(int), 1, file);
	if (!mode) {

		for (int i = 0; i < array->size; i++)
		{
			comp = (array->arr + i);
			(temp + i)->user_radio = 'f';
			memset((temp + i)->user_txt, '|', 7500);
			strcpy((temp + i)->label_text, comp->label_text);
			strcpy((temp + i)->name, comp->name)  ;
			strcpy((temp + i)->label, comp->label);
			strcpy((temp + i)->radio, comp->radio);
			(temp + i)->height = comp->height;
			(temp + i)->width = comp->width;
			(temp + i)->x = comp->x;
			(temp + i)->y = comp->y;
			fwrite(temp + i, sizeof(Component), 1, file);
		}
	}
	else {
		for (int i = 0; i < array->size; i++)
		{
			fwrite(array->arr + i, sizeof(Component), 1, file);
		}
	}
	fclose(file);
}

////////////////////////////////draw component
void view(){ 
	int k = 0;
	Component* comp;
	reset_color;
	for (int i = 0; i < array->size; i++)
	{	
		k = 0;
		int temp = 1;
		comp = (array->arr + i);
		int coord_y = comp->y + 3;
		
		//////////////// Radio box 
		position_cmd(comp->x, comp->y );
	
		if ((comp->radio)[0] == 'y' && comp->user_radio == 't')
		{
			printf(green"O ");
			reset_color;
		}else if ((comp->radio)[0] == 'y')
			{
				printf(white"O "); 
			}else{
				printf(" ");
			}
		//////////////// Label
		if (comp->label[0] == 'y') {
			while (comp->label_text[k] != '\0' && comp->label_text[k] != '|')
			{
				printf("%c", comp->label_text[k]);
				k++;
			}
		}
		//////////////// form shape 
		position_cmd(comp->x, comp->y + 1);
		k = 0;
		while (k <= comp->width + 1 && comp->width != 0)
		{ 
			printf(white"-"); 
			k++; 
		}
		k = 1;
		while (k <= comp->height) {
			position_cmd(((comp->x + 1) + comp->width), (comp->y + 1) + k)
			printf(".");
			k++;
		}
		k = 1;
		while (k <= comp->height)
		{
			position_cmd((comp->x), (comp->y + 1) + k)
			printf(".");
			k++;
		}
		k = 0;
		position_cmd((comp->x), (comp->y) + comp->height + 2)\
		while (k <= comp->width + 1 && comp->width != 0)
		{ 
			printf("-");
			k++;
		}
		//////////////// text
		position_cmd(comp->x + 1, comp->y + 2);
		k = 0;
		while (k < (comp->width * comp->height) && comp->user_txt[k] != '\0')
		{
			if (comp->user_txt[k] == '\n' || (temp % (comp->width + 1) == 0))
			{
				position_cmd(comp->x + 1, coord_y);
				coord_y++;
				temp = 1;
			}
			if (coord_y > (coord_y + comp->height)) { break; }

			if (comp->user_txt[k] != '\n' && comp->user_txt[k] != '|')
			{
				printf("%c", comp->user_txt[k]);
				temp++;
			}
			k++;
		}
		////////////////
	}
}
//////////////////////////////////////////////// view component

void sign_in()
{
	show(1)
	int scan;
	int temp;
	FILE* file = NULL;
	char username[100];

	while (1) {
		system("cls");
		printf("which one?\n1)form maker\n2)form filler\nenter num:");
		access = (getchar() - '0');
		clearBuffer();
		system("cls");
		printf("please enter your username (only lowercase and number are allowed)\n");
		scan = scanf("%[a-z,0-9]", username);
		clearBuffer();
		if (scan != 0) 
		{ 
			break;
		}else{
			system("cls");
			printf("wrong username");
			Sleep(2000);
			}
	}
	strcat(username, ".txt");
	for (int i = 0; i < len_dir; i++)//////////// if username exist
	{

		if (strcmp(dir[i], username) == 0) 
		{ 
			file = fopen(dir[i], "rb");
			system("cls");
			if (access == 1) 
			{
				printf("select mode\n1)new form\n2)your form \nenter num: ");
				mode = (getchar() - '0');
				clearBuffer();
				system("cls");
				printf("your token is: ");
				scanf("%d", &token);
				fread(&temp, sizeof(int), 1, file);

				if (temp != token) 
				{ 
					system("cls");
					printf(red"wrong token");
					exit(1);
				}
				clearBuffer();
				fclose(file);
			
			}else{
				printf("select mode\n1)your form\n2)new form\nenter num: ");
				mode = (getchar() - '0')+1;
				clearBuffer();

				if (mode == 3) 
				{
					system("cls");
					printf("form_maker username is ...\n");
					scanf("%s",dest_username);
					strcat(dest_username, ".txt");
					clearBuffer();
				}
			}
			break; 
		}
	}
	if (file == NULL)
	{
		if (access == 1) 
		{
			printf("enter your token(only num):\n");
			scanf("%d",&token);
			
			file = fopen(username, "wb");
			array->size = 0;
			fwrite(&token, sizeof(int), 1, file);
			fwrite(&array->size, sizeof(int), 1, file);
			fclose(file);
		}else{
			mode = 3;
			printf("form_maker username is ...\n");
			scanf("%s", dest_username);
			strcat(dest_username, ".txt");
			
		}
		clearBuffer();
	}
	strcpy(get_username, username);
	show(0)
}




////////////////////////////////////////////////making and editing component
void txt_box(int n) {
	
	Component text_box;
	
	printf("\t");
	printf(red R"EOF(      make your text box with this pattern(screen is (X = 150 * 45 = Y) character, so make sure your text box is inside screen)
		additional note: there is space before label and label is located at x and y (even if there is no label)
		       so text box shape starts at x&y+1 and because of the border, to keep the area of the text box, 
		   width and hight each will be added by 2,so screen max x=148,y = 43 (if text box has height  and width) 

		                    "name label radio_box X Y hight width" e.g.: textbox1 yes no 10 10 10 10)EOF");

	if (array->size == 0) 
	{
		printf("\nno text box available\n");
	}else{
		available_text_box
	}
	show(1)
		if (n == 0) 
		{
			printf(white"\nmake your component\n");
			scanf("%s %s %s %d %d %d %d", text_box.name,text_box.label, text_box.radio,
				&text_box.x,&text_box.y, &text_box.height, &text_box.width);

			if (text_box.label[0] == 'y') 
			{ 
				printf("\n enter label: ");
				scanf("%[^\n]", text_box.label_text);
			}
			text_box.user_txt[0] = '\0';
			*(array->arr + array->size) = text_box;
			array->size++;
			show(0)
			clearBuffer();

		}else{
			char temp1[100];
			printf("component name: ");
			scanf("%s", temp1);
			printf("e.g. no no 10 10 10 10: ");
			strcpy(text_box.name, temp1);
		
			scanf("%s %s %d %d %d %d",text_box.label, text_box.radio,
				&text_box.x,&text_box.y, &text_box.height, &text_box.width);

			if (text_box.label[0] == 'y') 
			{ 
				printf("\n enter label: ");
				scanf("%[^\n]", text_box.label_text);
			}
			for (int i = 0; i < array->size; i++)
			{
				if( strcmp((array->arr+i)->name,temp1) == 0)
				{
					strcpy(text_box.user_txt, (array->arr + i)->user_txt);
					text_box.user_radio = (array->arr + i)->user_radio;
					*(array->arr + i) = text_box;
					break;
				}
			}
		}
	system("cls");

}

//////////////////////////////////////////////// filling component
void fill() {
	
	int j = 0;
	int n = 0;
	char radio;
	char c = '\0';
	char temp[100];
	
	available_text_box

	printf(white"enter name of component: ");
	scanf("%s", temp);
	clearBuffer();
	for (int i = 0; i < array->size; i++)
	{
		if (strcmp((array->arr + i)->name, temp) == 0) 
		{
			n = i;
			break;
		}
	}

	if ((array->arr + n)->radio[0] == 'y') 
	{ 
		printf("mode of radiobox?[t,f]: ");
		(array->arr + n)->user_radio = getchar();
		clearBuffer();
	}
	
	printf("enter string for your textbox (max length = %d,end your string with (|)): \n",
		((array->arr + n)->width* (array->arr + n)->height));
	while ((c=getchar())!= '|')
	{
		 (array->arr + n)->user_txt[j] = c;
		j++;
	}
	(array->arr + n)->user_txt[j] = '\0';
	system("cls");
}


void edit(char user_name[]) {
	show(1)
	int index;
	int mode_ = 1;
	
	char c = '\0';
	char name[100];

	FILE* file;

	while (1) {
		index = -1;
		system("cls");
		available_text_box

		printf("enter text box name:\n");
		scanf("%s", name);
		clearBuffer();

		for (int i = 0; i < array->size; i++)
		{
			if (strcmp((array->arr + i)->name, name) == 0) 
			{
				index = i;
				break;
			}
		}
		if (index != -1) 
		{
			printf("which one?\n1)Text_box\n");
			if ((array->arr + index)->radio[0] == 'y') 
			{ 
				printf("2)Radio_box\n");
			}

			scanf("%d", &mode_);
			clearBuffer();

			switch (mode_)
			{
			case(1): 
			{
				printf("enter your text(ends with (|)): \n");
				scanf("%[^|]", (array->arr + index)->user_txt);
				break; 
			}
			case(2): 
			{
				printf("mode for radio box[t,f]: \n");
				(array->arr + index)->user_radio = getchar(); 
				break; 
			}

			default:
				break;
			}
			clearBuffer();
		}else { 
			printf(red"not found\n");
			Sleep(2000); 
			}

		printf("are you done?[y,n]:");
		c = getchar();
		clearBuffer();

		if (c == 'y') 
		{ 
		file = fopen(user_name, "wb");
		write_(file, 1);
		break; 
		}
	}
	system("cls");
	show(0)

}

//////////////////////////////////////////////// get
void find_keyword() {
	int len;
	int temp;
	int scanf_; 
	int find = 0;
	int counter = 0;
	int keywords = 0;
	int form_files[100];
	char c;

	char find_label[150][150];
	char find_text[100][7500];

	Component find_comp;

	FILE* file;
	FILE* main;

	show(1)
	len_dir = readdir_(dir);
	system("cls");
	printf(white);
	printf("how many keywords?\n");
	scanf("%d", &keywords);
	clearBuffer();
	for (int j = 0; j < keywords; j++)
	{
		printf("what label are you looking for"
			"(if what your looking doest have label or you don't know the label use (|)"
			" (end with (|))):\n");
		scanf_ = scanf("%[^|]", find_label[j]);
		if (scanf_ == 0) 
		{ 
			find_label[j][0] = '\0'; 
		}

		clearBuffer();
		printf("what keyword are you looking for(end with (|))):\n");

		scanf_ = scanf("%[^|]", find_text[j]);

		if (scanf_ == 0) 
		{ 
			find_text[j][0] = '\0'; 
		}
		clearBuffer();
	}
	system("cls");
	
	for (int i = 0; i < len_dir; i++)
	{	
		find = 0;
		if (strstr(dir[i], ".txt")) 
		{
			file = fopen(dir[i],"rb");
			fread(&temp,sizeof(int),1,file);
			if (temp == token) 
			{
				fread(&temp, sizeof(int), 1, file);
				for (int j = 0; j < temp; j++)
				{
					fread(&find_comp, sizeof(Component), 1, file);
					for (int k = 0; k < keywords; k++)
					{
						if (strstr(find_comp.label_text, find_label[k]) 
						 && strstr(find_comp.user_txt, find_text[k]  )) 
						{
							find++;
						}
					}
					if (find == keywords) 
					{  
					form_files[counter] = i;
					counter++; 
					break; 
					}
				}
			}
			fclose(file);
		}
	}
	if (counter == 0) 
	{
		position_cmd(0, 0) 
		printf(red"404 not found");
		Sleep(2000);
	}else {
		len = counter;
		counter = 0;
		while (1) {
			system("cls");
			change_form(dir[form_files[counter]]);
			view();
			position_cmd(0, 45);
			make_border();
			position_cmd(0, 48);
			printf(blue"you are now in :%s\n"
				"availble commands : n(next form), p(previous form), e(edit), r(remove), b(back to main menu)"
				,dir[form_files[counter]]);
			show(1)
			position_cmd(0, 46);
			c = getchar();
			clearBuffer();
			switch (c)
			{
			case('n'): 
			{
				if (counter < len-1)
					counter++;
				break;
			}
			case('p'): 
			{
				if (counter > 0)
					counter--;
				break;
			}
			case('e'): 
			{
				edit(dir[form_files[counter]]);
				break;
			}
			case('r'): 
			{
				remove(dir[form_files[counter]]); 
				if (len != 1) 
				{
					for (int s = counter + 1; s < len + 1; s++)
					{
						form_files[s - 1] = form_files[s];
					}
					len--;
					counter = 0;
				}else{ 
					main = fopen(get_username, "rb");
					read_info(main);
					return;
					}
				break;
			}
			case('b'): 
			{
				main = fopen(get_username, "rb");
				read_info(main);
				return;
			}
			default:
				break;
			}
		}
	}
}
