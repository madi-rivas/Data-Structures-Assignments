// ==========================================
// File: Assignment 3 starter code
// Author: Madison Rivas
// Date: 1/29/2018
// Modified: Matt Bubernack
// Fall 2018 S. Gupta
// Description: Linked List Fun
// ==========================================
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

// DO NOT MODIFY THIS STRUCT
struct city
{
  string name; // name of the city
  city *next; // pointer to the next city
  int numberMessages; // how many messages passed through this city
  string message; // message we are sending accross
};

/* Function prototypes */
city* addCity(city *head, city *previous, string cityName );
city* deleteCity(city *head, string cityName);
city* deleteEntireNetwork(city *head);
city* searchNetwork(city *head, string cityName);
city* loadDefaultSetup(city *head);
void transmitMsg(city *head, string receiver, string message);
void printPath(city *head);
void displayMenu();
city* handleUserInput(city *head);

/* Do NOT modify main function */
int main(int argc, char* argv[])
{
  // pointer to the head of our network of cities
  city *head = NULL;

  head = handleUserInput(head);
  printPath(head);
  head = deleteEntireNetwork(head);
  if (head == NULL)
  cout << "Path cleaned" << endl;
  else
  printPath(head);
  cout << "Goodbye!" << endl;
  return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param head: the start of the linked list
 * @return: the start of the linked list
 *
 * DO NOT MODIFY THIS FUNCTION
 */
city* handleUserInput(city *head)
{
  bool quit = false;
  string s_input;
  int input;
  // loop until the user quits
  while (!quit)
  {
    displayMenu();
    // read in input, assuming a number comes in
    getline(cin, s_input);
    input = stoi(s_input);
    switch (input)
    {
      // print all nodes
      case 1: //rebuild network
        head = loadDefaultSetup(head);
        printPath(head);
        break;

      case 2: // print path
        printPath(head);
        break;

      case 3: //message is read in from file
        {
          string cityReceiver;

          cout << "Enter name of the city to receive the message: "
          << endl;
          getline(cin, cityReceiver);
          cout << "Enter the message to send: " << endl;
          string message;
          getline(cin, message);

          transmitMsg(head, cityReceiver, message);
        }
        break;

      case 4:
        {
          string newCityName;
          string prevCityName;
          cout << "Enter a new city name: " << endl;
          getline(cin, newCityName);
          cout << "Enter the previous city name (or First): " << endl;
          getline(cin, prevCityName);
          // find the node containing prevCity
          city *tmp = NULL;
          if(prevCityName !="First")
          tmp = searchNetwork(head, prevCityName);
          // add the new node
          head = addCity(head, tmp, newCityName);
          printPath(head);
        }
        break;

      case 5: // delete city
        {
          string city;
          cout << "Enter a city name: " << endl;
          getline(cin, city);
          head = deleteCity(head, city);
          printPath(head);

        }
        break;

      case 6: // delete network
        head = deleteEntireNetwork(head);
        break;

      case 7: // quit
        quit = true;
        cout << "Quitting... cleaning up path: " << endl;
        break;

      default: // invalid input
        cout << "Invalid Input" << endl;
        break;
    }
  }
  return head;
}

/*
 * Purpose: Add a new city to the network
 * between the city *previous and the city that follows it in the network.
 * Prints: `prev: <city name> new: <city name>` when a city is added,
 * prints _nothing_ if the city is being added to the _first_ position in
 * the list.
 * @param head: pointer to start of the list
 * @param previous: name of the city that comes before the new city, or null if
 *    the city is being added to the first position
 * @param cityName: name of the new city
 * @return: pointer to first node in list
 */
city* addCity(city *head, city *previous, string cityName)
{

    // Only print this if previous is not NULL
    city *newCity = new city;
    newCity->name = cityName;

    if (previous != NULL)
    {
        cout << "prev: " << previous->name << " new: " << cityName << endl;
        newCity->next = previous->next;
        previous->next = newCity;
    }
    else
    {
        newCity->next = head;
        head = newCity;
    }

    return head;
}
/*
 * Purpose: Search the network for the specified city and return a pointer
 * to that node
 * @param head: head of the list
 * @param cityName: name of the city to look for in network
 * @return: pointer to node of cityName, or NULL if not found
 * @see addCity, deleteCity
 */
city *searchNetwork(city *head, string cityName)
{
  city *index=head;
  while(index!=NULL){
    if(index->name==cityName){
      return index;
    }
    index=index->next;
  }
  return NULL;
}

/*
 * Purpose: deletes all cities in the network starting at the head city.
 * @param head: head of list
 * @return: NULL as the list is empty
 */
city* deleteEntireNetwork(city *head)
{
	if(head==NULL){
		return head;
	}

	while(head!=NULL){
		cout << "deleting: " << head->name << endl;
		head=head->next;
		}

  // Return head, which should be NULL
   	cout << "Deleted network" << endl;
	return head;
}

/*
 * Purpose: transmit a message from city to city
 * @param head: pointer to head of the list
 * @param receiver: the name of the City to receive the message
 * @param message: the message to transmit*/
void transmitMsg(city *head, string receiver, string message)
{
  if(head == NULL)
  {
    cout << "Empty list" << endl;
    return;
  }

  city *sender;
  sender=head;
  while(sender->name!=receiver){
  	sender->numberMessages++;
	// Use the following output statements to print each node of the linked list:
	sender->message=message;
	cout << sender->name << " [# messages passed: " <<
	sender->numberMessages << "] received: " <<
	sender->message << endl;
	sender=sender->next;
	sender->message=message;
  }
    sender->numberMessages++;
    sender->message=message;
    cout << sender->name << " [# messages passed: " <<
    sender->numberMessages << "] received: " <<
    sender->message << endl;
 
}

/*
 * Purpose: delete the city in the network with the specified name.
 * @param head: first node in list
 * @param cityName: name of the city to delete in the network
 * @return: head node of list
 */
city* deleteCity(city *head, string cityName)
{

	city* ptr;
	city* ptr2;
	ptr=searchNetwork(head, cityName);

	if(ptr==NULL){
		// If the city dosn't exist, use this output statement:
  		cout << "City does not exist." << endl;
  		return NULL;

	}

	if(ptr!=head){
	ptr2=ptr->next;
	head->next=ptr2;
	return head;
	  
	}

	if(ptr==head){
	head=head->next;
	return head;
	}

  return head;
}

/*
 * Purpose: prints the current list nicely
 * @param head: head of list
 */
void printPath(city *head)
{
	cout << "== CURRENT PATH ==" << endl;
	city *ptr;
	ptr=head;
	while(ptr!=NULL){
		cout<<ptr->name<<" -> ";
		ptr=ptr->next;

	}
  if (head == NULL) {
    cout << "nothing in path" << endl;
  }

  // Add code here to print the network path.

  cout <<" NULL"<<endl<< "===" << endl;
}

/*
 * Purpose: populates the network with the predetermined cities
 * @param head: start of list
 * @return: head of list
 */
city* loadDefaultSetup(city *head)
{
    // Add code here to populate the LinkedList with the default values
	if(head!=NULL){
		deleteEntireNetwork(head);
	}
	city* ptr=new city;
	head=addCity(head, head, "New York");
	ptr=head;
	ptr=ptr->next;
	head=addCity(head, ptr, "Atlanta");
	ptr=head;
	ptr=ptr->next;
	ptr=ptr->next;
	head=addCity(head, ptr, "Dallas");
	ptr=head;
	ptr=ptr->next;
	ptr=ptr->next;
	ptr=ptr->next;
	head=addCity(head, ptr, "Denver");
	ptr=head;
	ptr=ptr->next;
	ptr=ptr->next;
	ptr=ptr->next;
	ptr=ptr->next;
	head=addCity(head, ptr, "Phoenix");
	ptr=head;
	ptr=ptr->next;
	ptr=ptr->next;
	ptr=ptr->next;
	ptr=ptr->next;
	ptr=ptr->next;
	head=addCity(head, ptr, "Los Angeles");
	ptr=head;
	while(ptr->next!=NULL){
		cout<<"prev: "<<ptr->name<<"  new: ";
		city*temp;
		temp=ptr->next;

		cout<<temp->name<<endl;
		ptr=ptr->next;
	}
	
 return head;
}

/* Purpose: displays a menu with options
 * DO NOT MODIFY THIS FUNCTION
 */
void displayMenu()
{
  cout << "Select a numerical option:" << endl;
  cout << "======Main Menu=====" << endl;
  cout << "1. Build Network" << endl;
  cout << "2. Print Network Path" << endl;
  cout << "3. Transmit Message" << endl;
  cout << "4. Add City" << endl;
  cout << "5. Delete City" << endl;
  cout << "6. Clear Network" << endl;
  cout << "7. Quit" << endl;
}