#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

struct node{
int value;
struct node*left;
struct node*right;
};

struct node *newNode(int value){
struct node *node=(struct node*)malloc(sizeof(struct node));
node->value=value;
node->left=NULL;
node->right=NULL;
return(node);
}

void Postorder(struct node* node){
int left=0;
int right=0;
if(node==NULL)
return;
#pragma omp taskshared(left)
Postorder(node->left);
#pragma omp taskshared(right)
Postorder (node->right);
#pragma omp taskwait
printf("%d",node->value);
}

int main(){
struct node*root=newNode(10);
root->left=newNode(12);
root->right=newNode(14);
root->left->left=newNode(16);
root->left->right=newNode(18);
double time;
printf("\nName: Ritika Kayal\nRegistration number: 18BCE2518");
time= omp_get_wtime();
printf("\nPostorder traversal: \n");
Postorder(root);
time=omp_get_wtime()-time;
printf("\nThe time taken is: %g\n\n",time);
return 0;
}
