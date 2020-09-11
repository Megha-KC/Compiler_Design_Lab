#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_OF_ALPHABETS 20
#define MAX_NUM_OF_STATES 20

struct state {
    int stateNum;
    struct state* link;
};

static int index;
int numOfStates, numOfAlphabets, numOfTransitions;


int visitedState[MAX_NUM_OF_STATES];
int epsilonClosure[MAX_NUM_OF_STATES][MAX_NUM_OF_STATES] = {0};
char alphabets[MAX_NUM_OF_ALPHABETS];
struct state* transitions[MAX_NUM_OF_STATES][MAX_NUM_OF_ALPHABETS] = {NULL};

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

void displayEpsilonClosure(int stateNum) {
    printf("{ q%d", stateNum);
    for (int i=1; i<index; i++)
        printf(", q%d", epsilonClosure[stateNum][i]);
    printf(" }\n");
}

int main() {
    int i;
    int currStateNum, nextStateNum;
    char alphabet;

    printf("Enter the number of states: ");
    scanf("%d", &numOfStates);

    printf("Enter the number of alphabets: ");
    scanf("%d", &numOfAlphabets);
    getchar();

    printf("Enter the alphabets:\n(Enter e for Epsilon & add it as the last alphabet)\n");
    for (i=0; i<numOfAlphabets; i++) {    
        alphabets[i] = getchar();
        getchar();
    }

    printf("Enter the number of transistions: ");
    scanf("%d", &numOfTransitions);

    printf("\nNOTE: State number begins at 1\nEnter transition in the format: CurrentStateNumber Alphabet NextStateNumber\n");
    for (i=0; i<numOfTransitions; i++) {
        scanf("%d %c%d", &currStateNum, &alphabet, &nextStateNum);
        createTransitionTable(currStateNum, alphabet, nextStateNum);
    }

    printf("Epsilon closure for the states are:\n");
    for (int row=1; row<=numOfStates; row++) {
        index = 0;
        for (i=0; i<MAX_NUM_OF_STATES; i++)
            visitedState[i] = 0;

        findEpsilonClosure(row, row);
        printf("e-closure(q%d) = ", row);
        displayEpsilonClosure(row);
    }


    return 0;
}


