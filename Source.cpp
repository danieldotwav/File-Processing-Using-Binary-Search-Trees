#include <limits>
#include <fstream>
#include <sstream>
#include "BinarySearchTree.h"
using namespace std;

enum Menu { UPDATE = 1, BUILDBST, PRINT, SEARCH, DELETE, EXIT };

void updateInputFile(string fileName);
void populateBinaryTree(BinarySearchTree& tree, string fileName);
void printBinaryTree(BinarySearchTree tree);
void searchBinaryTree(BinarySearchTree tree);
void deleteFromBinaryTree(BinarySearchTree& tree);
bool isPunctuation(char c);
void purgeInputErrors(string error);

int main() {
	BinarySearchTree tree;
	string fileName = "Input.txt";
	int selection;

	do {
		cout << "MENU\nPlease select one of the following:\n"
			"1. Update Input File\n"
			"2. Build BST\n"
			"3. Print BST\n"
			"4. Search\n"
			"5. Delete\n"
			"6. Exit\n"
			"Selection: ";
		cin >> selection;

		switch (selection) {
		case UPDATE:
			updateInputFile(fileName);
			cout << "\n**Input File Updated**\n\n";
			break;
		case BUILDBST:
			populateBinaryTree(tree, fileName);
			cout << "\n**Binary Tree Built Successfully**\n\n";
			break;
		case PRINT:
			printBinaryTree(tree);
			break;
		case SEARCH:
			searchBinaryTree(tree);
			break;
		case DELETE:
			deleteFromBinaryTree(tree);
			break;
		case EXIT:
			cout << "\nTerminating Program\n";
			break;
		default:
			purgeInputErrors("Invalid Menu Option");
		}
	} while (selection != EXIT);

	return 0;
}

void updateInputFile(string fileName) {
	ifstream infile(fileName);

	if (!infile) {
		cout << "Error: Input file not found. Terminating program\n";
		exit(EXIT_FAILURE);
	}
	if (infile.peek() == EOF) {
		cout << "Error: Input file is empty. Terminating program\n";
		infile.close();
		exit(EXIT_FAILURE);
	}

	// Process Input File
	string line, word, result;

	while (getline(infile, line)) {
		for (char& c : line) {
			if (isPunctuation(c)) {
				c = ' ';
			}
			else {
				c = tolower(c);
			}
		}

		istringstream stream(line);
		while (stream >> word) {
			size_t pos = word.find('\'');
			if (pos != string::npos) {
				word = word.substr(0, pos);
			}

			// Exclude words with up to 4 letters
			if (word.length() > MIN_LETTERS) {
				result += word + " ";
			}
		}
	}
	infile.close();

	// Write back to the input file
	ofstream outfile(fileName, ios::trunc);
	if (outfile) {
		outfile << result;
		outfile.close();
	}
	else {
		cout << "Error opening " << fileName << " for reading\n"
			"Terminating Program\n";
		exit(EXIT_FAILURE);
	}
}

void populateBinaryTree(BinarySearchTree& tree, string fileName) {
	try {
		ifstream infile(fileName);
		if (infile) {
			string word;

			while (infile >> word) {
				tree.insert(word);
			}
			infile.close();
		}
		else {
			cout << "Error opening " << fileName << " for reading.\n"
				"Terminating Program\n";
			exit(EXIT_FAILURE);
		}
	}
	catch (const bad_alloc& e) {
		cout << "Error: Memory cannot be allocated for the BST. Please try again later\n" << e.what() << "\n\n";
		tree.destroyTree(); // free up any memory
	}
}

void printBinaryTree(BinarySearchTree tree) {
	cout << '\n' << left << setw(WORD_WIDTH) << "Word" << right << setw(COUNT_WIDTH) << "Count\n\n";
	tree.printInorder();
	
	cout << "\nTotal Unique Words Processed: " << tree.treeNodeCount() << "\n\n";
}

void searchBinaryTree(BinarySearchTree tree) {
	string query;

	cout << "\nSEARCH\nEnter search word: ";
	cin >> query;

	cout << "\nSearch Results: '" << query << "':\n";
	std::cout << '\n' << std::left << std::setw(WORD_WIDTH) << "Word" << std::right << std::setw(COUNT_WIDTH) << "Count\n";
	
	tree.findWordsContaining(query);
	cout << endl;
}

void deleteFromBinaryTree(BinarySearchTree& tree) {
	string query;

	cout << "\nSEARCH\nEnter word to delete: ";
	cin >> query;

	tree.deleteNode(query);
}

bool isPunctuation(char c) {
	return string(".,;:\"!?()[]{}<>-_").find(c) != string::npos;
}

void purgeInputErrors(string error) {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Error: " << error << "\n\n";
}