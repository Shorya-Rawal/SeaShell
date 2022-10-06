#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define PATH_MAX 200
void engine(char path[64]);
int main(){
	char command[32], pwd[64];
	char binPath[64] = "../bin/";
	char cwd[PATH_MAX];
	FILE *file;
	while(0<1){
		getcwd(cwd, PATH_MAX);
		printf("%s _> ", cwd);
		scanf("%s", command);
		if(strcmp(command, "exit") == 0) break;
		else{
			strcat(binPath, command);
			if((file = fopen(binPath, "r"))){
				engine(binPath);
			}else{
				printf("Command not found in bin\n");
			}
		}
		strcpy(command, "");
		strcpy(binPath, "../bin/");
	}
}

void engine(char path[64]){
	pid_t pid = fork();
	if(pid == 0){
		static char *argv[] = {NULL};
		execv(path, argv);
	}else{
		waitpid(pid, 0, 0);
	}
}