#include "BinarySearchTree.h"
#include <fstream>


//Destruktor
template<typename TName, typename TGenre, typename TYear, typename TRank>
BinarySearchTree<TName, TGenre, TYear, TRank>::~BinarySearchTree() 
{}

//ListAll
template<typename TName, typename TGenre, typename TYear, typename TRank>
void BinarySearchTree<TName, TGenre, TYear, TRank>::ListAll(Node* n)
{
	if (n != NULL) {
		if (n->left != nullptr){ ListAll(n->left); }
		cout << n->name << " " << n->genre << " " << n->year << " " << n->rank << endl;
		ListAll(n->right);
	}
}

//Insert
template<typename TName, typename TGenre, typename TYear, typename TRank>
void BinarySearchTree<TName, TGenre, TYear, TRank>::Insert(TName name, TGenre genre, TYear year, TRank rank) 
{
	Node* nodeToAdd = new Node;
	nodeToAdd->name = name;
	nodeToAdd->genre = genre;
	nodeToAdd->year = year;
	nodeToAdd->rank = rank;

	if (root == NULL)
	{ 
		root = nodeToAdd;
	}
	else 
	{
		AddNode(nodeToAdd, root); 
	}
}


template<typename TName, typename TGenre, typename TYear, typename TRank>
void BinarySearchTree<TName, TGenre, TYear, TRank>::Delete(TName name) 
{
	Node* nodeToDelete = new Node;
	nodeToDelete->name = name;
	DeleteNode(nodeToDelete, root);
}

//Find
template<typename TName, typename TGenre, typename TYear, typename TRank>
bool BinarySearchTree<TName, TGenre, TYear, TRank>::Find(TName name, TGenre genre) 
{
	if (root != nullptr)
	{
		if (root->name == name || root->genre == genre)
		{
			cout << " Same as the root.";
			return true;
		}
		else
			return Search(root, name, genre);
	}
	else
	{
		cout << " No games found. Please add some first!";
		return false;
	}
}

//Load
template<typename TName, typename TGenre, typename TYear, typename TRank>
bool BinarySearchTree<TName, TGenre, TYear, TRank>::Load(){

	ifstream fin("LoadThis.txt");
	TName n;
	TGenre g;
	TYear y;
	TRank r;

	if (fin.fail()) {
		cout << "Cannot open file.\n";
		return false;
	}
	int i = 0;
	if (fin.is_open()) 
	{
		while (!fin.eof()) 
		{
			if      (i % 4 == 0){ fin >> n; 
			}
			else if (i % 4 == 1){ fin >> g;
			}
			else if (i % 4 == 2){ fin >> y; 
			}
			else if (i % 4 == 3)
			{ 
				fin >> r;
				Insert(n, g, y, r);
			}
			i++;
		}
	}
	fin.close();
	return true;
}

//AddNode
template<typename TName, typename TGenre, typename TYear, typename TRank>
void BinarySearchTree<TName, TGenre, TYear, TRank>::AddNode(Node* nodeToAdd, Node* currentParent) 
{
	if (nodeToAdd->name < currentParent->name)
	{
		if (currentParent->left == NULL)
			currentParent->left = nodeToAdd;
		else
			AddNode(nodeToAdd, currentParent->left);
	}
	else 
	{
		if (currentParent->right == NULL)
			currentParent->right = nodeToAdd;
		else
			AddNode(nodeToAdd, currentParent->right);
	}
}

//DeleteNode
template<typename TName, typename TGenre, typename TYear, typename TRank>
void BinarySearchTree<TName, TGenre, TYear, TRank>::DeleteNode(Node* nodeToDelete, Node* currentParent)
{
	if (currentParent != nullptr)
	{
		//if in left subtree
		if (nodeToDelete->name < currentParent->name)
		{ 
			if (currentParent->left != nullptr)
			{ 
				if (nodeToDelete->name == currentParent->left->name)
				{
					Node* x = currentParent->left;           
					currentParent->left = nullptr;           
					if (x->left != nullptr)                  
						AddNode(x->left, currentParent);     
					
					if (x->right != nullptr)                 
						AddNode(x->right, currentParent);   
					
					cout << " Deleted " << nodeToDelete->name << "." << endl;
					return;
				}
				DeleteNode(nodeToDelete, currentParent->left); 
			}
			else
			{ 
				cout << " Didn't find what was meant to be deleted." << endl;
			}
		}
		//if in right subtree
		else if (nodeToDelete->name > currentParent->name)
		{ 
			if (currentParent->right != nullptr)
			{ 
				if (nodeToDelete->name == currentParent->right->name)
				{	
					Node* x = currentParent->right;
					currentParent->right = nullptr;
					if (x->left != nullptr)
						AddNode(x->left, currentParent);

					if (x->right != nullptr)
						AddNode(x->right, currentParent);
					
					cout << " Deleted " << nodeToDelete->name << "." << endl;
					return;
				}
				DeleteNode(nodeToDelete, currentParent->right);
			}
			else
			{
				cout << " Didn't find what was meant to be deleted." << endl;
			}
		}
		else{
			
			if (currentParent->left == nullptr && currentParent->right == nullptr)
			{
				delete currentParent;
				currentParent = nullptr;
				root = nullptr;
				cout << " Deleted leaf with no children.";
			}
			
			else if (currentParent->left == nullptr)
			{
				Node *temp = currentParent;
				currentParent = currentParent->right;
				delete temp;
				cout << "Deleted node with one child on the right side." << endl;
			}
			
			else if (currentParent->right == nullptr)
			{
				Node *temp = currentParent;
				currentParent = currentParent->left;
				delete temp;
				cout << "Deleted node with one child on the left side." << endl;
			}
			
			else 
			{
				Node* temp = root;
				while (temp->left != nullptr)
				{
					temp = temp->left; 
				} 
				currentParent->name = temp->name;
				DeleteNode(nodeToDelete, currentParent->right);
			}
		}
	}
	else
	{
		cout << " There are no entries to delete." << endl; 
	}
}

//Save
template<typename TName, typename TGenre, typename TYear, typename TRank>
bool BinarySearchTree<TName, TGenre, TYear, TRank>::Save(Node* n) {
	ofstream fout("SearchTree", ios::app);

	if (!fout) {
		cout << "Cannot open output file.\n";

		return false;
	}

	if (n != nullptr){ 
		fout << n->name << endl << n->genre << endl << n->year << endl << n->rank << endl;
		cout << "\n Saved!";
	}
	else { cout << "\n There is nothing to save!"; }
	fout.close();

	return true;
}

//InOrder
template<typename TName, typename TGenre, typename TYear, typename TRank>
void BinarySearchTree<TName, TGenre, TYear, TRank>::InOrder(Node n) {
	if (n != NULL) {
		InOrder(n.left);
		cout << n.name << n.genre << n.year << n.rank << endl;
		InOrder(n.right);
	}
}

//Search
template<typename TName, typename TGenre, typename TYear, typename TRank>
bool BinarySearchTree<TName, TGenre, TYear, TRank>::Search(Node* currentParent, TName name, TGenre genre) {
	if (currentParent->name == name || currentParent->genre == genre){
		cout << " Found it!" << endl;
		return true;
	}
	else if (currentParent->left == nullptr && currentParent->right == nullptr){
		cout << " Did not find it." << endl;
		return false;
	}
	else if ((currentParent->left != nullptr) && (currentParent->left->name == name || currentParent->left->genre == genre))
			return Search(currentParent->left, name, genre);

	else if ((currentParent->right != nullptr) && (currentParent->right->name == name || currentParent->right->genre == genre))
			return Search(currentParent->right, name, genre);
	
	else if ((name < currentParent->name && name != "")||(genre < currentParent->genre && genre != ""))
		return Search(currentParent->left, name, genre);
	
	else if ((name > currentParent->name && name != "")||(genre > currentParent->genre && genre != ""))
		return Search(currentParent->right, name, genre);

	else {
		cout << " I dunno? It was not found.";
		return false;
	}
}

template<typename TName, typename TGenre, typename TYear, typename TRank>
void BinarySearchTree<TName, TGenre, TYear, TRank>::FindMin(Node* root){
	if (root == nullptr){
		cout << "Error: Tree is empty" << endl;
	}
	while (root->left != nullptr) { root = root->left; }
	return root->name;
}

template<typename TName, typename TGenre, typename TYear, typename TRank>
void BinarySearchTree<TName, TGenre, TYear, TRank>::FindMax(Node* root){
	if (root == nullptr){
		cout << "Error: Tree is empty" << endl;
	}
	while (root->right != nullptr){ root = root->right; }
	return root->name;
}