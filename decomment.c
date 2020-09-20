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
                fprintf("Error: line %d: unterminated comment", nlc);
                break;
            }
            j++;
        }
    }
    return state;
}

int main(int argc, char** argv)
{   char buffer[300];
    int i, j;
    FILE *filedes;
    enum Statetype state = Accept;
    i = 0;
    j = 0;
    filedes = fopen(argv[1], "r+");

    if (filedes == NULL)
    {   
        fprintf("ERROR: FILE DOES NOT EXIST");
    }
    fread(&buffer, sizeof(char), 300, filedes);
    
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
            fprintf("EXIT_FAILURE");
            break;
        }

        i++;
    }

    if (state == Accept)
    {   
        fwrite(&buffer, sizeof(char), 300, filedes);
        fprintf("EXIT_SUCCESS");
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