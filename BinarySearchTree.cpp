#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
	destroy(root);
}

const BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& otherTree) {
	if (this != &otherTree) {
		Node* tempRoot = nullptr;
		try {
			copyTree(tempRoot, otherTree.root);
			destroy(root);
			root = tempRoot;
		}
		catch (const std::bad_alloc& e) {
			std::cerr << "Error: Memory cannot be allocated for the BST. Original tree object is unchanged. Please try again later.\n" << e.what() << "\n\n";
			destroy(tempRoot);
		}
	}
	return *this;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& otherTree) : root(nullptr) {
	try {
		if (otherTree.root != nullptr) {
			copyTree(root, otherTree.root);
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Error: Copy was not successful, empty object created instead. Please try again later.\n" << e.what() << "\n\n";
		destroy(root);
		root = nullptr;
	}
}

bool BinarySearchTree::isEmpty() const {
	return (root == nullptr);
}

void BinarySearchTree::printInorder() const {
	inorder(root);
}

int BinarySearchTree::treeNodeCount() const {
	return nodeCount(root);
}

void BinarySearchTree::destroyTree() {
	destroy(root);
}

void BinarySearchTree::insert(const std::string& insertWord) {
	Node* current; // pointer to traverse tree
	Node* trailCurrent = nullptr; // pointer behind current
	bool duplicateFound = false;
	
	if (root == nullptr) {
		root = new Node;
		root->word = insertWord;
		root->left = nullptr;
		root->right = nullptr;
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
				current = current->left;
			}
			else {
				current = current->right;
			}
		}

		if (duplicateFound == false) {
			Node* insertNode = new Node;
			insertNode->word = insertWord;
			insertNode->left = nullptr;
			insertNode->right = nullptr;

			if (trailCurrent->word > insertWord) {
				trailCurrent->left = insertNode;
			}
			else {
				trailCurrent->right = insertNode;
			}
		}
	}
}

void BinarySearchTree::findWordsContaining(const std::string searchWord) const {
	std::string wordList;
	bool isMatch = false;
	search(root, searchWord, wordList, isMatch);
	
	if (wordList.empty() && isMatch == false) {
		std::cout << "**No Matches Found**\n";
	}
	else {
		std::stringstream matchingWords(wordList);
		std::string word{ "" };

		while (getline(matchingWords, word)) {
			std::cout << word << '\n';
		}
	}
}

void BinarySearchTree::search(Node* currentNode, const std::string& searchWord, std::string& wordList, bool& isMatch) const {
	if (currentNode != nullptr) {
		search(currentNode->left, searchWord, wordList, isMatch);
		if (currentNode->word.find(searchWord) != std::string::npos) {
			std::cout << std::left << std::setw(WORD_WIDTH) << currentNode->word
				<< std::right << std::setw(COUNT_WIDTH) << currentNode->count << std::endl;
			isMatch = true;
		}
		search(currentNode->right, searchWord, wordList, isMatch);
	}
}

void BinarySearchTree::deleteFromTree(Node*& nodeToDelete) {
	Node* current; // pointer to traverse the tree
	Node* trailCurrent; // pointer behind current
	Node* temp; // pointer to delete the node

	if (nodeToDelete == nullptr) {
		std::cout << "Error: The node to be deleted does not exist\n\n";
	}
	else if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
		temp = nodeToDelete;
		nodeToDelete = nullptr;
		delete temp;
	}
	else if (nodeToDelete->left == nullptr) {
		temp = nodeToDelete;
		nodeToDelete = temp->right;
		delete temp;
	}
	else if (nodeToDelete->right == nullptr) {
		temp = nodeToDelete;
		nodeToDelete = temp->left;
		delete temp;
	}
	else {
		current = nodeToDelete->left;
		trailCurrent = nullptr;

		while (current->right != nullptr) {
			trailCurrent = current;
			current = current->right;
		}

		nodeToDelete->word = current->word;
		nodeToDelete->count = current->count;

		if (trailCurrent == nullptr) {
			nodeToDelete->left = current->left;
		}
		else {
			trailCurrent->right = current->left;
		}

		delete current;
	}
}

void BinarySearchTree::deleteNode(const std::string& deleteWord, bool& found) {
	Node* current; // pointer to traverse tree
	Node* trailCurrent; // pointer behind current
	found = false;

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
					current = current->left;
				}
				else {
					current = current->right;
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
				deleteFromTree(trailCurrent->left);
			}
			else {
				deleteFromTree(trailCurrent->right);
			}
			std::cout << "Success: \"" << deleteWord << "\"" << " has been deleted\n\n";
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
		copyTree(copiedTreeRoot->left, otherTreeRoot->left);
		copyTree(copiedTreeRoot->right, otherTreeRoot->right);
	}
}

void BinarySearchTree::destroy(Node*& p) {
	if (p != nullptr) {
		destroy(p->left);
		destroy(p->right);
		delete p;
		p = nullptr;
	}
}

void BinarySearchTree::inorder(Node* currentNode) const {
	if (currentNode != nullptr) {
		inorder(currentNode->left);
		std::cout << std::left << std::setw(WORD_WIDTH) << currentNode->word 
			<< std::right << std::setw(COUNT_WIDTH) << currentNode->count << std::endl;
		inorder(currentNode->right);
	}
}

int BinarySearchTree::nodeCount(Node* currentNode) const {
	int count = 0;
	if (currentNode != nullptr) {
		count = (1 + nodeCount(currentNode->left) + nodeCount(currentNode->right));
	}
	return count;
}


/*
void BinarySearchTree::search(Node* currentNode, const std::string& searchWord, std::string& wordList) const {
	if (currentNode != nullptr) {
		search(currentNode->left, searchWord, wordList);
		if (currentNode->word.find(searchWord) != std::string::npos) {
			wordList += currentNode->word + '\n';
		}
		search(currentNode->right, searchWord, wordList);
	}
}
*/