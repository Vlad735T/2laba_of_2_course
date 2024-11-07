#include "structures/hash.h" 
#include "structures/vector.h"

using namespace std;

void processInput(const string& input) {
    Hashtable<string, int> hash(10); 
    Myvector<char> seenChars; // Вектор для отслеживания символов в текущей подстроке
    string currentSubstring;
    int length = 0;
    size_t start = 0; // Начальный индекс новой подстроки при сбросе

    for (size_t i = 0; i < input.length(); i++) {
        char ch = input[i];

        // Если символ уже встречался, добавляем текущую подстроку в хеш-таблицу
        if (contains(seenChars, ch)) {
            if (!currentSubstring.empty()) { 
                hash[currentSubstring] = length; 
            }

            currentSubstring.clear();
            length = 0;
            seenChars = Myvector<char>(); 

            // Возвращаемся к последней позиции символа ch и начинаем с него новую подстроку
            i = start; 
            start++;
        } else {
            // Если символ не повторялся, добавляем его в текущую подстроку
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
    
    return 0;
}
