/*
 * Semantic.cpp
 *
 *  Created on: Feb 22, 2020
 *      Author: Patrick
 */
#include <time.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include"Semantic.hpp"
using namespace std;

string Randomize(string k, int r){
	//would like to use an AES block cipher here but don't have a library for it so writing my own block cypher
	string ctxt = "";
	for(char c : k){
		int temp = (int)c | r;	//or the binary of the key with rand
		temp = temp ^ (int)c;	//xor temp with key
		ctxt += (char)temp;
	}

	//would like to have a longer DRBG to xor with ptxt but this is ok for now
	return ctxt;
}

Semantic::Semantic(){
	srand(time(NULL));
	int r = rand();
	int len = 0;
	int count = 0;
	string key = "RANDOM";
	string DRBG = "";

	string ptxt = "SEND IN THE UNITS";
	len = ptxt.length();
	DRBG = Randomize(key, r);
	string ctxt = "";
	while(count < len){
		for(char c : DRBG){
			if(count < len){
				ctxt += (char)((int)c ^ (int)ptxt[count]);
				count++;
			}
		}
	}
	count = 0;
	cout << "transmission 1 ptxt: " << ptxt << endl;
	cout << "transmission 1 ctxt: " << ctxt << endl;

	r = rand();	//get new rand for each new transmission
	ptxt = "THIS IS A SECRET TRANSMISSION";
	len = ptxt.length();
	DRBG = Randomize(key, r);
	ctxt = "";
	while(count < len){
		for(char c : DRBG){
			if(count < len){
				ctxt += (char)((int)c ^ (int)ptxt[count]);
				count++;
			}
		}
	}
	count = 0;
	cout << "transmission 2 ptxt: " << ptxt << endl;
	cout <<  "transmission 2 ctxt: " <<  ctxt << endl;


	r = rand();	//get new rand for each new transmission
	ptxt = "WE ARE THE WORLD";
	len = ptxt.length();
	DRBG = Randomize(key, r);
	ctxt = "";
	while(count < len){
		for(char c : DRBG){
			if(count < len){
				ctxt += (char)((int)c ^ (int)ptxt[count]);
				count++;
			}
		}
	}
	count = 0;
	cout << "transmission 3 ptxt: " << ptxt << endl;
	cout <<  "transmission 3 ctxt: " <<  ctxt << endl;

	r = rand();
	ptxt = "THE BEATLES WERE GOOD";
	len = ptxt.length();
	DRBG = Randomize(key, r);
	ctxt = "";
	while(count < len){
		for(char c : DRBG){
			if(count < len){
				ctxt += (char)((int)c ^ (int)ptxt[count]);
				count++;
			}
		}
	}
	count = 0;
	cout << "transmission 4 ptxt: " << ptxt << endl;
	cout <<  "transmission 4 ctxt: " <<  ctxt << endl;

	r = rand();
	ptxt = "ALL YOUR BASE ARE BELONG TO US";
	len = ptxt.length();
	DRBG = Randomize(key, r);
	ctxt = "";
	while(count < len){
		for(char c : DRBG){
			if(count < len){
				ctxt += (char)((int)c ^ (int)ptxt[count]);
				count++;
			}
		}
	}
	count = 0;
	cout << "transmission 5 ptxt: " << ptxt << endl;
	cout <<  "transmission 5 ctxt: " <<  ctxt << endl;


	//To prove it is different for each transmission I will transmit the same ptxt again
	//with the same key and get a different ctxt
	r = rand();
	ptxt = "THIS IS A SECRET TRANSMISSION";
	len = ptxt.length();
	DRBG = Randomize(key, r);
	ctxt = "";
	while(count < len){
		for(char c : DRBG){
			if(count < len){
				ctxt += (char)((int)c ^ (int)ptxt[count]);
				count++;
			}
		}
	}
	count = 0;
	cout << "Retrans same ptxt: " << ptxt << endl;
	cout <<  "New ctxt ctxt: " <<  ctxt << endl;

}



