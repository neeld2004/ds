#include <stdio.h>

#define TABLE_SIZE 10
#define EMPTY -1

int hashTable[TABLE_SIZE];

// Primary hash function (mod-based)
int hash1(int key) {
    return key % TABLE_SIZE;
}

// Secondary hash function (must never return 0)
int hash2(int key) {
    return 7 - (key % 7);  // 7 is a prime less than TABLE_SIZE
}

// Insert using Double Hashing
void insert(int key) {
    int index1 = hash1(key);
    int index2 = hash2(key);
    int i = 0;
    int index;

    // Double hashing to find the next available slot
    while (i < TABLE_SIZE) {
        index = (index1 + i * index2) % TABLE_SIZE;

        if (hashTable[index] == EMPTY) {
            hashTable[index] = key;
            return;
        } else {
            printf("Collision detected for key %d at index %d\n", key, index);
        }

        i++;
    }

    printf("Hash table is full. Cannot insert key %d\n", key);
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

    // Keys (some will cause collisions to test double hashing)
    int keys[] = {10, 20, 30, 21, 32, 43};  // Some collisions will occur
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insert(keys[i]);
    }

    display();
    return 0;
}
