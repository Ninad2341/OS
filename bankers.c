#include <stdio.h>

#define MAX 10
#define RESOURCES 3

// Function to calculate the need matrix
void calculateNeed(int need[MAX][RESOURCES], int max[MAX][RESOURCES], int allot[MAX][RESOURCES], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < RESOURCES; j++)
        {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

// Function to check if the system is in a safe state
int isSafe(int processes, int resources, int avail[], int max[][RESOURCES], int allot[][RESOURCES])
{
    int need[MAX][RESOURCES];
    calculateNeed(need, max, allot, processes);

    int finish[MAX] = {0};
    int safeSeq[MAX];
    int work[RESOURCES];

    // Initialize work array
    for (int i = 0; i < resources; i++)
    {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < processes)
    {
        int found = 0;

        for (int p = 0; p < processes; p++)
        {
            if (!finish[p])
            {
                int canAllocate = 1;

                for (int r = 0; r < resources; r++)
                {
                    if (need[p][r] > work[r])
                    {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (int r = 0; r < resources; r++)
                    {
                        work[r] += allot[p][r];
                    }
                    finish[p] = 1;
                    safeSeq[count++] = p;
                    found = 1;
                    break;
                }
            }
        }

        if (!found)
        {
            printf("System is not in a safe state\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < processes; i++)
    {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return 1;
}

int main()
{
    int processes, resources;

    printf("Enter number of processes: ");
    scanf("%d", &processes);

    printf("Enter number of resources: ");
    scanf("%d", &resources);

    int avail[RESOURCES];
    printf("Enter the available instances of resources:\n");
    for (int i = 0; i < resources; i++)
    {
        printf("Resource %d: ", i);
        scanf("%d", &avail[i]);
    }

    int max[MAX][RESOURCES];
    int allot[MAX][RESOURCES];

    printf("Enter the maximum resource requirement matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            printf("Max[%d][%d]: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocated resources matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            printf("Allot[%d][%d]: ", i, j);
            scanf("%d", &allot[i][j]);
        }
    }

    isSafe(processes, resources, avail, max, allot);

    return 0;
}
