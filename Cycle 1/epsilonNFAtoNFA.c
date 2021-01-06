#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_OF_ALPHABETS 20
#define MAX_NUM_OF_STATES 20

struct state {
    int stateNum;
    struct state* link;
};

static int index;
int numOfStates, numOfAlphabets, numOfTransitions, numOfFinalStates, start;


int visitedState[MAX_NUM_OF_STATES], finalStates[MAX_NUM_OF_STATES];
static int set[20], epsilonClosure[MAX_NUM_OF_STATES][MAX_NUM_OF_STATES] = {0};
char alphabets[MAX_NUM_OF_ALPHABETS];
struct state* transitions[MAX_NUM_OF_STATES][MAX_NUM_OF_ALPHABETS] = {NULL};

void displayEpsilonClosure(int stateNum) {
    printf("{ q%d", stateNum);
    for (int i=1; epsilonClosure[stateNum][i]!=0; i++)
        printf(", q%d", epsilonClosure[stateNum][i]);
    printf(" }\t");
}

void findfinalstate() {
    int i,j,k,t;
    for(i=0;i<numOfFinalStates;i++) {
        for(j=1;j<=numOfStates;j++) {
            for(k=0;epsilonClosure[j][k]!=0;k++) {
                // check if any of the state j contain final states in its epsilon closures; all such states would be final states.
                if(epsilonClosure[j][k] == finalStates[i]) {
                    displayEpsilonClosure(j);
                }
            }
        }
     }


  }

void unionclosure(int i) {
    int j=0,k;
    // obtain all epsilon closures of state i.
    while(epsilonClosure[i][j]!=0) {
        k=epsilonClosure[i][j]; 
        set[k]=1; 
        j++;
    }         
}

int getPositionOfAlphabet(char ch) {
    for(int idx=0; idx<numOfAlphabets; idx++)
        if (alphabets[idx] == ch)
            return idx;
}

void createTransitionTable(int currStateNum, char alphabet, int nextStateNum) {
    int position = getPositionOfAlphabet(alphabet);
    struct state* temp;
    temp = (struct state*)malloc(sizeof(struct state));
    temp->stateNum = nextStateNum;
    temp->link = transitions[currStateNum][position];
    transitions[currStateNum][position] = temp;
}

void findEpsilonClosure(int currStateNum, int reachedStateNum) {
    if (visitedState[reachedStateNum])
        return;
    epsilonClosure[currStateNum][index++] = reachedStateNum;
    visitedState[reachedStateNum] = 1;
    if (alphabets[numOfAlphabets-1] == 'e' && transitions[reachedStateNum][numOfAlphabets-1] != NULL) {
        struct state* temp;
        temp = transitions[reachedStateNum][numOfAlphabets-1];
        while(temp!=NULL) {
            findEpsilonClosure(currStateNum, temp->stateNum);
            temp = temp->link;
        }
    }
}



int main() {
    int i;
    int currStateNum, nextStateNum;
    char alphabet;

    struct state *temp;

    // states
    printf("Enter the number of states: ");
    scanf("%d", &numOfStates);

    // start-state
    printf("Enter the start state?\n");
    scanf("%d",&start);

    // final-state
    printf("Enter the number of final states?\n");
    scanf("%d", &numOfFinalStates);
    printf("Enter the final states?\n");
    for(i=0;i<numOfFinalStates;i++)
        scanf("%d", &finalStates[i]);

    // alphabets
    printf("Enter the number of alphabets: ");
    scanf("%d", &numOfAlphabets);
    getchar();

    printf("Enter the alphabets:\n(Enter e for Epsilon & add it as the last alphabet)\n");
    for (i=0; i<numOfAlphabets; i++) {    
        alphabets[i] = getchar();
        getchar();
    }

    // transitions
    printf("Enter the number of transistions: ");
    scanf("%d", &numOfTransitions);

    printf("\nNOTE: State number begins at 1\nEnter transition in the format: CurrentStateNumber Alphabet NextStateNumber\n");
    for (i=0; i<numOfTransitions; i++) {
        scanf("%d %c%d", &currStateNum, &alphabet, &nextStateNum);
        createTransitionTable(currStateNum, alphabet, nextStateNum);
    }

    for (int row=1; row<=numOfStates; row++) {
        index = 0;
        for (i=0; i<MAX_NUM_OF_STATES; i++)
            visitedState[i] = 0;

        findEpsilonClosure(row, row);
    }

    printf("Equivalent NFA without epsilon\n");
    printf("-----------------------------------\n");
    
    // new start state contains start state plus all its epsilon transitions.
    printf("Start state: ");
    displayEpsilonClosure(start);
    
    printf("\nAlphabets: ");
    for(i=0;i<numOfAlphabets;i++)
        printf("%c ",alphabets[i]);
    
    // new states would be the orginal state plus its epsilon transitions.
    printf("\n States: " );
    for (int row=1; row<=numOfStates; row++) {
        displayEpsilonClosure(row);
    }

    printf("\nTransitions are...:\n");
    for(int i=1;i<=numOfStates;i++) {
        for(int j=0;j<numOfAlphabets-1;j++) {
            for(int m=1;m<=numOfStates;m++)
                set[m]=0;

            for(int k=0;epsilonClosure[i][k]!=0;k++) {
                int t = epsilonClosure[i][k]; // reached state number.
                temp = transitions[t][j]; // obtain transition from state t with alphabet j.
                // obtain all epsilon closures
                while(temp!=NULL) {
                    unionclosure(temp -> stateNum);
                    temp = temp -> link;
                }
            }
            // set would contain all states that could be visited with alphabet j.
            printf("\n");
            displayEpsilonClosure(i);
            printf("%c\t",alphabets[j]);
            printf("{");
            for(int n=1;n<=numOfStates;n++) {
                if(set[n]!=0)
                    printf("q%d,",n);
            }
            printf("}");
        }
    }
    printf("\n Final states:");
    printf("-");
    findfinalstate();
    return 0;
}


