#include <stdio.h>
#include <stdbool.h>

int max[5][3] = {
{7, 5, 3},
{3, 2, 2},
{9, 0, 2},
{2, 2, 2},
{4, 3, 3}
};

int allocated[5][3] = {
{0, 1, 0},
{2, 0, 0},
{3, 0, 2},
{2, 1, 1},
{0, 0, 2}
};

int need[5][3];
int available[3] = {3, 3, 2};
bool finish[5] = {false, false, false, false,false};

int idx = 0;
int safeSequence[5];

void printMatrix(int matrix[5][3])
{
	printf("[\n");
	for (int i = 0; i < 5; i++) {
		printf(" [");
		for (int j = 0; j < 3; j++) {
			printf("%d", matrix[i][j]);
			if(j < 2) {
				printf(", ");
			}
		}
			printf("]");
			if(i < 4) {
				printf(",");
			}
			printf("\n");
	}
		printf("]\n");
}

void calcNeed() 
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			need[i][j] = max[i][j] - allocated[i][j];
		}
	}
}

void bankersAlgo()
{
	for (int i = 0; i < 5; i++) {
		if (!finish[i]) {
			if (need[i][0] <= available[0] &&
			    need[i][1] <= available[1] &&
			    need[i][2] <= available[2]) {
			    finish[i] = true;
			    available[0] += allocated[i][0];
			    available[1] += allocated[i][1];
			    available[2] += allocated[i][2];
			    printf("Process %d in safe sequence\n", i);
			    safeSequence[idx] = i;
			    idx++;
		    }
		    else {
				printf("\nProcess %d does not have resources, must wait\n", i);
		    		continue;
		    	}
	    	}
    	}
}			    
			    


void findSafeSequence() {
    int count = 0;

    while (count < 5) {
        for (int i = 0; i < 5; i++) {
            bankersAlgo();
        }
        count++;
    }

    bool isSafe = true;

    for (int i = 0; i < 5; i++) {
        if (finish[i] != true) {
            printf("\nSafe sequence not found\n");
            isSafe = false;
        }
    }

    printf("\nSafe Sequence: ");

    if (isSafe) {
        printf("[");

        for (int i = 0; i < 5; i++) {
            printf("%d", safeSequence[i]);

            if (i < 4) {
                printf(", ");
            }
        }

        printf("]\n");
    }
}

int main() {
    printf("Initial Matrices:\n");

    printf("\nAllocation Matrix:\n");
    printMatrix(allocated);

    printf("\n");
    printf("Max Matrix:\n");
    printMatrix(max);

    printf("\n");
    calcNeed();

    printf("Need Matrix:\n");
    printMatrix(need);
    printf("\n");

    printf("Request for P1(1, 0, 2)\n");

    need[1][0] -= 1;
    need[1][1] -= 0;
    need[1][2] -= 2;

    available[0] -= 1;
    available[1] -= 0;
    available[2] -= 2;

    allocated[1][0] += 1;
    allocated[1][1] += 0;
    allocated[1][2] += 2;

    printf("Updated Matrices:\n");

    printf("\nAllocation Matrix:\n");
    printMatrix(allocated);
    printf("\n");

    printf("Max Matrix:\n");
    printMatrix(max);

    printf("\n");
    calcNeed();

    printf("Need Matrix:\n");
    printMatrix(need);

    findSafeSequence();

    return 0;
}
