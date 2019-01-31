#include<stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum { subtract = 0, add = 1};

int assignIslanders(int* islanders);
void allowChoice(int* islanders);
void processChoice(int* islanders);
void takeGuess(int* islanders, int rightAnswer);
void printArray(int* myRightArray, int myRightCount);
void printDashes();

void clean_stdin(void);
int HOWMANY;

int main(/*int argc, char* argv[]*/)
{
	HOWMANY = 12;
	
	int *islanders = new int[HOWMANY];
	int weightTimes;
	if (HOWMANY <= 4)
	{
		weightTimes = 2;
	}
	else if (HOWMANY <= 12)
	{
		weightTimes = 3;
	}
	else if (HOWMANY <= 40)
	{
		weightTimes = 40;
	}

	srand(time(0));

	int rightAnswer = assignIslanders(islanders);

	for (int ii = weightTimes; ii > 0; ii--)
	{
		printf("Use the scale (%i remaining)\n", ii);
		allowChoice(islanders);
	}

	takeGuess(islanders, rightAnswer);
	char dummy;
	cin >> dummy;
	return 0;
}

int assignIslanders(int* islanders)
{
	int uniqueIslander, addOrSub;
	for (int ii = 0; ii < HOWMANY; ii++)
	{
		islanders[ii] = 100;
	}
	uniqueIslander = rand() % HOWMANY;
	addOrSub = rand() % 2;
	if (addOrSub == subtract)
	{
		islanders[uniqueIslander] = 100 - 2;
	}
	else
	{
		islanders[uniqueIslander] = 100 + 2;
	}
	return uniqueIslander;
}

void allowChoice(int* islanders)
{
	processChoice(islanders);
	clean_stdin();
}

void processChoice(int* islanders)
{
	char* temp = new char[HOWMANY];
	char tempChar;
	int count = 0;
	int myLeft = 0, myRight = 0, myLeftCount = 0, myRightCount = 0;
	int* myLeftArray = new int[HOWMANY];
	int* myRightArray = new int[HOWMANY];
	printf("L for left, R for right, - for neither\n");
	do {
		scanf_s("%c", &tempChar);
		if (tempChar == '\n') break;
		temp[count] = tempChar;
		count++;
	} while (count < HOWMANY);
	for (int ii = 0; ii < HOWMANY; ii++)
	{
		if (temp[ii] == 'L' || temp[ii] == 'l')
		{
			myLeft += islanders[ii];
			myLeftArray[myLeftCount] = ii + 1;
			myLeftCount++;
		}
		else if (temp[ii] == 'R' || temp[ii] == 'r')
		{
			myRight += islanders[ii];
			myRightArray[myRightCount] = ii + 1;
			myRightCount++;
		}
	}
	if (myLeft > myRight)
	{
		printf("%*s", HOWMANY * 2, " \t\t"); printArray(myRightArray, myRightCount); printf("\n");
		printf("%*s", HOWMANY * 2 + 3, "/"); printDashes(); printf("\n");
		printArray(myLeftArray, myLeftCount);
		printf("%*s", HOWMANY * 2 - myLeftCount * 2, "^"); printf("\n");
		printDashes(); printf("\n");
	}
	if (myRight > myLeft)
	{
		printArray(myLeftArray, myLeftCount); printf("\n");
		printDashes(); printf("\\"); printf("\n");
		printf("%*s", HOWMANY * 2 + 2, "^"); printf("\t\t"); printArray(myRightArray, myRightCount); printf("\n");
		printf("%*s", HOWMANY * 2 + 3, "\\"); printDashes(); printf("\n");
	}
	if (myRight == myLeft)
	{
		printArray(myLeftArray, myLeftCount); printf("\t\t\t"); printArray(myRightArray, myRightCount); printf("\n");
		printDashes(); printf(" ^ "); printDashes(); printf("\n");
	}
	printf("\n");
}

void takeGuess(int* islanders, int rightAnswer)
{
	int guess;
	printf("\n--Make your guess!--\n\n");
	scanf_s("%i", &guess);
	if (islanders[guess - 1] != 100)
	{
		printf("You're right! %i = %i\n", guess, islanders[guess - 1]);
	}
	else
	{
		printf("Nope, %i = %i\n", rightAnswer, islanders[rightAnswer - 1]);
	}
}

void printArray(int* myArray, int myCount)
{
	for (int ii = 0; ii < myCount; ii++)
	{
		printf("%d ", myArray[ii]);
	}
}

void printDashes()
{
	for (int ii = 0; ii < HOWMANY * 2; ii++)
	{
		printf("-");
	}
}
void clean_stdin(void)
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}