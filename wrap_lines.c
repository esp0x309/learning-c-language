#include <stdio.h>

#define WRAPLINE 4 
#define MAXLINE 1000
#define MAXLENGTH 10000 

/* program to wrap lines */
int getline(char line[], int limit);
int length(char str[]);
void mergeLines(char from[], char to[]);
void wrapLines(char str[], int maxLineLength);

int main()
{
    char line[MAXLINE]; 
    char mergedLines[MAXLENGTH];

    while ((getline(line, MAXLINE)) > 0) { /* for every input line */
        mergeLines(line, mergedLines); /* merge them with others */
    }

    /* printf("%s", mergedLines); */
    wrapLines(mergedLines, WRAPLINE); 

    return 0;
}

int getline(char s[], int limit)
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

    return i-1; /* -1 because last char is \n and we don't want count him */
}

void mergeLines(char from[], char to[])
{
    int i;
    int shift;

    i = 0;
    shift = 0;

    while (to[i++] != '\0') { /* check where where is end of string to  */
        ++shift; /* merge next line to end of prev */ 
    }

    for (i = 0; i < length(from); i++) { /* merging */
        to[i + shift] = from[i];
    }
    /* if line doesnt ended by ' ' or \t then add ' ' to separate lines */
    if (to[i - 1 + shift] != ' ' && to[i - 1 + shift] != '\t') /* last char of to */
        to[i + shift] = ' ';
}
void wrapLines(char str[], int maxLineLength)
{
    /* TO DO */
    int i;
    for (i = 0; i <= length(str); i++) {
        printf("%c", str[i]);
        if ((i+1) % maxLineLength == 0)
            printf("\n");
    }
}
