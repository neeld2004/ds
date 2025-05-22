#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node*next;
    struct node*prev;
};

struct node*nodecreation(int newdata){
struct node*newnode=(struct node*)malloc(sizeof(struct node));
newnode->data=newdata;
newnode->next=NULL;
newnode->prev=NULL;
return newnode;
}

void sort(struct node* head) {
    struct node* i;
    struct node* j;
    int temp;

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                // Swap data values
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
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
    struct node*second=nodecreation(45);
    struct node*third=nodecreation(78);
    struct node*forth=nodecreation(36);
   
    head->next=second;
    second->prev=head;
    second->next=third;
    third->prev=second;
    third->next=forth;
    forth->prev=third;
    forth->next=NULL;
    sort(head);
    printL(head);

}