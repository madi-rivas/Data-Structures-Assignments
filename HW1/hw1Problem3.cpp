#include <iostream>
#include <string>

using namespace std;

class Movie
{
public:
	Movie(string myTitle, int myYear, float newRating);
	Movie();
	string getTitle();
	void setTitle(string newTitle);
	void setTitle();

	int getYear();
	void setYear(int newYear);
	void setYear();

	float getRating();
	void setRating(float newRating);
	void setRating();

private:
	std::string Title;
	int Year;
	float Rating;
	
};

Movie::Movie(string myTitle, int myYear, float myRating)
{
	Title=myTitle;
	Year=myYear;
	Rating=myRating;
}

Movie::Movie()
{
	Title="Unknown";
	Year=2018;
	Rating=0.0;
}

void Movie::setTitle(string newTitle){
	Title=newTitle;
}
string Movie::getTitle(){
	return Title;
}

void Movie::setYear(int newYear){
	Year=newYear;
}
int Movie::getYear(){
	return Year;
}

void Movie::setRating(float newRating){
	Rating=newRating;
}
float Movie::getRating(){
	return Rating;
}

int main(int argc, char const *argv[])
{

	return 0;
}