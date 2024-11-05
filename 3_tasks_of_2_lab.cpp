#include <iostream> 
#include "structures/set.h"
using namespace std;

set<string> divideGenes(const string& geneChain) {
    set<string> genes(10);
    for (int i = 0; i < geneChain.size() - 1; i++) {
        if (65 <= geneChain[i] && geneChain[i] <= 90) {
            if (65 <= geneChain[i + 1] && geneChain[i + 1] <= 90) {
                genes.SPUSH(string(1, geneChain[i]) + string(1, geneChain[i + 1]));
            } else {
                cout << "Broken gene detected" << endl;
                exit(0);
            }
        } else {
            cout << "Broken gene detected" << endl;
            exit(0);
        }
    }
    return genes;
}

void compareGenes(const set<string>& firstChain, const set<string>& secondChain) {
    int matches = 0;

    for (int i = 0; i < firstChain.memoryCapacity; i++) {
        if (!firstChain.arr[i].isEmpty()) {
            Node<string>* current = firstChain.arr[i].head;
            while (current) {
                if (secondChain.check(current->value)) {
                    matches++;
                }
                current = current->next;
            }
        }
    }
    cout << "These genomes have similar genes: " << matches << endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    string input1, input2;

    cout << "Введите первую строку генов (только большие английские буквы): ";
    cin >> input1;

    cout << "Введите вторую строку генов (только большие английские буквы): ";
    cin >> input2;

    set<string> test1 = divideGenes(input1);
    set<string> test2 = divideGenes(input2);

    test1.print();
    cout << "\n";
    test2.print();
    cout << "\n";
    compareGenes(test1, test2);

    return 0;
}
