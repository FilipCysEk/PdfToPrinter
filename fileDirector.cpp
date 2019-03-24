#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <errno.h>
#include <experimental/filesystem>
#include <vector>
#include <cstring>
#include <dirent.h>

using namespace std;
namespace fs = std::experimental::filesystem;

class FileDirector{
private:
	string path;
	error_code errFS;
	DIR *pdfsDir;
	struct dirent *ent;

	void prepareDirs();
	bool isPdf(char*);
public:
	FileDirector(string);
	vector<string> scanPrintedDir();

};

FileDirector::FileDirector(string path)
:path(path)
{
	logTfile.addNewLineL3("Path to pdf's set: " + path);

	prepareDirs();
}

void FileDirector::prepareDirs(){
	string temp = path + "/printed";
	int dirErr = mkdir(temp.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(-1 == dirErr){
		if(EEXIST != errno){
			logTfile.addNewLineL1("Error when creating dir for printing pdf's. App closed!");
			exit(1);
		}
		else{
			if(!fs::remove_all(temp.c_str())){
				logTfile.addNewLineL1("Error when emptying dir " + errFS.message() + ". App closed!");
				exit(1);
			}
			prepareDirs();
		}
	}
}

vector<string> FileDirector::scanPrintedDir(){
	if((pdfsDir = opendir(path.c_str())) != NULL){
		vector<string> pdfList;
		while((ent = readdir(pdfsDir)) != NULL){
			if(isPdf(ent->d_name)){
				pdfList.push_back(ent->d_name);
				fs::rename((path + '/' + ent->d_name).c_str(), (path + "/printed/" + ent->d_name).c_str(),errFS);

				if( errFS.value() != 0){
					logTfile.addNewLineL1("Error when copying file " + errFS.message() + ". App closed!");
					exit(3);
				}
				logTfile.addNewLineL3("Copied file: " + (string)(ent->d_name));
			}
		}

		return pdfList;
	}
	else{
		logTfile.addNewLineL1("Error when opening dir, when app runing. App closed!");
		exit(2);
	}
}

bool FileDirector::isPdf(char* fname){
	int len = strlen(fname);
	if(len > 5){
		if(fname[len-1] == 'f' && fname[len-2] == 'd' && fname[len-3] == 'p' && fname[len-4] == '.')
			return true;
	}
	return false;
}
