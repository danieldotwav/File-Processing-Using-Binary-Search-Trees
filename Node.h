#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
public:
	std::string word;
	int count;
	Node* left;
	Node* right;
	Node() : word(""), count(1), left(nullptr), right(nullptr) {}
};

#endif