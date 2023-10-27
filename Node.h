#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
public:
	std::string word;
	int count;
	Node* leftLink;
	Node* rightLink;
	Node() : word(""), count(1), leftLink(nullptr), rightLink(nullptr) {}
};

#endif