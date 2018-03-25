#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
void error(char *s){
	fprintf(stderr, "%s", s);
	exit(1);
}
void main(int argc, char *argv[]){
if (argc!=3)
{
error("invalid no of arguemts");	
}

	int pipefd[2], f, status, f2;
	int fp_in, fp_out;
	fp_in=open(argv[1], O_RDONLY);
	if(fp_in<0)
		error("error");
	fp_out=creat(argv[2], 0777);
	if(fp_out<0)
		error("error related to file2");
	pipe(pipefd);
	close(0);
	dup(fp_in);
	close(1);
	dup(fp_out);
	f=fork();
	if(f==0){
		close(1);
		dup(pipefd[1]);
		close(pipefd[1]);
		close(fp_in);
		execl("as3", "as3", NULL); //]as3 is convert
		fprintf(stderr, "Converted");
	}
	else{
		f2=fork();
		if(f2==0){
			close(pipefd[1]);
			wait(&status);
			close(0);
			dup(pipefd[0]);
			close(pipefd[0]);
			close(1);
			dup(fp_out);
			close(fp_out);
			execl("as2", "as2", NULL); //as2 is count
			fprintf(stderr, "Counting is done.");
			
		}
		else{
			close(pipefd[1]);
			wait(&status);
			wait(&status);
			close(0);
			close(1);
			close(fp_in);
			close(fp_out);
		}
	}
}
