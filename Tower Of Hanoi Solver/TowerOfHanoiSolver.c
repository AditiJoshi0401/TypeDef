#include <stdio.h>
#include <stdlib.h>
#define MAX_DISKS 10

typedef struct
{
    int disks[MAX_DISKS];
    int top;
} Stack;

void initStack(Stack *stack)
{
    stack->top = -1;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, int disk)
{
    if (stack->top == MAX_DISKS - 1)
    {
        printf("Error: Stack is full\n");
        return;
    }
    stack->disks[++stack->top] = disk;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Error: Stack is empty\n");
        return -1;
    }
    return stack->disks[stack->top--];
}

int topDisk(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Error: Stack is empty\n");
        return -1;
    }
    return stack->disks[stack->top];
}

void moveDisk(Stack *from, Stack *to, int diskNo)
{
    int disk = pop(from);
    printf("Move disk %d from %c to %c\n", disk, 'A' + from->top + 1, 'A' + to->top + 1);
    push(to, disk);
}

void towerOfHanoi(int n, Stack *source, Stack *destination, Stack *auxiliary)
{
    if (n == 1)
    {
        moveDisk(source, destination, 1);
        return;
    }
    towerOfHanoi(n - 1, source, auxiliary, destination);
    moveDisk(source, destination, n);
    towerOfHanoi(n - 1, auxiliary, destination, source);
}

int main()
{
    int n;
    Stack source, destination, auxiliary;
    initStack(&source);
    initStack(&destination);
    initStack(&auxiliary);

    printf("Enter the number of disks: ");
    scanf("%d", &n);

    for (int i = n; i >= 1; i--)
    {
        push(&source, i);
    }

    printf("The sequence of moves involved in the Tower of Hanoi are:\n");
    towerOfHanoi(n, &source, &destination, &auxiliary);

    return 0;
}
