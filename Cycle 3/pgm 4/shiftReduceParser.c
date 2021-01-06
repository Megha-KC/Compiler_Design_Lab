/*Shift reduce parser or LR parser
Grammar: 
S->S+S
S->S-S
S->(S)
S->i
*/

#include <stdio.h>

char input[100];
int len = -1;
char stack[100];
int top = -1;

void display(int idx, char* action) {
    // Stack
    for(int i = 0; i <= top; i++)
        printf("%c", stack[i]);
    printf("\t\t");
    // Input
    for(int i = idx; i < len; i++) 
        printf("%c", input[i]);
    // Action
    printf("$\t\t%s\n", action);
}

void checkForReduce(int i) {
    int checkFurther = 1;
    while(checkFurther) {
        checkFurther = 0;
        // S->S+S
        if (stack[top-2] == 'S' && stack[top-1] == '+' && stack[top] == 'S') {
            display(i, "REDUCE");
            stack[top-2] = 'S';
            top -= 2;
            checkFurther = 1;
        }
        // S->S-S
        if (stack[top-2] == 'S' && stack[top-1] == '-' && stack[top] == 'S') {
            display(i, "REDUCE");
            stack[top-2] = 'S';
            top -= 2;
            checkFurther = 1;
        }
        // S->(S)
        if (stack[top-2] == '(' && stack[top-1] == 'S' && stack[top] == ')') {
            display(i, "REDUCE");
            stack[top-2] = 'S';
            top -= 2;
            checkFurther = 1;
        }
        // S->i
        if (stack[top] == 'i') {
            display(i, "REDUCE");
            stack[top] = 'S';
            checkFurther = 1;
        }
    }
}

int main() {
    int i;
    printf("Enter the input:\n");
    scanf("%s", input);

    // calculate the input length in len.
    while(input[++len]!='\0');

    stack[++top] = '$'; 
    printf("Stack\t\tInput\t\tAction\n");
    for(i = 0; i < len; i++) {
        display(i, "SHIFT");
        stack[++top] = input[i];
        // parse from next input char i.e. i+1
        checkForReduce(i+1); 
    }
    // Accepted.
    if(top == 1 && stack[top] == 'S') 
        display(i, "ACCEPTED");
    // Rejected.
    else
        display(i, "REJECTED");
}