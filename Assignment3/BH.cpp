/*
 * BH.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: Jonathan Barnes
 */

#include<iostream>
#include <stdlib.h>
#include <string>         // std::string
#include "BH.hpp"
#include "AES.hpp"
#include <time.h>
using namespace std;
string encrypt(string plain, int k){
	unsigned char L[8];
	unsigned char R[8];
	unsigned char temp[8];
	int subkeys[40];	//2 bytes from rand(), need 5 subkeys 16 bytes each so 40 = (5 * 16) / 2
	srand(k);	//send key into psudo random number generator to get more keys
	unsigned int len = 0;

	for(int i = 0; i < 40; i++){	//generate subkeys
			subkeys[i] = rand();
		}

	for(int i = 0; i < 16; i++){//fill left and right array
		if(i < 8){
			L[i] = plain[i];
		}
		else{
			R[i - 8] = plain[i];
		}
	}

	AES aes(128); //from AES library

	for(int j = 0; j<5; j++){ //do 5 rounds of AES for feistle function (take 64 most sig bits)
		//using library for AES I found on Github
		//int kv = rand();
		unsigned char key[16];
		//cout << "encrypt: " << endl;
		for(int i =0; i<16; i++ ){ //fill in 16 byte subkey
			if(i < 2){
				key[i] = ((subkeys[j*8] >> (i * 8)) & 0b11111111);	//each subkeys value has 16 bits split into 2 sets of 8 and put into round key
			}
			else if(i < 4){
				key[i] = ((subkeys[j*8+1] >> ((i-2) * 8)) & 0b11111111);
			}
			else if(i < 6){
				key[i] = ((subkeys[j*8+2] >> ((i-4) * 8)) & 0b11111111);
			}
			else if(i < 8){
				key[i] = ((subkeys[j*8+3] >> ((i-6) * 8)) & 0b11111111);
			}
			else if(i < 10){
				key[i] = ((subkeys[j*8+4] >> ((i-8) * 8)) & 0b11111111);
			}
			else if(i < 12){
				key[i] = ((subkeys[j*8+5] >> ((i-10) * 8)) & 0b11111111);
			}
			else if(i < 14){
				key[i] = ((subkeys[j*8+6] >> ((i-12) * 8)) & 0b11111111);
			}
			else{
				key[i] = ((subkeys[j*8+7] >> ((i-14) * 8)) & 0b11111111);
			}
			//cout << i << ": "<< key[i] << " ";
		}
		unsigned int plainLen = 8;
		unsigned char *out = aes.EncryptECB(R, plainLen, key, len);
		//cout << "len: " << len << " sizeof(out): " << sizeof(out) << endl;
		for(int i = 0; i<8; i++){
			temp[i] = out[i+8];
		} //since aes outputs 128 bit and we want 64 most significant bits

		for(int i = 0; i < 8; i++){
			temp[i] = (L[i] ^ temp[i]);
			L[i] = R[i];
			R[i] = temp[i];
		}
		//temp = L xor F(R)
		//swap L and R
	}

	//one last flip of left and right
	for(int i = 0; i < 8; i++){
		temp[i] = L[i];
		L[i] = R[i];
		R[i] = temp[i];
	}

	for(int i = 0; i < 16; i++){//fill plain again to be sent back
		if(i < 8){
			plain[i] = L[i];
		}
		else{
			plain[i] = R[i - 8];
		}
	}

	return plain;
}

string decrypt(string plain, int k){
	unsigned char L[8];
	unsigned char R[8];
	unsigned char temp[8];
	int subkeys[40];	//2 bytes from rand(), need 5 subkeys 16 bytes each so 40 = (5 * 16) / 2
	srand(k);	//send key into psudo random number generator to get more keys
	unsigned int len = 0;

	for(int i = 0; i < 40; i++){	//generate subkeys
			subkeys[i] = rand();
		}

	for(int i = 0; i < 16; i++){//fill left and right array
		if(i < 8){
			L[i] = plain[i];
		}
		else{
			R[i - 8] = plain[i];
		}
	}

	AES aes(128); //from AES library

	for(int j = 0; j<5; j++){ //do 5 rounds of AES for feistle function (take 64 most sig bits)
		//using library for AES I found on Github
		//int kv = rand();
		unsigned char key[16];
		//cout << "decrypt: " << endl;
		for(int i =0; i<16; i++ ){ //fill in 16 byte subkey
			int k = 4 - j;//fill in subkeys in oposite order
			if(i < 2){
				key[15-i] = ((subkeys[k*8+7] & (0b1111111100000000 >> (i * 8))) >> ((1-i)*8));
			}
			else if(i < 4){
				key[15-i] = ((subkeys[k*8+6] & (0b1111111100000000 >> ((i-2) * 8))) >> ((3-i) * 8));
			}
			else if(i < 6){
				key[15-i] = ((subkeys[k*8+5] & (0b1111111100000000 >> ((i-4) * 8))) >> ((5-i) * 8));
			}
			else if(i < 8){
				key[15-i] = ((subkeys[k*8+4] & (0b1111111100000000 >> ((i-6) * 8))) >> ((7-i) * 8));
			}
			else if(i < 10){
				key[15-i] = ((subkeys[k*8+3] & (0b1111111100000000 >> ((i-8) * 8))) >> ((9-i) * 8));
			}
			else if(i < 12){
				key[15-i] = ((subkeys[k*8+2] & (0b1111111100000000 >> ((i-10) * 8))) >> ((11-i) * 8));
			}
			else if(i < 14){
				key[15-i] = ((subkeys[k*8+1] & (0b1111111100000000 >> ((i-12) * 8))) >> ((13-i) * 8));
			}
			else{
				key[15-i] = ((subkeys[k*8] & (0b1111111100000000 >> ((i-14) * 8))) >> ((15-i) * 8));
			}
			//cout << i << ": "<< key[i] << " ";
		}
		unsigned int plainLen = 8;
		unsigned char *out = aes.EncryptECB(R, plainLen, key, len);
		//cout << "len: " << len << " sizeof(out): " << sizeof(out) << endl;
		for(int i = 0; i<8; i++){
			temp[i] = out[i+8];
		} //since aes outputs 128 bit and we want 64 most significant bits

		for(int i = 0; i < 8; i++){
			temp[i] = (L[i] ^ temp[i]);
			L[i] = R[i];
			R[i] = temp[i];
		}
		//temp = L xor F(R)
		//swap L and R
	}

	//one last flip of left and right
	for(int i = 0; i < 8; i++){
		temp[i] = L[i];
		L[i] = R[i];
		R[i] = temp[i];
	}

	for(int i = 0; i < 16; i++){//fill plain again to be sent back
		if(i < 8){
			plain[i] = L[i];
		}
		else{
			plain[i] = R[i - 8];
		}
	}

	return plain;
}

string ctrDecrypt(string plain, int k, long long n){
	int c = 0;
	int ct = 0;
	long long count = 0;
	string r;
	//gonna use an iterator to count the size of text and decide how many subtexts we need
	for(std::string::iterator it = plain.begin(); it!=plain.end(); it++){
		if((ct % 16) == 0){
			c++;
		}
		ct++;
	}
	string temp;
	string toEncrypt;
	string holdEncrypt;
	for(int i = 0; i < c; i++){
		for(int j = 0; j< 16; j++){
			char thing = plain[j + i*16];
			temp += thing;
			if(j < 8){
				toEncrypt += (char)((n >> (j*8)) & 0b11111111);	//take one char at a time of
			}
			else{
				toEncrypt += (char) ((count >> ((j-8)*8)) & 0b11111111);
			}
			//cout << toEncrypt << endl;
		}
		holdEncrypt = encrypt(toEncrypt, k);
		for(int x = 0; x < 16; x++){
			r += holdEncrypt[x] ^ temp[x];
		}
		temp = "";
		toEncrypt = "";
		count++;
	}
	return r;
}

string ctrEncrypt(string p, int key, long long nonce){
	int c = 0;
	int ct = 0;
	long long count = 0;
	string r;
	//gonna use an iterator to count the size of text and decide how many subtexts we need
	for(std::string::iterator it = p.begin(); it!=p.end(); it++){
		if((ct % 16) == 0){
			c++;
		}
		ct++;
	}
	string temp;
	string toEncrypt;
	string holdEncrypt;
	for(int i = 0; i < c; i++){
		for(int j = 0; j< 16; j++){
			char thing = p[j + i*16];
			temp += thing;
			if(j < 8){
				toEncrypt += (char)((nonce >> (j*8)) & 0b11111111);	//take one char at a time of
			}
			else{
				toEncrypt += (char) ((count >> ((j-8)*8)) & 0b11111111);
			}
			//cout << toEncrypt << endl;
		}
		holdEncrypt = encrypt(toEncrypt, key);
		for(int x = 0; x < 16; x++){
			r += holdEncrypt[x] ^ temp[x];
		}
		temp = "";
		toEncrypt = "";
		count++;
	}
	return r;
}

string cbcEncrypt(string p, int key, long long IV){
	int c = 0;
	int ct = 0;
	string r;
	//gonna use an iterator to count the size of text and decide how many subtexts we need
	for(std::string::iterator it = p.begin(); it!=p.end(); it++){
		if((ct % 16) == 0){
			c++;
		}
		ct++;
	}
	string toEncrypt;
	string holdEncrypt = "";	//because IV is 0 first hold is ""
	for(int i = 0; i < c; i++){
		for(int j = 0; j< 16; j++){
			char thing = p[j + i*16] ^ holdEncrypt[j];	//xor plaintext with previous ciphertext
			toEncrypt += thing;
			//cout << toEncrypt << endl;
		}
		holdEncrypt = encrypt(toEncrypt, key);
		r += holdEncrypt;
		toEncrypt = "";
	}
	return r;
}

string cbcCSEncrypt(string p, int key, long long IV){
	int c = 0;
	int ct = 1;
	string r;
	string steal;
	//gonna use an iterator to count the size of text and decide how many subtexts we need
	for(std::string::iterator it = p.begin(); it!=p.end(); it++){
		if((ct % 16) == 0){
			c++;
		}
		ct++;
	}

	//here is where we find how many bytes to steal
	int toSteal = ct %16;

	string toEncrypt;
	string holdEncrypt = "";	//because IV is 0 first hold is ""
	for(int i = 0; i < c; i++){
		for(int j = 0; j< 16; j++){
			char thing = p[j + i*16] ^ holdEncrypt[j];	//xor plaintext with previous ciphertext
			toEncrypt += thing;
			//cout << toEncrypt << endl;
		}
		holdEncrypt = encrypt(toEncrypt, key);

		//do stealing
		if((i == (c-2)) && (toSteal != 0)){
			for(int i = toSteal-1; i >=0; i-- ){
				p += holdEncrypt[15 - i];	//add onto end of plaintext
			}
			holdEncrypt.erase(15 - toSteal);//remove it from output ciphertext
		}

		r += holdEncrypt;
		toEncrypt = "";
	}
	return r;
}


string cbcCSDecrypt(string p, int key, long long IV){
	int c = 0;
	int ct = 1;
	string r;
	string steal;
	//gonna use an iterator to count the size of text and decide how many subtexts we need
	for(std::string::iterator it = p.begin(); it!=p.end(); it++){
		if((ct % 16) == 0){
			c++;
		}
		ct++;
	}

	//here is where we find how many bytes to steal
	int toSteal = ct %16;

	string toEncrypt;
	string holdEncrypt = "";	//because IV is 0 first hold is ""
	for(int i = 0; i < c; i++){
		for(int j = 0; j< 16; j++){
			char thing = p[j + i*16] ^ holdEncrypt[j];	//xor plaintext with previous ciphertext
			toEncrypt += thing;
			//cout << toEncrypt << endl;
		}
		holdEncrypt = encrypt(toEncrypt, key);

		//do stealing
		if((i == (c-2)) && (toSteal != 0)){
			for(int i = toSteal-1; i >=0; i-- ){
				p += holdEncrypt[15 - i];	//add onto end of plaintext
			}
			holdEncrypt.erase(15 - toSteal);//remove it from output ciphertext
		}

		r += holdEncrypt;
		toEncrypt = "";
	}
	return r;
}


 BH::BH(){
	 srand(time(NULL));
	 string plain;
	 int key;
	 key = rand();	//get random key
	 cout << "Q2 A: " << endl;
	 plain = "Applied Crypto  ";
	 cout << "start: " <<  plain << endl;
	 plain = encrypt(plain, key);
	 cout << "encrypted: " << endl << plain << endl;
	 plain = decrypt(plain, key);
	 cout << "decrypted: " << endl << plain << endl;

	 cout << "Second Example " << endl;
	 plain = "Hello World     ";
	 cout << "start: " <<  plain << endl;
	 plain = encrypt(plain, key);
	 cout << "encrypted: " << plain << endl;
	 plain = decrypt(plain, key);
	 cout << "decrypted: " << plain << endl;


	 cout << endl << "Q2 B: " << endl;
	 long long nonce = 0;
	 for(int i = 0; i<8; i++){
		nonce = ((nonce << 16) | rand());
	 }

	 string p = "He that would make an acceptable present, will pitch upon something that is desired, sought for, and hard to be found; that which he sees nowhere else, and which few have; or at least not in that place or season; something that may be always in his eye, and mind him of his benefactor. If it be lasting and durable, so much the better; as plate, rather than money; statues than apparel; for it will serve as a monitor to mind the receiver of the obligation, which the presenter cannot so handsomely do.          ";

	 p = ctrEncrypt(p, key, nonce);
	 cout << "Encrypted version: " << endl << p << endl;
	 p = ctrDecrypt(p, key, nonce);
	 cout << "decrypted version: " << endl << p << endl;

	 cout << endl << "Q2 C: " << endl;
	 long long IV = 0;//shouldn't make it 0 or a constant for that matter because insecure but running low on time
	 cout << "original text is same as the last: " << endl << p << endl;
	 p = cbcEncrypt(p, key, IV);
	 cout << "encrypted: " << endl << p << endl;

	 p = "This is the new plaintext I hope you lik";
	 cout << endl << "Q2 D: " << endl;
	 cout << "start: " << endl << p << endl;
	 p = cbcCSEncrypt(p, key, IV);
	 cout << "encrypted: " << endl << p << endl;
	 p = cbcCSDecrypt(p, key, IV);
	 cout << "decrypted: " << endl << p << endl;

 }
