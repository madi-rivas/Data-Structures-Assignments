#include <string>
#include <fstream>
#include <iostream>

#include "PRIORITYQUEUE.hpp"

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
        repairUpward(currentQueueSize);
        return;

    }

}

void PriorityQueue::dequeue()
{
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
    /*if((nodeIndex)<1)
        return;*/
    if(priorityQueue[nodeIndex].injurySeverity > priorityQueue[nodeIndex*2].injurySeverity)
        return;
    if(priorityQueue[nodeIndex].injurySeverity > priorityQueue[nodeIndex*2-1].injurySeverity)
        return;
    if(priorityQueue[nodeIndex*2].injurySeverity > priorityQueue[nodeIndex*2+1].injurySeverity){
        if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex*2].injurySeverity){
            swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2]);
            repairUpward(nodeIndex*2);
        }
        if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex*2].injurySeverity)
        {
            if(priorityQueue[nodeIndex].treatmentTime>priorityQueue[nodeIndex*2].treatmentTime)
            {
                swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2]);
                repairUpward(nodeIndex*2);
            }
            else
                return;
        }
    }

    if(priorityQueue[nodeIndex*2].injurySeverity < priorityQueue[nodeIndex*2+1].injurySeverity){
        if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex*2+1].injurySeverity){
            swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2+1]);
            repairUpward(nodeIndex*2+1);
        }
        if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex*2+1].injurySeverity)
        {
            if(priorityQueue[nodeIndex].treatmentTime>priorityQueue[nodeIndex*2+1].treatmentTime)
            {
                swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2+1]);
                repairUpward(nodeIndex*2+1);
            }
            else
                return;
        }
    }

    if(priorityQueue[nodeIndex*2].injurySeverity == priorityQueue[nodeIndex*2+1].injurySeverity){
        if(priorityQueue[nodeIndex*2].treatmentTime > priorityQueue[nodeIndex*2+1].treatmentTime)
        {
            if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex*2].injurySeverity){
                swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2]);
                repairUpward(nodeIndex*2);
            }
            if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex*2].injurySeverity)
            {
                if(priorityQueue[nodeIndex].treatmentTime>priorityQueue[nodeIndex*2].treatmentTime)
                {
                    swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2]);
                    repairUpward(nodeIndex*2);
                }
                else
                    return;
            }
        }
        if(priorityQueue[nodeIndex*2].treatmentTime > priorityQueue[nodeIndex*2+1].treatmentTime)
        {
                if(priorityQueue[nodeIndex].injurySeverity < priorityQueue[nodeIndex*2+1].injurySeverity){
                    swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2+1]);
                    repairUpward(nodeIndex*2+1);
                }
                if(priorityQueue[nodeIndex].injurySeverity==priorityQueue[nodeIndex*2+1].injurySeverity)
                {
                    if(priorityQueue[nodeIndex].treatmentTime>priorityQueue[nodeIndex*2+1].treatmentTime)
                    {
                        swap(&priorityQueue[nodeIndex], &priorityQueue[nodeIndex*2+1]);
                        repairUpward(nodeIndex*2+1);
                    }
                    else
                        return;
                }
        }

    }
}

using namespace std;

int main(int argc, char** argv)
{
	/* code */

	int maxSize = stoi(argv[1]);
	PriorityQueue p(maxSize);
	string name_;
    int injurySeverity_;
    int treatmentTime_;
    int totalTreatmentTime = 0;

	int choice = 0;
	while(choice != 6)
    {
        cout << "======Main Menu======" <<endl;
        cout << "1. Get Patient Information from File" <<endl;
        cout << "2. Add Patient to Priority Queue" <<endl;
        cout << "3. Show Next Patient" <<endl;
        cout << "4. Treat Next Patient" << endl;
		cout << "5. Treat Entire Queue" << endl;
		cout << "6. Quit" << endl;
        cin>>choice;
       

        switch(choice)
        {
            case 1:
            {
                string fileName;
                string line;
                cin>>fileName;
                ifstream myFile(fileName);
                string word;

                fstream file;
                file.open(fileName.c_str()); 
  
			    // extracting words form the file 
			    while (file >> word) 
			    { 
			        // displaying content 
			        name_ = (word);
			        injurySeverity_ = stoi(word);
			        treatmentTime_ = stoi(word);
			        p.enqueue(name_, injurySeverity_, treatmentTime_);
			        cout << name_ << injurySeverity_ << treatmentTime_ << endl; 
			    } 


                //choice = 6;
                break;
            }
            case 2:
            {
                // add patient to priority queue
                cout << "Enter Patient Name:" << endl;
                cin>>name_;
                cout << "Enter Injury Severity:" << endl;
                cin>>injurySeverity_;
                cout << "Enter Treatment Time:" << endl;
                cin>>treatmentTime_;
                p.enqueue(name_, injurySeverity_, treatmentTime_);
                
                break;
            }
            case 3:
            {
                // show next patient
                cout << "Patient Name: " << p.peekName() << endl;
                cout << "Injury Severity: " << p.peekInjurySeverity() << endl;
                cout << "Treatment Time: " << p.peekTreatmentTime() << endl;
                break;
            }
            case 4:
            {
                // treat next patient
                if(p.isEmpty())
                {
                    cout<<"Queue Empty"<<endl;
                    break;
                }
                totalTreatmentTime = totalTreatmentTime + p.peekTreatmentTime();
                cout<<"Patient Name: "<< p.peekName() << " - Total Time Treating Patients: " << totalTreatmentTime << endl;
                p.dequeue();
                break;
            }
            
            case 5:
            {
            	// treat entire queue

                break;
            }
            default:
            {
                break;
            }

        }
    }
    cout << "Goodbye!" << endl;



	return 0;
}