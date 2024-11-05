#include "structures/bst.h"
#include "structures/vector.h"



int main() {

	BST search_tree;

	cout << "Enter number of chisel: ";
	int size_of_num;
	cin >> size_of_num;

	if (size_of_num <= 0) {
		cerr << "Number of chisels must be greater than 0." << endl;
		return 1;
	}

	cout << "Enter the number:\n";
	for (int i = 0; i < size_of_num; i++) {
		int value;

		if (!(cin >> value)) {
			cerr << "You entered a non-integer value!" << endl;
			return 1; 
		}

		search_tree.add(value);
	}

	cout << "The heights of tree: " << search_tree.height() << "\n";

	search_tree.print();

	return 0;
}
