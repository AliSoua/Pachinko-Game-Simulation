#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


// Define structures
typedef struct Player {
    int id;
    char name[50];
    float balance;
    float mostBetWon; // New attribute to track the most bet won by the player
    struct Player* next; // Pointer to the next player node
} Player;

typedef struct Node {
    float multiplier;
    struct Node *left;
    struct Node *right;
} Node;

Player* createPlayer(int id, const char name[], float balance) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    if (newPlayer != NULL) {
        newPlayer->id = id;
        strcpy(newPlayer->name, name);
        newPlayer->balance = balance;
        newPlayer->mostBetWon = 0;
        newPlayer->next = NULL;
    }
    return newPlayer;
}

void addPlayer(Player** head, int id, const char name[], float balance) {
    Player* newPlayer = createPlayer(id, name, balance);
    if (newPlayer != NULL) {
        newPlayer->next = *head;
        *head = newPlayer;
    }
}

void deletePlayer(Player** head, int id) {
    Player* current = *head;
    Player* prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Player with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

void updatePlayer(Player* head, int id, const char newName[], float newBalance) {
    Player* current = head;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Player with ID %d not found.\n", id);
        return;
    }

    strcpy(current->name, newName);
    current->balance = newBalance;
}

void addBalance(Player* head, int id, float amount) {
    Player* current = head;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Player with ID %d not found.\n", id);
        return;
    }

    current->balance += amount;
}

void addmostwon(Player* head, int id, float amount) {
    Player* current = head;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Player with ID %d not found.\n", id);
        return;
    }
    if (current->mostBetWon < amount){
        current->mostBetWon = amount;
    }
}

void withdrawBalance(Player* head, int id, float amount) {
    Player* current = head;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Player with ID %d not found.\n", id);
        return;
    }

    if (current->balance >= amount) {
        current->balance -= amount;
    } else {
        printf("Insufficient balance for player with ID %d.\n", id);
    }
}

void displayPlayers(const Player* head) {
    printf("Players:\n");
    const Player* current = head;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Balance: %.2f\n", current->id, current->name, current->balance);
        current = current->next;
    }
}


void freePlayers(Player* head) {
    Player* current = head;
    while (current != NULL) {
        Player* temp = current;
        current = current->next;
        free(temp);
    }
}

void displayClientMenu() {
    printf("\nClient Menu:\n");
    printf("1. Play the Pachinko game\n");
    printf("2. Add balance to a player\n");
    printf("3. Withdraw balance from a player\n");
    printf("4. Check leaderboard\n");
    printf("5. Exit\n");
}

void displayAdminMenu() {
    printf("\nAdmin Menu:\n");
    printf("1. Add a player\n");
    printf("2. Delete a player\n");
    printf("3. Update player info\n");
    printf("4. Show all players\n");
    printf("5. Exit\n");
}

void displayleaderboard(const Player* head) {
    printf("Players:\n");
    const Player* current = head;
    while (current != NULL) {
        printf("Name: %s, Most Bet Won: %.2f\n", current->name, current->mostBetWon);
        current = current->next;
    }
}

bool validateId(const Player* head, int id) {
    const Player* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function to generate a random multiplier attribute
float generateMultiplier() {
    float multipliers[] = {0, 0.5, 1, 2, 0.75, 50};
    int index = rand() % 100; // Adjusted range for finer control

    // Adjusting the probability of getting 50
    if (index == 99) {
        index = rand() % 5; // Select from the first five multipliers with higher probability
    }

    return multipliers[index % 6]; // Ensure the index is within the range of the original array
}


// Function to generate a random tree with given depth
Node* generateTree(int depth, bool isRoot) {
    if (depth == 0) return NULL;

    Node *node = (Node*)malloc(sizeof(Node));

    // Generate the root node with a multiplier of 1 if it's the root of the tree
    if (isRoot)
        node->multiplier = 1.0;
    else
        node->multiplier = generateMultiplier();

    node->left = generateTree(depth - 1, false); // Pass false for subsequent nodes
    node->right = generateTree(depth - 1, false);

    return node;
}



// Function to traverse the tree with random decisions and update the bet
float traverseTreeWithPrint(Node *root, float bet) {
    if (root == NULL) return bet;

    float multiplier = root->multiplier;
    int direction = rand() % 2; // 0 for left, 1 for right

    if (direction == 0) {
        printf("Left (%.2f) -> ", multiplier);
        return traverseTreeWithPrint(root->left, bet * multiplier);
    } else {
        printf("Right (%.2f) -> ", multiplier);
        return traverseTreeWithPrint(root->right, bet * multiplier);
    }
}

// Function to print the tree (for visualization purposes)
void printTree(Node *root, int level) {
    if (root == NULL) return;

    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("\t");
    printf("%.2f\n", root->multiplier);
    printTree(root->left, level + 1);
}

int main() {
    Player* head = NULL;
    int choice;
    int userType = 0; // Initialize userType to 0 to enter the loop
    int id;
    char name[50];
    float balance, amount;
    Node* root = NULL;

    printf("Welcome to the Pachinko game !!\n");

    // Loop until the user chooses to exit
    while (userType != 3) {
        printf("\nChoose user type:\n");
        printf("1. Client\n");
        printf("2. Admin\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &userType) != 1) {
            printf("Invalid input. Please enter a valid choice.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (userType) {
            case 1:
                do {
                    displayClientMenu();
                    printf("Enter your choice: ");
                    if (scanf("%d", &choice) != 1) {
                        printf("Invalid input. Please enter a valid choice.\n");
                        while (getchar() != '\n'); // Clear input buffer
                        continue;
                    }

                    switch (choice) {
                        case 1:
                            // Play Pachinko game
                            printf("Playing Pachinko game...\n");
                            int id;
                            float bet;

                            // Prompt the user for player ID
    printf("Enter player ID: ");
    scanf("%d", &id);

    // Check if the player ID exists
    if (!validateId(head, id)) {
        printf("Player with ID %d not found.\n", id);
        break;
    }

    // Prompt the user for bet amount
    printf("Enter your bet amount: ");
    scanf("%f", &bet);

    // Check if the player has sufficient balance
    Player *current = head;
    while (current != NULL) {
        if (current->id == id) {
            if (current->balance < bet) {
                printf("Insufficient balance for player with ID %d.\n", id);
                break;
            }
            break; // Found the player, exit the loop
        }
        current = current->next;
    }

    // If the player has sufficient balance, proceed with tree generation and traversal
    if (current != NULL && current->id == id && current->balance >= bet) {
        int depth = rand() % 4 + 2; // Generate random depth between 2 and 5

        Node *root = generateTree(depth,true);
        printTree(root,depth);
        printf("\nTraversal Route:\n");
        float finalBet = traverseTreeWithPrint(root, bet);
        printf("\nFinal Bet: %.2f\n", finalBet);

        // Update player's balance after the bet
        withdrawBalance(head, id, bet);
        addBalance(head,id,finalBet);

        if ( finalBet > bet ){
            printf("Congratulation you won this amout %2f !!!",finalBet);
            addmostwon(head,id,finalBet);
        }
        else{
            printf("Unfortunately you lost %2f ..",finalBet);
        }
        break;
    }
    break;
                        case 2:
                            printf("Enter player ID to add balance: ");
                            if (scanf("%d", &id) != 1) {
                                printf("Invalid input. Please enter a valid player ID.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            if (!validateId(head, id)) {
                                printf("Player with ID %d not found.\n", id);
                                break;
                            }
                            printf("Enter amount to add: ");
                            if (scanf("%f", &amount) != 1) {
                                printf("Invalid input. Please enter a valid amount.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            addBalance(head, id, amount);
                            break;
                        case 3:
                            printf("Enter player ID to withdraw balance: ");
                            if (scanf("%d", &id) != 1) {
                                printf("Invalid input. Please enter a valid player ID.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            if (!validateId(head, id)) {
                                printf("Player with ID %d not found.\n", id);
                                break;
                            }
                            printf("Enter amount to withdraw: ");
                            if (scanf("%f", &amount) != 1) {
                                printf("Invalid input. Please enter a valid amount.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            withdrawBalance(head, id, amount);
                            break;
                        case 4:
                            // Display leaderboard
                            displayleaderboard(head);
                            break;
                        case 5:
                            printf("Exiting client mode.\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (choice != 5);
                break;

            case 2:
                do {
                    displayAdminMenu();
                    printf("Enter your choice: ");
                    if (scanf("%d", &choice) != 1) {
                        printf("Invalid input. Please enter a valid choice.\n");
                        while (getchar() != '\n'); // Clear input buffer
                        continue;
                    }

                    switch (choice) {
                        case 1:
                            printf("Enter player ID: ");
                            if (scanf("%d", &id) != 1) {
                                printf("Invalid input. Please enter a valid player ID.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            printf("Enter player name: ");
                            scanf("%s", name); // No error handling for name input
                            printf("Enter player balance: ");
                            if (scanf("%f", &balance) != 1) {
                                printf("Invalid input. Please enter a valid balance.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            addPlayer(&head, id, name, balance);
                            break;
                        case 2:
                            printf("Enter player ID to delete: ");
                            if (scanf("%d", &id) != 1) {
                                printf("Invalid input. Please enter a valid player ID.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            deletePlayer(&head, id);
                            break;
                        case 3:
                            printf("Enter player ID to update: ");
                            if (scanf("%d", &id) != 1) {
                                printf("Invalid input. Please enter a valid player ID.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            printf("Enter new name: ");
                            scanf("%s", name); // No error handling for name input
                            printf("Enter new balance: ");
                            if (scanf("%f", &balance) != 1) {
                                printf("Invalid input. Please enter a valid balance.\n");
                                while (getchar() != '\n'); // Clear input buffer
                                continue;
                            }
                            updatePlayer(head, id, name, balance);
                            break;
                        case 4:
                            displayPlayers(head);
                            break;
                        case 5:
                            printf("Exiting admin mode.\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (choice != 5);
                break;

            case 3:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid user type. Please try again.\n");
                break;
        }
    }

    freePlayers(head);
    return 0;
}
