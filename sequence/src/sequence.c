/*
 ============================================================================
 Name        : Mmn11.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#define MAX 101

int main() {
	int i=1;
	while(i){
	printf("Please enter you'r string\n");
	char str[MAX];
	scanf("%s",str);
	f_sequence(str);
	printf("\nif you want to continue press 1 or 0 to close the program\n");
	scanf("%d",&i);
}
	return 0;
}
void f_sequence(char str[]){
	if(isAbsoluteBigger(str)){
		printf("%s is an absolute bigger sorted",str);
	}else{
		if(isBigger(str)){
			printf("%s is an bigger sorted",str);
		}else{
			if(isAbsoluteSmaller(str)){
				printf("%s is an absolute smaller sorted",str);
			}else{
				if(isSmaller(str)){
					printf("%s is an smaller sorted",str);
				}else{
					printf("%s is a randomally sorted",str);
				}
			}
		}
	}
}
int isAbsoluteBigger(char str[]){
	int j,i=0;
	while(str[i]!='\0'){
		j=i+1;
		while(str[j]!='\0'){
			if(str[i]<=str[j]){
				return 0;
			}
			j++;
		}
		i++;
	}
	return 1;
}

int isBigger(char str[]){
	int j,i=0;
		while(str[i]!='\0'){
			j=i+1;
			while(str[j]!='\0'){
				if(str[i]<str[j]){
					return 0;
				}
				j++;
			}
			i++;
		}
		return 1;
	}

int isAbsoluteSmaller(char str[]){
	int j,i=0;
		while(str[i]!='\0'){
			j=i+1;
			while(str[j]!='\0'){
				if(str[i]>=str[j]){
					return 0;
				}
				j++;
			}
			i++;
		}
		return 1;
	}

int isSmaller(char str[]){
	int j,i=0;
		while(str[i]!='\0'){
			j=i+1;
			while(str[j]!='\0'){
				if(str[i]>str[j]){
					return 0;
				}
				j++;
			}
			i++;
		}
		return 1;
	}
