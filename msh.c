//Input manager for remade bash
#include <stdio.h>
#include <string.h>

int main(){
    char c[121];
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
        else{
            char * args = strtok(c, " ");
            printf("%s\n", c);
            int count = 1;
            while(args != NULL){
                printf("%d: %s\n", count, args);
                args = strtok(NULL, " ");
                count++;
            }
        }
    }
    return 0;
}
