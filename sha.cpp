/*----------------sha256-----------*/
#include "sha256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hash(char *, char *);
char * getText(void);

void main(){
	char texthash[2*SHA256_BLOCK_SIZE+1]; // all sha256 are 2*32(=64) bit long + 1 bit for '\0' at the end
	char * mystr = getText();
	hash(mystr, texthash); // filles texthash with sha256 of getText()
	printf("sha 256 of \"%s\" is :. \n%s", mystr, texthash);
}

char * getText(){ // get an unknown length char array
    char * str = (char *) malloc(sizeof(char));
	int lastIndex = 0;
	int c;
	while((c = getchar()) != '\n')
	{
		str = (char *) realloc((void *) str, (sizeof(str) + sizeof(char)));
		str[lastIndex++] = c;
	}
	str[lastIndex] = '\0';
	return str;
}
	

void hash(char * textregular, char * buffer){ // buffer is String (printable) form of the raw hash - printf((const char*)rawHash); is nonsense
	
	Sha256* generator =new Sha256();
	BYTE rawHash[SHA256_BLOCK_SIZE];
	BYTE * text = (BYTE *) textregular; // use char * as BYTE * (witch is actually unsigned char * so no data is lost)
	
	(*generator).update(text, strlen((const char*)text)); // prepare generator
	(*generator).final(rawHash); // actual hash algoritem and put hash in rawhash
	
	
	
	for(int i=0; i<SHA256_BLOCK_SIZE; ++i)
	  sprintf(buffer+2*i, "%02X", rawHash[i]); // prefix every number with 0 and append to buffer
}