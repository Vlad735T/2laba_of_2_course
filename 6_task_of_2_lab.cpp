#include "structures/hash.h"
#include "structures/vector.h"

using namespace std;


void processInput(const string& input) {

    Hashtable<string, int> hash(10); 
    Myvector<char> seenChars; // Множество для отслеживания встреченных символов

    string currentSubstring; 
    int length = 0;

    for (char ch : input) {

        // Если символ уже встречался, добавляем текущую подстроку в хеш-таблицу
        if (contains(seenChars, ch)) {

            if (!currentSubstring.empty()) { 
                hash[currentSubstring] = length; 
            }

            currentSubstring.clear();
            length = 0;
            seenChars = Myvector<char>(); 
        }else {
            
            currentSubstring += ch;
            seenChars.MPUSH(ch); 
            length++;
        }
    }

    if (!currentSubstring.empty()) {
        hash[currentSubstring] = length;
    }

    hash.print();
    
    string longestKey;
    int longestValue = 0;
    hash.search_line_and_size(longestKey, longestValue);


    cout << "The longest line: \'" << longestKey << "\' with length: \'" << longestValue << "\'\n";
}

int main() {
    string input;
    cout << "Enter the line: ";
    cin >> input; 

    processInput(input); 
    
    string line;
    int size;

    return 0;
}

