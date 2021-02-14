/* Title : WAP to print “Hello” in X format. */

#include <stdio.h>

#define MAXDIMENSION 30
#define MINDIMENSION 0
int main()
{
	int row, column, lineCount, lines;
	char option;
	do
	{
		printf("Enter the dimension used for Hello World printing. \n");
		printf("Dimension: ");
		scanf("%d", &lineCount);
		if (lineCount > MAXDIMENSION)
		{
			printf("lineCount is Not valid number\n");
			return 1;
		}
		if (lineCount < MINDIMENSION) 
		{
			printf("lineCount is Not valid number\n");
			return 1;
		}
		lines = lineCount;

		if(lineCount % 2 != 0)
		{
			lineCount = lineCount + 1;
		}

		for(row = 0 ; row < lineCount; row++ )
		{
			for(column = 0; column < lineCount; column++ )
			{
				if(row == lineCount / 2 && lines % 2 != 0 )
				{
					continue;
				}
				if(row == column || column == (lineCount - 1) -row)
				{
					printf("hello");
				}
				else
				{
					printf("  "); /*else space is printed*/
				}
			}
			/* if actual lines was odd, then when the row is half of linecount then skip printing newline */
	if(row == lines / 2 && lines % 2 != 0 )
	{
		continue;
	}
			else
			{
				printf("\n"); /*after every row, a new line*/
			}	
		}

		/* check for continue */
		printf("Continue (y/n): ");
		scanf("\n%c", &option);

		if ( option == 'y' )
		{
			continue;
		} else
		{
			break;
		}

	} while (1);
	return 0;
} 
