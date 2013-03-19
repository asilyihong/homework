#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void itoa_rec(int v, char s[], int index, int sign);
void reverse(char s[]);

int main(int argc, char **argv)
{
    char sr[256] = {'\0'};
    int i = -28765;
    itoa_rec(i, sr, 0, 0);
    printf("result: %s from: %d\n", sr, i);

    return EXIT_SUCCESS;
}

void itoa_rec(int v, char s[], int index, int sign)
{
    if (0 > v)
    {
	itoa_rec(-v, s, index, -1);
    } 
    else if (0 < v)
    {
	s[index] = (v % 10)+ '0';
	itoa_rec(v / 10, s, index + 1, sign);
    }
    else
    {
	if (0 > sign)
	    s[index] = '-';
	
	reverse(s);
    }
}

void reverse(char s[])
{
    int i, j;
    char tmp;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
	tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
    }
}
