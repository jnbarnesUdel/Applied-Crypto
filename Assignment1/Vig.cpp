/*
 * Ceas.cpp
 *
 *  Created on: Feb 11, 2020
 *      Author: Patrick
 */

#include "Vig.hpp"

#include<string>
#include<iostream>
using namespace std;

string enc (string pt, string k, int len){
	string ctx = "";
	int count = 0;
	for(char c : pt){
		ctx += char(((int)c + (int)k[count]) % 26 + (int)'A');
		count = (count + 1) % len;
	}
	return ctx;
}

string dec (string ct, string k, int len){
	string ptx = "";
	int count = 0;
	for(char c : ct){
		int num = (int)c - (int)k[count];
		if (num >= 0){
			ptx += char((num) % 26 + (int)'A');
		}
		else{
			ptx += char(num + 26 + (int)'A');
		}
		count = (count + 1) % len;
	}
	return ptx;
}

Vig::Vig(){
	string pt = "APPLIEDCRYPTO";
	string key = "NEKT";
	pt = enc(pt, key, 4);
	cout << "Ctxt: " << pt << endl;
	pt = dec(pt, key, 4);
	cout << "Ptxt: " << pt << endl;

	cout << endl;
	pt = "VIGENERECIPHER";
	pt = enc(pt, key, 4);
	cout << "Ctxt: " << pt << endl;
	pt = dec(pt, key, 4);
	cout << "Ptxt: " << pt << endl;

	cout << endl;
	pt = "WINDOWS";
	pt = enc(pt, key, 4);
	cout << "Ctxt: " << pt << endl;
	pt = dec(pt, key, 4);
	cout << "Ptxt: " << pt << endl;

	cout << endl;
	pt = "MICROSOFT";
	pt = enc(pt, key, 4);
	cout << "Ctxt: " << pt << endl;
	pt = dec(pt, key, 4);
	cout << "Ptxt: " << pt << endl;

	cout << endl;
	pt = "TOOTHBRUSH";
	pt = enc(pt, key, 4);
	cout << "Ctxt: " << pt << endl;
	pt = dec(pt, key, 4);
	cout << "Ptxt: " << pt << endl;
}
