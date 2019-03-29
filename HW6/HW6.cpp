#include <string>
#include "MovieTree.hpp"


MovieTree::MovieTree() {
	MovieNode* root;
	root = NULL;//new MovieNode;
}

void Delete(MovieNode *root)
{
    if (root!=NULL)
    {
        Delete(root->leftChild);
        Delete(root->rightChild);
        delete root;
    }
}

MovieTree::~MovieTree(){
	Delete(root);
}



MovieNode* MovieTree::search(string title)
{
	MovieNode *temp =root;
	
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

MovieNode* successor(MovieNode* node) 
{ 
    MovieNode* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->leftChild != NULL) 
        current = current->leftChild; 
  
    return current; 
}

MovieNode* delNode(MovieNode *root, string title)
{
  if(root == NULL)
  {
    cout<<"Movie not found."<<endl;
    return NULL;
  }
  // If value to be deleted is less than the root
  // Then we need to search in the left subtree
  else if(title < root->title)
  {
    root->leftChild = delNode(root->leftChild, title);
  }
  // If value to be deleted is greater than the root
  // Then we need to search in the right subtree
  else if(title > root->title)
  {
    root->rightChild = delNode(root->rightChild, title);
  }
  // We found the node with the value to be deleted
  else
  {
    //Case 1
    // Leaf node
    if(root->leftChild == NULL)
    {
		MovieNode *temp = root->rightChild; 
		delete root; 
		return temp; 
    }
    /*************************
      Case 2 - Node with one child
      Has a right child
      Complete this function
    *************************/
    else if(root->leftChild == NULL)
    {
      MovieNode *temp = root->rightChild;
      delete root; 
      return temp;
        // TODO
    }
    /*************************
      Case 2 - Node with one child
      Has a left child
      Complete this function
    *************************/
    else if(root->rightChild == NULL)
    {
      MovieNode *temp = root->leftChild; 
      delete root;  
      return temp;
        // TODO
    }
    /*************************
      Case 3 - Node with two children
      Complete this function
    *************************/
    else
    {
      MovieNode* temp = successor(root->rightChild);
      root->title = temp->title;
      root->quantity = temp->quantity;
      root->rightChild = delNode(root->rightChild, temp->title); 
        // TODO
    }

  }
return root;
}

void MovieTree::deleteMovie(string title) {
  root = delNode(root, title);
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
		cout<<"Movie not found.";
		return;
	}

	else{
		temp->quantity--;
		cout<<"Movie has been rented."<<endl;
	}
	findMovie(title);
}


int counter(MovieNode *root) {
	int num = 0;
	if(root != NULL) {
		num++;
		num=counter(root->leftChild)+num;
		num=counter(root->rightChild)+num;
	}
	return num;
}

void MovieTree::countMovies()
{
    int count=counter(root);
    cout<<"Count = "<<count<<endl;
}
