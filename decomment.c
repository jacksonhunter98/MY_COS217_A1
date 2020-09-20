/*----------------------------------------------------*/
/* decomment.c                                        */
/* Author: Jackson Hunter                             */
/* Cos217 Assignment 1                                */
/*----------------------------------------------------*/

# include <stdio.h>
# include <ctype.h>

enum Statetype {Accept, Reject};
void erase(char buffer[300], int i, int j);
int newlinecount(char buffer[300], int i);

/*----------------------------------------------------*/
/* Implement the Accept state of the DFA.             */
/*----------------------------------------------------*/

enum Statetype handleAcceptstate(char buffer[300], int i, int j)
{   enum Statetype state;
    int begin;
    int end;
    int nlc;

    if (buffer[i] == '/' && buffer[i+1] == '*')
    {   begin = i;
        while (buffer[i+j] != '\0')
        {   if(buffer[i+j] == '*' && buffer[i+j+1] == '/')
            {   
                end = i+j+1;
                erase(buffer, begin, end);
                break;
            }
            else if(buffer[i+j+1] == '\0')
            {   
                state = Reject;
                nlc = newlinecount(buffer, i);
                printf("Error: line %d: unterminated comment", nlc);
                break;
            }
            j++;
        }
    }
    return state;
}

int main(void)
{   char buffer[300];
    int i, j, k, c;
    enum Statetype state = Accept;
    i = 0;
    j = 0;
    k = 0;

    while ((c = getchar()) != EOF)
    {
        buffer[k] = c;
        k++;
    }

    if (buffer == NULL)
    {   
        printf("ERROR: FILE DOES NOT EXIST");
        return(0);
    }
    
    while (buffer[i+1] != '\0')
    {   
        if (state == Accept)
        {   
            if (buffer[i] == '"' && buffer[i-1] != '\\') 
            {
                i++;
                while (buffer[i] != '\0')
                {
                    if(buffer[i] == '"' && buffer[i-1] != '\\')
                    {
                        i++;
                        break;
                    }
                    i++;
                }
            }
            if (buffer[i] == '\'' && buffer[i-1] != '\\')
            {
                i++;
                while (buffer[i] != '\0')
                {
                    if(buffer[i] == '\'' && buffer[i-1] != '\\')
                    {
                        i++;
                        break;
                    }
                    i++;
                }
            } 
            state = handleAcceptstate(buffer, i, j);
        }
        if (state == Reject)
        {   
            printf("EXIT_FAILURE");
            break;
        }

        i++;
    }

    if (state == Accept)
    {   
        while ((c = getchar(buffer)) != EOF)
        {
            putchar(c);
        }
        printf("EXIT_SUCCESS");
    }
    return 0;
}

int newlinecount(char buffer[300], int i)
{   
    int c = 0;
    int newline = 0;
    while (c != i)
    {
        if (buffer[c] == '\n')
        {
            newline++;
        }
        c++;
    }
    return newline;
}

void erase(char buffer[300], int i, int j)
{
    while (i != j)
    {
        if (buffer[i] != '\n')
        {
            i++;
        }
        buffer[i] = buffer[i+1];
        i++;
    }
    
}