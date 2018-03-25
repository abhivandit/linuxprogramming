#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<string.h>
int i=0,j=0,*command;
void main(int argc, char* argv[]){
	char dkm[50];
	while(1){

		printf("$");
		int ppcount=0;
		
		
		fgets(dkm, 50, stdin);
		
		
		for(i=0; i<strlen(dkm); i++){
			if(dkm[i]=='|')
				ppcount++;
		}
		
		
		int sin = dup(0);
		int sout = dup(1);
		char **ind;
		char *svptr;

		ind=(char **)malloc(ppcount);

		ind[0]=strtok_r(dkm, "|", &svptr);

		for( i=1; i<=ppcount; i++){
			ind[i]=strtok_r(NULL, "|", &svptr);
		} 
		
		if(ppcount==0){
					if(!strcmp(dkm, "exit\n"))
						exit(1);
					else if(dkm[0]=='c' && dkm[1]=='d'){
						svptr=NULL;
						ind[0]=strtok_r(dkm, " ", &svptr);
						ind[0]=strtok_r(NULL, " ", &svptr);
						printf("%s\n", ind[0]);
						chdir(ind[0]);
						continue;
					}
				}
		int pipefd[ppcount+1][2];

		for( i=0; i<ppcount; i++)
			pipe(pipefd[i]);

		char *svptr2;
		char *back[2];

		for( i=0; i<=ppcount; i++){
			
			back[0]=strtok_r(ind[i], "\t", &svptr2);
			back[1]=strtok_r(NULL, "\t", &svptr2);

			int status;
			

			pid_t pid=fork();

			if(pid==0){
				if(i!=0){
					close(0);
					close(pipefd[i-1][1]);
					dup(pipefd[i-1][0]);
				}
				if(i!=ppcount){
					close(1);
					dup(pipefd[i][1]);
				}
				if(i==ppcount){
					close(1);
					dup(sout);
				}
				execl("/bin/bash", "bash", "-c", back[0], NULL);
				fprintf(stdout, "After execl\n");
			}
			else{
					
				waitid(P_PID, pid, NULL, 0);
				if(i==ppcount){
					close(0);
					dup(sin);
					close(1);
					dup(sout);
				}
				
			}
		}		
	}
}
