#pragma once

#include <iostream>

using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;

	Node(int value) : key(value), left(nullptr), right(nullptr) {}
};


int max(int left, int right) {
	if (left > right) {
		return left;
	}
	return right;
}



struct BST {
private:

	Node* root;


	Node* addNode(Node* node, int value) {

		if (node == nullptr) {
			return new Node(value);
		}

		if (value < node->key) {
			node->left = addNode(node->left, value);

		}
		else if (value > node->key) {
			node->right = addNode(node->right, value);

		}
		return node;
	}

	int calculate_heights(Node* node) {
		if (node == nullptr) {
			return -1;
		}

		int left_heights = calculate_heights(node->left);
		int rights_heights = calculate_heights(node->right);
		return max(left_heights, rights_heights) + 1;
	}



	void delete_tree(Node* node) {
		if (node != nullptr) {
			delete_tree(node->left);
			delete_tree(node->right);
		}
	}

	void printTree(Node* node, int space) const {
		if (node == nullptr) {
			return;
		}

		space += 10;  // Увеличиваем отступ для следующего уровня

		// Сначала печатаем правое поддерево
		printTree(node->right, space);

		// Печатаем текущий узел
		cout << endl;
		for (int i = 10; i < space; i++) {
			cout << " ";  // Печатаем пробелы для форматирования
		}
		cout << node->key << "\n";

		// Затем печатаем левое поддерево
		printTree(node->left, space);
	}


public:

	BST() : root(nullptr) {}

	~BST() {
		delete_tree(root);
	}

	void add(int value) {
		root = addNode(root, value);
	}

	int height() {
		return calculate_heights(root);
	}


	void print() const {
		printTree(root, 0);
	}
};
