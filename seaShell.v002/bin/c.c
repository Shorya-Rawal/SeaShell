#include<stdio.h>
int main(int argc, char* argv[]){
    if(argc == 1) printf("No arguments.\n");
    else if(argc == 2) printf("argument passed.\n");
    else printf("multiple arguemnts passed.\n");
}
