#include <ctype.h>

double atof(char s[])
{
    double val, power, e_power = 1.0;
    int i, j, sign, e_sign, e_val;

    for (i = 0; isspace(s[i]); i ++)
	;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
	i++;
    for (val = 0.0; isdigit(s[i]); i++)
	val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
	i++;
    for (power = 1.0; isdigit(s[i]); i++) {
	val = 10.0 * val + (s[i] - '0');
	power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E')
    {
	i++;
	e_sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
	    i++;
	for (e_val = 0; isdigit(s[i]); i++)
	    e_val = 10 * e_val + (s[i] - '0');

	if (e_sign > 0)
	    for (j = 0; j < e_val; j++) 
		e_power *= 10.0;
	else 
	    for (j = 0; j < e_val; j++)
		e_power /= 10.0;
    }

    return sign * val / power * e_power;
}

int atoi(char s[])
{
    int i, val, sign;
    for (i = 0; isspace(s[i]); i ++)
	;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
	i++;
    for (val = 0; isdigit(s[i]); i++)
	val = 10 * val + (s[i] - '0');
    return sign * val;
}
