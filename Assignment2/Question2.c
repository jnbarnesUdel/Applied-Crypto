//Jonathan Barnes
//Question 2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <time.h>

int fourBitMod(int b1, int b2, int b3, int b4){
	return (b1 + b2 + b3 + b4) %2;
}
int seed(int *arr){
	for(int i = 0; i<16; i++){
		arr[i] = rand() % 2;
		//printf("%d \n", arr[i]);
	}
}

void sixteenBit(int *arrIn, int *arrOut){
	
	arrOut[0] = fourBitMod(arrIn[10], arrIn[12], arrIn[13], arrIn[15]);
	for(int i = 1; i<16; i++){
		arrOut[i] = arrIn[i-1];
	}
}

void undo(int *arrIn, int *arrOut){
	arrOut[15] = fourBitMod(arrIn[0], arrIn[11], arrIn[13], arrIn[14]);	//have to undo the xoring that happened before and put on the end
	for(int i = 0; i<15; i++){
		arrOut[i] = arrIn[i+1];	//shift to the left
	}
}

int main(){
	srand(time(NULL));
	int b1, b2, b3, b4;
	int in[16];
	int out[16];
	int p = 0;
	int save = 0;
	b1 = 1;
	b2 = 0;
	b3 = 0;
	b4 = 1;
	printf("part 1 : \n sample data = 1001 \n output of func = %d", fourBitMod(b1, b2, b3, b4));
	seed(in);
	
	printf("\n part 3 output generating 20 numbers \n");
	for(int i = 0; i<20; i++){
		sixteenBit(in, out);
		p = 0;
		for(int j = 0; j <16; j++){
			in[j] = out[j];
			//printf("%d", out[j]);
			p = (p << 1) | out[j];
		}
		//printf("\n");
		if(i == 10){
			save = p;
		}
		printf("%u \n", p);
	}
	
	
	//not good random if you know where the xoring happens
	
	printf("Part 4 generating the previous numbers for %u, and the next five numbers in its sequence \n", save);
	
	printf("5 nums before %d \n", save);
	int temp = save;
	for(int x = 15; x >= 0; x--){
		in[x] = temp & 1;
		temp = temp >> 1;
	}
	
	for(int i = 0; i<5; i++){
		undo(in, out);
		p = 0;
		for(int j = 0; j <16; j++){
			in[j] = out[j];
			//printf("%d", out[j]);
			p = (p << 1) | out[j];
		}
		printf("%u \n", p);
	}
	
	printf("5 nums after %u \n", save);
	temp = save;
	for(int x = 15; x >= 0; x--){
		in[x] = temp & 1;
		temp = temp >> 1;
	}
	
	for(int i = 0; i<5; i++){
		sixteenBit(in, out);
		p = 0;
		for(int j = 0; j <16; j++){
			in[j] = out[j];
			//printf("%d", out[j]);
			p = (p << 1) | out[j];
		}
		printf("%u \n", p);
	}
	
}