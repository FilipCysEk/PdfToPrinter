#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

class Loging{
private:
	string logPath;
	unsigned int level = 3;
	/*
	* 0 - no loging
	* 1 - only errors
	* 2 - log important things with start and shutdown
	* 3 - loging all
	*/

	time_t actTime;
	struct tm actTimeStr;

	void addNewLine(string);

public:
	Loging();
	void setLogingLevel(int);
	void addNewLineL1(string);
	void addNewLineL2(string);
	void addNewLineL3(string);
};
Loging::Loging(){
}

void Loging::setLogingLevel(int level){
	this->level = level;
}

void Loging::addNewLineL1(string text){
	if(level >=  1 && level != 0)
		addNewLine(text);
}

void Loging::addNewLineL2(string text){
	if(level >= 2 && level != 0)
		addNewLine(text);
}

void Loging::addNewLineL3(string text){
	if(level >=  3 && level != 0)
		addNewLine(text);
}

void Loging::addNewLine(string text){
	time(&actTime);
	actTimeStr = *localtime(&actTime);
	char temp[25];
	strftime(temp, 25, "[%Y-%m-%d] %H:%M:%S", &actTimeStr);
	printf("%s\t%s\n", temp, text.c_str());
}
