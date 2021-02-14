#include "headerfile.h"

/* Created by: Harish. Date Created: 12 Dec 2018 */
/* header files required: stdio.h, unistd.h */
/* ProgBar: prints the progress bar in stdout, accepts a progress string, returns 0 if succeeded, -1 if failed and if argument > 100 */
int ProgBar(char* str, int end, useconds_t usec)
{
	int start = 1;
	if (end > 100 || end < 0) {
		fprintf(stderr, "error: end value is out of range! Progress bar must not be more than 100%% and less than 0%%.\nProgram terminated.\n");
		return -1;
	}

	printf(BOLDRED "%s [", str);
	while (start <= end && start <= 100) {
        if (start == 26)
            sleep(1);
        else if (start == 51)
            sleep(1);
		else if (start == 76) {
			printf(BOLDMAGENTA"");
            sleep(1);
        }else if (start == 86) {
			printf(BOLDGREEN"");
            sleep(1);
        }
		printf("-");
		usleep(usec);				/* sleep for usec */
		fflush(stdout);
		printf("] %3d%%", start++);		/* prints the progress */
		fflush(stdout);
		printf("\b\b\b\b\b\b");
		fflush(stdout);
	}

	int i = end;
	while (i <= 100) {
		printf(" ");
		fflush(stdout);
		++i;
	}
	if (--start == end) {
		if (start > 85 && start <= 100) {
			printf(BOLDRED "\b]" BOLDGREEN " %d%% Done. Succeded.\n" RESET, start);
			return 0;
		} else if (start > 75 && start <= 85) {
			printf(BOLDRED "\b]" BOLDMAGENTA " %d%% Done.\n" RESET, start);
			return 0;
		} else if (start <= 75) {
			printf("\b] %d%% Sorry. Failed. Try Again Later.\n" RESET, start);
			return 0;
		}
	} else
		return -1;
}
