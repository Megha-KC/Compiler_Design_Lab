/* To find the first and follow of any given grammar. */
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

void follow(char*, char);
int numOfProductions, i;
char productions[10][10];

void addToResult(char* result, char c) {
    //check if already added to result
    int k;
    for(k = 0; result[k] != '\0'; k++) {
        if(result[k] == c) {
            return;
        }
    }
    result[k++] = c;
    result[k] = '\0';
}

void first(char* result, char c) {
    int isEpsilon, j;
    char subResult[20];

    // clear result and subresult
    result[0] = '\0';
    subResult[0] = '\0';

    if(!isupper(c)) {
        // terminal
        addToResult(result, c);
        return;
    }
    // non-terminal 
    for(int i = 0; i < numOfProductions; i++) {
        // consider productions with 'c' as the start symbol
        if(productions[i][0] == c) {
            // check if it is an epsilon production
            if(productions[i][3] == '#')
                //add epsilon to the result
                addToResult(result, '#');
            else {
                j = 3;
                while(productions[i][j]!='\0') {
                    isEpsilon = 0;
                    first(subResult, productions[i][j]);
                    //add subResult to result
                    for(int k = 0; subResult[k] != '\0'; k++)
                        addToResult(result, subResult[k]);
                    //check if epsilon is in subResult
                    for(int k = 0; subResult[k] != '\0'; k++) 
                        if(subResult[k] == '#') {
                            isEpsilon = 1;
                            break;
                        }
                    if(!isEpsilon) 
                        break;
                    
                    j++;
                }
            }
        }
    }
}   

void firstForFollow(char* result, char c)
{
    int k;
    // terminals
    if(!isupper(c))
        addToResult(result, c);
    // non-terminal: A->pcB
    for(k=0; k < numOfProductions; k++) {
        if(productions[k][0] == c) {
            // if epsilon is present in FIRST(B) then add FOLLOW(A) to result.
            if(productions[k][3]=='#') 
                follow(result, productions[i][0]);
            // if FIRST(B) is a terminal add it to result.
            else if(islower(productions[k][3]))
                addToResult(result, productions[k][3]);
            // FIRST(B) is a non-terminal.
            else 
                firstForFollow(result, productions[k][3]);
        }
    }
}

void follow(char* result, char c) {
    //check if start symbol 
    if(productions[0][0] == c)
        addToResult(result, '$');
    //check if c is present in the RHS of any production
    for(i = 0; i < numOfProductions; i++) {
        for(int j = 3; productions[i][j] != '\0'; j++) {
            if(productions[i][j] == c) {
                // A -> pc => every element in FOLLOW(A) will be in FOLLOW(c)
                if(productions[i][j+1] == '\0' && productions[i][0] != c)
                    follow(result, productions[i][0]);
                // A -> pcB every element in FIRST(B) is present in FOLLOW(c) except epsilon; if epsilon is present in FIRST(B) then add FOLLOW(A) to result.
                if(productions[i][j+1] != '\0')
                    firstForFollow(result, productions[i][j+1]);
            }
        }
    }
}

void main() {
    char firstResult[20], followResult[20];
    char* nonTerminals;
    int numOfNonTerminals, i;

    // non terminals
    printf("Enter the number of non-terminals: ");
    scanf("%d", &numOfNonTerminals);

    nonTerminals = (char *)malloc(numOfNonTerminals);
    printf("Enter the non-terminals:\n");
    for(i=0; i< numOfNonTerminals; i++)
        scanf(" %c", &nonTerminals[i]);

    // productions
    printf("Enter the number of productions: ");
    scanf("%d", &numOfProductions);
    printf("Represent epsilon as '#'\n");
    for(i = 0; i < numOfProductions; i++) {
        printf("Enter production %d: ", i+1);
        scanf("%s", productions[i]);
    }
    
    for(i = 0; i < numOfNonTerminals; i++) {

        // FIRST
        first(firstResult, nonTerminals[i]);
        printf("\nFIRST(%c): {", nonTerminals[i]);
        int j = 0;
        printf(" %c", firstResult[j]);
        for(j = 1; firstResult[j] != '\0'; j++)
            printf(", %c", firstResult[j]);

        printf(" }\t\t");

        // FOLLOW
        followResult[0] = '\0';
        follow(followResult, nonTerminals[i]);
        printf("FOLLOW(%c): {", nonTerminals[i]);
        j = 0;
        printf(" %c", followResult[j]);
        for(j = 1; followResult[j] != '\0'; j++)
            printf(", %c", followResult[j]);
        printf(" }\n");
    }

    

}