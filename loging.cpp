#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class Loging{
private:
	string logPath;
	bool enabled;

public:
	Loging();
	void setStateLoging(bool state){
		enabled = state;
	}

	void test(){
		printf("Test comunicate\n");
	}

	/*void addNewLine(string text){
		printf("%s\n", text.c_str());
		//cout<<text<<endl;
	}*/
	void addNewLine(string);
};
Loging::Loging(){
	enabled = 1;
}

void Loging::addNewLine(string text){
	cout<<enabled << " - ";
	printf("%s\n", text.c_str());
	//cout<<text<<endl;
}
