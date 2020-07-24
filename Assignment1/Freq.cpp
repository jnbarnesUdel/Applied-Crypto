/*
 * Freq.cpp
 *
 *  Created on: Feb 21, 2020
 *      Author: Patrick
 */
#include<iostream>
#include<fstream>
#include <stdlib.h>
#include <string>         // std::string
#include <locale>         // std::locale, std::tolower
#include "Freq.hpp"
using namespace std;

Freq::Freq(){
	string line;
	locale loc;
	float arr[26] = {0};
	int count = 0;
	ifstream myfile ("example.txt");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
		  for(char c : line){
			  c = tolower(c, loc);
			  int num = (int) c - 97;
			  if((int) num < 25 && num >=0){
				  arr[num]++;
				  count++;
			  }

		  }
		}
		cout << endl << "FREQ:" << endl;
		for(int i = 0; i<26; i++){
			cout << (char)(i + (int)'A') << ": "<< (arr[i]/count) * 100<< "%" << endl;
		}
		myfile.close();
	  }

	  else cout << "Unable to open file";
}



