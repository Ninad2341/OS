#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function to check if page is in frame
int isInFrame(int frames[], int size, int page)
{
    for (int i = 0; i < size; i++)
        if (frames[i] == page)
            return 1;
    return 0;
}

// FIFO Page Replacement
void fifo(int pages[], int n, int frame_size)
{
    int frames[frame_size];
    int i, j, page_faults = 0, front = 0;

    for (i = 0; i < frame_size; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (i = 0; i < n; i++)
    {
        if (!isInFrame(frames, frame_size, pages[i]))
        {
            frames[front] = pages[i];
            front = (front + 1) % frame_size;
            page_faults++;
            printf("Page %d -> Page Fault! Frames: ", pages[i]);
        }
        else
        {
            printf("Page %d -> Hit! Frames: ", pages[i]);
        }

        for (j = 0; j < frame_size; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

// Find the page to replace for Optimal algorithm
int findOptimal(int frames[], int n, int pages[], int current_index, int frame_size)
{
    int i, j;
    int res = -1, farthest = current_index;

    for (i = 0; i < frame_size; i++)
    {
        int j;
        for (j = current_index; j < n; j++)
        {
            if (frames[i] == pages[j])
                break;
        }

        if (j == n)
            return i; // not found in future
        if (j > farthest)
        {
            farthest = j;
            res = i;
        }
    }
    if (res == -1)
        return 0;
    else
        return res;
}

// Optimal Page Replacement
void optimal(int pages[], int n, int frame_size)
{
    int frames[frame_size];
    int i, j, page_faults = 0;

    for (i = 0; i < frame_size; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (i = 0; i < n; i++)
    {
        if (!isInFrame(frames, frame_size, pages[i]))
        {
            if (i < frame_size)
            {
                frames[i] = pages[i];
            }
            else
            {
                int idx = findOptimal(frames, n, pages, i + 1, frame_size);
                frames[idx] = pages[i];
            }
            page_faults++;
            printf("Page %d -> Page Fault! Frames: ", pages[i]);
        }
        else
        {
            printf("Page %d -> Hit! Frames: ", pages[i]);
        }

        for (j = 0; j < frame_size; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

// Find LRU page index to replace
int findLRU(int time[], int n)
{
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; i++)
    {
        if (time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

// LRU Page Replacement
void lru(int pages[], int n, int frame_size)
{
    int frames[frame_size];
    int counter = 0, page_faults = 0;
    int time[frame_size];
    int i, j;

    for (i = 0; i < frame_size; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for (i = 0; i < n; i++)
    {
        int page = pages[i];
        if (isInFrame(frames, frame_size, page))
        {
            // Update time for used frame
            for (j = 0; j < frame_size; j++)
            {
                if (frames[j] == page)
                {
                    time[j] = counter++;
                    break;
                }
            }
            printf("Page %d -> Hit! Frames: ", page);
        }
        else
        {
            int pos = -1;
            // Check if empty frame
            for (j = 0; j < frame_size; j++)
            {
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = findLRU(time, frame_size);
            frames[pos] = page;
            time[pos] = counter++;
            page_faults++;
            printf("Page %d -> Page Fault! Frames: ", page);
        }

        for (j = 0; j < frame_size; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main()
{
    int n, frame_size, choice;
    int pages[MAX];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frame_size);

    printf("\nSelect Page Replacement Algorithm:\n");
    printf("1. FIFO\n2. LRU\n3. Optimal\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        fifo(pages, n, frame_size);
        break;
    case 2:
        lru(pages, n, frame_size);
        break;
    case 3:
        optimal(pages, n, frame_size);
        break;
    default:
        printf("Invalid choice!\n");
    }

    return 0;
}
