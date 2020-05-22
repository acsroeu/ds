#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "string.h"

using namespace std;
struct Employee
{
	char* profession;
	float salary;
};
struct BST
{
	Employee* info;
	int balanceFactor;
	BST* left;
	BST* right;
};

Employee* createElement(const char*, float);
BST* createNode(Employee*);
void insertNode(BST**, BST*); //root //node
void preOrder(BST*);
void postOrder(BST*);
void inOrder(BST*);
void afisareStructura(BST*, int);
void afisareFrunze(BST*);
float sumaArbore(BST*);
void main()
{
	FILE* pFile = fopen("Date.txt", "r");
	BST* root = NULL;
	if (pFile)
	{
		char buffer[100]; float salary;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile))
		{
			fscanf(pFile, "%f", &salary);
			//1. create an element of type List*
			Employee* newElement = createElement(buffer, salary);
			//2. insert the newly created element
			BST* node = createNode(newElement);
			//3. inseert the node in the AVL tree
			insertNode(&root, node);
			fscanf(pFile, "%s", buffer);
		}
		fclose(pFile);
	}
	printf("=============Preordine=============\n");
	preOrder(root);
	
	printf("=========AfisareStructura==========\n");
	afisareStructura(root, 0);
	
	//deleteNode(root, 8977);
	Employee* item = createElement("Scafandru", 2200);
	BST* node = createNode(item);
	insertNode(&root, node);

	printf("=========AfisareStructura==========\n");
	afisareStructura(root, 0);

//	printf("=========AfisareParintiFrunze==========\n");
//	afisareFrunze(root);
//	printf("Suma elemente: %f\n",sumaArbore(root));

}

void searchAndDelete(BST** root, BST*& left)
{
	if (left->right != NULL)
	{
		searchAndDelete(&(*root), left->right);
	}
	else
	{
		Employee* tmpInfo = (*root)->info;
		(*root)->info = left->info;
		BST* tmpNode = left;
		left = left->left;
		free(tmpInfo->profession);
		free(tmpInfo);
		free(tmpNode);
	}
}

void deleteNode(BST*& root, float key) //O(log)
{
	if (root)
	{
		if (root->info->salary == key)
		{
			//stergere cu cele 3 cazuri
			if (root->left == NULL && root->right == NULL)//stergere frunza
			{
				BST* tmp = root;
				root = NULL;
				free(tmp->info->profession);
				free(tmp->info);
				free(tmp);
			}
			else
			{
				if (root->left != NULL && root->right == NULL)
				{
					BST* tmp = root;
					root = root->left;
					free(tmp->info->profession);
					free(tmp->info);
					free(tmp);
				}
				else
				{
					if (root->left == NULL && root->right != NULL)
					{
						BST* tmp = root;
						root = root->right;
						free(tmp->info->profession);
						free(tmp->info);
						free(tmp);
					}
					else
					{
						searchAndDelete(&root,root->left);
					}
				}
			}
		}
		else
		{
			if (root->info->salary > key)
				deleteNode(root->left, key);
			else
				deleteNode(root->right, key);
		}
	}
}
float sumaArbore(BST* root)
{
	if (root)
	{
		if (root->left && root->left->left == NULL && root->left->right == NULL
			|| root->right && root->right->left == NULL && root->right->right == NULL)
			return root->info->salary + sumaArbore(root->left) + sumaArbore(root->right);
		else
			return sumaArbore(root->left) + sumaArbore(root->right);
	}
	else
		return 0;
}
void afisareFrunze(BST* root)
{
	if (root)
	{
		//afisarea parinti frunze
		if(root->left && root->left->left == NULL && root->left->right == NULL
			||root->right && root->right->left == NULL && root->right->right == NULL)
			printf("%f\n", root->info->salary);
		afisareFrunze(root->left);
		afisareFrunze(root->right);
	}
}


void afisareStructura(BST* root, int level)
{
	if (root)
	{
		for (int i = 0; i < level; i++)
			printf("\t");
		printf("%f\n", root->info->salary);
		afisareStructura(root->left, level + 1);
		afisareStructura(root->right, level + 1);
	}
	else
	{
		for (int i = 0; i < level; i++)
			printf("\t");
		printf("NULL\n");
	}
}

void inOrder(BST* root)
{
	if (root)
	{
		inOrder(root->left);
		printf("Salary: %f\n", root->info->salary);
		inOrder(root->right);
	}
}
void preOrder(BST* root)
{
	if (root)
	{
		printf("Salary: %f\n", root->info->salary);
		preOrder(root->left);
		preOrder(root->right);
	}
}
void postOrder(BST* root)
{
	if (root)
	{
		postOrder(root->left);
		postOrder(root->right);
		printf("Salary: %f\n", root->info->salary);
	}
}
int max(int a, int b)
{
	return a > b ? a : b;
}
int getHeight(BST* node)
{
	if (node != NULL)
		return 1 + max(getHeight(node->left), getHeight(node->right));
	else
		return 0;
}
int getBalanceFactor(BST* pivot)
{
	int hSLeft = 0, hSRight = 0;
	if (pivot->left)
		hSLeft = getHeight(pivot->left);
	if (pivot->right)
		hSRight = getHeight(pivot->right);
	return hSRight - hSLeft;
}

BST* rightRotation(BST* pivot)
{
	BST* desc = pivot->left;
	pivot->left = desc->right;
	desc->right = pivot;
	return desc;
}

BST* leftRotation(BST* pivot)
{
	BST* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;
	return desc;
}

BST* rebalance(BST* pivot)
{
	pivot->balanceFactor = getBalanceFactor(pivot);
	if (pivot->balanceFactor == -2)
	{
		BST* desc = pivot->left;
		if (desc->balanceFactor == 1)
		{
			//rotire la stanga in desc
			pivot->left = leftRotation(desc);
		}
		//rotire la dreapta in pivot
		pivot = rightRotation(pivot);
	}
	else if (pivot->balanceFactor == 2)
	{
		BST* desc = pivot->right;
		if (desc->balanceFactor == -1)
		{
			//rotire la dreapta in desc
			pivot->right = rightRotation(desc);
		}
		//rotire la stanga in pivot
		pivot = leftRotation(pivot);
	}
	return pivot;
}
void insertNode(BST** root, BST* node)
{
	if (*root == NULL)
		*root = node;
	else
	{
		if ((*root)->info->salary > node->info->salary)
			insertNode(&(*root)->left, node);
		else if ((*root)->info->salary < node->info->salary)
			insertNode(&(*root)->right, node);
		else
			printf("Cheie existenta");
	}
	(*root) = rebalance(*root);
}

BST* createNode(Employee* item)
{
	BST* node = (BST*)malloc(sizeof(BST));
	node->info = createElement(item->profession, item->salary);
	node->left = node->right = NULL;
	node->balanceFactor = 0;
	return node;
}

Employee* createElement(const char* buffer, float salary)
{
	//1.allocate memory for the new element
	Employee* newElement = (Employee*)malloc(sizeof(Employee));
	//2.initialize it with the params 
	//(the connection attributes should remain NULL)
	newElement->salary = salary;
	newElement->profession = (char*)malloc(strlen(buffer) + 1);
	strcpy(newElement->profession, buffer);
	//3.return the new element
	return newElement;
}