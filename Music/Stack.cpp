/*
 *  Stack.cpp
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

#include "Stack.h"

template <class T>
void Stack<T>::push(const T& obj) {
    top = new StackNode(obj, top);
}

template <class T>
T Stack<T>::pop() {
#ifdef DEBUG
    if ( !isEmpty() ) {
#endif
        StackNode *topNode = top;
        top = top->next;
        T data = topNode->data;
        delete topNode;
        return data;
#ifdef DEBUG
    }
    throw StackException ("Empty Stack");
    return 0;
#endif
}

template <class T>
const T& Stack<T>::topElement() {
#ifdef DEBUG
    if ( !isEmpty() ) {
#endif
        return top->data;
#ifdef DEBUG
    }
    throw StackException("Empty Stack");
    return 0;
#endif
}

template <class T>
bool Stack<T>::isEmpty() {
    return top == 0;
}
