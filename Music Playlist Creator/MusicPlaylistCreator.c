#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct song
{
    char *songName;
    char *artistName;
    struct song *next;
    struct song *prev;
} *head;

void create(struct song *temp)
{
    temp->next = malloc(sizeof(struct song));
    temp->next->songName = malloc(sizeof(char) * 21);
    temp->next->artistName = malloc(sizeof(char) * 21);

    printf("\nEnter song name : ");
    scanf("%20s", temp->next->songName);

    printf("\nEnter artist name : ");
    scanf("%20s", temp->next->artistName);

    temp->next->next = NULL;
    temp->next->prev = temp;
}

void traverseList()
{
    struct song *temp = head->next;
    printf("\nList of all your songs : ");
    while (temp != NULL)
    {
        printf("\n=> %s by %s", temp->songName, temp->artistName);
        temp = temp->next;
    }
    printf("\n--x-- End Of List --x--");
}

void insert()
{
    struct song *temp = head->next;
    if (temp == NULL)
    {
        // Agar Linked list is empty
        create(head);
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        create(temp);
    }
}

void deleteAtindex(int index, int sizeofLL)
{
    struct song *temp = head->next;
    if (index > 0)
    {
        if (index <= sizeofLL)
        {
            for (int i = 1; i < index - 1; i++)
            {
                temp = temp->next;
            }
            struct song *temp2 = temp->next;
            if (temp2 != NULL)
            {
                temp->next = temp->next->next;
                if (temp->next != NULL)
                {
                    temp->next->prev = temp;
                }
                free(temp2->songName);
                free(temp2->artistName);
                free(temp2);
            }
            else
            {
                printf("Invalid Index.. Index was greater than size of LL!");
            }
        }
        else
        {
            printf("Invalid Index.. Index was greater than size of LL!");
        }
    }
    else
    {
        printf("Invalid Index.. Index was smaller than 0!");
    }
}

int main()
{
    head = malloc(sizeof(struct song));
    struct song *temp = head;
    int numberOfSongs = 0;

    while (true)
    {
        printf("\n1. Add a song\n2. Remove a song\n3. Browse the playlist\nEnter which operation to perform : ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            insert();
            numberOfSongs++;
            break;
        case 2:
            printf("Enter the index to delete: ");
            int deleteIndex;
            scanf("%d", &deleteIndex);
            deleteAtindex(deleteIndex, numberOfSongs);
            numberOfSongs--;
            break;
        case 3:
            traverseList();
            break;
        default:
            printf("Invalid Answer!");
        }
    }

    // Free memory
    temp = head;
    while (temp != NULL)
    {
        struct song *next = temp->next;
        free(temp->songName);
        free(temp->artistName);
        free(temp);
        temp = next;
    }

    return 0;
}
