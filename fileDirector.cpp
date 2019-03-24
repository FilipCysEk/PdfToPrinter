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
	bool isNum(char);
	string repetableFileName(string);
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
				if(fs::exists((path + "/printed/" + ent->d_name).c_str())){
					pdfList.push_back(repetableFileName(ent->d_name));
				}
				else{
					pdfList.push_back(ent->d_name);
				}

				fs::rename((path + '/' + ent->d_name).c_str(), (path + "/printed/" + pdfList.back()).c_str(),errFS);

				if( errFS.value() != 0){
					logTfile.addNewLineL1("Error when copying file " + errFS.message() + ". App closed!");
					exit(3);
				}
				logTfile.addNewLineL3("Copied file: " + (string)(ent->d_name) + " as " + pdfList.back());
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

string FileDirector::repetableFileName(string name){
	string namecut[3];
	int len, i;
	while(fs::exists((path + "/printed/" + name).c_str())){
		len = name.length();
		namecut[2] = name.substr( len - 4);
		i = len - 4;
		for(--i; i >= 0; i--){
			if(!isNum(name[i])){
				break;
			}
		}

		namecut[0] = name.substr(0, i + 1);
		if(len - 4 - i - 1 > 0){
			namecut[1] = name.substr(i + 1, len - 4 - i - 1);
			//i now is temp;
			i = stoi(namecut[1]);
			i++;
			namecut[1] = to_string(i);

			name = namecut[0] + namecut[1] + namecut[2];
		}
		else
			name = namecut[0] + '0' + namecut[2];

		//logTfile.addNewLineL3("file: " + namecut[0] + " - " + namecut[1] + " -- " + namecut[2]);
	}
	return name;
}

bool FileDirector::isNum(char ch){
	if(ch >= '0' && ch <= '9')
		return true;

	return false;
}
