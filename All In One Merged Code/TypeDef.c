#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LEN 6
#define MAX_WORDS 1000
#define MAX_DISKS 10

// Structures
typedef struct Node {
    char name[50];
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
} FamilyNode;

typedef struct {
    int disks[MAX_DISKS];
    int top;
} TowerStack;

struct SongNode {
    char* songTitle;
    char* artistName;
    struct SongNode* next;
    struct SongNode* prev;
} *songHead;

// Function Prototypes
void createSongNode(struct SongNode* temp);
void traverseSongList();
void insertSong();
void deleteSongAtIndex(int index, int sizeOfList);
FamilyNode* createFamilyNode(char* name);
void addFamilyMember(FamilyNode* parent, FamilyNode* child, char* relation);
FamilyNode* searchFamilyTree(FamilyNode* root, char* name);
void printFamilyMemberInfo(FamilyNode* node);
void initTowerStack(TowerStack* stack);
int isStackEmpty(TowerStack* stack);
void pushToDisk(TowerStack* stack, int disk);
int popFromDisk(TowerStack* stack);
int topDiskOnStack(TowerStack* stack);
void moveTowerDisk(TowerStack* from, TowerStack* to, int diskNo);
void solveTowerOfHanoi(int n, TowerStack* source, TowerStack* destination, TowerStack* auxiliary);
int readWordsFromFile(const char* filename, char words[][MAX_WORD_LEN], int* num_words);
void playWordle(const char words[][MAX_WORD_LEN], int num_words);

int main() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Song Playlist\n");
        printf("2. Family Tree Simulator\n");
        printf("3. Tower of Hanoi Solver\n");
        printf("4. Wordle Game\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                songHead = malloc(sizeof(struct SongNode));
                struct SongNode* temp = songHead;
                int numSongs = 0;

                while (1) {
                    printf("\n1. Add a song\n2. Remove a song\n3. Browse the playlist\n4. Back to menu\nEnter your choice: ");
                    int songChoice;
                    scanf("%d", &songChoice);

                    switch (songChoice) {
                        case 1:
                            insertSong();
                            numSongs++;
                            break;
                        case 2:
                            printf("Enter the index to delete: ");
                            int deleteIndex;
                            scanf("%d", &deleteIndex);
                            deleteSongAtIndex(deleteIndex, numSongs);
                            numSongs--;
                            break;
                        case 3:
                            traverseSongList(numSongs);
                            break;
                        case 4:
                            goto menu_exit;
                        default:
                            printf("Invalid choice!\n");
                    }
                }
                menu_exit:
                // Free memory
                temp = songHead;
                while (temp != NULL) {
                    struct SongNode* next = temp->next;
                    free(temp->songTitle);
                    free(temp->artistName);
                    free(temp);
                    temp = next;
                }
                break;
            }
            case 2: {
                FamilyNode* root = NULL;
                int familyChoice;
                char name[50];
                char relation[10];
                char searchName[50];

                do {
                    printf("\nFamily Tree Menu:\n");
                    printf("1. Add a person\n");
                    printf("2. Search for a person\n");
                    printf("3. Back to menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &familyChoice);

                    switch (familyChoice) {
                        case 1:
                            printf("Enter the name of the person: ");
                            scanf("%s", name);

                            if (root == NULL) {
                                root = createFamilyNode(name);
                            } else {
                                printf("Enter the name of the parent: ");
                                scanf("%s", relation);
                                FamilyNode* parent = searchFamilyTree(root, relation);

                                if (parent != NULL) {
                                    FamilyNode* newNode = createFamilyNode(name);
                                    printf("Enter 'l' for left child or 'r' for right child: ");
                                    scanf("%s", relation);
                                    addFamilyMember(parent, newNode, relation);
                                } else {
                                    printf("Parent not found.\n");
                                }
                            }
                            break;

                        case 2:
                            printf("Enter the name to search: ");
                            scanf("%s", searchName);
                            FamilyNode* found = searchFamilyTree(root, searchName);

                            if (found != NULL) {
                                printFamilyMemberInfo(found);
                            } else {
                                printf("Person not found in the family tree.\n");
                            }
                            break;

                        case 3:
                            printf("Returning to menu...\n");
                            break;

                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (familyChoice != 3);
                break;
            }
            case 3: {
                int numDisks;
                TowerStack source, destination, auxiliary;
                initTowerStack(&source);
                initTowerStack(&destination);
                initTowerStack(&auxiliary);

                printf("Enter the number of disks: ");
                scanf("%d", &numDisks);

                for (int i = numDisks; i >= 1; i--) {
                    pushToDisk(&source, i);
                }

                printf("The sequence of moves involved in the Tower of Hanoi are:\n");
                solveTowerOfHanoi(numDisks, &source, &destination, &auxiliary);
                break;
            }
            case 4: {
                char words[MAX_WORDS][MAX_WORD_LEN];
                int num_words;
                if (readWordsFromFile("words.csv", words, &num_words) != 0) {
                    printf("Error reading word file.\n");
                    break;
                }

                playWordle(words, num_words);
                break;
            }
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Song Playlist Functions
void createSongNode(struct SongNode* temp) {
    temp->next = malloc(sizeof(struct SongNode));
    temp->next->songTitle = malloc(sizeof(char) * 21);
    temp->next->artistName = malloc(sizeof(char) * 21);

    printf("\nEnter song name : ");
    scanf("%20s", temp->next->songTitle);

    printf("\nEnter artist name : ");
    scanf("%20s", temp->next->artistName);

    temp->next->next = NULL;
    temp->next->prev = temp;
}

void traverseSongList(int numSongs) {
    struct SongNode* temp = songHead->next;
    printf("\nList of all your songs : ");
    while (temp != NULL) {
        printf("\n=> %s by %s", temp->songTitle, temp->artistName);
        temp = temp->next;
    }
    printf("\nTotal number of songs in playlist : %d", numSongs);
    printf("\n--x-- End Of List --x--");
}

void insertSong()
{
    struct SongNode *temp = songHead->next;
    if (temp == NULL)
    {
        // Agar Linked list is empty
        createSongNode(songHead);
    }
    else
    {
        while (songHead->next != NULL)
        {
            temp = temp->next;
        }
        createSongNode(temp);
    }
}

void deleteSongAtIndex(int index, int sizeOfList) {
    struct SongNode *temp = songHead;
    if (songHead->next == NULL) {
        printf("List is empty!\n");
        return;
    }

    if (index > 0) {
        if (index <= sizeOfList) {
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            struct SongNode *temp2 = temp->next;
            if (temp2 != NULL) {
                temp->next = temp->next->next;
                if (temp->next != NULL) {
                    temp->next->prev = temp;
                }
                free(temp2->songTitle);
                free(temp2->artistName);
                free(temp2);
            }
        } else {
            printf("Invalid Index.. Index was greater than size of Playlist!\n");
        }
    } else {
        printf("Invalid Index.. Index was smaller than 0!\n");
    }
}

FamilyNode* createFamilyNode(char* name){
    FamilyNode* newNode = (FamilyNode*)malloc(sizeof(FamilyNode));
    strcpy(newNode->name, name);
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

void addFamilyMember(FamilyNode* parent, FamilyNode* child, char* relation){
    child->parent = parent;

    if (relation[0] == 'l')
        parent->leftChild = child;
    else
        parent->rightChild = child;
}

FamilyNode* searchFamilyTree(FamilyNode* root, char* name){
    if (root == NULL || strcmp(root->name, name) == 0)
        return root;

    FamilyNode* found = searchFamilyTree(root->leftChild, name);

    if (found != NULL)
        return found;

    return searchFamilyTree(root->rightChild, name);
}

void printFamilyMemberInfo(FamilyNode* node){
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

void initTowerStack(TowerStack* stack){
    stack->top = -1;
}

int isStackEmpty(TowerStack* stack){
    return stack->top == -1;
}

void pushToDisk(TowerStack* stack, int disk){
    if (stack->top == MAX_DISKS - 1)
    {
        printf("Error: Stack is full\n");
        return;
    }
    stack->disks[++stack->top] = disk;
}

int popFromDisk(TowerStack* stack){
    if (isStackEmpty(stack))
    {
        printf("Error: Stack is empty\n");
        return -1;
    }
    return stack->disks[stack->top--];
}

int topDiskOnStack(TowerStack* stack){
    if (isStackEmpty(stack))
    {
        printf("Error: Stack is empty\n");
        return -1;
    }
    return stack->disks[stack->top];
}

void moveTowerDisk(TowerStack* from, TowerStack* to, int diskNo){
    int disk = popFromDisk(from);
    printf("Move disk %d from %c to %c\n", disk, 'A' + from->top + 1, 'A' + to->top + 1);
    pushToDisk(to, disk);
}

void solveTowerOfHanoi(int n, TowerStack* source, TowerStack* destination, TowerStack* auxiliary){
    if (n == 1)
    {
        moveTowerDisk(source, destination, 1);
        return;
    }
    solveTowerOfHanoi(n - 1, source, auxiliary, destination);
    moveTowerDisk(source, destination, n);
    solveTowerOfHanoi(n - 1, auxiliary, destination, source);
}

int readWordsFromFile(const char* filename, char words[][MAX_WORD_LEN], int* num_words){
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    printf("Error: Could not open file %s\n", filename);
    return 1;
  }

  char line[MAX_WORD_LEN];
  int i = 0;
  while (fgets(line, MAX_WORD_LEN, file) && i < MAX_WORDS)
  {
    // Remove the newline character from the end of the line
    line[strcspn(line, "\n")] = '\0';
    strcpy(words[i], line);
    i++;
  }

  *num_words = i;
  fclose(file);
  return 0;
}

void playWordle(const char words[][MAX_WORD_LEN], int num_words){
  char answer[MAX_WORD_LEN];
  int answer_len;

  // Seed the random number generator
  srand(time(NULL));

  // Select a random word from the list
  int random_index = rand() % num_words;
  strcpy(answer, words[random_index]);
  answer_len = strlen(answer);

  char guess[MAX_WORD_LEN];
  int attempts = 0;
  int max_attempts = 6;

  printf("Welcome to Wordle!\n");
  printf("You have %d attempts to guess the %d-letter word.\n", max_attempts,
         answer_len);

  while (attempts < max_attempts)
  {
    printf("\nEnter your guess: ");
    scanf("%s", guess);

    if (strlen(guess) != answer_len)
    {
      printf("Invalid guess length!\n");
      continue;
    }

    int correct_letters = 0;
    int correct_positions = 0;

    // Check for correct letters and positions
    for (int i = 0; i < answer_len; i++)
    {
      if (guess[i] == answer[i])
      {
        correct_positions++;
      }
      else
      {
        for (int j = 0; j < answer_len; j++)
        {
          if (guess[i] == answer[j])
          {
            correct_letters++;
            break;
          }
        }
      }
    }

    // Print the result
    printf("Correct letters in the right position: %d\n", correct_positions);
    printf("Correct letters in the wrong position: %d\n", correct_letters);

    if (correct_positions == answer_len)
    {
      printf("\nCongratulations! You guessed the word correctly!\n");
      return;
    }

    attempts++;
  }

  printf("\nSorry, you ran out of attempts. The word was: %s\n", answer);
}
