#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
//#include<sys/types.h>
//#include<sys/wait.h>

#define PATH_MAX 200
#define ARRAY_LEN 4
#define ARGUMENT_SIZE 64
#define CLIPBOARD_SIZE 64

char *splitPath[ARRAY_LEN];
char *argumentList[1];
char *clipboard;
char binPath[64] = "/bin/";
char program[64];

void engine(char path[64]);
void arguments(char path[64]);
void ls(char path[64]);
int main(){
    char command[32];
    char cwd[PATH_MAX];
    FILE *file;
    while(1){
        getcwd(cwd, PATH_MAX);
        printf("\x1b[36m");
        printf("%s $ ", cwd);
        printf("\x1b[0m");
        scanf("%[^\n]%*c", command);
        arguments(command);
        strcat(binPath, program);
        if(strcmp(command, "exit") == 0) break;
        else if(strcmp(command, "clear") == 0) printf("\e[1;H\e[2J");
        else if(strcmp(program, "cd") == 0) chdir(argumentList[0]);
        else if(strcmp(program, "ls") == 0) (argumentList[0] == NULL) ? ls(cwd) : ls(argumentList[0]);
        else ((file = fopen(binPath, "r"))) ? engine(program) : printf("%s: Not Found.\n", program);
        strcat(command, "\n");
        strcpy(binPath, "/bin/");
        strcpy(command, "");
    }
}
void engine(char path[64]){
    pid_t pid = fork();
    (pid == 0) ? execv(binPath, argumentList) : waitpid(pid, 0, 0);
}
void arguments(char path[64]){
    for(int h = 0; h < ARRAY_LEN; h++){
        splitPath[h] = NULL;
        argumentList[h] = NULL;
    }
    char *token = strtok(path, " ");
    for(int i = 0; i < ARRAY_LEN; i++){
        if(token == NULL) break;
        splitPath[i] = malloc(ARGUMENT_SIZE);
        splitPath[i] = token;
        token = strtok(NULL, " ");
    }
    strcpy(program, splitPath[0]);
    for(int j = 0; j < ARRAY_LEN; j++) argumentList[j] = splitPath[j+1];
}
void ls(char path[64]){
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if(d){
        while((dir = readdir(d)) != NULL){
            if(strcmp(dir->d_name, ".") == 0) continue;
            else if(strcmp(dir->d_name, "..") == 0) continue;
            else printf("%s\n", dir->d_name);
        }
    }
}
