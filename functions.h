#define show(x) cursorInfo.bVisible = x;\
cursorInfo.dwSize = 100;\
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
#define position_cmd(x,y) coord.X = x;\
coord.Y = y;\
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

void make_border() {
	for (int i = 0; i < 15; i++)
	{
		printf(magenta"----------");
	}
	printf(black"\n");
	
}
int readdir_(char dir[][1000])
{
    DIR* folder;
    struct dirent* entry;
    int files = 0;
    folder = opendir(".");
    while ((entry = readdir(folder)))
    {
        strcpy(dir[files], entry->d_name);
        files++;
    }
    closedir(folder);
    return files++;
}

void clearBuffer() {
    // clearing scanf buffer 
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void read_info(FILE* file,int mode) {
	int i = 0;
	rewind(file);
	fread(&array->size, sizeof(int), 1, file);
	fread(&goto_text->size, sizeof(int), 1, file);
	while (i < array->size)
	{
		fread(&array->arr[i], sizeof(Commponent), 1, file);
		i++;
	}
	if (mode) {
		i = 0;
		while (i < goto_text->size)
		{
			fread(&goto_text->arr[i], sizeof(Text), 1, file);
			i++;
		}
	}else goto_text->size = 0;
	fclose(file);

}

void write_( FILE* file, int mode ) {
	rewind(file);
	
	fwrite(&array->size, sizeof(int), 1, file);
	fwrite(&goto_text->size, sizeof(int), 1, file);

	Commponent* temp = (Commponent*)malloc(100 * sizeof(Commponent));
	
	if (!mode) {
		
		for (int i = 0; i < array->size; i++)
		{
			(temp + i)->user_radio = 'f';
			memset((temp + i)->user_label, '|', 150);
			memset((temp + i)->user_txt, '|', 7500);
			strcpy((temp+i)->name, (array->arr+i)->name);
			strcpy((temp + i)->label, (array->arr + i)->label);
			strcpy((temp + i)->radio, (array->arr + i)->radio);
			(temp + i)->hight = (array->arr + i)->hight;
			(temp + i)->width = (array->arr + i)->width;
			(temp + i)->x = (array->arr + i)->x;
			(temp + i)->y = (array->arr + i)->y;
			fwrite(temp + i, sizeof(Commponent), 1, file);
		}
	}
	else {
		for (int i = 0; i < array->size; i++)
		{
			fwrite(array->arr + i, sizeof(Commponent), 1, file);
		}
		for (int i = 0; i < goto_text->size; i++)
		{
			fwrite(goto_text->arr + i, sizeof(Text), 1, file);
		}
	}
	fclose(file);
}

void sign_in()
{
	FILE* file = NULL;
	FILE* file_info;
	char username[100], info[105]="./info/";
	int scan;
	show(1)
	while (1) {
		system("cls");
		printf("please enter your user name (only lowercase and number are allowed)\n");
		scan = scanf("%[a-z,0-9]", username);
		if (scan != 0)break;
		else
		{
			clearBuffer();
			system("cls");
			printf("wrong username");
			Sleep(2);
		}
	}
	strcat(username, ".txt");
	for (int i = 0; i < len_dir; i++)
	{
		if (strcmp(dir[i], username) == 0) { 
		file = fopen(dir[i], "rb");
		system("cls");
		printf("select mode\n1)new form\n2)only shape (no text)\n3)load everything\nenter num: ");
		clearBuffer();
		mode = (getchar() - '0');
		break; }
	}
	if (file == NULL)
	{
		file = fopen(username, "wb");
		strcat(info, username);
		file_info = fopen(info, "wb");
		array->size = 0;
		goto_text->size = 0;
		fwrite(&array->size, sizeof(int), 1, file_info);
		fwrite(&goto_text->size, sizeof(int), 1, file_info);// make sure to delete
		fwrite(&array->size, sizeof(int), 1, file);
		fwrite(&goto_text->size, sizeof(int), 1, file);
		fclose(file_info);
		fclose(file);
		
	}
	
	strcpy(get_username, username);
	show(0)
}






void txt_box(int n) {
	
	Commponent text_box;
	char arr[6600];
	FILE* user_view;
	FILE* file;
	char info_dir[100] = "./info/";
	strcat(info_dir, get_username);
	file = fopen(info_dir, "rb");
	printf("\t");
	printf(red R"EOF(      make your text box with this pattern(screen is X = 150 * 50 = Y character so make your sure your txt box is inside screen)
		                     "name label radio_box X Y hight width" e.g.: textbox1 yes no 10 10 10 10)EOF");
	if (array->size == 0) {printf("\nno text box available\n");
	}else {
		printf(cyan"\nthere are %d text box available\n", array->size);
		for (int j = 0; j < array->size; j++)
		{
			printf("name=%s \tlabel=%s \tradio_Box=%s \tX=%d \tY=%d \thight=%d \twidth=%d\n", (array->arr + j)->name ,
				(array->arr + j)->label, (array->arr + j)->radio,
				(array->arr + j)->x, (array->arr + j)->y,
				(array->arr + j)->hight, (array->arr + j)->width);
		}
	}
	show(1)
		if (n == 0) {
			printf(white"\nmake your text box\n");
			scanf("%s %s %s %d %d %d %d", text_box.name,
				text_box.label, text_box.radio, &text_box.x,
				&text_box.y, &text_box.hight, &text_box.width);
			
			*(array->arr + array->size) = text_box;
			show(0)
			clearBuffer();
			array->size++;
			

		}else{
			char temp1[100];
			printf("text box name: ");
			scanf("%s", temp1);
			printf("i.e. no no 10 10 10 10: ");
			strcpy(text_box.name, temp1);
			
			scanf("%s %s %d %d %d %d",
				text_box.label, text_box.radio, &text_box.x,
				&text_box.y, &text_box.hight, &text_box.width);
			for (int i = 0; i < array->size; i++)
			{
				if( strcmp((array->arr+i)->name,temp1) == 0){
					strcpy(text_box.user_txt, (array->arr + i)->user_txt);
					strcpy(text_box.user_label ,(array->arr + i)->user_label);
					text_box.user_radio = (array->arr + i)->user_radio;
					*(array->arr + i) = text_box;
					 break;
				}
			}
		}
	system("cls");
	fclose(file);
}

void fill() {
	FILE* file;
	char info_dir[100] = "./info/";
	char temp[100];
	char radio;
	char c = '\0';
	int j = 0;
	int n = 0;
	strcat(info_dir, get_username);
	file = fopen(info_dir, "rb");
	printf(cyan"\nthere are %d text box available\n", array->size);
	for (int j = 0; j < array->size; j++)
	{
		printf("name=%s \tlabel=%s \tradio_Box=%s \tX=%d \tY=%d \thight=%d \twidth=%d\n", (array->arr + j)->name,
			(array->arr + j)->label, (array->arr + j)->radio,
			(array->arr + j)->x, (array->arr + j)->y,
			(array->arr + j)->hight, (array->arr + j)->width);
	}
	printf(white"enter name of text box: ");
	scanf("%s", temp);
	for (int i = 0; i < array->size; i++)
	{
		if (strcmp((array->arr + i)->name, temp) == 0) {
			n = i; break;
		}
	}
	if ((array->arr + n)->label[0] == 'y') {
		printf("enter text for your label(maximum length =%d ): ", (array->arr + n)->width);
		clearBuffer();
		scanf("%[^\n]", (array->arr + n)->user_label);
	}
	clearBuffer();
	if ((array->arr + n)->radio[0] == 'y') { printf("mode of radiobox?[t,f]: "); (array->arr + n)->user_radio = getchar(); }
	clearBuffer();
	printf("enter string for your textbox (max length = %d,end your string with (|)): \n",((array->arr + n)->width* (array->arr + n)->hight));
	while ((c=getchar())!= '|')
	{
		 (array->arr + n)->user_txt[j] = c;
		j++;
	}
	(array->arr + n)->user_txt[j] = '\0';
	system("cls");
	fclose(file);
}
void goto_() {
	
	system("cls");
	printf(red"be careful this function might over write some information USE IT CAREFULLY\n");
	Sleep(50);
	system("cls");
	clearBuffer();
	printf("enter X = ");
	scanf("%d",&(goto_text->arr+goto_text->size)->x);
	printf("\nenter Y = ");
	scanf("%d", &(goto_text->arr + goto_text->size)->y);
	printf("enter your text(ends with (|) symbol):\n");
	clearBuffer();
	scanf("%[^|]", ((goto_text->arr + goto_text->size)->arr));
	goto_text->size++;
	system("cls");

}