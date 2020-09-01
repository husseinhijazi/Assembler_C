/*
 * header.h
 *
 *  Created on: Mar 11, 2020
 *      Author: USER
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct cpus{
	unsigned int r0:24;
	unsigned int r1:24;
	unsigned int r2:24;
	unsigned int r3:24;
	unsigned int r4:24;
	unsigned int r5:24;
	unsigned int r6:24;
	unsigned int r7:24;
	unsigned int PC:24;
}cpu;


#define null NULL
#define false 0
#define true 1
#define min -9999999

typedef struct errors{
	char* error;
	unsigned int ErrLine;
    struct errors *next;

}error;

typedef struct datas{
	struct dataWords* word;
    struct datas *next;

}data;

typedef struct dataWords{
	int word:24;
	char *isDataOrStr;
	unsigned int address;
	unsigned int DC;

}dataWord;


typedef struct functions{
	unsigned int opcode:6;
	unsigned int sourceAdrres:2;
	unsigned int sourceReg:3;
	unsigned int goalAdrres:2;
	unsigned int goalReg:3;
	unsigned int funct:5;
	unsigned int R:1;
	unsigned int E:1;
	unsigned int A:1;
    struct words *Fword;
    struct words *Sword;
	char* myLine;
	int numLine;
	struct functions *next;
	unsigned int IC;
	unsigned int L;
}function;


typedef struct words{
    int word:21;
	unsigned int E:1;
	unsigned int R:1;
	unsigned int A:1;
	unsigned int addres;
}word;


typedef struct externals{
    struct words *word;
    char *name;
    struct externals *next;
}external;


typedef struct labels{
	char* name;
	unsigned int address;
	unsigned int DC;
    struct labels *next;
    char *isDataOrCode;

}label;


cpu* myCpu;
int IC,DC,isThereLabel;
struct labels *searchLabelByName(char* str);
struct labels *searchLabelByAddress(unsigned int addr);
int isLabelsEmpty();
void addToLabels(label* label);
void addToFunctions(function* function);
void addToErrors(error *newError);
void addToDatas(data *newData);
void addToExternals(external *newExternal);
void clearAllLabels();
int isComment(const char* str);
void printErrors();
void addFunction(function *function);
void clearAllFunctions();
void clearAllExternals();
void clearAllDatas();
int isFunctionsEmpty();
int isErrorsEmpty();
int isExternalsEmpty();
#define line 82
char* trimLStr(const char* str);
char* trimRStr(char* str);
char* trimStr(char* str);
int isNull(char* str);
int isSpace(char ch);
int isNullOrWhite(const char* string);
void execute1(char *token);
void execute2(char *token);
void DataEncoding(char *str);
int getIsExcist();
FILE* getFile();
int isNLineOrEndStr(char ch);
int isNLine(char ch);
int isEndStr(char ch);
char* getStr(char* token,char* p);
int isLigal(function *funct);
int isLigalLabel(label *temp);
char* getLabel(char* token);
int isHasLabel(char* token);
function* searchFunctionByAddress(unsigned int addr);
data* searchDataByAddress(unsigned int addr);
char getHexValue(int rest);
char getHexValueFromChar(char *bin);
char* int2hex(int decimal);
int getIntValue(char hex);
int power16(int i);
int stringToInt(char* nrStr);
int power(int base, int exp);
char* int2bin(int n,int size);
char getBinaryValue(int val);
int getOpcode(char* token);
int getFunct(char *token);
int isNumber(char* ch);
int isChar(char ch);
int isDoubleLabel(char* temp);
void freeAll();
void clearAllErrors();
void addNewError(function* fun);
char* getPureFunction(const char* token);
char* getCommand(char* token);
void decryption(char *token,char *label);
char* append(char* str1,char* str2);
int getAddressing(char *ch);
int getRigester(char *ch);
int char2int(char nrStr);
int isGuidance(char *str);
int isDataGuidance(char *str);
int isDigit(char ch);
int isDatasEmpty();
void makeFiles();
char *getOutAddress(int IC);
char *bin2hex(char *bin,int z);
int isEntryEmpty();

#endif /* HEADER_H_ */
