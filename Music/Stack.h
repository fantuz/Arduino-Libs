
/*
 *  Stack.h
 *  A class implementing a very basic stack
 *  This is meant to run on Arduino
 *  Define the label DEBUG to have some debug support
 *
 *  Written by Enrico Formenti, 22 dec 2014
 *
 *  BSD license, check License page on the blog for more information
 *  All this text must be included in any redistribution.
 *
 *  See macduino.blogspot.com for more details.
 */

#ifndef ___Stack_h
#define ___Stack_h


#ifdef DEBUG

#include <Serial.h>

class StackException {
public:
    StackException(char *s) : str(s) {};
    ~StackException() {};
    void what() {
        Serial.println(str);
    };
    
private:
    char *str;
};
#endif

template <class T>
class Stack {
public:
    Stack():top(0){};
    ~Stack() {
        while ( !isEmpty() )
            pop();
    }
    
    void push (const T& object);
    T pop();
    const T& topElement();
    bool isEmpty();
    
private:
    struct StackNode {              // linked list node
        T data;                     // data at this node
        StackNode *next;            // next node in list
        
        // StackNode constructor initializes both fields
        StackNode(const T& newData, StackNode *nextNode)
        : data(newData), next(nextNode) {}
    };

    StackNode *top;                 // top of stack
    
};

#endif /* defined(____Stack_h) */
