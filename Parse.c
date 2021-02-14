#include "headerfile.h"

void Search(char *line, FILE* dest_fp)
{
#if 1
    char parse[MAXLINE];

    int i = 0, j = 0;
    extern int brace;
    

        if (brace) {
        fprintf(dest_fp, "\n ");
        for (int k = 1; k < brace-1; k++)
            fprintf(dest_fp, "\t");
        }


    while (*(line + i))
    {
        /* comments */
        if (*(line + i) == '/' && *(line + i + 1) == '*') {
            parse[j++] = *(line + i); parse[j++] = *(line + i + 1);
            ++i;
            ++i;

            while (*(line + i)) {
                parse[j++] = *(line + i);
                if (*(line + i) == '*') {
                    ++i;
                    if (*(line + i) == '/') {
                        parse[j++] = *(line + i);
                        parse[j] = '\0';
                        j = 0;
                        fprintf(dest_fp, "<element style=\"color: #191970;\"> %s</element>", parse);
                    }
                }
                ++i;
            }

            ++i;
        }


        /* find the character and string literals */
        else if (*(line + i) == '\"' || *(line + i) == '\'')
        {
            parse[j++] = *(line + i++);
            while (*(line + i) != '\"' && *(line + i) != '\'')
                parse[j++] = *(line + i++);
            parse[j++] = *(line + i);
            parse[j] = '\0';
            fprintf(dest_fp, "<element style=\"color: #EE82EE;\">%s</element>", parse);
             ++i;
            j = 0;
        }
        
        /* find the pre-processor directives */
        else if (*(line + i) == '#') 
        {
            j = 0;
            while (*(line + i) != '\0' && *(line + i) != '<' && *(line + i) != '\"')
                parse[j++] = *(line + i++);
            parse[j] = '\0';
            fprintf(dest_fp, "<element style=\"color: #FF0000;\">%s</element>", parse);
            j = 0;
            while (j < MAXLINE)
                parse[j++] = 0;
            if (*(line + i) == '\"') {
                j = 0;
                while(*(line + i) != '\0' && *(line + i) != '\n')
                    parse[j++] = *(line + i++);
                parse[j++] = '\0';
            }
            else if (*(line + i) == '<')  {
                j = 0;
                parse[j++] = '&';
                parse[j++] = 'l';
                parse[j++] = 't';
                ++i;
            while (*(line + i) != '\0' && *(line + i) != '>') {
                parse[j++] = *(line + i++);
            }
                if (*(line + i) == '>') {
                    parse[j++] = '&';
                    parse[j++] = 'g';
                    parse[j++] = 't';
                    ++i;
                }
                parse[j] = '\0';
            }
            fprintf(dest_fp, "<element style=\"color: #FFFF00;\">%s</element>", parse);
            j = 0;
            while (j < MAXLINE)
                parse[j++] = 0;
            ++i;
        }


        /* find the operator symbols */
        else if (!isalnum(*(line + i)) && Operator(line + i) && *(line + i) != ' ')
        {
            fprintf(dest_fp, "<element style=\"color: #A52A2A;\"><span class=\"backspace\"></span>%c</element>", *(line + i));
            ++i;
        }


        /* find the keywords and identifiers */ 
        else if (isalpha(*(line + i)))
        {
            while (*(line + i) != ' ' && isalpha(*(line + i))) 
                parse[j++] = *(line + i++);
            parse[j] = '\0';

            if (Keyword(parse))
                fprintf(dest_fp, "<element style=\"color: #006400;\"> %s</element>", parse);
            else
                fprintf(dest_fp, "<element style=\"color: #000000;\"> %s</element>", parse);
            j = 0;
        }
        
        /* find the lonely integer literals */
        else if (isdigit(*(line + i)))
            fprintf(dest_fp, "<element style=\"color: #EE82EE;\"><span class=\"backspace\"></span>%c</element>", *(line + i++)); 
        
        else 
            ++i;
    }
#else
    printf("%s\n", line);
#endif
}
