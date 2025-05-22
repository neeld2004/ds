#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#define max 100
int stack[max];
int top=-1;
void push(char c){
    stack[++top]=c;
}

char pop(){
    return stack[top--];
}

char peek(){
    return stack[top];

}

int precedence(char c){
    if(c=='+' || c=='-') return 1;
    if(c=='*' || c=='/') return 2;
    if(c=='^') return 3;
    return 0;
}

bool isoperator(char c){
    return (c=='+' || c=='-' || c=='*' || c=='/' ||c=='^');
}

int infixtopostfix(char infix[], char postfix[]){

int k=0,i=0;
char c;
while((c=infix[i++]) != '\0'){
    if(isdigit(c) || isalpha(c)){
        postfix[k++]=c;
    }
    if(c=='('){
        push(c);
    }
    if(c==')'){
        while(top!=-1 && peek()!='('){
            postfix[k++]=pop();
        }
        pop();
    }
    if(isoperator(c)){
     while(top!=-1 && precedence(peek())>=precedence(c)){
        postfix[k++]=pop();
     }
     push(c);
    }

  
}
  while(top!=-1){
        postfix[k++]=pop();
    }
     postfix[k] = '\0';
     return 0;
}

// Main function
int main() {
    char infix[max], postfix[max];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixtopostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
