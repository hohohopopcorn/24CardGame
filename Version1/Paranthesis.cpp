#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int cards[4]={6, 6, 6, 6};
int temp[4];
int operations[3]={'+', '+', '+'};

bool signs()
{
	int i;
	int times=0;
	int powering=1;
	for(i=0; i<3; i++)
	{
		switch(operations[i])
		{
		case '+':
			times=times+powering*0;
			break;
		case '-':
			times=times+powering*1;
			break;
		case '*':
			times=times+powering*2;
			break;
		case '/':
			times=times+powering*3;
			break;
		}
		powering=powering*4;
	}
	if(times==powering-1)
	{
		operations[0]='+';
		operations[1]='+';
		operations[2]='+';
		return false;
	}

	times=times+1;
	int remainders;
	powering=powering/4;

	for(i=2; i>=0; i--)
	{
		remainders=(times-(times%powering))/powering;

		switch(remainders)
		{
		case 0:
			operations[i]='+';
			break;
		case 1:
			operations[i]='-';
			break;
		case 2:
			operations[i]='*';
			break;
		case 3:
			operations[i]='/';
			break;
		}

		times=times-powering*remainders;
		powering=powering/4;
	}

	return true;
}

int operating(int which, int a, int b)
{
	int value;

	if(operations[which]=='+')value=a+b;
	if(operations[which]=='-')value=a-b;
	if(operations[which]=='*')value=a*b;
	if(operations[which]=='/'&&b!=0)value=a/b;
	if(operations[which]=='/'&&b==0)value=10000000;

	return value;
}

//((a b) c) d
int para1(int solutions)
{
	int value;
	bool more=true;
	while(more==true)
	{
		value=operating(2, operating(1, operating(0, temp[0], temp[1]), temp[2]), temp[3]);


		if(value==24)
		{
			solutions++;
			printf("%d: ((%2d %c %2d) %c %2d) %c %2d  = %d\n", solutions, temp[0], operations[0], temp[1], operations[1], temp[2], operations[2], temp[3], value);
		}
		more=signs();
	}

	return solutions;
}

//a (b (c d))
int para2(int solutions)
{
	int value;
	bool more=true;
	while(more==true)
	{
		value=operating(0, temp[0], operating(1, temp[1], operating(2, temp[2], temp[3])));


		if(value==24)
		{
			solutions++;
			printf("%d: %2d %c (%2d %c (%2d %c %2d))  = %d\n", solutions, temp[0], operations[0], temp[1], operations[1], temp[2], operations[2], temp[3], value);
		}
		more=signs();
	}

	return solutions;
}

//(a b) (c d)
int para3(int solutions)
{
	int value;
	bool more=true;
	while(more==true)
	{
		value=operating(1, operating(0, temp[0], temp[1]), operating(2, temp[2], temp[3]));

		if(value==24)
		{
			solutions++;
			printf("%d: (%2d %c %2d) %c (%2d %c %2d)  = %d\n", solutions, temp[0], operations[0], temp[1], operations[1], temp[2], operations[2], temp[3], value);
		}
		more=signs();
	}

	return solutions;
}

//(a (b c)) d
int para4(int solutions)
{
	int value;
	bool more=true;
	while(more==true)
	{
		value=operating(2, operating(0, temp[0], operating(1, temp[1], temp[2])), temp[3]);

		if(value==24)
		{
			solutions++;
			printf("%d: (%2d %c (%2d %c %2d)) %c %2d  = %d\n", solutions, temp[0], operations[0], temp[1], operations[1], temp[2], operations[2], temp[3], value);
		}
		more=signs();
	}

	return solutions;
}

//a ((b c) d)
int para5(int solutions)
{
	int value;
	bool more=true;
	while(more==true)
	{
		value=operating(0, temp[0], operating(2, operating(1, temp[1], temp[2]), temp[3]));

		if(value==24)
		{
			solutions++;
			printf("%d: %2d %c ((%2d %c %2d) %c %2d)  = %d\n", solutions, temp[0], operations[0], temp[1], operations[1], temp[2], operations[2], temp[3], value);
		}
		more=signs();
	}

	return solutions;
}

void main()
{
	int solutions=0;
	bool more=true;
	temp[0]=cards[0];
	temp[1]=cards[1];
	temp[2]=cards[2];
	temp[3]=cards[3];

	solutions=para1(solutions);
	solutions=para2(solutions);
	solutions=para3(solutions);
	solutions=para4(solutions);
	solutions=para5(solutions);

	printf("\n\n %5d   solutions\n\n", solutions);
}