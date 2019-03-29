#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;


MovieTree::MovieTree() {
	MovieNode* root;
	root = NULL;//new MovieNode;
	root->parent = NULL;
	root->leftChild = NULL;
	root->rightChild = NULL;
	root->ranking = 0;
	root->title = "";
	root->year = 0;
	root->quantity = 0;
	this->root=root;
}

void Delete(MovieNode *root)
{
	if (root->leftChild != NULL)
	{
		Delete(root->leftChild);
	}
	if (root->rightChild != NULL)
	{
		Delete(root->rightChild);
	}
	//cout << "Deleting: " << node->title << endl;
	
	delete root;
}

MovieTree::~MovieTree(){
	Delete(root);
}


MovieNode* MovieTree::search(string title)
{
	MovieNode *temp = new MovieNode;
	temp = root;
	
	while (temp != NULL)
	{
		if (title.compare(temp->title)==0) //returns the pointer to the desired node when title is found in it
		{
			return temp;
		}
		else if (title.compare(temp->title)<0) //searches the left child node
		{
			if (temp->leftChild == NULL) 
			{
				temp = NULL;
			}
			else
			{
				temp = temp->leftChild;
			}
		}	
		else if (title.compare(temp->title)>0) //searches the right child node
		{
			if (temp->rightChild == NULL)
			{
				temp = NULL;
			}
			else
			{
				temp = temp->rightChild;
			}
		}
	}
	return temp;
}

void deleteMovie(string title){
	MovieNode* temp = MovieTree::search(title);
	Delete(temp);
}


void MovieTree::addMovieNode(int ranking, string title, int year, int quantity)
{
	MovieNode* temp = search(title);
	MovieNode* newNode=new MovieNode;
	newNode->leftChild=NULL;
	newNode->rightChild=NULL;
	newNode->parent=NULL;
	newNode->ranking=ranking;
	newNode->title=title;
	newNode->year=year;
	newNode->quantity=quantity++;
	if(this->root==NULL){
		root=newNode;
		return;
	}

	else if(temp){
		return;
	}

	else{
		temp=this->root;
		while(temp!=NULL){
			if(newNode->title.compare(temp->title)<0){
				if(temp->leftChild!=NULL){
					temp=temp->leftChild;
				}
				else{
					temp->leftChild=newNode;
					newNode->parent=temp;
					temp=NULL;
				}
			}
			else{
				if(temp->rightChild != NULL)
                {
                    temp = temp->rightChild;
                }
                else
                {
                    temp->rightChild=newNode;
                    newNode->parent=temp;
                    temp=NULL;
                }
			}
		}
	}	
}

void printMovieInventory_(MovieNode *node)
{
    if(node->leftChild != NULL)
    {
        printMovieInventory_(node->leftChild);
    }
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;
    if(node->rightChild != NULL)
    {
        printMovieInventory_(node->rightChild);
    }
}

void MovieTree::printMovieInventory(){
	if(this->root==NULL)
		return;
	printMovieInventory_(this->root);
}



void MovieTree::findMovie(string title)
{
    MovieNode *temp = search(title);

    if(temp == NULL)
    {
        cout<<"Movie not found."<<endl;
    }
    else{
    
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << temp->ranking << endl;
        cout << "Title:" << temp->title << endl;
        cout << "Year:" << temp->year << endl;
        cout << "Quantity:" << temp->quantity << endl;
    }
}

void MovieTree::rentMovie(string title)
{
	MovieNode * temp=search(title);

	if(temp==NULL){
			cout<<"Movie not found."<<endl;
			return;
		}
	else if(temp->quantity==0){
		cout<<"Movie out of stock.";
		return;
	}

	else{
		temp->quantity--;
		cout<<"Movie has been rented."<<endl;
	}
	findMovie(title);
}


int main(int argc, char const *argv[])
{
	string name=argv[1];
    ifstream myFile(name.c_str());
    MovieTree obj;
    string line;

    while(getline(myFile, line))
    {
        stringstream ss(line);
        string Ranking;
        string Title;
        string Year;
        string Quantity;
        unsigned int ranking_;
        unsigned int year_;
        unsigned int quantity_;
        
        getline(ss, Ranking, ',');
        getline(ss, Title, ',');
        getline(ss, Year, ',');
        getline(ss, Quantity, ',');

        quantity_=stoi(Quantity);
        year_=stoi(Year);
        ranking_=stoi(Ranking);

        obj.addMovieNode(ranking_, Title, year_, quantity_);
    }


    int choice = 0;

    while(choice != 4)
    {
        cout<<"======Main Menu======"<<endl;
        cout<<"1. Find a movie"<<endl;
        cout<<"2. Rent a movie"<<endl;
        cout<<"3. Print the inventory"<<endl;
        cout<<"4. Quit"<<endl;

       
        cin>>choice;
        
        switch(choice)
        {
            case 1:
            {
                cin.ignore();
                string titleInput;
                cout << "Enter title:" << endl;
                getline(cin, titleInput);
    
                obj.findMovie(titleInput);
                choice = 1;
                break;
            }
            case 2:
            {
                cin.ignore();
                string titleInput;
                cout<<"Enter title:"<<endl;
                getline(cin, titleInput);
                obj.rentMovie(titleInput);
                break;
            }
            case 3:
            {
                obj.printMovieInventory();
                break;
            }
            case 4:
            {
                cout<<"Goodbye!"<<endl;
                break;
            }
            default:
            {
                cout<<"Please enter a number between 1 and 4: "<<endl;
                break;
            }

        }
    }

	return 0;
}
