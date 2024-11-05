#include <iostream>
#include "structures/vector.h"
#include <string>

bool is_upp(char c){
    return 65 <= c && c <= 90;
}

bool check_correct_word(const string&  word){
    int up_symbol = 0;
    for (char sym : word){
        if (is_upp(sym)) up_symbol++;
    }
    if (up_symbol == 1) return true;
    return false;
}

void word_in_dict(int num_of_words, Myvector<string>& wordList){

    string input;
    cout << "Enter the words:\n";

    for (int i = 0; i < num_of_words; i++){

        while(true){

            cin >> input;
            if (check_correct_word(input)){
                wordList.MPUSH(input);
                break;
            } else { 
                cout << "The word was entered incorrectly: " << input << endl; 
                cout << "Please enter a valid word:\n";
            }
        }
    }
}

Myvector<string> add_words_in_vec(string& input){
    Myvector<string> processedWords;
    string word = "";

    for (char sym : input){
        if (sym == ' '){

            if (!word.empty()){ 
                processedWords.MPUSH(word);
                word = "";
            }
        }
        else word += sym; 
    } 

    if (!word.empty()) processedWords.MPUSH(word); 
    return processedWords;
}

string to_low(const string& word){
    string lowerWord = "";
    for (char sym : word){
        lowerWord += tolower(sym);
    }
    return lowerWord;
}

int in_dictionary(const string& word, Myvector<string> dictionary){

    string lowerWord = to_low(word);

    for (int j = 0; j < dictionary.size(); j++){
        string word_in_dir = dictionary.MGET(j);

        if (lowerWord == to_low(word_in_dir)){
            if (word == word_in_dir) return 1;  // Слово корректно написано
            else return 0;  // Слово есть в словаре, но написано некорректно
        }
    }

    return 2;  // Слово не найдено в словаре
}

void find_wrong_words(Myvector<string> text, Myvector<string> dictionary){

    Myvector<string> wrong_words;
    int wrong_counter = 0;

    for (int i = 0; i < text.size(); i++){
        int checkResult = in_dictionary(text.MGET(i), dictionary);

        if (checkResult == 1) continue;

        if (checkResult == 0){
            wrong_counter++;
            wrong_words.MPUSH(text.MGET(i));
        }
        else if (checkResult == 2 && !check_correct_word(text.MGET(i))){
            wrong_counter++;
            wrong_words.MPUSH(text.MGET(i));
        }
    }

    cout << "This text has " << wrong_counter << " incorrect word(s)!" << endl;
    wrong_words.print();
}


bool is_number(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main(){

    Myvector<string> dictionary;
    string input;
    int number_of_words = 0;

    cout << "Enter the number of words in the dictionary: ";
    cin >> input;


    if (is_number(input)) {
        number_of_words = stoi(input);
        word_in_dict(number_of_words, dictionary); 
    } else {
        cout << "Error: You did not enter a valid number: " << input << endl;
        return 1;
    }

    // wait a new input from user!!
    cin.get();
    string userInput;
    cout << "Enter the text with accents: ";

    getline(cin, userInput);
    Myvector<string> text = add_words_in_vec(userInput);
    find_wrong_words(text, dictionary);

    return 0;
}
