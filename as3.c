//convert
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main()
{
	char ch;
	ch=getchar();
	while(ch!=EOF)
	{
		if(ch>=97 && ch<=122)
			{ch-=32;}
		else if(ch>=65 && ch<=90)
			{ch+=32;}
		printf("%c", ch);
		ch=getchar();
	}
	printf("\n");
	exit(0);
}
