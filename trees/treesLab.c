#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    char* data;
    struct Node *left;
    struct Node *right;
}Node;
Node* newNode(char*x)
{
    Node* n= malloc(sizeof(Node));
    n->data= malloc(strlen(x)+1);
    strcpy(n->data,x);
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* insert(Node* root,char* x)
{
    if (!root)
        return(newNode(x));
    if (strcasecmp(root->data,x)>0)
     root->left= insert (root->left,x);
    else if (strcasecmp(root->data,x)<0)
      root->right= insert (root->right,x);
      return root;
}
void calculate(Node* root,int* x)
{
    if (root)
   {
    *x=*x+1;
    calculate (root->left,x);
    calculate (root->right,x);
   }
}
int no_of_nodes(Node* root)
{
    int *x;
    *x=0;
    calculate(root,x);
    return *x;
}
int maxHeight(Node* root)
{
    if (root==NULL)
        return -1;

       int l=maxHeight(root->left);
       int r=maxHeight(root->right);
        if (l>r)
            return(l+1);
        else
            return (r+1);
}
void inorder(Node* root)
{
   if (root)
   {
    inorder (root->left);
    printf("%s\n",root->data);
    inorder (root->right);
   }
}
void preorder(Node* root)
{
   if (root)
   {
    printf("%s",root->data);
    preorder (root->left);
    preorder (root->right);
   }
}
Node* min(Node* root)
{
    if (!(root->left))
        return (root);
    else min(root->left);
}
Node* max(Node* root)
{
    if (!(root->right))
        return (root);
    else max(root->right);
}
int search(Node* n,char key[50])
{
    if (n == NULL)
        return 0;
    if (strcasecmp(n->data,key) == 0)
        return 1;
    else if (strcasecmp(n->data,key)>0)
      {
        return search(n->left,key);
      }
    else if (strcasecmp(n->data,key)<0)
         {
             return search(n->right,key);
         }
    return (0);
}
Node* searchN(Node* root,char* key)
{
    Node*n=root;
    if (strcasecmp(n->data,key)==0)
        return n;
    else if (strcasecmp(n->data,key)>0&&n->left)
      {
       n=n->left;
       return searchN(n,key);
      }
    else if (strcasecmp(n->data,key)<0&&n->right)
        {
            n=n->right;
            return searchN(n,key);
        }
        return n;
}
char* end_of_searche(Node* root,char* key)
{
    Node* n=root;
    n=searchN(n,key);
    return (n->data);
}
char* successor(Node* root,char* key)
{
    Node* n=root;
    Node* suc=NULL;

    while (n&&strcasecmp(n->data,key))
    {
        if (strcasecmp(n->data,key)>0)
            {
                suc=n;
                n=n->left;
            }
            else n=n->right;
    }
    if (!n)
        return(NULL);
    if (n&&n->right)
        suc=min(n->right);
    return (suc->data);
}
char* pre_desuccessor(Node* root,char* key)
{
    Node* n=root;
    Node* desuc=NULL;

    while (n&&strcasecmp(n->data,key))
    {
        if (strcasecmp(n->data,key)<0)
            {
                desuc=n;
                n=n->right;
            }
            else n=n->left;
    }
    if (!n)
        return(NULL);
    if (n&&n->left)
        desuc=max(n->left);
    return (desuc->data);
}
Node* readFromFile(Node* n)
{
    FILE *f=fopen("EN-US-Dictionary.txt","r");
    char str[50];
    int c=1;
    fgets(str,50,f);

    n=insert(n,str);
    while(!feof(f))
    {
        fgets(str,50,f);
        str[strcspn(str,"\n")]='\0';
        n=insert(n,str);
        c++;
    }
    fclose(f);
    printf("Dictionary Loaded Successfully...!\n");
    printf("..................................\n");
    printf("Size = %d\n",c);
    printf("..................................\n");
    printf("Height = %d\n",maxHeight(n));
    printf("..................................\n");
    return n ;
}
char* print(Node* root)
{
    return(root->data);

}



int main()
{
   char s[100];
   Node* root=NULL;
   Node* n=NULL;
   root=readFromFile(n);
   printf("Enter Sentence :\n");
   gets(s);
   char* token=strtok(s," ");
    while(token!=NULL)
    {
       if (search(root,token))
       printf("%s - Correct\n",token);
       else {
               n=searchN(root,token);
               printf("%s - Incorrect, Suggestions : %s %s %s\n",token,print(n),successor(root,print(n)),pre_desuccessor(root,print(n)));
            }
       token=strtok(NULL," ");
    }
    return 0;
    }

