#include <cmath>
#include <cstdlib>
#include <iostream>
#include <malloc.h>
using namespace std;


struct node {
	node* parent; 
	node* child; 
	node* left; 
	node* right;
	int key; 
	int degree; 
	char mark; 
	char flag; 
};

struct node* minimum = NULL;
int nodecount = 0;
int found ;

void insertion(int val)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->key = val;
	new_node->degree = 0;
	new_node->mark = 'W';
	new_node->flag = 'N';
	new_node->parent = NULL;
	new_node->child = NULL;
	new_node->left = new_node;
	new_node->right = new_node;
	
	if (minimum != NULL)
	{
	(minimum->left)->right = new_node;
	new_node->right = minimum;
	new_node->left = minimum->left;
	minimum->left = new_node;
	
	if (new_node->key < minimum->key)
	minimum = new_node;
	}
	
	else 
	{minimum = new_node;}
	nodecount++;
}


void link(struct node* ptr2, struct node* ptr1)
{
	(ptr2->left)->right = ptr2->right;
	(ptr2->right)->left = ptr2->left;
	
	if (ptr1->right == ptr1)
	minimum = ptr1;
	
	ptr2->left = ptr2;
	ptr2->right = ptr2;
	ptr2->parent = ptr1;
	
	if (ptr1->child == NULL)
	ptr1->child = ptr2;
	ptr2->right = ptr1->child;
	ptr2->left = (ptr1->child)->left;
	((ptr1->child)->left)->right = ptr2;
	(ptr1->child)->left = ptr2;
	if (ptr2->key < (ptr1->child)->key)
		ptr1->child = ptr2;
	ptr1->degree++;
}

void restructure()
{
	int temp1;
	float temp2 = (log(nodecount)) / (log(2));
	int temp3 = temp2;
	
	struct node* arr[temp3];
	for (int i = 0; i <= temp3; i++)
	arr[i] = NULL;
	node* ptr1 = minimum;
	node* ptr2;
	node* ptr3;
	node* ptr4 = ptr1;
	do 
	{
	ptr4 = ptr4->right;
	temp1 = ptr1->degree;
	while (arr[temp1] != NULL) 
	{
	ptr2 = arr[temp1];
	if (ptr1->key > ptr2->key)
	{
	ptr3 = ptr1;
	ptr1 = ptr2;
	ptr2 = ptr3;
	}
	if (ptr2 == minimum)
	minimum = ptr1;
	
	link(ptr2, ptr1);
	
	if (ptr1->right == ptr1)
	minimum = ptr1;
	
	arr[temp1] = NULL;
	temp1++;
	}
	arr[temp1] = ptr1;
	ptr1 = ptr1->right;
	} while (ptr1 != minimum);
	
	minimum = NULL;
	for (int j = 0; j <= temp3; j++)
	{
	if (arr[j] != NULL) {
	arr[j]->left = arr[j];
	arr[j]->right = arr[j];
	
	if (minimum != NULL)
	{
	(minimum->left)->right = arr[j];
	arr[j]->right = minimum;
	arr[j]->left = minimum->left;
	minimum->left = arr[j];
	if (arr[j]->key < minimum->key)
	minimum = arr[j];
	}
	else 
	{minimum = arr[j];}
	
	if (minimum == NULL)
	minimum = arr[j];
	
	else if (arr[j]->key < minimum->key)
	minimum = arr[j];
	}
	}
}


void extract_min()
{
	if (minimum == NULL)
	cout << "The heap is empty" << endl;
	
	else 
	{
	node* temp = minimum;
	node* ptr;
	ptr = temp;
	node* x = NULL;
	if (temp->child != NULL) 
	{
	x = temp->child;
	do
	{
	ptr = x->right;
	(minimum->left)->right = x;
	x->right = minimum;
	x->left = minimum->left;
	minimum->left = x;
	
	if (x->key < minimum->key)
	minimum = x;
	
	x->parent = NULL;
	x = ptr;
	} while (ptr != temp->child);
	}

	(temp->left)->right = temp->right;
	(temp->right)->left = temp->left;
	minimum = temp->right;
	if (temp == temp->right && temp->child == NULL)
	minimum = NULL;
	else 
	{
	minimum = temp->right;
	restructure();
	}
	nodecount--;
	}
}


void cut(struct node* found, struct node* temp)
{
	if (found == found->right)
	temp->child = NULL;

	(found->left)->right = found->right;
	(found->right)->left = found->left;
	if (found == temp->child)
		temp->child = found->right;

	temp->degree = temp->degree - 1;
	found->right = found;
	found->left = found;
	(minimum->left)->right = found;
	found->right = minimum;
	found->left = minimum->left;
	minimum->left = found;
	found->parent = NULL;
	found->mark = 'B';
}


void cut_rearrrange(struct node* temp)
{
	node* ptr = temp->parent;
	if (ptr != NULL) 
	{
	if (temp->mark == 'W')
	{temp->mark = 'B';}
	else 
	{
	cut(temp, ptr);
	cut_rearrrange(ptr);
	}
	}
}


void decrease_key(struct node* found, int val)
{
	if (minimum == NULL)
	cout << "The Heap is Empty" << endl;

	if (found == NULL)
	cout << "Node not found in the Heap" << endl;

	found->key = val;

	struct node* temp = found->parent;
	if (temp != NULL && found->key < temp->key) {
	cut(found, temp);
	cut_rearrrange(temp);
	}
	if (found->key < minimum->key)
	minimum = found;
}


void revalue(struct node* minimum, int old_val, int val)
{
	struct node* found = NULL;
	node* temp = minimum;
	temp->flag = 'Y';
	node* ptr = NULL;
	if (temp->key == old_val) {
		ptr = temp;
		temp->flag = 'N';
		found = ptr;
		decrease_key(found, val);
	}
	if (ptr == NULL) {
		if (temp->child != NULL)
			revalue(temp->child, old_val, val);
		if ((temp->right)->flag != 'Y')
			revalue(temp->right, old_val, val);
	}
	temp->flag = 'N';
	found = ptr;
}


int search(struct node* minimum, int old_val)
{
	node* temp = minimum;
	temp->flag = 'Y';
	node* ptr = NULL;
	
	if (temp->key == old_val) {
	ptr = temp;
	temp->flag = 'N';
	found = 1;
	}
	
	if (ptr == NULL) {
	if (temp->child != NULL)
	search(temp->child, old_val);
	
	if ((temp->right)->flag != 'Y')
	search(temp->right, old_val);
	}
	
	temp->flag = 'N';

}



void deletion(int val)
{
	if (minimum == NULL)
	cout << "The heap is empty" << endl;
	
	else {
	revalue(minimum, val, 0);
	extract_min();
	cout << "Key Deleted" << endl;
}
}


void display()
{
	node* ptr = minimum;
	if (ptr == NULL)
	cout << "The Heap is Empty" << endl;

	else {
	cout << "The root nodes of Heap are: " << endl;
	do
	{
	cout << ptr->key;
	ptr = ptr->right;
	if (ptr != minimum) {
	cout << "-->";
	}
	} while (ptr != minimum && ptr->right != NULL);
	cout << endl;
	cout<<"The number of nodes in heap are "<<nodecount<<endl;
	}
}


void search_min()
{
    cout << "The minimum of heap is: " << minimum->key << endl;
}
 


int main()
{
	
	cout << "\nCreating an initial heap" << endl;
	insertion(2);
	insertion(3);
	insertion(4);
	insertion(6);
	insertion(8);
	insertion(9);
	insertion(10);
	insertion(12);
	

	display();
	
	cout << "\nDelete the node 12" << endl;
	deletion(12);
	display();
	
	cout << "\nFind the minimum" << endl;
	search_min();
	
	cout << "\nExtracting min" << endl;
	extract_min();
	display();
	
	cout << "\nSearch 10\n";
	found = 0;
	search(minimum,10);
	if(found == 1)
	cout << "Element found\n";
	else
	cout << "Element not found\n";
	
}

