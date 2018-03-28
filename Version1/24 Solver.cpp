#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define canum 4
#define LOW 1
#define HIGH 13
#define Range HIGH-LOW
#define GOAL 24

float cards[canum]={LOW, LOW, LOW, LOW};
float temp[canum];
int operations[canum-1]={0, 0, 0};
char ops[canum-1];
int layout[canum]={0, 1, 2, 3};

void asking()
{
	int i;
	for(i=0; i<canum; i++)
	{
		printf("%d Card: ", i+1);
		scanf("%f", &cards[i]);
	}
}

//moving cards around
bool valswitch()
{
	int times=0;
	int power=canum*canum*canum*canum;
	int i;
	bool goodval=false;

	for(i=0; i<canum; i++)
	{
		power=power/canum;
		times=times+power*layout[i];
	}


	while(goodval==false)
	{
		if(times>=canum*canum*canum*canum)return false;
		times++;
		power=canum*canum*canum;
		layout[0]=(times-times%power)/power;
		layout[1]=(times-layout[0]*power-times%(power/canum))/(power/canum);
		layout[2]=(times-layout[0]*power-layout[1]*power/canum-times%(power/canum/canum))/(power/canum/canum);
		layout[3]=(times-layout[0]*power-layout[1]*power/canum-layout[2]*power/canum/canum-times%(power/canum/canum/canum))/(power/canum/canum/canum);

		if((layout[0]>=0&&layout[0]<=3)&&(layout[1]>=0&&layout[1]<=3)&&(layout[2]>=0&&layout[2]<=3)&&(layout[3]>=0&&layout[3]<=3))
		{
			if(layout[0]!=layout[1]&&layout[0]!=layout[2]&&layout[0]!=layout[3]&&layout[1]!=layout[2]&&layout[1]!=layout[3]&&layout[2]!=layout[3])goodval=true;
		}
	}

	for(i=0; i<canum; i++)temp[i]=cards[layout[i]];

	return true;
}

//just looking nice
void displaying()
{
	int i;
	char lettering[canum][2];

	for(i=0; i<canum; i++)
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

//changing signs
bool signs()
{
	int i;
	int times=0;
	int powering=1;
	for(i=0; i<canum-1; i++)
	{
		times=times+powering*operations[i];
		powering=powering*canum;
	}
	if(times==powering-1)
	{
		for(i=0; i<canum-1; i++)operations[i]=0;
		return false;
	}

	times=times+1;
	powering=powering/canum;

	for(i=2; i>=0; i--)
	{
		operations[i]=(times-(times%powering))/powering;

		times=times-powering*operations[i];
		powering=powering/canum;
	}

	for(i=0; i<canum-1; i++)
	{
		switch(operations[i])
		{
		case 0:
			ops[i]='+';
			break;
		case 1:
			ops[i]='-';
			break;
		case 2:
			ops[i]='*';
			break;
		case 3:
			ops[i]='/';
			break;
		}
	}

	return true;
}

//calculating method
float operating(int which, float a, float b)
{
	float value=10000000;

	if(a==value||b==value)return value;

	if(operations[which]==0)value=a+b;
	if(operations[which]==1)value=a-b;
	if(operations[which]==2)value=a*b;
	if(operations[which]==3&&b!=0)value=a/b;

	return value;
}

int paranthesis(int solutions)
{
	float value;
	bool more=true;
	while(more==true)
	{
		//((a b) c) d
		value=operating(2, operating(1, operating(0, temp[0], temp[1]), temp[2]), temp[3]);
		if(value>=GOAL-0.01&&value<=GOAL+0.01)
		{
			solutions++;
			printf("%4d: ((%2d %c %2d) %c %2d) %c %2d  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
		}

		//a (b (c d))
		value=operating(0, temp[0], operating(1, temp[1], operating(2, temp[2], temp[3])));
		if(value>=GOAL-0.01&&value<=GOAL+0.01)
		{
			solutions++;
			printf("%4d: %2d %c (%2d %c (%2d %c %2d))  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
		}
		
		//(a b) (c d)
		value=operating(1, operating(0, temp[0], temp[1]), operating(2, temp[2], temp[3]));
		if(value>=GOAL-0.01&&value<=GOAL+0.01)
		{
			solutions++;
			printf("%4d: (%2d %c %2d) %c (%2d %c %2d)  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
		}

		//(a (b c)) d
		value=operating(2, operating(0, temp[0], operating(1, temp[1], temp[2])), temp[3]);
		if(value>=GOAL-0.01&&value<=GOAL+0.01)
		{
			solutions++;
			printf("%4d: (%2d %c (%2d %c %2d)) %c %2d  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
		}
		
		//a ((b c) d)
		value=operating(0, temp[0], operating(2, operating(1, temp[1], temp[2]), temp[3]));
		if(value>=GOAL-0.01&&value<=GOAL+0.01)
		{
			solutions++;
			printf("%4d: %2d %c ((%2d %c %2d) %c %2d)  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
		}

		more=signs();
	}

	return solutions;
}

void main()
{
	asking();
	displaying();
	int solutions=0;
	bool more=true;

	for(int i=0; i<canum; i++)temp[i]=cards[i];

	while(more==true)
	{
		solutions=paranthesis(solutions);

		more=valswitch();
	}
	printf("\n\n %5d   solutions\n\n", solutions);
}