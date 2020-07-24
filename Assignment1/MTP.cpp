/*
 * MTP.cpp
 *
 *  Created on: Feb 23, 2020
 *      Author: Patrick
 */
#include "MTP.hpp"
#include <time.h>
#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;

//this function takes in 10 ciphertexts and creates an array/histogram of the different letters gibven from xoring each of them with the first
//this will allow me to create the plaintext
void decoder(long long a[], long long b[], long long c[], long long d[], long long e[], long long f[], long long g[], long long h[], long long x[], long long y[]){
	int thing = 0;
		string ptx1[100] = {""};
		string out = "";
		for(int i =0; i < 9; i++){	//go through all the hex
			for(int j=0; j<8 ; j++){	//break up long long into chars
				thing = ((a[i] ^ b[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and two: " << endl;
		cout << out << endl << endl;

		out = "";
		for(int i =0; i < 9; i++){
			for(int j=0; j<8 ; j++){
				thing = ((a[i] ^ c[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and three: " << endl;
		cout << out << endl << endl;

		out = "";
		for(int i =0; i < 9; i++){
			for(int j=0; j<8 ; j++){
				thing = ((a[i] ^ d[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and four: " << endl;
		cout << out << endl << endl;

		out = "";
		for(int i =0; i < 9; i++){
			for(int j=0; j<8 ; j++){
				thing = ((a[i] ^ e[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and five: " << endl;
		cout << out << endl << endl;

		out = "";
		for(int i =0; i < 9; i++){
			for(int j=0; j<8 ; j++){
				thing = ((a[i] ^ f[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and six: " << endl;
		cout << out << endl << endl;

		out = "";
		for(int i =0; i < 9; i++){
			for(int j=0; j<8 ; j++){
				thing = ((a[i] ^ g[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and seven: " << endl;
		cout << out << endl << endl;

		out = "";
		for(int i =0; i < 9; i++){
			for(int j=0; j<8 ; j++){
				thing = ((a[i] ^ h[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and eight: " << endl;
		cout << out << endl << endl;

		out = "";
		for(int i =0; i < 9; i++){
			for(int j=0; j<8 ; j++){
				thing = ((a[i] ^ x[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and nine: " << endl;
		cout << out << endl << endl;

		out = "";
		for(int i =0; i < 9; i++){
			for(int j=0; j<8 ; j++){
				thing = ((a[i] ^ y[i]) >> (8 * j)) & 255;
				out += (char)(thing);
				if(thing > 65 && thing <90 ){
					ptx1[j+(i*8)] += (char)(thing);
					//cout << (char)thing << ": " << j+ (i*8) << endl;
				}
			}
		}
		thing = 0;
		cout << "one and ten: " << endl;
		cout << out << endl << endl;

		for(int i = 0; i<100; i++){
			cout << i << ": " << ptx1[i] << endl;
		}
}


MTP::MTP(){

	//In C++ I can't just set a variable equal to these hex things I have to make an array of long longs
	long long ctxt1[9] = {0X004e0c1c1c090c1a, 0X0d49081f001d1b45, 0X41430b0f10085406, 0X0d04450c12001506, 0X411d440c1d540854, 0X094f1011080c0b45, 0X551c0e1e1d121d45, 0X0106411706010d45, 0X0e0a451046};
	long long ctxt2[17] ={0X004e43131110040d, 0X1f49081f00081d00, 0X084e10041a154900, 0X0c0b094315430048, 0X030d001e1b490248, 0X500e1c54040c180c, 0x540b451106111608, 0X1e0012541d004e45, 0X1907441148164502, 0X060106171041070c, 0X1d18490100075704, 0X0b0a0017074f0505, 0X110b541d0e0c4501, 0X45021b1649155955, 0X1e0618490c1f000e, 0X135409451d0d1a17, 0X041947};
	long long ctxt3[9] = {0X0055171a000a1107, 0X170815054f075349, 0X120010091141501d, 0X0d09001007001b0e, 0X4102451b1a461849, 0X1e08521541010004, 0X491f45041a040745, 0X0f54120d1a1b0b4d, 0X4f034e0001115941};  //1c014f101012000c024e5207161b0217060b00090f534905450d111b12080c1c00001a10520842001a0c54560e0a55045b;
	long long ctxt4[9] = {0X0541171345070a00, 0X120005094e1d1a41, 0X0d4910185408534f, 0X1602004304521b18, 0X0406541053540941, 0X044f161515034c0c, 0X53520b1f0645170c, 0X1d170d1b1a0a0a00, 0X1b09000711165404}; //1e530a0d1d0800000a1d00170b181216164e54090b59490c04181149040c001c00001b10480e521c140c10001b09000a1b1b1f451a1c0c4305151d0e40;
	long long ctxt5[9] = {0X05411713450d0b1a, 0X110e130554105349, 0X120010091141501d, 0X0d1a00110059541c, 0X0915544917411541, 0X50071307410c0311, 0X001000151c45100d, 0X0f1a06110d434e44, 0X0a155406071c4505}; //5f530011490d1b1a1b4e490c45151945100041141a4806160c14110d4606175241020d0d44044e010f05544d0e084e04075a;
	long long ctxt6[9] = {0X11520a0404071c4e, 0X1d1a4118480c5352, 0X08470c15540e464f, 0X030445061a541d1c, 0X185800081054084e, 0X174f1b1a410b1816, 0X001d121e5207160d, 0X0f180758491b0100, 0X0b0354111a08490f}; //16531b0b0c41100c081c450745001845120649020600001045191d050a490c1c54041c0543150002071d1c0006125341101a1e0c1c1b070e041a1d434e49070d0a1a16040f13491b064900050b0352110d41004f43160649010d00041a00530000000c105946060100021a094c00004756111d491511081c0200081a534914001c07061a184c43050f0f0217094116104f0f4e570c1a1c491b0d48111a125a;
	long long ctxt7[9] = {0X137322520c17450f, 0X1a49000047060149, 0X15480941120e524f, 0X03191c0e1945001a, 0X0817000a01591154, 0X1f080015110a1549, 0X001b0b06170b0700, 0X0a54081a495e5717, 0X5846420d48374f0f}; //532106150c1200454f2f440b45271f040807524d4e410700452211060808171600200a08450c411b40;
	long long ctxt8[9] = {0X0055171a0a160c14, 0X151d08034e491a53, 0X41410a411511501d, 0X0d1c040f54541c09, 0X1554491a53471341, 0X1e1b171041160345, 0X4152160901111608, 0X4e110f00001b1700, 0X1b0900150b064512}; //00530e431a18071d0a03001000071810170d454f;
	long long ctxt9[9] = {0X0000001d1301171a, 0X540a090d4e07164c, 0X41491741150f001a, 0X0c030b17114e100d, 0X05544f1b53550f41, 0X051b1a1b130b1600, 0X44520c1e06171248, 0X1d0d12000c024e43, 0X07074e1a0d090015}; //1b121b430c0f150b030b53421103184506014f110b5208100c0013490307111b54080b1700154f551a1b154e1c004513551d060301060402151d06014e49074e074f050c18541d070f580017070b4c151c04070017090b00111c5304170854164e070007551406065955030a4c000d595607071d461d060b14000f015449011d0d110c1059540b09410c03110d540b1c53464e41060d111a075941011c091b52080e1511041f1a000e;
	long long ctxt10[9] ={0X0000001b150c001c, 0X000c19180d061d4c, 0X1800051500004304, 0X420316431500171a, 0X180454081d410d59, 0X0306015415070f0d, 0X4e1b140517451a0b, 0X4e03091d0a074e54, 0X0703001506044c18}; //00074f171b08111a4f1a4f42011103001703490f0b001d0c004e1f0c1f49161d4c04021d0007521a03491f4e00114c0411130d450112490a0f000c1d0d45191a030b520e0804010a1c0c540416100e;


	cout << "PTXT one: "<< endl;
	decoder(ctxt1, ctxt2, ctxt3, ctxt4, ctxt5, ctxt6, ctxt7, ctxt8, ctxt9, ctxt10);

	cout << "PTXT two: "<< endl;
	decoder(ctxt2, ctxt1, ctxt3, ctxt4, ctxt5, ctxt6, ctxt7, ctxt8, ctxt9, ctxt10);

	cout << "PTXT three: "<< endl;
	decoder(ctxt3, ctxt2, ctxt1, ctxt4, ctxt5, ctxt6, ctxt7, ctxt8, ctxt9, ctxt10);

	long long key[9] = {0};
	string sentanceCT1 = "f ib   or  obc unknown y being   denialof of on conditiy in themnonypit"; //what I think plaintext of ciphertext1 may be
	int temp = 0;
	for(int i = 0; i<9; i++){
		for(int j = 0; j<8; j++){
			temp += (int)sentanceCT1[(i*8)+j];
		}
		key[i] = ctxt1[i] ^ temp;
		temp = 0;
	}

	//xor hidden message ciphertext with key to get plaintext back
	long long hiddenMsg[12] = {0X084e43011c09080b, 0X001b080f000a0159, 0X11540b0606005007, 0X1b4a110b11001504, 0X061b520007480c53, 0X501a011141160400, 0X0001041d17451800, 0X1754071b1b4f0c4f, 0X1b0e001106065218, 0X0307060c07411507, 0X0b4e440706060e15, 0X11074f0f40};
	string output = "";
	int num = 0;
	for(int i =0; i<12; i++){
		for(int j=0; j<8 ; j++){
			if(i<9){
				num = ((hiddenMsg[i] ^ key[i]) >> (8 * j)) & 255;
			}
			else{
				num = ((hiddenMsg[i] ^ key[i - 9]) >> (8 * j)) & 255;
			}
			output += (char)(num);
		}
	}

	cout << "Final output: " << endl;	//original method of finding goal text

	//new method of trying to decrypt goal text
	decoder(hiddenMsg, ctxt1, ctxt3, ctxt4, ctxt5, ctxt6, ctxt7, ctxt8, ctxt9, ctxt10);
	decoder(hiddenMsg, ctxt1, ctxt2, ctxt4, ctxt5, ctxt6, ctxt7, ctxt8, ctxt9, ctxt10);


}
