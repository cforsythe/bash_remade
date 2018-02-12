//Input manager for remade bash
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

const int MAX_SIZE = 121;

int main(){
    char c[MAX_SIZE];
    while(1){
        printf("msh> ");
        if(!fgets(c, 122, stdin)){ //if line doesn't recieve input
            printf("\n");
            break; //exits program
        }
        if(!strchr(c, '\n')){ //check if \n is found in line makes sure input is max of 120 chars
            scanf("%*[^\n]"); scanf("%*c"); //if \n not found flush stdin
            printf("Error, input should not be more than 120 characters\n");
        }
        else if(strcmp(c, "exit\n") == 0) break; //check if input = exit
        else if(strcmp(c, "help\n") == 0) printf("enter Linux commands or 'exit' to exit\n"); //check if input = exit
        else{
            printf("%s", c);
            char * s = c;
            s[strcspn(s, "\n")] = 0;
            char * args[MAX_SIZE];
            char * tok = strtok(s, " ");
            int count = 0;
            while(tok != NULL){
                args[count] = strdup(tok);
                tok = strtok(NULL, " ");
                count++;
            }
            args[count] = NULL;
            int pid = fork(); 
            if(pid < 0){
                printf("Fork failed\n");
            }
            else if(pid == 0){
                execvp(args[0], args);
                perror("Exec failed");
                return 1;
            }
            else{
                int wc = wait(NULL);
            }
        }
    }
    return 0;
}
