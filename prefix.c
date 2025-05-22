#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define max 100

int stack[max];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

char peek() {
    return stack[top];
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

bool isoperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to reverse a string
void reverse(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char t = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = t;
    }
}

// Convert infix to prefix
void infixtoprefix(char infix[], char prefix[]) {
    char temp[max];
    int i = 0, k = 0;
    char c;

    reverse(infix); // Step 1: Reverse infix

    // Step 2: Replace ( with ) and vice versa
    while (infix[i] != '\0') {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
        i++;
    }

    i = 0;
    while ((c = infix[i++]) != '\0') {
        if (isdigit(c) || isalpha(c)) {
            temp[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && peek() != '(') {
                temp[k++] = pop();
            }
            pop(); // remove '('
        } else if (isoperator(c)) {
            while (top != -1 && precedence(peek()) > precedence(c)) {
                temp[k++] = pop();
            }
            push(c);
        }
    }

    while (top != -1) {
        temp[k++] = pop();
    }
    temp[k] = '\0';

    reverse(temp); // Final Step: Reverse result to get prefix
    strcpy(prefix, temp);
}

// Main
int main() {
    char infix[max], prefix[max];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixtoprefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}
