#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int cards[4]={1, 2, 3, 4};
int temp[4];
char layout[4]={'a', 'b', 'c', 'd'};

bool valswitch()
{
	int times=0;
	int power=256;
	int newval[4];
	int i;
	bool goodval=false;

	for(i=0; i<4; i++)
	{
		power=power/4;
		switch(layout[i])
		{
		case 'a':
			times=times+power*0;
			break;
		case 'b':
			times=times+power*1;
			break;
		case 'c':
			times=times+power*2;
			break;
		case 'd':
			times=times+power*3;
		}
	}

	if(times>=(3*4*4*4)+(2*4*4)+(1*4))return false;

	while(goodval==false)
	{
		times++;
		power=64;
		newval[0]=(times-times%power)/power;
		newval[1]=(times-newval[0]*power-times%(power/4))/(power/4);
		newval[2]=(times-newval[0]*power-newval[1]*power/4-times%(power/4/4))/(power/4/4);
		newval[3]=(times-newval[0]*power-newval[1]*power/4-newval[2]*power/4/4-times%(power/4/4/4))/(power/4/4/4);

		if((newval[0]>=0&&newval[0]<=3)&&(newval[1]>=0&&newval[1]<=3)&&(newval[2]>=0&&newval[2]<=3)&&(newval[3]>=0&&newval[3]<=3))
		{
			if(newval[0]!=newval[1]&&newval[0]!=newval[2]&&newval[0]!=newval[3]&&newval[1]!=newval[2]&&newval[1]!=newval[3]&&newval[2]!=newval[3])goodval=true;
		}
	}

	for(i=0; i<4; i++)
	{
		switch(newval[i])
		{
		case 0:
			layout[i]='a';
			break;
		case 1:
			layout[i]='b';
			break;
		case 2:
			layout[i]='c';
			break;
		case 3:
			layout[i]='d';
			break;
		}
		switch(layout[i])
		{
		case 'a':
			temp[i]=cards[0];
			break;
		case 'b':
			temp[i]=cards[1];
			break;
		case 'c':
			temp[i]=cards[2];
			break;
		case 'd':
			temp[i]=cards[3];
			break;
		}
	}

	return true;
}

void main()
{
	bool more=true;
	
	temp[0]=cards[0];
	temp[1]=cards[1];
	temp[2]=cards[2];
	temp[3]=cards[3];

	while(more==true)
	{
		more=valswitch();
		printf("%d  %d  %d  %d \n", temp[0], temp[1], temp[2], temp[3]);
	}
}