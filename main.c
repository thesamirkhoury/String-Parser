/**
 * Author - Samir Khoury
 * String Parser
 * Takes an input from the user and coutns how many words and the sum of all letters despite spaces.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 510
#define TRUE 1
#define FALSE 0

#define word 0
#define letter 1

#define EXIT 1
#define HISTORY 2
#define NON -1

int *wordCounter(char *str);
int writeHistory(char *str);
int printHistory();
int parseCommand(char *str);

int main() {
    char input[MAX_LEN + 1];
    char historyCopy[MAX_LEN + 1];
    while (1){
        printf("Enter String, or \"exit\" to end program:\n");

        //user input.
        fgets(input, MAX_LEN, stdin);
        //removing the last '\n' character.
        if((strlen(input) > 0) && (input[strlen(input) - 1] == '\n')){
            input[strlen(input) - 1]='\0';
        }

        strcpy(historyCopy,input);
        int command= parseCommand(input);
        int *count=wordCounter(input);

        //check if user entered the command "exit" despite spaces.
        if(command==EXIT && count[word] == 1 && count[letter] == 4){
            free(count);
            exit(EXIT_SUCCESS);
        }
        //check if user entered the command "history" despite spaces.
        else if(command==HISTORY && count[word] == 1 && count[letter] == 7){
            printHistory();
            free(count);
        }
        else if(count[word] == 0 && count[letter] == 0){
            continue;
        }
        else{
            writeHistory(historyCopy);
            printf("%d words\n%d chars\n", count[word], count[letter]);
            free(count);
        }
    }
}

/**
 * Counts how many words in a string, and the sum of letters in every word despite spaces.
 * @param str
 * @return int array were count[0] is the word count, and count[1] is the sum of all letters in the word
 */
int *wordCounter(char *str){
    int *count=(int*) malloc(sizeof (int)*2);
    if(count==NULL){
        printf("Error: can not allocate memory!\n");
        exit(EXIT_FAILURE);
    }
    count[word]=0;
    count[letter]=0;

    char * token = strtok(str, " ");//breaks a string very space character.
    while( token != NULL ) {
        count[letter]=(int)count[letter]+((int)strlen(token));
        token = strtok(NULL, " ");
        count[word]++;
    }

    return count;
}
/**
 * Writes a strong to a locally stored txt file.
 * @param str
 * @return 1 if successful, 0 otherwise.
 */
int writeHistory(char *str){
    FILE *fp= fopen("file.txt","a");

    if (fp==NULL){
        printf("Error: can not open file!\n");
        return FALSE;
    }
    fprintf(fp,"%s\n", str);
    fclose(fp);
    return TRUE;
}
/**
 * Prints the strings written in the locally stored txt file.
 * @return 1 if successful, 0 otherwise.
 */
int printHistory(){
    char buff[MAX_LEN+1];
    int i=0;

    FILE *fp= fopen("file.txt","r");
    if (fp==NULL){
        return FALSE;
    }
    while (fgets(buff, sizeof (buff), fp) != NULL){
        printf("%d: %s",i,buff);
        i++;
    }
    fclose(fp);
    return TRUE;
}
/**
 * parses a string and checks for the word "exit" or "history", despite spaces.
 * @param str
 * @return 1 if exit, 2 if history, -1 otherwise.
 */
int parseCommand(char *str){
    char *exit=strstr(str,"exit");
    if(exit!=NULL){//checks the first instance of "exit" int the user input.
        return EXIT;
    }
    else{
        char *history=strstr(str,"history");
        if(history!=NULL){//checks the first instance of "history" int the user input.
            return HISTORY;
        } else{
            return NON;
        }
    }
}