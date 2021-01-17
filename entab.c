#include <stdio.h>

#define TABSTOP 8
#define MAXLINE 1000
#define MAXLINES 1000

int length(char string[]);/* funkcja zwraca ilosc znakow w podanym stringu*/
int getline(char line[], int lim);
void copy(char to[], char from[]);
void entab(char to[], char from[]);
int getNextTabstop(int currentPosition, int tabstop);
int checkInsertTab(char str[], int begin, int end);

int main(void)
{
    char line[MAXLINE];
    /* char lines[MAXLINES]; */
    char output[MAXLINES];

    while ((getline(line, MAXLINE)) > 0)
        entab(output, line); /* biore biezaca linie i entabuje */

    return 0;
}

int length(char s[])
{
    int i;
    i = 0;
    while (s[i] != '\0')
        ++i;

    return i-1; /* -1 bo nie chcemy znaku nowej linii \n */
}
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;
    i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}

void entab(char to[], char from[])
{
    int i; /* iterator dla tablicy from */
    int j; /* iterator dla tablicy to */
    int shift;
    int nextTabstop;
    int len; /* przechowuje dlugosc stringa */


    len = length(from); /* wyliczamy dlugosc tablicy to */

    shift = 0;
    /* wykonujemy petle po wszystkich elementach tablicy from */
    for (i = 0, j = 0; i < len; i++, j++) {
        nextTabstop = getNextTabstop(i + shift, TABSTOP);

        if (from[i] != ' ') { /* kopiujemy wszystkie znaki poza spacja */
            to[j] = from[i];

            if (from[i] == '\t') /* a gdy skopiowalismy TABa to ustawiamy przesuniecie */
                shift += nextTabstop - i;
        }
        else { /* jezeli mamy spacje to */
            if (checkInsertTab(from, i, nextTabstop - shift)) { /* spr czy mozemy wstawic TAB */
                to[j] = '\t'; /* jesli tak to wstawiamy taba */
                i = nextTabstop - shift; /* i przenosimy sie za spacje ktore zastapilismy TAB */
            }
            else 
                to[j] = ' ';
        }
    }

    to[j] = '\0';

    printf("\n%s%s\n", from, to);
}

int getNextTabstop(int currentPosition, int tabstop) {
    int nextTabstopPosition;

    if (currentPosition <= tabstop - 1)
        nextTabstopPosition = tabstop - 1; /* ustawiamy najblizszy TABSTOP */
    else {                       /* lub w razie potrzeby */
        nextTabstopPosition = tabstop - 1;
        while (currentPosition > nextTabstopPosition)
            nextTabstopPosition += tabstop; /*ustawiamy kolejny TABSTOP > i*/
    }
    return nextTabstopPosition;
}

int checkInsertTab(char str[], int begin, int tabstop) {
    int i;
    int isSpace = 1;
    int spaceCount;

    spaceCount = 0;

    for (i = begin; i <= tabstop; i++) {
        if (str[i] == ' ') {
            spaceCount++;
        }

        if (str[i] != ' ') {
           isSpace = 0;
           break;
        }

        /* jezeli mam wstawic TABa to musze obliczyc czy jego szerokosc */
        /* bedzie rowna zastepowanym spacja */
    }
    return isSpace;
}
