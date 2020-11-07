#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t lock;
 
struct node
{
   int data;
   struct node *next;
};
typedef struct node node;
 
struct queue
{
   int count;
   node *front;
   node *rear;
};
typedef struct queue queue;
 
void make_queue(queue *q)
{
   q->count = 0;
   q->front = NULL;
   q->rear = NULL;
}
 
int isempty(queue *q)
{
   return (q->rear == NULL);
}
 
void Search (node *head, int key)
{
   int flag=0;
   if(head == NULL)
   {
       printf("Empty\n");
   }
   else
   {
       while (head->next)
       {
           if (head->data==key)
           {
            printf("%d found\n", key);
               flag=1;
               break;
           }
           head=head->next;
       }
   }
   if (flag==0)
   {
       printf("%d not found\n", key);
   }
}
 
void Print(node *head)
{
   if(head == NULL)
   {
       printf("NULL\n");
   }
   else
   {
       printf("%d ", head -> data);
       Print(head->next);
   }
}
 
void Free(node* head)
{
   while (head != NULL)
   {
       node* temp = head;
       head = head -> next;
       free(temp);
   }
}
 
void Enqueue(queue *q, int value)
{
   if (q->count < 10)
   {
       node *tmp;
       tmp = malloc(sizeof(node));
       tmp->data = value;
       tmp->next = NULL;
       if(!isempty(q))
       {
           q->rear->next = tmp;
           q->rear = tmp;
 
       }
       else
       {
           q->front = q->rear = tmp;
       }
       q->count++;
   }
   else
   {
       printf("List is full\n");
   }
}
 
int Dequeue(queue *q)
{
   node *tmp;
   int n = q->front->data;
   tmp = q->front;
   q->front = q->front->next;
   q->count--;
   free(tmp);
   return(n);
}
 
int main()
{
   printf("\nDone by Ritika Kayal, 18BCE2518\n");
   int op, val;
   queue *q;
   q = malloc(sizeof(queue));
   make_queue(q);
 
   do {
       printf("\nOperation:\n1. Enqueue\n2. Dequeue\n3. Print\n4. Search\n5. Free\n6. Quit\n\n");
       scanf("%d", &op);
       switch (op) {
           case 1:
               printf("Enter value to enqueue\n");
               scanf("%d", &val);
               pthread_mutex_lock(&lock);
               Enqueue(q, val);
               pthread_mutex_unlock(&lock);
               break;
           case 2:
               pthread_mutex_lock(&lock);
               val = Dequeue(q);
               pthread_mutex_unlock(&lock);
               if (val)
               printf("Dequeued value: %d\n", val);
               else
               printf("Queue is empty\n");
               break;
           case 3:
               printf ("Queue is:\n");
               Print(q->front);
               printf("\n");
           break;
           case 4:
               printf("Enter the value to be searched\n");
               scanf("%d", &val);
               Search(q->front, val);
               break;
           case 5:
               printf("Freeing allocated memory\n");
               pthread_mutex_lock(&lock);
               Free(q->front);
               pthread_mutex_unlock(&lock);
               break;
           case 6:
               printf("Quitting\n\n");
               break;
           default:
               printf("%d isn’t a valid option\n", op);
           }
       } while (op!=6);
   return 0;
}

