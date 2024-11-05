#pragma once
#include "vector.h"
#include <fstream>
#include <sstream>

template<typename T>
struct Node{
	T value;
	Node* next;

	Node(const T& value): value(value), next(nullptr) {}
};

template<typename T>
struct bucket{
public:

	Node<T>* head;
	Node<T>* tail;

	bucket() : head(nullptr), tail(nullptr) {}


	bool isInSet(const T& value){
		if (isEmpty()) return false;

		Node<T>* currentNode = head;
		while (currentNode && currentNode->value != value) currentNode = currentNode->next;
		if (currentNode && currentNode->value == value) return true;
		return false;
	}

	T get(const T& value){
		if (isEmpty()) return false;

		Node<T>* currentNode = head;
		while (currentNode && currentNode->value != value) currentNode = currentNode->next;
		if (currentNode && currentNode->value == value) return currentNode->value;
		throw runtime_error("Value not found");
	}

	void push(const T& value){
		Node<T>* newNode = new Node<T>(value);
		if (isEmpty()){
			head = newNode;
			tail = newNode;
			return;
		}
		tail->next = newNode;
		tail = newNode;
	}

	void remove(const T& value){
		if (isEmpty()) return;

		if (head->value == value){
			Node<T>* temp = head;
			head = head->next;
			delete temp;

			if (head == nullptr) tail = nullptr;
			return;
		}

		Node<T>* prev = head;
		Node<T>* current = head->next;

		while (current){
			if (current->value == value){
				prev->next = current->next;
				if (current == tail) tail = prev;
				delete current;
				return;
			}
			prev = current;
			current = current->next;
		}
	}

	void print(){
		if (isEmpty()) return;

		Node<T>* current = head;
		while (current){
			cout << "[ " << current->value << " ] ";
			current = current->next;
		}
	}



	bool isEmpty(){
		return head == nullptr;
	}
};


template<typename T>
struct set{
private:

	int memoryCapacity;
	int currentSize;
	bucket<T>* arr;

	int hash(const std::string& value) const{
		int hash = 5381;
		for (char c : value){
			hash = ((hash << 5) + hash) + c;
		}
		return hash % memoryCapacity;
	}

public:

	set(){
		arr = new bucket<T>[10];
		memoryCapacity = 1;
		currentSize = 0;
	}

	set(int sizeVal){
		arr = new bucket<T>[sizeVal];
		memoryCapacity = sizeVal;
		currentSize = 0;
	}

	~set(){
		delete[] arr;
	}

	void SPUSH(const T& value){
		int index = hash(value);
		if (arr[index].isInSet(value)) return;
		else{
			arr[index].push(value);
			currentSize++;
		}
	}

	void SDEL(const T& value){
		int index = hash(value);
		if (!arr[index].isInSet(value)) return;
		arr[index].remove(value);
		currentSize--;

	}

	int size(){
		return currentSize;
	}

	bool check(const T& value) const{
		int index = hash(value);
		return arr[index].isInSet(value);
	}

	void print(){
		for (int i = 0; i < memoryCapacity; i++){
			if (!arr[i].isEmpty()){
				arr[i].print();
				cout << " ";
			}
		}
	}

	void save_to_file(const string& filename, const string& name_structure) const{
		ifstream read_file(filename);
		Myvector<string> lines;
		string line;
		bool structure_found = false;

		// Read existing lines from the file
		if (read_file.is_open()){
			while (getline(read_file, line))
			{
				lines.MPUSH(line);
			}
			read_file.close();
		}
		else{
			cerr << "Error opening the file for reading.\n";
			return;
		}

		ofstream write_file(filename);
		if (!write_file.is_open()){
			cerr << "Error opening the file for writing.\n";
			return;
		}

		// Write lines back, updating or adding the structure line
		for (auto& existing_line : lines){
			if (existing_line.find(name_structure + " : ") == 0) {
				structure_found = true;
				write_file << name_structure << " : ";

				bool first = true;
				for (int i = 0; i < memoryCapacity; i++){
					Node<T>* current = arr[i].head;
					while (current != nullptr){
						if (!first) write_file << ", ";
						write_file << current->value;
						current = current->next;
						first = false;
					}
				}
				write_file << endl;
			}
			else{
				write_file << existing_line << endl;
			}
		}

		// If structure was not found, add it to the end
		if (!structure_found){
			write_file << name_structure << " : ";
			bool first = true;
			for (int i = 0; i < memoryCapacity; i++){
				Node<T>* current = arr[i].head;
				while (current != nullptr){
					if (!first) write_file << ", ";
					write_file << current->value;
					current = current->next;
					first = false;
				}
			}
			write_file << endl;
		}

		write_file.close();
	}

	void load_from_file(const string& filename, const string& name_structure){
		ifstream file(filename);

		if (!file.is_open()){
			cerr << "Error opening the file for reading.\n";
			return;
		}

		string line;
		bool structure_found = false;

		// Read lines from the file
		while (getline(file, line)){
			// Look for the line that starts with the structure name
			if (line.find(name_structure + " : ") == 0){
				structure_found = true;
				size_t pos = line.find(':');
				string values = line.substr(pos + 1);  // Extract values after " : "
				stringstream ss(values);
				string value;

				// Parse values and add them to the set
				while (getline(ss, value, ',')){
					// Remove leading and trailing whitespace
					value.erase(0, value.find_first_not_of(" "));
					value.erase(value.find_last_not_of(" ") + 1);

					SPUSH(value);
				}
				break;
			}
		}

		file.close();
	}

	friend void compareGenes(const set<string>& firstChain, const set<string>& secondChain);
};