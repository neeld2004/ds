#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *left, *right;
} Node;
// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// Insert node into BST
Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}
// Search for a key in BST
int find(Node* root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    else if (key < root->data) return find(root->left, key);
    else return find(root->right, key);
}
// Inorder traversal (for display)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
// Mirror the BST (invert left and right children)
void mirror(Node* root) {
    if (root == NULL) return;
    // Swap left and right children
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}
int main() {
    Node* root = NULL;
    int choice, val;
    do {
        printf("\n\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Find\n");
        printf("3. Display Inorder\n");
        printf("4. Mirror Image\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Enter value to find: ");
                scanf("%d", &val);
                if (find(root, val))
                    printf("%d found in BST.\n", val);
                else
                    printf("%d not found in BST.\n", val);
                break;
            case 3:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                mirror(root);
                printf("BST mirrored.\n");
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 5);
    return 0;
}
