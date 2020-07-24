//Jonathan Barnes

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

int power(int ex, int bs){
	int sum = 1;
	for(int i = 0; i < ex; i++){
		sum = sum * bs;
	}
	return sum;
}

void refreshPool(int seed, int a, int c, int m, int buf[]){
	buf[0] = seed;
	int p = power(m, 2);
	for(int i = 1; i<30; i++){
		buf[i] = ((buf[i-1] * a + c) % p);	//X(i) = (X(i-1) * a + c) % 2^m
	}
}


void refreshPoolBiased(int seed, int a, int c, int m, int buf[]){
	
}

int main(){
	srand(time(NULL));
	int fp = -1;
	char buffer[50] = {""};
	char bufferTemp[50] = {""};
	size_t len = 0;
	size_t result = 0;
	while(fp == -1){ //if it fails to open it will make fp -1
		fp = open("/dev/urandom", O_RDONLY);	//open dev random and save file pointer
	}
	while(len < sizeof(buffer)){
		result = read(fp, buffer + len, sizeof(buffer) - len);
		if(result < 0){
			printf("Read went bad! \n");
			return 3;
		}
		len += result;
	}
	close(fp);
	
	len = 0;
	while(len < sizeof(bufferTemp)){
		result = scanf("%s", bufferTemp);
		len += result; 
	}
	
	//combine the /dev/random and random.org bytes
	while(len > 0){
		buffer[len -1] = buffer[len-1] ^ bufferTemp[len-1];
		len = len - 1;
	}
	
	int rc = RAND_bytes(bufferTemp, sizeof(bufferTemp));
	unsigned long err = ERR_get_error();

	if(rc != 1) {
		printf("Bad STUFF");
		return 1;	//failed return 1
	}
	else{
		len = 50;
	}
	
	//combine in the openssl stuff
	while(len > 0){
		buffer[len -1] = buffer[len-1] ^ bufferTemp[len-1];
		len = len - 1;
	}
	len = 50;
	
	printf("\n This is the entropy pool calculated in part A: \n");
	for(int i = 0; i < 50; i++ ){
		printf("%c", buffer[i]);
	}
	printf("\n");
	//write to output file
	while(len > 0){
		fp = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC);
		result = write(fp, buffer, len);
		len -= result;
	}
	
	
	//now for part B
	//we will be using a linear congruential generator for this
	
	
	unsigned int seed = (int) buffer[0]; //init the entropy pool, can cycle it 50 times
	int a = 1664525;
	int c = 1013904223;
	int m = 16;
	int pool[30] = {0}; //pool will be 30 int's in size
	refreshPool(seed, a, c, m, pool);
	
	printf("first pool of bits generated psudorandom bits \n");
	for(int i = 0; i<30; i++){
		for(int j = 0; j<16; j++){
			printf("%d", ((pool[i] >>j) & 1));	//prints each bit one at a time
		}
	}
	
	//add a file to hold this output or someting also
	
	//Part C
	// I will make it 80% 0 by changing 60% of the 1's
	
	printf("\n Part C output after adding bias \n");
	int temp = 0;
	char arrC[30][16];

	for(int i = 0; i<30; i++){
		for(int j = 0; j<16; j++){
			temp = ((pool[i] >>j) & 1);
			if(temp == 1 && ((rand() % 10) < 6)){
				temp = 0;
			}
			arrC[i][j] = temp;
			printf("%d", temp);
			
		}
	}
	
	
	//Part D
	//only count on changes from 1 to 0 or 0 to 1 to get back to 50 50
	int prev = arrC[0][0];
	int current = 0;
	printf("\n Part D after adjusting to 50:50 \n");
	printf("%d", prev);
	
	for(int i = 0; i<30; i++){
		for(int j = 0; j<16; j++){
			current = arrC[i][j];
			if(current == 1 && prev == 0){
				printf("1");
			}
			else if(current == 0 && prev == 1){
				printf("0");
			}
			prev = current;
		}
	}
	
	
	return 0;
}