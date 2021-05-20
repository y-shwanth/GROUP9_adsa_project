#include <bits/stdc++.h>
using namespace std;

struct node
{
	int key, priority;
	node *left, *right;
};


node *rightrotate(node *y)
{
	node *x = y->left;
	node *temp = x->right;

	x->right = y;
	y->left = temp;

	return x;
}


node *leftrotate(node *x)
{
	node *y = x->right;
	node *temp = y->left;

	y->left = x;
	x->right = temp;

	return y;
}


node* newnode(int key)
{
	node* temp = new node;
	temp->key = key;
	temp->priority = rand()%100;
	temp->left = temp->right = NULL;
	return temp;
}


void inorder(node* root)
{
	if (root!=NULL)
	{
	inorder(root->left);
	cout << "key: "<< root->key << "\t\tpriority: "<< root->priority;
	if (root->left)
	cout << "\t\tleft child: " << root->left->key;
	if (root->right)
	cout << "\t\tright child: " << root->right->key;
	cout << endl;
	inorder(root->right);
	}
}

node* insert(node* root, int key)
{
	
	if (root==NULL)
	return newnode(key);

	if (key <= root->key)
	{
	root->left = insert(root->left, key);

	if (root->left->priority > root->priority)
	root = rightrotate(root);
	}
	
	
	else 
	{
	root->right = insert(root->right, key);
	
	if (root->right->priority > root->priority)
	root = leftrotate(root);
	}
	return root;
}

node* deletenode(node* root, int key)
{
	if (root == NULL)
	return root;

	if (key < root->key)
	root->left = deletenode(root->left, key);

	else if (key > root->key)
	root->right = deletenode(root->right, key);

	else if (root->left == NULL)
	{
	node *temp = root->right;
	delete(root);
	root = temp; 
	}

	else if (root->right == NULL)
	{
	node *temp = root->left;
	delete(root);
	root = temp; 
	}

	else if (root->left->priority < root->right->priority)
	{
	root = leftrotate(root);
	root->left = deletenode(root->left, key);
	}
	
	else
	{
	root = rightrotate(root);
	root->right = deletenode(root->right, key);
	}

	return root;
}


node* search(node* root, int key)
{
	if (root == NULL || root->key == key)
	return root;

	if (root->key < key)
	return search(root->right, key);

	return search(root->left, key);
}


void find_min(node* root)
{
   while(root->left!=NULL)
   root=root->left;
   
   cout<<"The minimum value is "<<root->key<<endl;
   cout<<endl;
}


node* extractmin(node* root)
{
    node *p,*parent;
    p=root;
    while(p->left!=NULL)
    {parent=p;p = p->left;}
    cout << "Extracted min is " << p->key<<endl;
    if(p->right==NULL)
    {delete(p);parent->left=NULL;}
    else
    {
    	parent->left=p->right;
    	p->left=NULL;
    	delete(p);
    }
    return root;
}


int main()
{
	srand(time(NULL));

	struct node *root = NULL;
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 4);
	root = insert(root, 6);
	root = insert(root, 8);
	root = insert(root, 9);
	root = insert(root, 10);
	root = insert(root, 12);

	cout << "Inorder traversal of the given tree \n";
	inorder(root);

	
	cout << "\nDelete 12\n";
	root = deletenode(root, 12);
	cout << "Inorder traversal of the tree after deletion\n";
	inorder(root);

	
	cout << "\nFind minimum in the heap\n";
	find_min(root);
		
	
	cout << "Extract min\n";
	root = extractmin(root);
	cout << "Inorder traversal of the tree after extract min \n";
	inorder(root);
	
	cout << "\nSearch 10\n";
	node* find=search(root,10);
	if(find==NULL)
	cout<<"10 is not present in the heap";
	else
	cout<<"10 is found in the heap";
	return 0;
}
