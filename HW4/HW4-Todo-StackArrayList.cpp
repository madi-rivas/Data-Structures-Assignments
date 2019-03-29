#include <iostream>
#include "HW4-Todo-StackArray.hpp"

using namespace std;

TodoStackArray::TodoStackArray()
{
	stackTop=-1;

}

bool TodoStackArray::isEmpty()
{
	if (stackTop==-1)
		return true;
	else
		return false;
}

bool TodoStackArray::isFull()
{
	if ((MAX_STACK_SIZE-1)==stackTop)
		return true;
	else
		return false;

}

void TodoStackArray::push(std::string todoItem)
{
	if(stackTop>=5)
	{
		cout<<"Stack full, cannot add new todo item."<<endl;
	}
	else
	{
		stack[stackTop++];
		stack[stackTop].todo=todoItem;
	}

}

void TodoStackArray::pop()
{
	if(isEmpty())
		cout<<"Stack empty, cannot pop an item."<<endl;
	else
	{
		stackTop--;
	}
}

TodoItem TodoStackArray::peek()
{
	if(isEmpty())
	{
		cout<<"Stack empty, cannot peek."<<endl;
		return *stack;
	}
	else
	{
		return stack[stackTop];

	}

}

