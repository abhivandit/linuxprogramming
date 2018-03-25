//count
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>//error file
#include<ctype.h>

void main()
{
	int c=0;//counter variable
	char ch;
	ch=getchar();
	while((ch=getchar())!=EOF)
	{
		{
			if(((ch>=65)&&(ch<=90)) || ((ch>=97)&&(ch<=122)))//ascii values
			{
				printf("%c",ch);
			}
			else 
			{
				printf("%c",ch);

				c++;
				//printf("%d\n",c);
			}
		}
	
		//ch=getchar();

		
	}
	fprintf(stderr, "%d\n", c);//getchar putchar errno stderr foile stream
	
}

/*#include<stdio.h>

void main()
{
	int count=0;
	char c;
	c=getchar();
	while(c!=EOF)
	{
		if(!((c>='a' && c<='z') || (c>='A' && c<='Z')))
			count++;
		printf("%c", c);
		c=getchar();
	}
	fprintf(stderr, "%d\n", count);*/
/**/
