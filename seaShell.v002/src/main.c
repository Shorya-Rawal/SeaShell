#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

#define PATH_MAX 200
#define ARRAY_LEN 16
#define ARGUMENT_SIZE 64

char *splitPath[ARRAY_LEN];
char *argumentList[1];
char binPath[64] = "/bin/";
char program[64];

void engine(char path[64]);
void arguments(char path[64]);
int main(){
	char command[32];
	char cwd[PATH_MAX];
	FILE *file;
	while(0<1){
		getcwd(cwd, PATH_MAX);
		printf("\x1b[36m");
		printf("%s _> ", cwd);
		printf("\x1b[0m");
		scanf("%[^\n]%*c", command);
		strcat(binPath, command);
		arguments(binPath);
		if(strcmp(command, "exit") == 0) break;
		else if(strcmp(command, "clear") == 0) printf("\e[1;1H\e[2J");
		else if(strcmp(program, "/bin/cd") == 0) chdir(argumentList[0]);
		else{
			if((file = fopen(program, "r"))){
				engine(program);	
			}else{
				printf("command does not exist\n");
			}
		}
		strcpy(binPath, "/bin/");
		strcpy(command, "");
	}
}
void engine(char path[64]){
	pid_t pid = fork();
	if(pid == 0){
		execv(path, argumentList);
	} else waitpid(pid, 0, 0);
}
void arguments(char path[64]){
	for(int h = 0; h < ARRAY_LEN; h++){ 
		splitPath[h] = NULL;
		argumentList[h] = NULL;
	}
	char *token = strtok(path, " ");
	for(int i = 0; i < ARRAY_LEN; i++){
		if(token != NULL){
			splitPath[i] = malloc(ARGUMENT_SIZE);
			splitPath[i] = token;
			token = strtok(NULL, " ");
		} else break;
	}
	strcpy(program, splitPath[0]);
	for(int j = 0; j < 4; j++) argumentList[j] = splitPath[j+1];
}