#include "HashTable.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



HashTable::HashTable(int size)
{
	hashTableSize=size;
	hashTable = new wordItem*[hashTableSize];
	for (int i = 0; i < hashTableSize; i++)
	{
		hashTable[i] = new wordItem;
		hashTable[i] = NULL;

	}
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
	const char* fileName = ignoreWordFileName;
	ifstream filestream(fileName);
	string word;
	int index = 0;
	while(filestream >> word)
	{
		this->vecIgnoreWords[index] = word;
		index++;
	}
}


bool HashTable::isStopWord(std::string word)
{
	for(int i=0; i<STOPWORD_LIST_SIZE; i++)
	{
		if(vecIgnoreWords[i]==word)
			return true;
	}
	return false;
}

bool HashTable::isInTable(std::string word)
{
	wordItem* ptr = new wordItem;
	ptr = searchTable(word);
	if(ptr==NULL)
		return false;
	else
		return true;
}


void HashTable::incrementCount(std::string word)
{
	wordItem* ptr = searchTable(word);
	ptr->count = ptr->count+1;
}


void HashTable::addWord(string word)
{
	if(isStopWord(word))
		return;
	if(searchTable(word)!=NULL)
	{
		incrementCount(word);
		return;
	}
	int index = getHash(word);
	wordItem* prev = NULL;
	wordItem* temp = hashTable[index];
	while (temp != NULL)
	{
	    prev = temp;
	    temp = temp->next;
	}
    temp = new wordItem;
    temp->count = 1;
    temp->word = word;
    temp->next = NULL;
    if (prev == NULL)
    {
        hashTable[index]= temp;
        return;
    }
    else
    {
        prev->next = temp;
        return;
    }
    incrementCount(word);
    temp->word = word;

}


int HashTable::getTotalNumberNonStopWords()
{
    int count = 0;
	wordItem* ptr = new wordItem;
	for(int i = 0; i<hashTableSize; i++)
	{
		ptr = hashTable[i];
		while(ptr!=NULL)
		{
		    count+=ptr->count;
		    ptr = ptr->next;
		}
	}

	return count;
	
}


int findMax(int n, wordItem** table, int size)
{
    cout<<"finding max..."<<endl;
	wordItem* temp;
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
				temp = temp->next;
			}
		}
	}
	
	for(int k=1; k<(n+1); k++)
		cout<<array[k].count<<" - "<<array[k].word<<endl;
}


void HashTable::printTopN(int n)
{
	wordItem* temp;
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
				temp = temp->next;
			}
		}
	}
	
	for(int k=1; k<(n+1); k++)
		cout<<array[k].count<<" - "<<array[k].word<<endl;

}


int HashTable::getNumUniqueWords()
{
    int count = 0;
	wordItem* ptr = new wordItem;
	for(int i = 0; i<hashTableSize; i++)
	{
		ptr = hashTable[i];
		while(ptr!=NULL)
		{
		    count++;
		    ptr = ptr->next;
		}
	}

	return count;
}

int HashTable::getNumCollisions()
{
	int words = getNumUniqueWords();
	int collisions = (words-hashTableSize);
}


int HashTable::getHash(string word)
{
	int hash = 5381;
	for(string::size_type c = 0; c < word.size(); c++)
		hash = hash*33 + c;
	hash = hash % hashTableSize;
	if(hash < 0)
		hash+=hashTableSize;
	return hash;
}


wordItem* HashTable::searchTable(std::string word)
{
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
    
    hashT.printTopN(N);
    
    cout << "#" << endl;
    cout << "Number of collisions: " << hashT.getNumCollisions() << endl;
    cout << "#" << endl;
    cout<< "Unique non-stop words: " << hashT.getNumUniqueWords() << endl;
    cout << "#" << endl;
    cout << "Total non-stop words: " << hashT.getTotalNumberNonStopWords() << endl;

    return 0;
}