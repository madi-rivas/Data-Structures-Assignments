#include <string>
#include <fstream>
#include <iostream>

#include "PriorityQueue.hpp"

using namespace std;


PriorityQueue::PriorityQueue(int queueSize)
{
    maxQueueSize = queueSize;
    currentQueueSize = 0;
    priorityQueue = new PatientNode[maxQueueSize+1];


}



PriorityQueue::~PriorityQueue()
{
    delete [] priorityQueue;
}

 void PriorityQueue::enqueue(string _name, int _injurySeverity, int _treatmentTime)
{
    if(!isFull())
    {
        priorityQueue[currentQueueSize+1].name = _name;
        priorityQueue[currentQueueSize+1].injurySeverity = _injurySeverity;
        priorityQueue[currentQueueSize+1].treatmentTime = _treatmentTime;
        currentQueueSize++;
        //cout<<"ENQUEUED: "<<priorityQueue[currentQueueSize].name<<endl;
        repairUpward(currentQueueSize);
        return;

    }

}

void PriorityQueue::dequeue()
{
    if(currentQueueSize==2){
        cout<<"Currently: "<<priorityQueue[1].name<<endl;
        return;
    }
    cout<<"dequeueing: "<<priorityQueue[1].name<<" "<<currentQueueSize<<endl;
    priorityQueue[1]=priorityQueue[currentQueueSize];
    priorityQueue[currentQueueSize].name.clear();
    priorityQueue[currentQueueSize].injurySeverity = 0;
    priorityQueue[currentQueueSize].treatmentTime = 0;
   
    currentQueueSize--;
    repairDownward(1);
}

string PriorityQueue::peekName()
{
    if(!isEmpty())
    {
        return priorityQueue[1].name;
    }

    return "Queue empty." ;
}

int PriorityQueue::peekTreatmentTime()
{
    if(!isEmpty())
    {
        return priorityQueue[1].treatmentTime;
    }

}

bool PriorityQueue::isFull()
{
    if((currentQueueSize-1)==maxQueueSize)
        return true;
    else
        return false;

}

bool PriorityQueue::isEmpty()
{
    return(currentQueueSize==0);
}

void swap(PatientNode* a, PatientNode* b)
{
    PatientNode temp = *a;
    *a = *b;
    *b = temp;
}

void PriorityQueue::repairUpward(int nodeIndex)
{
    if((nodeIndex/2)<1)
        return;
    if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex/2].injurySeverity)
        return;
    if(priorityQueue[nodeIndex].injurySeverity > priorityQueue[nodeIndex/2].injurySeverity){
        swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex/2]);
        repairUpward(nodeIndex/2);
    }
    if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex/2].injurySeverity)
    {
        if(priorityQueue[nodeIndex].treatmentTime<priorityQueue[nodeIndex/2].treatmentTime)
        {
            swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex/2]);
            repairUpward(nodeIndex/2);
        }
        else
            return;
    }

    

}

void PriorityQueue::repairDownward(int nodeIndex)
{
    if(priorityQueue[nodeIndex].injurySeverity > priorityQueue[nodeIndex*2].injurySeverity){
        if(priorityQueue[nodeIndex].injurySeverity > priorityQueue[nodeIndex*2-1].injurySeverity)
            return;        
    }

    if(priorityQueue[nodeIndex*2].injurySeverity > priorityQueue[nodeIndex*2+1].injurySeverity){
        if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex*2].injurySeverity){
            swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2]);
            repairDownward(nodeIndex*2);
        }
        if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex*2].injurySeverity)
        {
            if(priorityQueue[nodeIndex].treatmentTime>priorityQueue[nodeIndex*2].treatmentTime)
            {
                swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2]);
                repairDownward(nodeIndex*2);
            }
            else
                return;
        }
        else
            return;
    }

    if(priorityQueue[nodeIndex*2].injurySeverity < priorityQueue[nodeIndex*2+1].injurySeverity){
        if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex*2+1].injurySeverity){
            swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2+1]);
            repairDownward(nodeIndex*2+1);
        }
        if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex*2+1].injurySeverity)
        {
            if(priorityQueue[nodeIndex].treatmentTime>priorityQueue[nodeIndex*2+1].treatmentTime)
            {
                swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2+1]);
                repairDownward(nodeIndex*2+1);
            }
            else
                return;
        }
        else
            return;
    }

    if(priorityQueue[nodeIndex*2].injurySeverity == priorityQueue[nodeIndex*2+1].injurySeverity){
        if(priorityQueue[nodeIndex*2].treatmentTime < priorityQueue[nodeIndex*2+1].treatmentTime)
        {
            if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex*2].injurySeverity){
                swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2]);
                repairDownward(nodeIndex*2);
            }
            if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex*2].injurySeverity)
            {
                if(priorityQueue[nodeIndex].treatmentTime>priorityQueue[nodeIndex*2].treatmentTime)
                {
                    swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2]);
                    repairDownward(nodeIndex*2);
                }
                else
                    return;
            }
            else
                return;
        }
        if(priorityQueue[nodeIndex*2].treatmentTime > priorityQueue[nodeIndex*2+1].treatmentTime)
        {
                if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex*2+1].injurySeverity){
                    swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2+1]);
                    repairDownward(nodeIndex*2+1);
                }
                if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex*2+1].injurySeverity)
                {
                    if(priorityQueue[nodeIndex].treatmentTime>priorityQueue[nodeIndex*2+1].treatmentTime)
                    {
                        swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2+1]);
                        repairDownward(nodeIndex*2+1);
                    }
                    else
                        return;
                }
                else
                    return;
        }

    }
}

