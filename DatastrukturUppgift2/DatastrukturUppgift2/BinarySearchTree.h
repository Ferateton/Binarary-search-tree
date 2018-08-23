#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

template<typename TName, typename TGenre, typename TYear, typename TRank>
class BinarySearchTree {
private:
	struct Node {
		Node() {
			left = NULL;
			right = NULL;
		}
		Node* left;
		Node* right;
		TName name;   
		TGenre genre; 
		TYear year;   
		TRank rank;

		void Save();
	};
	Node* root;

public:
	BinarySearchTree() { root = NULL; }
	~BinarySearchTree();
	void ListAll(Node*);//In-order
	void Insert(TName, TGenre, TYear, TRank);
	void Delete(TName);
	bool Find(TName, TGenre);
	bool IsEmpty()const { return root == NULL; }
	void Print(){ ListAll(root); }
	void Save(){ Save(root); } //pre-order
	bool Load();
	void FindMin(Node*);
	void FindMax(Node*);

private:
	void AddNode(Node*, Node*);
	bool Save(Node*);
	void InOrder(Node);
	void DeleteNode(Node*, Node*);
	bool Search(Node*, TName, TGenre);
};