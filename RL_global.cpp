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