#include "HashTable.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



HashTable::HashTable(int size)
{
    //cout<<"jgfdrr";
	hashTableSize=size;
	hashTable = new wordItem*[hashTableSize];
	//cout<<"njugyu";
	for (int i = 0; i < hashTableSize; i++)
	{
		hashTable[i] = new wordItem;
		hashTable[i] = NULL;

	}
	//cout<<"huh";
}

HashTable::~HashTable()
{
	for(int i=0; i<hashTableSize; ++i)
	{
		wordItem* entry = hashTable[i];
		while(entry!=NULL)
		{
			wordItem* prev = entry;
			entry = entry->next;
			delete prev;
		}
	}

	delete[] hashTable;
}



void HashTable::getStopWords(char *ignoreWordFileName)
{
    //cout<<"getting stop words..."<<endl;
	const char* fileName = ignoreWordFileName;
	ifstream filestream(fileName);
	string word;
	int index = 0;
	while(filestream >> word)
	{
		this->vecIgnoreWords[index] = word;
		index++;
	}
	//cout<<"done"<<endl;
}


bool HashTable::isStopWord(std::string word)
{   
    //cout<<"is stop word..."<<endl;
	for(int i=0; i<STOPWORD_LIST_SIZE; i++)
	{
		if(vecIgnoreWords[i]==word)
			return true;
	}
    //cout<<"done"<<endl;
	return false;
}

bool HashTable::isInTable(std::string word)
{
    //cout<<"checking is in table..."<<endl;
	wordItem* ptr = new wordItem;
	ptr = searchTable(word);
	if(ptr==NULL)
		return false;
	else
		return true;
}


void HashTable::incrementCount(std::string word)
{
    //cout<<"incrementing..."<<endl;
	wordItem* ptr = new wordItem;
	ptr = searchTable(word);
	ptr->count = ptr->count+1;
	//cout<<ptr->word<<": "<<ptr->count<<endl;
}


void HashTable::addWord(std::string Word)
{
	//cout<<"adding words..."<<endl;
	if(isStopWord(Word))
		return;
   int index = getHash(Word);
   wordItem* temp = new wordItem;
   temp->word = Word;
   temp->count = 1;
   //hashTable[index]->word = Word;
   //hashTable[index]->count = 5;
   /*if(hashTable[index]->next==NULL){
   		hashTable[index]->next = temp;
   		//cout<<"added: "<<temp->word<<" count: "<<temp->count<<endl;
   		return;
   }*/
   if(isInTable(Word))
   {
   		incrementCount(Word);
   		temp = searchTable(Word);
   		//cout<<temp->word<<temp->count<<endl;
   		return;
   }
   else
   {
   		wordItem* ptr = hashTable[index];
   		if(hashTable[index]==NULL)
   		{
   			hashTable[index] = temp;
   			return;
   		}
   		while(ptr!=NULL)
   		{
   			ptr = ptr->next;
   		}
   		ptr = temp;
   		//cout<<"added: "<<ptr->word<<" count: "<<ptr->count<<endl;
   }
}


int HashTable::getTotalNumberNonStopWords()
{
    //cout<<"getting total number non stop words..."<<endl;
    int count = 0;
	wordItem* ptr = new wordItem;
	for(int i = 0; i<hashTableSize; i++)
	{
		ptr = hashTable[i];
		while(ptr!=NULL)
		{
			//cout<<ptr->word<<endl;
		    count += ptr->count;
		    ptr = ptr->next;
		}
	}

	return count;
	
}


int findMax(int n, wordItem** table, int size)
{
    cout<<"finding max..."<<endl;
	wordItem* temp = new wordItem;
	int max=0;
	wordItem array[n+1];
	array[0].count=999999999;
	for(int k=1; k<(n+1); k++)
		array[k].count=0;
	for(int i=1; i<(n+1); i++)
	{
	    max = 0;
		for(int j=0; j<(size); j++)
		{
		    temp = table[j];
		    while(temp!=NULL)
			{
				if(array[i].count < temp->count && temp->count < array[i-1].count)
				{
					array[i].count = temp->count;
		        	array[i].word = temp->word;
				}
				//cout<<temp->word<<temp->count<<endl;
				temp = temp->next;
			}
		}
	}
	
	for(int k=1; k<(n+1); k++)
		cout<<array[k].count<<" - "<<array[k].word<<endl;
}


void HashTable::printTopN(int n)
{
	wordItem* temp = new wordItem;
	int max=0;
	wordItem array[n+1];
	array[0].count=999999999;
	for(int k=1; k<(n+1); k++){
		array[k].count=0;
	}

	for(int i=1; i<(n+1); i++)
	{
	    max = 0;
		for(int j=0; j<(hashTableSize); j++)
		{
		    temp = hashTable[j];
		    while(temp!=NULL)
			{
				if(array[i].count < temp->count && temp->count < array[i-1].count)
				{
					array[i].count = temp->count;
		        	array[i].word = temp->word;
				}
				//cout<<temp->word<<temp->count<<endl;
				temp = temp->next;
			}
		}
	}
	
	for(int k=1; k<(n+1); k++)
		cout<<array[k].count<<" - "<<array[k].word<<endl;

}


int HashTable::getNumUniqueWords()
{
    //cout<<"getting num unique words..."<<endl;
	int count;
	wordItem* temp = new wordItem;
	for(int i=0; i<hashTableSize; i++)
	{
		temp = hashTable[i];
		while(temp!=NULL){
			temp = temp->next;
			count = count+1;
		}
	}
	return count;
}

int HashTable::getNumCollisions()
{
    //cout<<"getting num collisions..."<<endl;
	int words = getNumUniqueWords();
	int collisions = (words-hashTableSize);
}


int HashTable::getHash(string word)
{
    //cout<<"getting hash..."<<endl;
	int hash = 5381;
	for(string::size_type c = 0; c < word.size(); c++)
		hash = hash*33 + c;
	hash = hash % hashTableSize;
	if(hash < 0)
		hash+=hashTableSize;
	//cout<<"done"<<endl;
	//cout<<hash<<endl;
	return hash;
}


wordItem* HashTable::searchTable(std::string word)
{
    //cout<<"searching table..."<<endl;
	int index = getHash(word);
	wordItem* temp = hashTable[index];
	while(temp!=NULL){
		if(temp->word == word)
			return temp;
		temp = temp->next;
	}
	return NULL;


}







int main(int argc, char** argv)
{
    HashTable hashT(stoi(argv[4]));

    int N = stoi(argv[1]);
    string fileName = argv[2];
    char* stopFile = argv[3];

    hashT.getStopWords(stopFile);
    ifstream myFile(fileName);

    string line;

    while(getline(myFile, line))
    {
        stringstream ss(line);
        string word;
        while(ss >> word) {
            hashT.addWord(word);
        }
    }
    //cout<<"done adding"<<endl;


    
    hashT.printTopN(N);
    
    cout << "#" << endl;
    cout << "Number of collisions: " << hashT.getNumCollisions() << endl;
    cout << "#" << endl;
    cout<< "Unique non-stop words: " << hashT.getNumUniqueWords() << endl;
    cout << "#" << endl;
    cout << "Total non-stop words: " << hashT.getTotalNumberNonStopWords() << endl;

    return 0;
}