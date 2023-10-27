#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include <iomanip>
#include "Node.h"

class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();
	const BinarySearchTree& operator=(const BinarySearchTree& otherTree);
	BinarySearchTree(const BinarySearchTree& otherTree);
	
	// Wrapper functions
	bool isEmpty() const;
	void inOrderTraversal() const;
	int treeNodeCount() const;
	void destroyTree();

	bool search(const std::string& searchItem) const;
	void insert(const std::string& insertItem);
	void deleteFromTree(Node*& p);
	void deleteNode(const std::string& deleteItem);

protected:
	Node* root;

private:
	void copyTree(Node*& copiedTreeRoot, Node* otherTreeRoot);
	void destroy(Node*& p);
	void inorder(Node* p) const;
	int nodeCount(Node* p) const;
};

#endif
