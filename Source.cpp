#include <limits>
#include <fstream>
#include <sstream>
#include "BinarySearchTree.h"
using namespace std;

enum Menu { UPDATE = 1, PRINT, EXIT };

const int WORD_WIDTH = 15;
const int COUNT_WIDTH = 5;
const int TABLE_WIDTH = 21;
const int MIN_LETTERS = 4;

void UpdateInputFile(string fileName);
void PopulatePrintAndDestroyTree(string fileName);
void PopulateBinaryTree(BinarySearchTree& tree, string fileName);
void PrintTreeAsTable(BinarySearchTree tree);
bool IsPunctuation(char c);
void PurgeInputErrors(string error);

// TODO: Currently, my add node function checks to see if a word
// exists before adding it. If it does exist, it just increments
// the count in the existing node.
// Is this fine or should I have a separate search function that
// checks for a duplicate first before 
int main() {
	string fileName = "Input.txt";

	int selection;
	//BinarySearchTree tree;

	do {
		cout << "Menu\nPlease select one of the following:\n"
			"1. Update Input File\n"
			"2. Print BST\n"
			"3. Exit\n"
			"Selection: ";
		cin >> selection;

		switch (selection) {
		case UPDATE:
			UpdateInputFile(fileName);
			cout << "\n**Input File Updated**\n\n";
			break;
		case PRINT:
			PopulatePrintAndDestroyTree(fileName);
			break;
		case EXIT:
			cout << "\nTerminating Program\n";
			break;
		default:
			PurgeInputErrors("Invalid Menu Option");
		}
	} while (selection != EXIT);

	return 0;
}


// TODO: Should I traverse the input file and make changes as I go,
// or can I keep the current implementation. I read the content of
// the file into a string and process the words, then CLOSE the input
// file. Reopen the input file as an istringstream, clear its contents
// and then write back to it.
void UpdateInputFile(string fileName) {
	ifstream infile(fileName);

	if (!infile) {
		cout << "ERROR: Input file not found. Terminating program\n";
		exit(EXIT_FAILURE);
	}
	if (infile.peek() == EOF) {
		cout << "ERROR: Input file is empty. Terminating program\n";
		infile.close();
		exit(EXIT_FAILURE);
	}

	// Process Input File
	string line, word, result;

	while (getline(infile, line)) {
		for (char& c : line) {
			if (IsPunctuation(c)) {
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

/*void UpdateInputFile(string fileName) {
	ifstream infile(fileName);

	if (!infile) {
		cout << "ERROR: Input file not found. Terminating program\n";
		exit(EXIT_FAILURE);
	}
	if (infile.peek() == EOF) {
		cout << "ERROR: Input file is empty. Terminating program\n";
		infile.close();
		exit(EXIT_FAILURE);
	}

	// Process Input File
	string line;
	string content;
	stringstream ss;

	while (getline(infile, line)) {
		content += line + ' ';
	}

	infile.close();

	// Replace punctuation with space
	string modified;
	for (char& c : content) {
		if (IsPunctuation(c)) {
			modified.push_back(' ');
		}
		else {
			modified.push_back(tolower(c));
		}
	}

	// Remove punctuation
	string result, word;
	istringstream stream(modified);

	while (stream >> word) {
		// Remove letters following an apostrophe
		size_t pos = word.find('\'');
		if (pos != string::npos) {
			word = word.substr(0, pos);
		}

		// Exclude words with up to 4 letters
		if (word.length() > MIN_LETTERS) {
			result += word + " ";
		}
	}

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
}*/

void PopulatePrintAndDestroyTree(string fileName) {
	BinarySearchTree tree;
	try {
		PopulateBinaryTree(tree, fileName);
		PrintTreeAsTable(tree);
		tree.destroyTree();
	}
	catch (const bad_alloc& e) {
		cout << "Error: Memory cannot be allocated for the BST. Please try again later\n" << e.what() << "\n\n";
		tree.destroyTree(); // free up any memory
	}
}

void PopulateBinaryTree(BinarySearchTree& tree, string fileName) {
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

void PrintTreeAsTable(BinarySearchTree tree) {
	cout << '\n' << left << setw(WORD_WIDTH) << "Word" << right << setw(COUNT_WIDTH) << "Count\n\n";
	tree.inOrderTraversal();
	cout << endl << endl;
}

bool IsPunctuation(char c) {
	return string(".,;:\"!?()[]{}<>-_").find(c) != string::npos;
}

void PurgeInputErrors(string error) {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Error: " << error << "\n\n";
}






















































/***********************************************************************************/

// Main before loop
	//string originalFileName = "Input.txt";
	//string backupFileName = "Input_backup.txt";
	//CopyFileContent(originalFileName, backupFileName);

// After
	//CopyFileContent(backupFileName, originalFileName);

// Prototype/Definition

//void CopyFileContent(const string& originalFileName, const string& backupFileName);

/*
void CopyFileContent(const string& originalFileName, const string& backupFileName) {
	ifstream infile(originalFileName);
	ofstream outfile(backupFileName);

	if (!infile) {
		cout << "Error opening " << originalFileName << " for reading.\n";
		return;
	}

	if (!outfile) {
		cout << "Error opening " << backupFileName << " for writing.\n";
		return;
	}

	char c;
	while (infile.get(c)) {
		outfile.put(c);
	}

	infile.close();
	outfile.close();
}

*/