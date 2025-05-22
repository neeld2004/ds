#include <stdio.h>

#define TABLE_SIZE 10
#define EMPTY -1

int hashTable[TABLE_SIZE];

// Hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Insert using Linear Probing
void insert(int key) {
    int index = hash(key);
    int originalIndex = index;
    int i = 0;

    // Linear probing to find the next available slot
    while (hashTable[index] != EMPTY) {
        printf("Collision detected for key %d at index %d\n", key, index);
        i++;
        index = (originalIndex + i) % TABLE_SIZE;

        if (i == TABLE_SIZE) {
            printf("Hash table is full. Cannot insert key %d\n", key);
            return;
        }
    }

    hashTable[index] = key;
}

// Display the hash table
void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != EMPTY)
            printf("Index %d: %d\n", i, hashTable[i]);
        else
            printf("Index %d: EMPTY\n", i);
    }
}

int main() {
    // Initialize hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }

    // Keys (some will cause collisions to test linear probing)
    int keys[] = {10, 20, 30, 21, 32, 43};  // Some collisions will occur
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insert(keys[i]);
    }

    display();
    return 0;
}
