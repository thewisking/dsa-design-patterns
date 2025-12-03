#include "iostream"
#include "stack.h"

int main() {
    Stack<int> myStack;
    myStack.push(1);
    std::cout << myStack.top() << '\n';
    myStack.push(2);
    myStack.push(4252);
    myStack.pop();
    std::cout << myStack.top() << '\n';
}