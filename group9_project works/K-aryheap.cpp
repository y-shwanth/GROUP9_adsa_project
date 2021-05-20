#include<bits/stdc++.h>
using namespace std;

void restoredown(int arr[], int len, int pos,int k)
{

	int child[k+1];

	while (1)
	{
	for (int i=1; i<=k; i++)
	{
	if((k*pos + i) < len)
	child[i]=(k*pos + i);
	else
	child[i]=-1;}

	int min_child = INT_MAX, min_child_pos ;

	for (int i=1; i<=k; i++)
	{
	if (child[i] != -1 &&arr[child[i]] < min_child)
	{
	min_child_pos = child[i];
	min_child = arr[child[i]];
	}
	}

	if (min_child == INT_MAX)
	break;
	
	if (arr[pos] > arr[min_child_pos])
	swap(arr[pos], arr[min_child_pos]);

	pos = min_child_pos;
	}
}


void restoreup(int arr[], int pos, int k)
{
	int parent = (pos-1)/k;

	while (parent>=0)
	{
	if (arr[pos] < arr[parent])
	{
	swap(arr[pos], arr[parent]);
	pos = parent;
	parent = (pos -1)/k;
	}
	else
	break;
	}
}

void formheap(int arr[], int n, int k)
{
	for (int i= (n-1)/k; i>=0; i--)
	restoredown(arr, n, i, k);
}


void insert(int arr[], int* n, int k, int key)
{
	arr[*n] = key;
	*n = *n+1;
	restoreup(arr, *n-1, k);
}


int extractmin(int arr[], int* n, int k)
{
	int max = arr[0];
	arr[0] = arr[*n-1];
	*n = *n-1;

	restoredown(arr, *n, 0, k);

	return max;
}


int findmin(int arr[], int n)
{return arr[0];}


int search(int arr[], int n, int k)
{
    for (int i=0; i<n; i++)
    if(arr[i] == k)
    return i; 
    
    return -1;
}


int deletion(int arr[], int* n, int k)
{
    int pos = search(arr, *n ,k);
    if(pos == -1)
    return -1;
    
    swap(arr[0] , arr[pos]);
    int ans = extractmin(arr, n ,k);
    return ans;
}

int main()
{
	const int size = 100;
	int arr[size] = {2, 3, 4, 6, 8, 9, 10};
	int n = 7;
	int k = 3;

	formheap(arr, n, k);

	cout<<"The Heap is : \n";
	for (int i=0; i<n; i++)
	cout << arr[i] <<" ";

	int key = 12;
	insert(arr, &n, k, key);

	cout << "\n\nHeap after insertion of "<< key <<"\n";
	
	for (int i=0; i<n; i++)
	cout << arr[i] <<" ";
	
	key = 12;
	cout << "\n\nDelete "<< key << " in the heap\n";
	int ans = deletion(arr, &n , key);
	cout << "\nDeleted value is "<< ans;

	cout << "\n\nHeap after deletion: \n";
	for (int i=0; i<n; i++)
	cout << arr[i] <<" ";
	
	cout << "\n\nFind minimum ";
	cout << "\n\nThe minimum value of heap is "<< findmin(arr, n) <<"\n";
	
	ans = extractmin(arr, &n, k);
	cout << "\nExtracted min is "<< ans;

	cout << "\n\nHeap after extract min: \n";
	for (int i=0; i<n; i++)
	cout << arr[i] <<" ";
	
	key = 10;
	cout << "\n\nSearch "<< key << " in the heap\n";
	int find = search(arr, n , key);
	if(find == -1)
	cout << key << " is not in the heap";
	else
	cout << key << " is present in the heap";
	
	return 0;
}

