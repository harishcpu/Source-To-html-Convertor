#include "headerfile.h"

int brace;

int main(int argc, char *argv[]) 
{
    extern int brace;
    FILE* fptr, *dest_fp;
    char ext[3] = ".c";
    char buf[FILESIZE], line[MAXLINE];
    
    system("clear");
    printf("\t\t\t" BOLDRED "Source To HTML" RESET "\n");
    printf("\t\t\t--------------" RESET "\n");
/* Open only files with ".c" extension */
    if(argv[1]) {
        if (NULL != strstr(argv[1], ext)) {
            fptr = fopen(argv[1], "r");
            printf("OPENING : %-10s : " BOLDRED "Success" RESET "\n", argv[1]);
        }
    if(argv[2]) {
            dest_fp = fopen(argv[2], "w+");
            printf("OPENING : %-10s : " BOLDRED "Success" RESET "\n", argv[2]);
        } else {
            fclose(fptr);
            printf("USAGE : ./a.out <filename.c> <filename.html>\n");
            return 0;
    }
    } else {
        printf("USAGE : ./a.out <filename.c> <filename.html>\n");
        return 0;
    }
    
/* copy file contents to buffer */
    int ch, i = 0, j = 0;
    while ((ch = fgetc(fptr)) != EOF && i < FILESIZE)
        buf[i++] = ch;
    buf[i++] = '\n';
    buf[i] = '\0';


    /* Add HTML begining tags into destination file */
	fprintf(dest_fp, "<!DOCTYPE html>\n");
	fprintf(dest_fp, "<html lang=\"en-US\">\n");
	fprintf(dest_fp, "<head>\n");
	fprintf(dest_fp, "<title>SOURCE CODE TO HTML</title>\n");
	fprintf(dest_fp, "<meta charset=\"UTF-8\">\n");
	fprintf(dest_fp, "<link rel=\"stylesheet\" href=\"styles.css\">\n");
	fprintf(dest_fp, "</head>\n");
	fprintf(dest_fp, "<body style=\"background-color:lightgrey;\">\n");
	fprintf(dest_fp, "<pre>\n");



/* Start Parsing */
    printf("\n" "PARSING : %s : " BOLDRED "Started" RESET "\n\n", argv[1]);
    printf("\t"BOLDGREEN "CONVERTING " BOLDBLACK "%s " BOLDGREEN "TO" BOLDBLACK " %s ..." RESET "\n\n", argv[1], argv[2]);
	ProgBar("STARTED", 100, 50000);
    i = 0;
    int lastb = 0;
    while (*(buf + i) != '\0') 
    {
        j = 0;
        while ((ch = *(buf + i)) != '\n') 
        {
            if (ch == '{') 
                ++brace;
            else if (ch == '}') 
                --brace;
 
            line[j++] = ch;
            ++i;
        }
        line[j] = '\0';

        
        if (!brace)
            fprintf(dest_fp, "\n");

            Search(line, dest_fp);

        for (int k = 0; k < MAXLINE; k++)
            line[k] = 0;
        ++i;
    }


    printf("\n\t" BOLDGREEN "CONVERSION SUCCESSFUL" RESET "\n");
    sleep(2);
    printf("\nPARSING : %s : " BOLDRED "Done" RESET "\n", argv[1]);

    /* Add HTML closing tags into destination file */
	fprintf(dest_fp, "</pre>\n");
	fprintf(dest_fp, "</body>\n");
	fprintf(dest_fp, "</html>\n");

    fclose(fptr);
    fclose(dest_fp);
    return 0;
}


int Keyword(char *str)
{
    char *keyword[] = {"auto", "break", "case", "char", "const", 
			"continue", "default", "do", "double", 
			"else", "enum", "extern", "float", "for", 
			"goto", "if", "int", "long", "register", 
			"return", "short", "signed", "sizeof", 
			"static", "struct", "switch", "typedef", 
			"union", "unsigned", "void", "volatile",
			"while", NULL,
		      };

    int i = 0;
    while (*(keyword + i) != NULL) {
        if (!strcmp(*(keyword + i), str))
            return 1;
        ++i;
    }
    return 0;
}


int Operator(char *str)
{
    char *operator[] = {"()", "[]", "->", ".",
        "!", "~", "++", "--", "+", "-", "(type)", "*", "&", "sizeof",
        "*", "/", "%",
        "+", "-",
        "<<", ">>",
        "<", "<=", ">", ">=",
        "==", "!=",
        "&",
        "^",
        "|",
        "&&",
        "||",
        "?:",
        "=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=",
        ",", NULL,
    };

    int i = 0;
    while (*(operator + i) != NULL) {
        if ((strcmp(*(operator + i), str)))
            return 1;
        ++i;
    }
    return 0;
}

