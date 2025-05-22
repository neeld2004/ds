#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node*next;
};

struct node*nodecreation(int newdata){
struct node*newnode=(struct node*)malloc(sizeof(struct node));
newnode->data=newdata;
newnode->next=NULL;
return newnode;
}

void insertionsort(struct node*head){
struct node*temp=head;
int holddata;
struct node*i;
struct node*j;
    for( i=temp;i!=NULL;temp=temp->next){
        j=i;
        while(j!=head && temp->data>temp->next->data){
            holddata= temp->data;
            temp->data=temp->next->data;
            temp->next->data=holddata;
            j--;
        }
    }
    
}
void printL(struct node*head){
while(head!=NULL){
    printf("%d ",head->data);
    head=head->next;
}
}
int main(){
    
    struct node*head=nodecreation(1);
    head->next=nodecreation(2);
    head->next->next=nodecreation(3);
    head->next->next->next=nodecreation(4);

   
    insertionsort(head);
    printL(head);

}