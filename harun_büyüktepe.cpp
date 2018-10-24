/*
* Harun Büyüktepe
*150115020
*/
#include<stdio.h>
#include"conio.h"
#include"stdlib.h"
#include<string.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"0
#include"time.h"

// An AVL tree node
struct Node
{
    char key[40];
    struct Node *left;
    struct Node *right;
    int height;
}; 
// A utility function to get maximum of two integers
int max(int a, int b);
double AVLgiveText1( void );
double AVLgiveText2( void );/*Define functions*/
struct Node* AVLdeleteNode(struct Node* root, char key[40]);

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
} 

int max(int a, int b)
{
    return (a > b)? a : b;
} 

    
struct Node* AVLnewNode(char key[40])
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    strncpy(node->key,key,40);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
    
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* AVLinsert(struct Node* node, char key[40])
{
    /* 1.  Perform the normal BST AVLinsertion */
    if (node == NULL)
        return(AVLnewNode(key)); 
    if (strcmp(key,node->key)<0)
        node->left  = AVLinsert(node->left, key);
    else if (strcmp(key,node->key)>0)
        node->right = AVLinsert(node->right, key);
    else // Equal keys are not allowed in BST
        return node; 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right)); 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
    // Left Left Case
    if (balance > 1 && strcmp(key,node->left->key)<0)
        return rightRotate(node); 
    // Right Right Case
    if (balance < -1 && strcmp(key,node->right->key)>0)
        return leftRotate(node); 
    // Left Right Case
    if (balance > 1 && strcmp(key,node->left->key)<0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && strcmp(key,node->right->key)<0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    /* return the (unchanged) node pointer */
    return node;
}
int count=0; 
void preOrder(struct Node *root)
{
    if(root != NULL)
    {
		printf("%s\n ", root->key);count++;
        preOrder(root->left);
        preOrder(root->right);
    }
}
	struct Node *root1 = NULL;
	struct Node *root2 = NULL;
/* Drier program to test above function*/

struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node; 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
struct Node* AVLdeleteNode(struct Node* root, char key[40])
{
    // STEP 1: PERFORM STANDARD BST DELETE 
    if (root == NULL)
        return root; 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (strcmp(key,root->key)<0)
        root->left = AVLdeleteNode(root->left, key); 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if(strcmp(key,root->key)>0)
        root->right = AVLdeleteNode(root->right, key); 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right; 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right); 
            // Copy the inorder successor's data to this node
            //root->key = temp->key;
 			strcpy(root->key,temp->key);
            // Delete the inorder successor
            root->right = AVLdeleteNode(root->right, temp->key);
        }
    } 
    // If the tree had only one node then return
    if (root == NULL)
      return root; 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right)); 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root); 
    // If this node becomes unbalanced, then there are 4 cases 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root); 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    } 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root); 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    } 
    return root;
}
//************		BST	'S INSERTETION	DELETIONN	**********************
struct node* BSTdeleteNode(struct node* root, char key[40]);
struct node
{
    char key[40];
    struct node *left, *right;
};

struct node *BSTnewNode(char key[40])
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    strncpy(temp->key,key,40);
    temp->left = temp->right = NULL;
    return temp;
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s \n", root->key);count++;
        inorder(root->right);
    }
}
struct node* BSTinsert(struct node* node, char key[40])
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return BSTnewNode(key);

    /* Otherwise, recur down the tree */
    if (strcmp(key,node->key)<0)
        node->left  = BSTinsert(node->left, key);
    else if (strcmp(key,node->key)>0)
        node->right = BSTinsert(node->right, key); 
	else return node;	  
 
    /* return the (unchanged) node pointer */
    return node;
}
struct node * minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
struct node* BSTdeleteNode(struct node* root, char key[40])
{
    // base case
    if (root == NULL) return root;

    if (strcmp(key,root->key)<0)
        root->left = BSTdeleteNode(root->left, key);

    else if (strcmp(key,root->key)>0)
        root->right = BSTdeleteNode(root->right, key);

    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);
        // Copy the inorder successor's content to this node
 		strncpy(root->key,temp->key,40);
        // Delete the inorder successor
        root->right = BSTdeleteNode(root->right, temp->key);
    }
    return root;
}
//*********************				BST 				************************
	struct node *root3 = NULL;
	struct node *root4 = NULL;
double BSTgiveText1(void){
	double ResultOfThat=0;
	char words[40];
	FILE *open;
	root3=NULL;
	open=fopen("text1.txt","r");/*Give adress to compiler*/
	ResultOfThat=sizeof(open=fopen("text1.txt","r"))+sizeof(double (ResultOfThat=0))+sizeof(char (words[40]))+sizeof(FILE (*open))+sizeof(root3=NULL);
	while(!feof(open))/*Give word from text*/
	{
		fscanf(open,"%s",words);	
		root3 = BSTinsert(root3, words);
		ResultOfThat+=sizeof(fscanf(open,"%s",words))+sizeof(root3 = BSTinsert(root3, words))+sizeof(struct node);
	}
	fclose(open);
	ResultOfThat+=sizeof(fclose(open));
	return ResultOfThat;
}
double BSTgiveText2(void){
	double ResultOfThat=0;
	FILE *p;
	char words[40];
	root4=NULL;
	p=fopen("text2.txt","r");/*Give adress to compiler*/
	ResultOfThat=sizeof(p=fopen("text2.txt","r"))+sizeof(double (ResultOfThat=0))+sizeof(char (words[40]))+sizeof(FILE (*p))+sizeof(root4=NULL);
	while(!feof(p))/*Give word from text*/
	{
		fscanf(p,"%s",words);	
		root4 = BSTinsert(root4, words);
		ResultOfThat+=sizeof(fscanf(p,"%s",words))+sizeof(root4 = BSTinsert(root4, words))+sizeof(struct node);
	}	
	fclose(p);
	ResultOfThat+=sizeof(fclose(p));
	return ResultOfThat;
}
double BSTdeleteWordText1(void){
	double ResultOfThat=0;
	char words[40];
	FILE *open;
	open=fopen("text1.txt","r");/*Give adress to compiler*/
	int i=0;
	while(i<19&&!feof(open))/*Give word from text*/
	{
		i++;
		fscanf(open,"%s",words);	
		root3 = BSTdeleteNode(root3, words);
		ResultOfThat+=sizeof(struct node);
	}
	fclose(open);
	return ResultOfThat;
}
double BSTdeleteWordText2(void){
	double ResultOfThat=0;
	char words[40];
	FILE *open;
	open=fopen("text2.txt","r");/*Give adress to compiler*/
	int i=0;
	while(i<18&&!feof(open))/*Give word from text*/
	{
		i++;
		fscanf(open,"%s",words);	
		root4 = BSTdeleteNode(root4, words);
		ResultOfThat+=sizeof(struct node);
	}
	fclose(open);
	return ResultOfThat;
}
//********************			AVL			************************************
double AVLgiveText1(void){
	double ResultOfThat=0;
	char words[40];
	FILE *open;
	root1=NULL;
	open=fopen("text1.txt","r");/*Give adress to compiler*/
	ResultOfThat=sizeof(open=fopen("text1.txt","r"))+sizeof(double (ResultOfThat=0))+sizeof(char (words[40]))+sizeof(FILE (*open))+sizeof(root1=NULL);
	while(!feof(open))/*Give word from text*/
	{
		fscanf(open,"%s",words);	
		root1 = AVLinsert(root1, words);
		ResultOfThat+=sizeof(fscanf(open,"%s",words))+sizeof(root1 = AVLinsert(root1, words))+sizeof(struct Node);
	}
	fclose(open);
	ResultOfThat+=sizeof(fclose(open));
	return ResultOfThat;
}
double AVLgiveText2(void){
	double ResultOfThat=0;
	FILE *p;
	char words[40];
	root2=NULL;
	p=fopen("text2.txt","r");/*Give adress to compiler*/
	ResultOfThat=sizeof(p=fopen("text2.txt","r"))+sizeof(double (ResultOfThat=0))+sizeof(char (words[40]))+sizeof(FILE (*p))+sizeof(root2=NULL);
	while(!feof(p))/*Give word from text*/
	{	
		fscanf(p,"%s",words);	
		root2 = AVLinsert(root2, words);
		ResultOfThat+=sizeof(fscanf(p,"%s",words))+sizeof(root2 = AVLinsert(root2, words))+sizeof(struct Node);
	}	
	fclose(p);
	ResultOfThat+=sizeof(fclose(p));
	return ResultOfThat;
}
double AVLdeleteWordText1(void){
	double ResultOfThat=0;
	char words[40];
	FILE *open;
	open=fopen("text1.txt","r");/*Give adress to compiler*/
	int i=0;
	while(i<19&&!feof(open))/*Give word from text*/
	{
		i++;
		fscanf(open,"%s",words);	
		root1 = AVLdeleteNode(root1, words);
		ResultOfThat+=sizeof(struct Node);
	}
	fclose(open);
	return ResultOfThat;
}
double AVLdeleteWordText2(void){
	double ResultOfThat=0;
	char words[40];
	FILE *open;
	open=fopen("text2.txt","r");/*Give adress to compiler*/
	int i=0;
	while(i<18&&!feof(open))/*Give word from text*/
	{
		i++;
		fscanf(open,"%s",words);	
		root2 = AVLdeleteNode(root2, words);
		ResultOfThat+=sizeof(struct Node);
	}
	fclose(open);
	return ResultOfThat;
}
int main()
{
	double total_timeBST1,total_timeBST2,total_timeAVL1,total_timeAVL2;
	double timeBST1,timeBST2,timeAVL1,timeAVL2;
	clock_t startBST1, endBST1,startBST2, endBST2,startAVL1, endAVL1,startAVL2, endAVL2;
	clock_t s_BST1,s_BST2,e_BST1,e_BST2,s_AVL1,s_AVL2,e_AVL1,e_AVL2;
//*********************			text1			********************************	
	printf("Text 1 is reading...\n"
	"BST is created for text 1...\n"
	"!!! DELETED FIRST SENTENCESE !!!\n\n");
	startBST1 = clock();//time count starts 
	int i=0;
	while(i<2000){
		BSTgiveText1();
		BSTdeleteWordText1(); 
		i++;
	}	
	printf("Inorder traversal of the modified tree \n");
	count=0;
	inorder(root3);
	endBST1 = clock();//time count stops 
	total_timeBST1 = ((double) (endBST1 - startBST1)) / CLK_TCK;//calulate total time
	printf("\n\tTree has %d diffrent words.",count);
	
	s_BST1=clock();
	i=0;
	while(i<2000){
		BSTgiveText1();
		i++;
	}	
	e_BST1=clock();
	timeBST1 = ((double) (e_BST1 - s_BST1)) / CLK_TCK;//calulate total time
	
	printf("\n\nText 1 is reading...\n"
	"AVL Tree is created for text 1...\n"
	"!!! DELETED FIRST SENTENCESE !!!\n\n");
	startAVL1 = clock();//time count starts 
	int j=0;
	while(j<2000){
		AVLgiveText1();
		AVLdeleteWordText1(); 
		j++;
	}
	printf("Preorder traversal of the constructed AVL"
	" tree is \n"); 
 	count=0;
	preOrder(root1);
	endAVL1 = clock();//time count stops 
	total_timeAVL1 = ((double) (endAVL1 - startAVL1)) / CLK_TCK;//calulate total time
	printf("\n\tTree has %d diffrent words.",count);
	
	s_AVL1=clock();
	j=0;
	while(j<2000){
		AVLgiveText1(); 
		j++;
	}
	e_AVL1=clock();
	timeAVL1 = ((double) (e_AVL1 - s_AVL1)) / CLK_TCK;//calulate total time
//*******************		text2			***************************	
	printf("\n\nText 2 is reading...\n"
	"BST is created for text 2...\n"
	"!!! DELETED FIRST SENTENCESE !!!\n\n");
	startBST2 = clock();//time count starts 
	int l=0;
	while(l<2000){
		BSTgiveText2();
		BSTdeleteWordText2(); 
		l++;
	}	
	printf("Inorder traversal of the modified tree \n");
	count=0;
	inorder(root4);	
	printf("\n\tTree has %d diffrent words.",count);
	endBST2 = clock();//time count stops 
	total_timeBST2 = ((double) (endBST2 - startBST2)) / CLK_TCK;//calulate total time
	s_BST2=clock();
	l=0;
	while(l<2000){
		BSTgiveText2();
		l++;
	}
	e_BST2=clock();
	timeBST2 = ((double) (e_BST2 - s_BST2)) / CLK_TCK;//calulate total time	
	printf("\n\nText 2 is reading...\n"
	"AVL Tree is created for text 2...\n"
	"!!! DELETED FIRST SENTENCESE !!!\n\n");
	startAVL2 = clock();//time count starts 
	int h=0;
	while(h<2000){
		AVLgiveText2();
		AVLdeleteWordText2(); 
		h++;
	}
	printf("Preorder traversal of the constructed AVL"
	" tree is \n");
	count=0; 
 	preOrder(root2);
	endAVL2 = clock();//time count stops 
	total_timeAVL2 = ((double) (endAVL2 - startAVL2)) / CLK_TCK;//calulate total time
	s_AVL2 = clock();
	h=0;
	while(h<2000){
		AVLgiveText2();
		h++;
	}
	e_AVL2=clock();
	timeAVL2 = ((double) (e_AVL2 - s_AVL2)) / CLK_TCK;//calulate total time
	printf("\n\tTree has %d diffrent words.",count);

	printf("\n\n**************		First BS Tree's Information		------------\n");
	printf("\nMemory usage of giving words to BS tree for text 1 is: 		%lf",BSTgiveText1());	
	printf("\nMemory usage of deleting words from BS tree for text 1 is: 	%lf",BSTgiveText1()-BSTdeleteWordText1());
	printf("\nTime taken insertetion without deletion for text 1 is: 		%f",timeBST1);
	printf("\nTime taken insertetion and deletion for text 1 is: 		%f\n", total_timeBST1); 
	
	printf("\n\n**************		First AVL Tree's Information		------------\n");
	printf("\nMemory usage of giving words to AVL tree for text 1 is: 	%lf",AVLgiveText1());
 	printf("\nMemory usage of deleting words from AVL tree for text 1 is: 	%lf",AVLgiveText1()-AVLdeleteWordText1());
 	printf("\nTime taken insertetion without deletion for text 1 is: 		%f",timeAVL1);
	printf("\nTime taken insertetion and deletion for text 1 is: 		%f\n", total_timeAVL1);
	
	printf("\n\n**************		Second BS Tree's Information		------------\n");
	printf("\nMemory usage of giving words to BS tree for text 2 is: 		%lf",BSTgiveText2()); 
	printf("\nMemory usage of deleting words from BS tree for text 2 is: 	%lf",BSTgiveText2()-BSTdeleteWordText2()); 
	printf("\nTime taken insertetion without deletion for text 2 is: 		%f",timeBST2);
	printf("\nTime taken insertetion and deletion for text 2 is: 		%f\n", total_timeBST2);
	
	printf("\n\n**************		Second AVL Tree's Information		------------\n");
	printf("\nMemory usage of giving words to AVL tree for text 2 is: 	%lf",AVLgiveText2());
	printf("\nMemory usage of deleting words from AVL tree for text 2 is: 	%lf",AVLgiveText2()-AVLdeleteWordText2());
	printf("\nTime taken insertetion without deletion for text 2 is: 		%f",timeAVL2);
	printf("\nTime taken insertetion and deletion for text 2 is: 		%f\n", total_timeAVL2);
		
	printf("\n\nThese execution time measurements give results for 2000 times run the progress.");	
		
		

	return 0;
}

/*printf("\n%d\n",sizeof(struct node));
		
printf("%d",sizeof(struct Node));	*/

