#include <iostream>
#include "HW4-Todo-QueueLinkedList.hpp"

using namespace std;

TodoQueueLinkedList::TodoQueueLinkedList()
{
	this->queueFront = NULL;
	this->queueEnd = NULL;

}

TodoQueueLinkedList::~TodoQueueLinkedList()
{
	TodoItem *temp=new TodoItem;
	temp=queueFront;
	while (temp!=NULL){
		temp->next=queueFront->next;
		delete queueFront;
		temp=temp->next;
	}
}

bool TodoQueueLinkedList::isEmpty()
{
    if (this->queueFront==NULL)
    	return true;
    else
    	return false;
}

void TodoQueueLinkedList::enqueue(std::string todoItem)
{
	TodoItem *temp=new TodoItem;
	temp->todo=todoItem;
	temp->next=NULL;
	if(isEmpty())
	{
		this->queueFront=this->queueEnd=temp;
	}
	else
	{
		this->queueEnd->next=temp;
		this->queueEnd=temp;
	}
}

void TodoQueueLinkedList::dequeue()
{
	if(isEmpty()){
		cout<<"Queue empty, cannot dequeue an item."<<endl;
		return;
	}
	this->queueFront=this->queueFront->next;
}

TodoItem* TodoQueueLinkedList::peek()
{
	if(isEmpty()){
		cout<<"Queue empty, cannot peek."<<endl;
		return queueFront;
	}

	return queueFront;
}
