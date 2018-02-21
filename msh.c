//Input manager for remade bash
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

const int MAX_SIZE = 121;
void printArray(char * args[], int size){
    int i = 0;
    for(i = 0; i < size; i++){
        if(i != size - 1) printf("%s, ", args[i]);
        else printf("%s\n", args[i]);
    }
}

void forkExec(char * args[], int count){
    if(strcmp(args[0], "cd") == 0){ //run different commands if cd
        int status;
        if(count == 1) status = chdir(getenv("HOME")); //send to home dir
        else if(strcmp(args[1], "~") == 0) status = chdir(getenv("HOME"));
        else status = chdir(args[1]); 
        if(status != 0){
            perror("Error");
        }
    }
    else{
        args[count] = NULL; //set last element to null termination
        int pid = fork(); 
        if(pid < 0){
            printf("Fork failed\n");
        }
        else if(pid == 0){ //if child run command using bash
            execvp(args[0], args);
            perror("Exec failed");
            return;
        }
        else{
            int wc = wait(NULL); //waits for child to complete
        }
    }
}
void runFunction(char c[MAX_SIZE]){
    char * s = c;
    s[strcspn(s, "\n")] = 0; //if \n found remove it
    char * args[121];
    char * tok = strtok(s, " "); //start tokenizing
    int count = 0;
    while(tok != NULL){ //put all tokens in an array
        args[count] = strdup(tok);
        tok = strtok(NULL, " ");
        count++;
    }
    forkExec(args, count);
}

int main(int argc, char * argv[]){
    char c[MAX_SIZE];
    if(argc > 1){
        FILE * f = fopen(argv[1], "r"); //check if is file
        if(f == NULL){  //run command if not file
            forkExec(argv+1, argc-1);
        }
        else{ //run all commands in file
            while(fgets(c, 122, f) != NULL){
                runFunction(c);
            }
            fclose(f);
        }
        return 0;
    }
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
            runFunction(c);
        }
    }
    return 0;
}
