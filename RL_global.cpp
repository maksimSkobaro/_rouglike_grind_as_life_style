#include "RL_global.h"

////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DEFINITION////////////////////
////////////////////////////////////////////////////////////



int log(const char *logString, const char *const logFileName)
{
	FILE *logfile;

	if(fopen_s(&logfile, logFileName, "a"))
	{
		exit(ERR_FILE);
	}

	char date[64];
	time_t currentSecond = time(0);
	ctime_s(date, 64, &currentSecond);
	strchr(date, '\n')[0] = '\0';

	fprintf_s(logfile, "[%s] : %s\n", date + 4, logString);

	fclose(logfile);

	return ERR_NO_ERR;
}

int getInt(const char *prompt, int a, int b)
{
	int retVal = 0;
	do
	{
		putchar('\n');
		fputs(prompt, stdout);
		scanf_s("%i", &retVal);
	} while(retVal > b || retVal < a);
	return retVal;
}

void swapInt(int &a, int &b)
{
	int c = a; a = b; b = c;
}

void readList(const char *listPath)
{
	FILE *pListToRead = nullptr;

	if(fopen_s(&pListToRead, listPath, "r"))
	{
		exit(ERR_FILE);
	}

	system("cls");

	char oneStr[FILE_ONE_LINE_SYMBS_MAX]{};
	while(!feof(pListToRead))
	{
		fgets(oneStr, FILE_ONE_LINE_SYMBS_MAX, pListToRead);
		fputs(oneStr, stdout);
	}

	puts("По прочтении нажмите любую кнопу . . .");
	_getch();

	fclose(pListToRead);
}