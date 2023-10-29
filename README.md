# File-Processing-Using-Binary-Search-Trees
This program implements a binary search tree to store and manage strings. Each node of the tree holds a string and a count indicating the number of times the string has been inserted into the tree.

## Features:
-Insertion: Add words to the tree. Duplicates are handled by incrementing a count in the corresponding node.
-Deletion: Remove words from the tree.
-Search: Check if a word is present in the tree.
-Traversal: For the purpose of this project, only in-order traversal is used.
-Tree Properties: You can fetch the height of the tree, count the total nodes, and count the leaf nodes.

## Limitations:
The tree does not self-balance. Prolonged insertions in a certain order can lead to a skewed tree, affecting performance.
Memory management is manual; ensure proper destruction of the tree to prevent leaks.
