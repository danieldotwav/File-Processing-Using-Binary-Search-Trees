#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include <iomanip>
#include <sstream>
#include "Node.h"
#include "Constants.h"

class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();
	const BinarySearchTree& operator=(const BinarySearchTree& otherTree);
	BinarySearchTree(const BinarySearchTree& otherTree);

	// Postcondition: Returns true if the binary tree is empty, otherwise returns false
	bool isEmpty() const;

	// Postcondition: Nodes are printed in inorder sequence
	void printInorder() const;

	// Postcondition:
	int treeNodeCount() const;

	// Postcondition: Memory occupied by each node is deallocated
	void destroyTree();

	// Postcondition: If no node exists for the string passed in as a parameter, a new node is created for the word, otherwise the count for the existing node is incremented by 1
	void insert(const std::string& insertItem);

	// Postcondition: 
	void findWordsContaining(const std::string searchItem) const;

	// Postcondition:
	void deleteFromTree(Node*& p);

	// Postcondition:
	void deleteNode(const std::string& deleteItem);

protected:
	Node* root;

private:
	// Postcondition: Creates a copy of the binary tree and points the otherTreeRoot pointer to the root of the copied tree
	void copyTree(Node*& copiedTreeRoot, Node* otherTreeRoot);

	// Postcondition: Destroys the binary tree to which p points by traversing the tree until every node's memory is deallocated
	void destroy(Node*& p);

	// Postcondition: Performs inorder traversal of the tree and prints each word / word count
	void inorder(Node* p) const;

	// Postcondition: Returns the number of nodes on the tree to which p points
	int nodeCount(Node* p) const;

	// Postcondition: Traverses tree and prints all nodes that are a substring of searchItem
	void search(Node* p, const std::string& searchItem, std::string& wordList, bool& isMatch) const;
};

#endif
