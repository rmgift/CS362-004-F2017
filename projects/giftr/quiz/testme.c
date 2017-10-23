#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

char inputChar()
{	// TODO: rewrite this function
	// ASCII base character range is 0 to 127
	// exclude all values less than 32, as they're not in our testing range
	// also exclude value 126 and 127
	// value = ((rand() % (maxValue - minValue + 1)) + minValue)
	// min value = 32 && maxValue = 125
	int minVal = 32, maxVal = 125;
	char newC = ((rand() % (maxVal - minVal + 1)) + minVal);
	return newC;
}

char *inputString()
{	// TODO: rewrite this function
	// ASCII base character range for lowercase letters is 97 to 122
	// value = ((rand() % (maxValue - minValue + 1)) + minValue)
	char *newS = malloc(6 * sizeof(char));
	memset(newS, '\0', sizeof(newS));
	int i;
	// only need ASCII values from e to t so limit or else it takes forever
	int min = 101, max = 116;
	for (i = 0; i < 5; i++)
	{
		newS[i] = ((rand() % (max - min + 1)) + min);
	}
	newS[5] = '\0';
	return newS;
}

void testme()
{
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;
	while (1)
	{
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
		// if char is [ = ascii value 91 and state is 0, set state to 1
		if (c == '[' && state == 0) state = 1;
		// if char is ( = ascii value 40 and state is 1, set state to 2
		if (c == '(' && state == 1) state = 2;
		// if char is { = ascii value 123 and state is 2, set state to 3
		if (c == '{' && state == 2) state = 3;
		// if char is a space = ascii value 32 and state is 3, set state to 4
		if (c == ' '&& state == 3) state = 4;
		// if char is a = ascii value 97 and state is 4, set state to 5 
		if (c == 'a' && state == 4) state = 5;
		// if char is x = ascii value 120 and state is 5, set state to 6
		if (c == 'x' && state == 5) state = 6;
		// if char is } = ascii value 125 and state is 6, set state to 7
		if (c == '}' && state == 6) state = 7;
		// if char is ) = ascii value 41 and state is 7, set state to 8
		if (c == ')' && state == 7) state = 8;
		// if char is ] = ascii value 93 and state is 8, set state to 9
		if (c == ']' && state == 8) state = 9;
		// if string is reset\0 and state is 9, print out error
		// reset\0 ascii value = 114 101 115 101 116 10 
		if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9)
		{
			printf("error ");
			exit(200);
		}
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
