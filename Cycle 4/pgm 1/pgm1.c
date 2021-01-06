#include<stdio.h>
#include<string.h>

void checkForOperator(char* input, char operator, char* reg) {
    int i = 0, j = 0;
    char temp[100];
    while(input[i] != '\0') {
        if(input[i] == operator) {
            printf("%c\t\t%c\t\t%c\t\t%c\n", operator, *reg, input[i-1], input[i+1]);
            temp[j-1] = *reg;
            i += 2;
            (*reg)--;
            continue;
        }
        temp[j] = input[i];
        i++;
        j++;    
    }
    temp[++j] = '\0';
    strcpy(input, temp);    
}

void generateIntermediateCode(char* input) {
    char reg = 'Z';
    checkForOperator(input, '/', &reg);
    checkForOperator(input ,'*', &reg);
    checkForOperator(input, '+', &reg);
    checkForOperator(input, '-', &reg);
    checkForOperator(input, '=', &reg);
}

void main() {
    char input[100];
    printf("Enter the expression: ");
    scanf("%s", input);
    printf("Operator\tDestination\tOperand1\tOperand2\n");
    generateIntermediateCode(input);
}