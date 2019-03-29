#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



struct User{
    string username;
    float gpa;
    int age;
};

void addUser(vector<User> *users, string _username, float _gpa, int _age);

int main(int argc, char* argv[])
{
	if (argc!=2)
	{
		cout<<"Error";
		return 1;
	}


    ifstream myFile(argv[1]);
    User studentInfo1;
    studentInfo1.username;
    studentInfo1.gpa;
    studentInfo1.age;

    User studentInfo2;
    studentInfo2.username;
    studentInfo2.gpa;
    studentInfo2.age;

    string line;
    vector<User> vect;
    vector<User> *v = &vect;

    while(getline(myFile,line)){

        
        stringstream ss;
        ss<<line;
        string Name;
        string GPA;
        string Age;

        getline(ss, Name,',');
        studentInfo1.username=(Name);
        cout<<studentInfo1.username<<" ";
        getline(ss, GPA,',');
        studentInfo1.gpa=stof(GPA);
        cout<<"["<<studentInfo1.gpa<<"]"<<" ";
        getline(ss, Age,',');
        studentInfo1.age=stoi(Age);
        cout<<"age: "<<studentInfo1.age<<endl;
        addUser(v, studentInfo1.username, studentInfo1.gpa,studentInfo1.age);


    }
    return 0;
}


void addUser(vector<User> *users, string _username, float _gpa, int _age){
    (*users).push_back(_username);

}