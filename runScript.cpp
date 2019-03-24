#include <stdio.h>
#include "printmaster.cpp"

int main(){
	PrintMaster master("/home/cysiu/Dokumenty/Printer script", "Lexmark E320", 20, 3);
	master.run();

}
