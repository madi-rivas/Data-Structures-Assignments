#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


int *getBiggerArray(int *oldArray, int oldCapacity)
{   
    int *newArray = new int [oldCapacity*2];// dynamically allocate an array of size 2 * oldCapacity

    for (int i=0; i<= oldCapacity*2; i++){
        newArray[i] = oldArray[i];
    }

    delete [] oldArray;
    return newArray;
}

int insertIntoSortedArray(int myArray[], int numEntries, int newValue)
{
    int j,b;

    myArray[numEntries]=newValue;
    numEntries++;

    for (int i=0; i<numEntries; i++)
    {
        j=numEntries-1;
        while(j>0 && myArray[j]<myArray[j-1]){
            b=myArray[j];
            myArray[j]=myArray[j-1];
            myArray[j-1]=b;
            j--;
        }
    }
    return numEntries;
}

int main(int argc, char* argv[])
{
	if (argc<2)
	{
		cout<<"Error. Please enter the name of the file.";
		return 1;
	}
    if (argc>2)
    {
        cout<<"Error. Too many arguments inputted";
        return 1;
    }

    int capacity = 10;
    int *array = new int[capacity];// dynamically allocate array with initial capacity
    int lineNumber = 0;
    int numberOfLines = 0;
    string line;


    ifstream myFile(argv[1]);

    while(getline(myFile,line)){

        if(numberOfLines >= capacity)
        {
            array = getBiggerArray(array, capacity);
            capacity = 2 * capacity;
        }

        array[numberOfLines]=stoi(line);
        numberOfLines=insertIntoSortedArray(array, numberOfLines, array[numberOfLines]);

        for (int i=0; i<numberOfLines; i++){
            cout<<array[i]<<",";
        }
        cout<<endl;
    }

 
    




	return 0;
}
