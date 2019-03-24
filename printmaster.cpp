#include <stdio.h>
#include <string>

#include "loging.cpp"
Loging logTfile;
#include "fileDirector.cpp"

using namespace std;

class PrintMaster{
private:
	string printerPdfs;
	string printerName;
	int time;

public:
	PrintMaster(string printerPdfs, string printerName, int time, bool logingf)
	/* printedPdfs - path to printed pdf with be print on printer
	 * peinterName - name of CUPS printer
	 * time - time sleep between search new pdf's to print in decyseconds (1s = 10ds)
	 * loging - saving in log file
	*/
	: printerPdfs(printerPdfs)
	, printerName(printerName)
	, time(time)
	{
		logTfile.setStateLoging(logingf);
	}

	void run(){
		logTfile.addNewLine("testString");
		FileDirector fd;
		fd.test();
	}

};
