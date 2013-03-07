#include <stdio.h>
#include <stdlib.h>	/* for atof() */
#include <math.h>

#define MAXOP   100	/* max size of operand or operator */
#define NUMBER  '0'

int getop(char []);
void push(double);
double pop(void);
double get_last(void);
void duplicate_top(void);
void swap_top_two(void);
void clear_stack(void);

/* reverse Polish calculator */
int main(int argc, char **argv)
{
    int type;
    double op2 = 0.0;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
	switch(type) {
	case NUMBER:
	    push(atof(s));
	    break;
	case '+':
	    push(pop() + pop());
	    break;
	case '*':
	    push(pop() * pop());
	    break;
	case '-':
	    op2 = pop();
	    push(pop() - op2);
	    op2 = 0.0;
	    break;
	case '/':
	    op2 = pop();
	    if (op2 != 0.0)
		push(pop() / op2);
	    else
		printf("Error: zero divisor\n");
	    op2 = 0.0;
	    break;
	case '%':   /* ex 4.3: add modulus operator */
	    op2 = pop();
	    if (op2 != 0.0)
		push((int)pop() % (int) op2);
	    else
		printf("Error: zero divisor\n");
	    op2 = 0.0;
	    break;
	case 't':   /* ex 4.4: add command to print the top element */
	    printf("print top element: \t%.8g\n", get_last());
	    break;
	case 'd':   /* ex 4.4: add command to duplicate the top element */
	    duplicate_top();
	    break;
	case 'w':   /* ex 4.4: add command to swap top two elements */
	    swap_top_two();
	    break;
	case 'c':   /* ex 4.4: add command to clear stack */
	    clear_stack();
	    break;
	case 's':   /* ex 4.5: add sign command */
	    push(sin(pop()));
	    break;
	case 'p':   /* ex 4.5: add pow command */
	    op2 = pop();
	    /* asil: need add a error handler here for pow? */
	    {
		double op3 = pop();
		if (op3 > 0)
		    push(pow(op3, op2));
		else 
		    push(pow(op3, (int)op2));
	    }
	    op2 = 0.0;
	    break;
	case 'e':   /* ex 4.5: add exp command */
	    push(exp(pop()));
	    break;
	case '\n':
	    printf("\t%.8g\n", pop());
	    break;
	default:
	    printf("Error: unknow command ((%s))\n", s);
	    break;
	}
    }
    return 0;
}

#define MAXVAL  100	/* maximum depth of val stack */

int sp = 0;		/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack*/
void push(double f)
{
    if (sp < MAXVAL)
	val[sp++] = f;
    else 
	printf("Error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
	return val[--sp];
    else {
	printf("Error: stack empty in pop\n");
	return 0.0;
    }
}

/* ex 4.4: add a command to print the top element */
/* get_last: get the last element without popping it */
double get_last(void)
{
    if (sp > 0)
	return val[sp - 1];
    else {
	printf("Error: stack empty in get last\n");
	return 0.0;
    }
}

/* ex 4.4: add a command to duplicate the top element of the stack */
/* duplicate_top: duplicate the top element of the stack */
void duplicate_top(void)
{
    if (sp <= 0)
	printf("Error: stack empty in duplicate top\n");
    else if (sp < MAXVAL - 1) {
	val[sp] = val[sp - 1];
	sp++;
    } else 
	printf("Error: out of stack bound");
}

/* ex 4.4: add a command to swap the top two elements */
/* swap_top_two: swap the top two elements */
void swap_top_two(void)
{
    if (sp > 1) {
	double tmp = val[sp -1];
	val[sp - 1] = val[sp - 2];
	val[sp - 2] = tmp;
    } else {
	printf("Error: stack has less than two element");
    }
}

/* ex 4.4: add a command to clear stack */
/* clear_stack: clear the stack */
void clear_stack(void)
{
    sp = 0;
    val[sp] = 0.0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
	;
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
	return c;	/* not a number */
    }
    i = 0;
    if (isdigit(c))	/* collect integer part */
    {
	while (isdigit(s[++i] = c = getch()))
	    ;
    }
    if (c == '.')	/* collect fraction part */
    {
	while (isdigit(s[++i] = c = getch()))
	    ;
    }
    s[i] = '\0';
    if (c != EOF)
	ungetch(c);
    return NUMBER;
}


#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;	    /* next free postition in buf */

int getch(void)	/* get a (possibly pushed back) character */
{
    return (bufp > 0)? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
	printf("ungetch: too mayn characters\n");
    else
	buf[bufp++] = c;
}
