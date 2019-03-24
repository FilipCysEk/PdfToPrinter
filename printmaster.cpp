#include <stdio.h>
#include <string>
#include <unistd.h>

#include "loging.cpp"
static Loging logTfile;

#include "fileDirector.cpp"

using namespace std;

class PrintMaster{
private:
	string printerPdfs;
	string printerName;
	int time;

public:
	PrintMaster(string printerPdfs, string printerName, int time, int logingLevel)
	/* printedPdfs - path to printed pdf with be print on printer
	 * peinterName - name of CUPS printer
	 * time - time sleep between search new pdf's to print in decyseconds (1s = 10ds)
	 * logingLevel:
	 * 0 - no loging
	 * 1 - only errors
	 * 2 - log important things with start and shutdown
	 * 3 - loging all
	*/
	: printerPdfs(printerPdfs)
	, printerName(printerName)
	, time(time)
	{
		logTfile.setLogingLevel(logingLevel);
	}

	void run(){
		logTfile.addNewLineL2("App started. Printer: " + printerName);
		FileDirector fd(printerPdfs);

		while(1){
			fd.scanPrintedDir();
			usleep(time * 100000);
		}
	}

};
