#include <stdio.h>
#define MAX 100

// Stack for factorial
int factStack[MAX];
int top1 = -1;

void pushFact(int val) {
    if (top1 < MAX - 1)
        factStack[++top1] = val;
}

int popFact() {
    if (top1 >= 0)
        return factStack[top1--];
    return 1; // base case
}

int factorial(int n) {
    int result = 1;
    while (n > 1) {
        pushFact(n);
        n--;
    }

    while (top1 >= 0) {
        result *= popFact();
    }

    return result;
}

// Stack for Fibonacci
int fibStack[MAX];
int top2 = -1;

void pushFib(int val) {
    if (top2 < MAX - 1)
        fibStack[++top2] = val;
}

void fibonacci(int n) {
    int a = 0, b = 1, c;

    if (n >= 1) pushFib(a);
    if (n >= 2) pushFib(b);

    for (int i = 2; i < n; i++) {
        a = fibStack[top2 - 1];
        b = fibStack[top2];
        c = a + b;
        pushFib(c);
    }

    printf("Fibonacci Series: ");
    for (int i = 0; i <= top2; i++) {
        printf("%d ", fibStack[i]);
    }
    printf("\n");
}

int main() {
    int num;

    // Factorial
    printf("Enter a number to find factorial: ");
    scanf("%d", &num);
    int fact = factorial(num);
    printf("Factorial of %d is %d\n", num, fact);

    // Fibonacci
    printf("Enter number of terms for Fibonacci series: ");
    scanf("%d", &num);
    fibonacci(num);

    return 0;
}
