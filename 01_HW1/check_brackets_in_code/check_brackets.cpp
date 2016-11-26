#include <iostream>
#include <stack>
#include <string>
#include <queue>
using namespace std;
struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_stack;
    std::queue <Bracket> closing_queue;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_stack.push(Bracket(next,position));
        }

        if (next == ')' || next == ']' || next == '}') {
            closing_queue.push(Bracket(next,position));
            if(opening_stack.empty()){
                cout<<position+1<<endl;
                return 0;
            }
            if(opening_stack.top().Matchc(next)){
                opening_stack.pop();
                closing_queue.pop();
            }else{
                cout<<1+closing_queue.front().position<<endl;
                return 0;
            }

        }
    }
    if (opening_stack.empty() and closing_queue.empty()){
        cout<<"Success"<<endl;
    }else{
        while(opening_stack.size()!=1 and not opening_stack.empty()) {
            opening_stack.pop();//get to the first element in the stack
        }
        while(closing_queue.size()!=1 and not closing_queue.empty()){
            closing_queue.pop();

        }
        if (closing_queue.empty()){
            cout<<1+opening_stack.top().position<<endl;
        }else{
            cout<<1+closing_queue.front().position<<endl;
        }
    }
    return 0;
}
