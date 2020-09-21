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
/* Implement the Accept state of the DFA. After       */
/* accepting the buffer with the text input, uses if  */
/* and while statements to check if the buffer at i   */
/* has /* to indicate comment. Then determines if     */
/* the comment is terminated without reaching the     */
/* end of the buffer string before calling the erase  */
/* function to erase the given comment. If the comment*/
/* is unterminated, the state is set to reject, and   */
/* the newlinecount function is called to print an    */
/* error at the specific line it occurs. The program  */
/* then loops and returns the state given a break     */
/* condition.                                         */
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

/*------------------------------------------------------*/
/* The main code of the program. After initializing the */
/* varaibles and setting state to Accept, uses a while  */
/* loop to fill buffer[] with getchar() from input file.*/
/* It then checks if the buffer is empty, and if so,    */
/* outputs an error file. After this, the code then uses*/
/* while and if statements to check the various cases   */
/* that have to be excluded for the program to properly */
/* remove any comments. If a comment is found with      */
/* the correct syntax to be removed, handleAcceptstate  */
/* is then called, checking if the DFA will Accept or   */
/* Reject the buffer for comment removal. If Accept, the*/
/* code will state "EXIT_SUCCESS" and print the         */
/* decommented text. If Reject, the code will state     */
/* "EXIT_FAILURE" and end.                              */

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
        printf(buffer);
        printf("EXIT_SUCCESS");
    }
    return 0;
}

/*--------------------------------------------------------*/
/* Function newlinecount for use in the handleAcceptstate */
/* function. Uses an if loop nested within a while loop to*/
/* check every character of buffer[] while increasing the */
/* newline count every time a new line indicator is found.*/
/* Function then returns the newline count as an integer. */
/*--------------------------------------------------------*/

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

/*--------------------------------------------------------*/
/* Function erase for use in the handleAccpetstate        */
/* function. Uses an if loop nested within a while loop to*/
/* first check if buffer[i] is a new line and increment i */
/* by 1, as new line characters should not be erased.     */
/* The function then sets buffer[i] to buffer of [i+1],   */
/* replacing buffer[i] with buffer[i+1] until buffer[i] is*/
/* replaced with j. This then ends the loop and has       */
/* effectively "erased" buffer[i] to buffer[j].           */
/*--------------------------------------------------------*/

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