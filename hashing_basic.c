#include <stdio.h>

#define TABLE_SIZE 10
#define EMPTY -1

int hashTable[TABLE_SIZE];

// Hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Insert without collisions
void insert(int key) {
    int index = hash(key);

    if (hashTable[index] == EMPTY) {
        hashTable[index] = key;
    } else {
        printf("Collision detected for key %d at index %d\n", key, index);
    }
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

    // Keys chosen to avoid collisions (all give unique hash indexes)
    int keys[] = {10, 21, 32, 43, 54};  // 10%10=0, 21%10=1, 32%10=2, etc.
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insert(keys[i]);
    }

    display();
    return 0;
}
