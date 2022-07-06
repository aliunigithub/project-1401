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

void write_(arr_commponent Commponents, FILE* file) {
	rewind(file);
	fwrite(&Commponents.size, sizeof(int), 1, file);
	for (int i = 0 ; i< Commponents.size;i++)
	{
		fwrite(Commponents.arr + i, sizeof(Commponent), 1, file);
	}
	fclose(file);
}

FILE* sign_in()
{
	FILE* file = NULL;
	FILE* file_info;
	char username[100], info[105]="./info/";
	int scan;
	arr_commponent* array_ = (arr_commponent*)malloc(sizeof(arr_commponent));
	array_->arr = (Commponent*)malloc(100 * sizeof(Commponent));
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
		if (strcmp(dir[i], username) == 0) { file = fopen(dir[i], "r+"); break; }
	}
	if (file == NULL)
	{
		file = fopen(username, "w+");
		strcat(info, username);
		file_info = fopen(info, "w");
		array_->arr = NULL;
		array_->size = 0;
		fwrite(&array_->size, sizeof(arr_commponent), 1, file_info);
		fclose(file_info);
	}
	
	strcpy(get_username, username);
	show(0)
	return file;
}

arr_commponent* read_info(FILE* file) {
	
	arr_commponent* array = (arr_commponent*)malloc(sizeof(arr_commponent));
	array->arr = (Commponent*)malloc(100 * sizeof(Commponent));
	int i = 0;
	
	fread(&array->size, sizeof(int), 1, file);
	while (i != array->size)
	{
		fread(&array->arr[i], sizeof(Commponent), 1, file);
		i++;
	}
	return array;
};




void txt_box(int n) {
	
	Commponent text_box;
	char arr[6600];
	FILE* user_view;
	FILE* file;
	char info_dir[100] = "./info/";
	strcat(info_dir, get_username);
	file = fopen(info_dir, "r+");
	arr_commponent* array = read_info(file);
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
			write_(*array, file);

		}else{
			char temp1[100];
			printf("text box name: ");
			scanf("%s", temp1);
			printf("i.e. no no 10 10 10 10: ");
			scanf("%s %s %d %d %d %d",
				text_box.label, text_box.radio, &text_box.x,
				&text_box.y, &text_box.hight, &text_box.width);
			for (int i = 0; i < array->size; i++)
			{
				if( strcmp((array->arr+i)->name,temp1) == 0){
					*(array->arr + i) = text_box;
					write_(*array, file); break;
				}
			}
		}
	system("cls");
}