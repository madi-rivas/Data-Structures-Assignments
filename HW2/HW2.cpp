#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct wordItem{
	string word;
	int count;
};

string *getBiggerArray(string *oldArray, int oldCapacity);

void getStopWords(char *ignoreWordFileName, string ignoreWords[]);

bool isStopWord(string word, string ignoreWords[]);

int getTotalNumberNonStopWords(wordItem list[], int length);

void arraySort(wordItem list[],int length);

void printTopN(wordItem wordItemList[], int length);

int main(int argc, char *argv[])
{
    if (argc<4){
        cout<<"Error: not enough input arguments!"<<endl;
    }

    if (argc>4){
        cout<<"Error: too many input arguments!"<<endl;
    }

    int N=stoi(argv[1]);
    string fileName=argv[2];

    int capacity = 50;
    int lineNumber=0;
    string ignoreWords_[50];
    string ignoreFileName=argv[3];
    string line;
    string line_;
    string *_wordsNoStruct = new string[capacity];
    wordItem arrayOfWords[capacity];

    ifstream ignoreFile(ignoreFileName);
    int k=0;
    while(getline(ignoreFile,line_)){
        ignoreWords_[k]=line_;
        //cout<<line_<<endl;
        k++;
    }

    ifstream myFile(fileName);

    while(getline(myFile,line, ' ')){
        if(lineNumber>=(capacity-1)){
            cout<<"testing";
            arrayOfWords=getBiggerArray(arrayOfWords,capacity);
            capacity=2*capacity;
        }
        else{
                cout<<lineNumber<<endl;
                arrayOfWords[lineNumber].word=line;
                cout<<arrayOfWords[lineNumber].word<<endl;
                lineNumber++;
            }
    }



    lineNumber--;
    for(int j=0; j<lineNumber; j++){
        
        if(!isStopWord(_wordsNoStruct[j],ignoreWords_)){
            for(int i=0; i<(j+1);i++){
                if(_wordsNoStruct[j]==arrayOfWords[i].word){
                    arrayOfWords[i].count=arrayOfWords[i].count+1;
                    cout<<arrayOfWords[j].word;
                }
            }
            arrayOfWords[j].word=_wordsNoStruct[j];
            arrayOfWords[j].count=1;
            cout<<arrayOfWords[j].word;
        }
    }







    return 0;



}
string *getBiggerArray(string *oldArray, int oldCapacity)
{   
    string *newArray = new string [oldCapacity*2];// dynamically allocate an array of size 2 * oldCapacity

    for (int i=0; i<= oldCapacity; i++){
        newArray[i] = oldArray[i];
    }

    delete [] oldArray;
    return newArray;
}

void getStopWords(char *ignoreWordFileName, string ignoreWords[]){

	string line;

	ifstream myFile(ignoreWordFileName);
	int i=0;

	while (getline(myFile,line)&& (i<51)){
		ignoreWords[i]=line;
		i++;
	}
}

bool isStopWord(string word, string ignoreWords[]){
	for (int i=0; i<51; i++){
		if (word==ignoreWords[i]){
			return true;
		}		
	}
	return false;
}

int getTotalNumberNonStopWords(wordItem list[], int length)
{
    int total=0;
    for(int i=0; i<length; i++)
    {
        total=total+list[i].count;
        
    }
    return total;
}

void arraySort(wordItem list[], int length)
{
    wordItem newArray[length];
    int temp;
    int ind;
    int j=0;
    string tempWord;
    while (j<length){
    for(int i=0; i<length; i++){
        if(list[i].count>temp){
            temp=list[i].count;
            ind=i;
            tempWord=list[i].word;
        }
    }
        newArray[j].count=temp;
        newArray[j].word=tempWord;
        list[ind].count=0;
        temp=0;
        j++;
    }
    for(int k=0; k<length; k++){
        list[k].count=newArray[k].count;
        list[k].word=newArray[k].word;
    }
}

void printTopN(wordItem wordItemList[], int topN)
{
    for(int i=0; i<topN; i++){
        cout<<wordItemList[i].count<<" - "<<wordItemList[i].word<<endl;
    }
}