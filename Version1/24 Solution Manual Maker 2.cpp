#define _CRT_SECURE_NO_WARNINGS
#define TOTAL 1820
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

clock_t t1;
int done;
int unique;
int cards[4]={1, 1, 1, 1};
int temp[4];
int operations[3]={0, 0, 0};
char ops[3];
int layout[4]={0, 1, 2, 3};
int already[TOTAL][4];

FILE *target=fopen("24 Solutions.txt", "w");


//quick sort
void sort(int *a, int ele)
{
  int curr, key, i;
  for(curr=1;curr<ele;++curr)
  {
    key=a[curr];
    i=0;
    while(i<curr)
    {
      if(a[curr]<a[i])
      { 
        memmove(&a[i+1],&a[i],(curr - i)*sizeof(int));
        a[i] = key;
        break;
      }
      ++i;
    }
  }
}

//next card combination
bool cardswitch()
{
	int times=0;
	int power=1;
	int i;
	bool goodval=false;
	
	memcpy(cards, temp, sizeof(cards));
	for(i=3; i>=0; i--)
	{
		times=(temp[i]-1)*power+times;
		power=power*13;
	}


	while(goodval==false)
	{
		if(times>=13*13*13*13-1)return false;
		times++;
		power=13*13*13;
		temp[0]=(times-times%power)/power;
		temp[1]=(times-temp[0]*power-times%(power/13))/(power/13);
		temp[2]=(times-temp[0]*power-temp[1]*power/13-times%(power/13/13))/(power/13/13);
		temp[3]=(times-temp[0]*power-temp[1]*power/13-temp[2]*power/13/13-times%(power/13/13/13))/(power/13/13/13);
		memcpy(cards, temp, sizeof(cards));
		sort(cards, 4);
		goodval=true;
		for(i=0; i<unique&&goodval==true; i++)
		{
				if(memcmp(cards, already[i], sizeof(cards))==0)goodval=false;
		}
		if(unique==0)break;
	}
	
	memcpy(already[unique], cards, sizeof(cards));
	unique++;

	cards[0]++;
	cards[1]++;
	cards[2]++;
	cards[3]++;

	return true;
}

//liesure time display
void waiting()
{
	int seconds=((float)(clock()-t1)/done*(TOTAL-done))/CLOCKS_PER_SEC;
	int minutes=(seconds-seconds%60)/60;
	seconds=seconds-minutes*60;
	int i;
	float percent=100*(float)done/TOTAL;
	char cover[23], middle[23];
	for(i=1; i<21; i++)cover[i]=205;
	cover[22]=0;
	middle[0]=186;
	for(i=1; i-1<=percent/5; i++)middle[i]=219;
	for(i=1+percent/5; i<21; i++)middle[i]=' ';
	middle[21]=186;
	middle[22]=0;
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("                        %f %% (%5d /     %5d)\n", percent, done, TOTAL);
	cover[0]=201;
	cover[21]=187;
	printf("                          %s\n", cover);
	printf("                          %s\n", middle);
	cover[0]=200;
	cover[21]=188;
	printf("                          %s\n", cover);
	printf("                    %2d MINUTES LEFT %2d SECONDS LEFT", minutes, seconds);
}

//moving cards around
bool valswitch()
{
	int times=0;
	int power=256;
	int i;
	bool goodval=false;

	for(i=0; i<4; i++)
	{
		power=power/4;
		times=times+power*layout[i];
	}

	if(times>=(3*4*4*4)+(2*4*4)+(1*4))return false;

	while(goodval==false)
	{
		times++;
		power=64;
		layout[0]=(times-times%power)/power;
		layout[1]=(times-layout[0]*power-times%(power/4))/(power/4);
		layout[2]=(times-layout[0]*power-layout[1]*power/4-times%(power/4/4))/(power/4/4);
		layout[3]=(times-layout[0]*power-layout[1]*power/4-layout[2]*power/4/4-times%(power/4/4/4))/(power/4/4/4);

		if((layout[0]>=0&&layout[0]<=3)&&(layout[1]>=0&&layout[1]<=3)&&(layout[2]>=0&&layout[2]<=3)&&(layout[3]>=0&&layout[3]<=3))
		{
			if(layout[0]!=layout[1]&&layout[0]!=layout[2]&&layout[0]!=layout[3]&&layout[1]!=layout[2]&&layout[1]!=layout[3]&&layout[2]!=layout[3])goodval=true;
		}
	}

	for(i=0; i<4; i++)temp[i]=cards[layout[i]];

	return true;
}

//just looking nice
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

	fprintf(target, "                   _____     _____\n");
	fprintf(target, "                   |   |     |   |\n");
	fprintf(target, "                   |%c%c |     |%c%c |\n", lettering[0][0], lettering[0][1], lettering[1][0], lettering[1][1]);
	fprintf(target, "                   |   |     |   |\n");
	fprintf(target, "                   _____     _____\n");
	fprintf(target, "\n");
	
	fprintf(target, "                   _____     _____\n");
	fprintf(target, "                   |   |     |   |\n");
	fprintf(target, "                   |%c%c |     |%c%c |\n", lettering[2][0], lettering[2][1], lettering[3][0], lettering[3][1]);
	fprintf(target, "                   |   |     |   |\n");
	fprintf(target, "                   _____     _____\n");
	fprintf(target, "\n");
}

//changing signs
bool signs()
{
	int i;
	int times=0;
	int powering=1;
	for(i=0; i<3; i++)
	{
		times=times+powering*operations[i];
		powering=powering*4;
	}
	if(times==powering-1)
	{
		operations[0]=0;
		operations[1]=0;
		operations[2]=0;
		return false;
	}

	times=times+1;
	int remainders;
	powering=powering/4;

	for(i=2; i>=0; i--)
	{
		operations[i]=(times-(times%powering))/powering;

		times=times-powering*operations[i];
		powering=powering/4;
	}

	for(i=0; i<3; i++)
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
	float value;

	if(operations[which]==0)value=a+b;
	if(operations[which]==1)value=a-b;
	if(operations[which]==2)value=a*b;
	if(operations[which]==3&&b!=0)value=a/b;
	if(operations[which]==3&&b==0)value=10000000;

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
		if(value>=24-0.01&&value<=24+0.01)
		{
			displaying();
			solutions++;
			fprintf(target, "%4d: ((%2d %c %2d) %c %2d) %c %2d  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
			return solutions;
		}

		//a (b (c d))
		value=operating(0, temp[0], operating(1, temp[1], operating(2, temp[2], temp[3])));
		if(value>=24-0.01&&value<=24+0.01)
		{
			displaying();
			solutions++;
			fprintf(target, "%4d: %2d %c (%2d %c (%2d %c %2d))  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
			return solutions;
		}
		
		//(a b) (c d)
		value=operating(1, operating(0, temp[0], temp[1]), operating(2, temp[2], temp[3]));
		if(value>=24-0.01&&value<=24+0.01)
		{
			displaying();
			solutions++;
			fprintf(target, "%4d: (%2d %c %2d) %c (%2d %c %2d)  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
			return solutions;
		}

		//(a (b c)) d
		value=operating(2, operating(0, temp[0], operating(1, temp[1], temp[2])), temp[3]);
		if(value>=24-0.01&&value<=24+0.01)
		{
			displaying();
			solutions++;
			fprintf(target, "%4d: (%2d %c (%2d %c %2d)) %c %2d  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
			return solutions;
		}
		
		//a ((b c) d)
		value=operating(0, temp[0], operating(2, operating(1, temp[1], temp[2]), temp[3]));
		if(value>=24-0.01&&value<=24+0.01)
		{
			displaying();
			solutions++;
			fprintf(target, "%4d: %2d %c ((%2d %c %2d) %c %2d)  = %d\n", solutions, (int)temp[0], ops[0], (int)temp[1], ops[1], (int)temp[2], ops[2], (int)temp[3], (int)value);
			return solutions;
		}

		more=signs();
	}

	return solutions;
}

void main()
{
	done=0;
	unique=0;
	int solutions;
	bool dif=true;
	bool more=true;

	t1=clock();

	while(dif==true)
	{
		solutions=0;
		more=true;

		temp[0]=cards[0];
		temp[1]=cards[1];
		temp[2]=cards[2];
		temp[3]=cards[3];

		while(more==true)
		{
			if(solutions==0)solutions=paranthesis(solutions);

			if(solutions==0)more=valswitch();
			else break;
		}

		if(solutions!=0)fprintf(target, "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
		dif=cardswitch();
		done=done+1;
		waiting();
	}
	printf("\n\n");
}