#include "BinarySearchTree.h"
const int WORD_WIDTH = 15;
const int COUNT_WIDTH = 5;

BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
	destroy(root);
}

const BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& otherTree) {
	if (this != &otherTree) {
		if (root != nullptr) {
			destroy(root);
		}
		if (otherTree.root == nullptr) {
			root = nullptr;
		}
		else {
			copyTree(root, otherTree.root);
		}
	}
	return *this;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& otherTree) {
	if (otherTree.root == nullptr) {
		root = nullptr;
	}
	else {
		copyTree(root, otherTree.root);
	}
}

bool BinarySearchTree::isEmpty() const {
	return (root == nullptr);
}

void BinarySearchTree::inOrderTraversal() const {
	inorder(root);
}

int BinarySearchTree::treeNodeCount() const {
	return nodeCount(root);
}

void BinarySearchTree::destroyTree() {
	destroy(root);
}

bool BinarySearchTree::search(const std::string& searchWord) const {
	Node* current;
	bool found = false;

	if (root == nullptr) {
		std::cout << "\nError: Cannot search an empty tree\n\n";
	}
	else {
		current = root;

		while (current != nullptr && !found) {
			if (current->word == searchWord) {
				found = true;
			}
			else if (current->word > searchWord) {
				current = current->leftLink;
			}
			else {
				current = current->rightLink;
			}
		}
	}
	return found;
}

void BinarySearchTree::insert(const std::string& insertWord) {
	Node* current; // pointer to traverse tree
	Node* trailCurrent = nullptr; // pointer behind current
	Node* newNode; // pointer to create the new node
	bool duplicateFound = false;

	if (root == nullptr) {
		root = new Node;
		root->word = insertWord;
		root->leftLink = nullptr;
		root->rightLink = nullptr;
	}
	else {
		current = root;
		
		while (current != nullptr && duplicateFound == false) {
			trailCurrent = current;

			if (current->word == insertWord) {
				current->count++;
				duplicateFound = true;
			}
			else if (current->word > insertWord) {
				current = current->leftLink;
			}
			else {
				current = current->rightLink;
			}
		}

		if (duplicateFound == false) {
			Node* newNode = new Node;
			newNode->word = insertWord;
			newNode->leftLink = nullptr;
			newNode->rightLink = nullptr;

			if (trailCurrent->word > insertWord) {
				trailCurrent->leftLink = newNode;
			}
			else {
				trailCurrent->rightLink = newNode;
			}
		}
	}
}

void BinarySearchTree::deleteFromTree(Node*& p) {
	Node* current; // pointer to traverse the tree
	Node* trailCurrent; // pointer behind current
	Node* temp; // pointer to delete the node

	if (p == nullptr) {
		std::cout << "Error: The node to be deleted does not exist\n\n";
	}
	else if (p->leftLink == nullptr && p->rightLink == nullptr) {
		temp = p;
		p = nullptr;
		delete temp;
	}
	else if (p->leftLink == nullptr) {
		temp = p;
		p = temp->rightLink;
		delete temp;
	}
	else if (p->rightLink == nullptr) {
		temp = p;
		p = temp->leftLink;
		delete temp;
	}
	else {
		current = p->leftLink;
		trailCurrent = nullptr;

		while (current->rightLink != nullptr) {
			trailCurrent = current;
			current = current->rightLink;
		}
		p->word = current->word;

		if (trailCurrent == nullptr) {
			p->leftLink = current->leftLink;
		}
		else {
			trailCurrent->rightLink = current->leftLink;
		}

		delete current;
	}
}

void BinarySearchTree::deleteNode(const std::string& deleteWord) {
	Node* current; // pointer to traverse tree
	Node* trailCurrent; // pointer behind current
	bool found = false;

	if (root == nullptr) {
		std::cout << "\nError: Cannot delete from an empty tree\n\n";
	}
	else {
		current = root;
		trailCurrent = root;

		while (current != nullptr && !found) {
			if (current->word == deleteWord) {
				found = true;
			}
			else {
				trailCurrent = current;

				if (current->word > deleteWord) {
					current = current->leftLink;
				}
				else {
					current = current->rightLink;
				}
			}
		}

		if (current == nullptr) {
			std::cout << "\nError: The word to be deleted is not in the tree\n\n";
		}
		else if (found) {
			if (current == root) {
				deleteFromTree(root);
			}
			else if (trailCurrent->word > deleteWord) {
				deleteFromTree(trailCurrent->leftLink);
			}
			else {
				deleteFromTree(trailCurrent->rightLink);
			}
		}
		else {
			std::cout << "\nError: The word to be deleted is not in the tree\n\n";
		}
	}
}

void BinarySearchTree::copyTree(Node*& copiedTreeRoot, Node* otherTreeRoot) {
	if (otherTreeRoot == nullptr) {
		copiedTreeRoot = nullptr;
	}
	else {
		copiedTreeRoot = new Node;
		copiedTreeRoot->word = otherTreeRoot->word;
		copiedTreeRoot->count = otherTreeRoot->count;
		copyTree(copiedTreeRoot->leftLink, otherTreeRoot->leftLink);
		copyTree(copiedTreeRoot->rightLink, otherTreeRoot->rightLink);
	}
}

void BinarySearchTree::destroy(Node*& p) {
	if (p != nullptr) {
		destroy(p->leftLink);
		destroy(p->rightLink);
		delete p;
		p = nullptr;
	}
}

void BinarySearchTree::inorder(Node* p) const {
	if (p != nullptr) {
		inorder(p->leftLink);
		std::cout << std::left << std::setw(WORD_WIDTH) << p->word 
			<< std::right << std::setw(COUNT_WIDTH) << p->count << std::endl;
		inorder(p->rightLink);
	}
}

int BinarySearchTree::nodeCount(Node* p) const {
	int count = 0;
	if (p != nullptr) {
		count = (1 + nodeCount(p->leftLink) + nodeCount(p->rightLink));
	}
	return count;
}