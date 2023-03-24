#include <iostream>
#include <algorithm>    // for transform()

using namespace std;

class Stack{
    private :
        const int MAX_SIZE = 30; 
        int size = 0;
        char *stack;
    public :
        Stack(string input){
            stack = new char[MAX_SIZE];

            for (int i = 0 ; i < input.size(); i++){
                this->push(input[i]);
            }
        }

        bool empty(){
            return !size;
        }

        bool full(){
            return size == MAX_SIZE;
        }

        void push(char letter){
            if (this->full()){
                cout << "The stack is full." << endl;
                return;
            }
            stack[size++] = letter;     // sets stack[size] into letter and then increments
        }

        char pop(){
            if (this->empty()){
                cout << "The stack is empty." << endl;
                exit(1);                // exits with error code
            }

            char top = stack[--size];   // takes top of stack and decrements size
            stack[size+1] = ' ';        // empties the popped index

            return top;
        }

};

int main(){
    string input_word;

    cout << "Input a string to palindrome check (space-sensitive): ";
    cin >> input_word;
    cout << endl;

    // lowercases word and puts into stack
    transform(input_word.begin(), input_word.end(),
              input_word.begin(), ::tolower);
    Stack word_stack(input_word);
    
    string popped_chars = "";
    while ( !(word_stack.empty()) ){
        popped_chars += word_stack.pop();
    }

    cout << ((input_word == popped_chars) ? "Your word is a palindrome." : "Your word is not a palindrome.") << endl;

    return 0;
}