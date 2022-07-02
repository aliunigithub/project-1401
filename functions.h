
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

FILE* sign_in()
{
	FILE* file = NULL;
	char username[100], info[105]="./info/";
	int scan;
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
		fopen(info, "w");
	}
	return file;
}
