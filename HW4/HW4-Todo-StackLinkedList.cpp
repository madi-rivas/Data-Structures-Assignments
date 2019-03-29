#include <iostream>
#include "HW4-Todo-StackLinkedList.hpp"

using namespace std;

TodoStackLinkedList::TodoStackLinkedList()
{
	this->stackHead=NULL;
}

TodoStackLinkedList::~TodoStackLinkedList()
{
	TodoItem* temp = new TodoItem;
	temp=this->stackHead;
	while(temp!=NULL)
	{
		temp=temp->next;
		delete stackHead;

	}
}

bool TodoStackLinkedList::isEmpty()
{
	if (this->stackHead==NULL)
		return true;
	else
		return false;
}

void TodoStackLinkedList::push(std::string todoItem)
{
	TodoItem* temp = new TodoItem;
	temp->todo=todoItem;
	temp->next=this->stackHead;
	this->stackHead=temp;

}

void TodoStackLinkedList::pop()
{
	if(isEmpty())
	{
		cout<<"Stack empty, cannot pop an item."<<endl;
		return;
	}

	else
	{
		TodoItem* temp = new TodoItem;
		temp = stackHead;
		stackHead = temp->next;
		delete temp;
		return;
	}
}

TodoItem* TodoStackLinkedList::peek()
{
	if(isEmpty())
	{
		cout<<"Stack empty, cannot peek."<<endl;
		return this->stackHead;
	}

	else
	{
		return stackHead;
	}
}

