#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int cards[4]={1, 10, 12, 13};
int temp[4];

void displaying()
{
	int i;
	char lettering[4][2];

	for(i=0; i<4; i++)
	{
		if(cards[i]==10)
		{
			lettering[i][0]='1';
			lettering[i][1]='0';
		}
		else
		{
			lettering[i][0]=' ';
			if(cards[i]==1)lettering[i][1]='A';
			else if(cards[i]==11)lettering[i][1]='J';
			else if(cards[i]==12)lettering[i][1]='Q';
			else if(cards[i]==13)lettering[i][1]='K';
			else lettering[i][1]='0'+cards[i];
		}
	}

	printf("_____     _____\n");
	printf("|   |     |   |\n");
	printf("|%c%c |     |%c%c |\n", lettering[0][0], lettering[0][1], lettering[1][0], lettering[1][1]);
	printf("|   |     |   |\n");
	printf("_____     _____\n");
	printf("\n\n");
	
	printf("_____     _____\n");
	printf("|   |     |   |\n");
	printf("|%c%c |     |%c%c |\n", lettering[2][0], lettering[2][1], lettering[3][0], lettering[3][1]);
	printf("|   |     |   |\n");
	printf("_____     _____\n");
	printf("\n\n");
}

void main()
{
	displaying();
}