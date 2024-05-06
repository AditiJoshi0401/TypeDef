#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a node in the binary tree
typedef struct Node {
    char name[50];
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

// Function prototypes
Node* createNode(char* name);
void addChild(Node* parent, Node* child, char* relation);
Node* searchTree(Node* root, char* name);
void printParentAndChildren(Node* node);

int main() {
    Node* root = NULL;
    int choice;
    char name[50];
    char relation[10];
    char searchName[50];

    do {
        printf("\nFamily Tree Menu:\n");
        printf("1. Add a person\n");
        printf("2. Search for a person\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the name of the person: ");
                scanf("%s", name);

                if (root == NULL) {
                    root = createNode(name);
                } else {
                    printf("Enter the name of the parent: ");
                    scanf("%s", relation);
                    Node* parent = searchTree(root, relation);

                    if (parent != NULL) {
                        Node* newNode = createNode(name);
                        printf("Enter 'l' for left child or 'r' for right child: ");
                        scanf("%s", relation);
                        addChild(parent, newNode, relation);
                    } else {
                        printf("Parent not found.\n");
                    }
                }
                break;

            case 2:
                printf("Enter the name to search: ");
                scanf("%s", searchName);
                Node* found = searchTree(root, searchName);

                if (found != NULL) {
                    printParentAndChildren(found);
                } else {
                    printf("Person not found in the family tree.\n");
                }
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

// Function to create a new node
Node* createNode(char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

// Function to add a child to a parent node
void addChild(Node* parent, Node* child, char* relation) {
    child->parent = parent;

    if (relation[0] == 'l')
        parent->leftChild = child;
    else
        parent->rightChild = child;
}

// Function to search for a node in the tree
Node* searchTree(Node* root, char* name) {
    if (root == NULL || strcmp(root->name, name) == 0)
        return root;

    Node* found = searchTree(root->leftChild, name);

    if (found != NULL)
        return found;

    return searchTree(root->rightChild, name);
}

// Function to print the parent and children of a node
void printParentAndChildren(Node* node) {
    printf("\nName: %s\n", node->name);

    if (node->parent != NULL)
        printf("Parent: %s\n", node->parent->name);
    else
        printf("Parent: None\n");

    printf("Children: ");
    if (node->leftChild != NULL)
        printf("%s ", node->leftChild->name);
    if (node->rightChild != NULL)
        printf("%s ", node->rightChild->name);
    if (node->leftChild == NULL && node->rightChild == NULL)
        printf("None");

    printf("\n");
}
