#include <stdio.h>

#define MAXLINELENGTH 80
#define MAXLINE 1000
#define MAXLINES 1000

/* program to wrap lines */
int getline(char line[], int limit);
void wrapLines(char str[], int maxLineLength);

int main()
{
    char line[MAXLINE]; 
    char wrappedLines[MAXLINES];

    while ((getline(line, MAXLINE)) > 0)
        wrapLines(line, MAXLINELENGTH);

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

void wrapLines(char str[], int maxLineLength)
{
    /* TO DO */
    printf("%s", wrappedLines);
}
