#include <stdio.h>
#include <ctype.h> /* isPrint(), isSpace()  */
#include <stdbool.h> 
#include <string.h>

#define MAXLINE 1000
#define MAXLENGTH 10000

#define EMPTY 0
#define CODE 1
#define COMMENT 2
#define ERROR 3


/* program to delete comments */
int getlines(char line[], int limit);
int length(char str[]);
void removeComments(char from[], char to[]);

/* global variables */
int STATE = CODE;
int isOnlyWhiteSpace = 0;

/* main function */
int main()
{
    char line[MAXLINE]; 
    char lineWithoutComments[MAXLINE];

    while ((getlines(line, MAXLINE)) > 0) {  /* for every input line */
        removeComments(line, lineWithoutComments); /* delete comment */
        if (strlen(lineWithoutComments) > 0) {

            /* don't show line with only whitespaces characters */ 
            /* after deleted ansi c styly comment */
            int i;
            for (i = 0; i < strlen(lineWithoutComments); i++) {
                if (!isspace(lineWithoutComments[i])) {
                    isOnlyWhiteSpace = 1;
                    break;
                }
                else {
                    isOnlyWhiteSpace = 0;
                }
            }
            /* if we have printable characters in line then show that line */
            if (isOnlyWhiteSpace == 1) {
                printf("%s\n", lineWithoutComments);
            }
        }
        if (line[0] == '\n') { /* if the line is empty then simply print it */
            printf("\n");
        } 
    }

    return 0;
}

int getlines(char s[], int limit)
{
    int c, i;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c!='\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int length(char str[])
{
    int i;
    i = 0;

    while (str[++i] != '\0') {} 

    return i - 1; /* -1 because last char is \n and we don't want count them */
}

void removeComments(char from[], char to[]) 
{
    int i; /* iterator for from */
    int j; /* iterator for to*/
    int nOpen; /* counter for open chars of comment */
    int nClose; /* counter for close chars of comment */

    j = 0;
    nOpen = 0;
    nClose = 0;

    /* TO DO */
    /* 1. add multi line 
       comment support 
       like this */

    /* check char by char from line */
    for (i = 0; i < length(from); i++) { 
        /* check if the comment's start */
        if (from[i] == '/' && from[i+1] == '*') {
            nOpen++;
            if (nOpen == 1) {
                STATE = COMMENT;
            }
            if (nOpen > 1) {
                STATE = ERROR;
            }
        }
        /* check if the comment's end */
        else if (from[i] == '*' && from[i+1] == '/') {
            nClose++;
            if (nClose == 1) {
                if (STATE == CODE) {
                    STATE = ERROR;
                }
                /* if we have correct end of comment we must set i variable */ 
                /* after the chars of end comment = i + 2 */
                if (STATE == COMMENT) {
                   STATE = CODE; 
                   i = i + 2; /* we must set i behind end of comments */
                }
            }
            if (nClose > 1) {
                STATE = ERROR;
            }
        }
        else if (STATE == CODE) {
            /* we have code + comment in line */
            to[i] = from[j++];
        }
    }
    if (STATE == CODE) {
        to[j] = '\0';
    }
}

