//Input manager for remade bash
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

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
        else if(strcmp(c, "today\n") == 0){ //print mm/dd/yyyy
            time_t seconds = time(NULL);
            struct tm * today = localtime(&seconds);
            char time_as_str[26];
            strftime(time_as_str, 26, "%m/%d/%Y", today);
            printf("%s\n",time_as_str); 
        }
        else{
            char * s = c;
            s[strcspn(s, "\n")] = 0; //if \n found remove it
            char * args[MAX_SIZE];
            char * tok = strtok(s, " "); //start tokenizing
            int count = 0;
            while(tok != NULL){ //put all tokens in an array
                args[count] = strdup(tok);
                tok = strtok(NULL, " ");
                count++;
            }
            args[count] = NULL; //set last element to null termination
            int pid = fork(); 
            if(pid < 0){
                printf("Fork failed\n");
            }
            else if(pid == 0){ //if child run command using bash
                execvp(args[0], args);
                perror("Exec failed");
                return 1;
            }
            else{
                int wc = wait(NULL); //waits for child to complete
            }
        }
    }
    return 0;
}
