/*
 ============================================================================
 Name        : Mmn14.c
 Author      : hussein hijazi
 ID          : 205923774
 Version     : c89
 Copyright   : All the copyrights are saved by Hussein's company
 Description : assembler in C, Ansi-style
 ============================================================================
 */

#include "header.h"
function *functionsHead=null;                       /*declaration of scoped varibales*/
label *labelsHead=null;
external *externalsHead=null;
error *errorsHead=null;
data *datasHead=null;
char *file_name;
unsigned int numberLine=0;
int IC,DC,DCF,ICF;
FILE *file;
int isExcist=false;
int thereIsLabel=false;
int main(void) {                                               /*main function*/
	printf("please enter the files name\n");
	fflush(stdout);
	char *comLine=(char*)malloc(line);
	gets(comLine);
	comLine=strtok(comLine," ");
	while(comLine){
	char *buffer=(char*)malloc(line);
		char ch;
		file_name=(char*)malloc(30);
		FILE *file;
		printf("%s\n",comLine);
		strcpy(file_name,comLine);
		file_name=append(file_name, ".as");
		file = fopen(file_name, "r");
		comLine=strtok(null," ");
	if (file) {
		    int  i=0;
		    IC=100;
		    DC=0;
	    	while((ch=fgetc(file))!=EOF){
	    		if(ch!='\n'){
	    			buffer[i]=ch;
	    		}else{
	    			buffer[i]='\0';
	    			execute1(buffer);
	    			buffer=(char*)malloc(line);
	    			i=-1;
	    		}
	    		i++;
	    	}
	    	buffer[i]='\0';
	    	execute1(buffer);
	    	fclose(file);
	}else{
		perror("Error While Open File!!!!!!!!");
		exit(0);
	}

		if(!isErrorsEmpty()){
			printErrors();
			exit(0);
		}else{
			ICF=IC;
			DCF=DC;
			IC=100;
			DC=0;
		numberLine=0;
		file=null;
		file=fopen(file_name,"r");
		if (file) {
			buffer=(char*)malloc(line);
			int  i=0;
			while((ch=fgetc(file))!=EOF){
				if(ch!='\n'){
					buffer[i]=ch;
				}else{
					buffer[i]='\0';
					execute2(buffer);
					buffer=(char*)malloc(line);
					i=-1;
				}
				i++;
			}
			buffer[i]='\0';
			execute2(buffer);
			fclose(file);
		}else{
			perror("Error While Open File!!!!!!!!");
			exit(0);
		 }
		}
		if(isErrorsEmpty()){
		makeFiles();

		}else{
			printErrors();
			exit(0);
		}
		freeAll();
	}
    	return 0;
}

char* trimLStr(const char* str){                     /*triming the string from left*/
	while(isSpace(*str)&&!isEndStr(*str)){
		str++;
	}
	return str;
}

char* trimRStr(char* str){                     /*triming the string from right*/
	char* back=str+(strlen(str)-1);
	while(isSpace(*back)&&back>str){
		back--;
	}
	back++;
	*back='\0';
	return str;
}

int isSpace(char ch){                     /*checking if this character is white space*/
	if(ch==' '||ch=='\t'){
		return true;
	}
	return false;
}

char* trimStr(char* str){                     /*triming the string from left and right*/
		return trimLStr(trimRStr(str));
	}

int isNullOrWhite(const char* string){        /*checking if this string is white space or null*/
	const char* str=string;
	while(str!=null){
		if(!isSpace(*str)&&!isNLine(*str)&&!isEndStr(*str)){
			return false;
		}
		if(isEndStr(*str)){
			break;
		}
		str++;
	}
	return true;
}

int isComment(const char* str){               /*checking if this string is comment*/
	if(*str==';'){
		return true;
	}
	return false;
}


int getGuidance(char* token){                /*function to decryption the guidance and return the perfect one*/
	if(strcmp(token,".data")==0){
		return 1;
	}
	if(strcmp(token,".string")==0){
		return 2;
	}
	if(strcmp(token,".entry")==0){
		return 3;
	}
	if(strcmp(token,".extern")==0){
			return 4;
		}
	return -1;
}

int isNLineOrEndStr(char ch){               /*checking if this character is new line or end string*/
	if(isNLine(ch)||isEndStr(ch)){
		return true;
	}
	return false;
}

int isNLine(char ch){               /*checking if this character is new line*/
	if(ch=='\n'){
		return true;
	}
	return false;
}

int isEndStr(char ch){               /*checking if this character is end string*/
	if(ch=='\0'){
		return true;
	}
	return false;
}

int isHasLabel(char* token){               /*checking if this string have label*/
	char p=':';
	if(strchr(token,p)!=null){
		return true;
	}
	return false;
}

char* getLabel(char* token){               /*getting the label from the string*/
	if(token==null){
		return null;
	}
	int size=0;
	while(token[size]!=':'){
		size++;
	}
	size++;
	char *str=(char*)malloc(size);
	size=0;
	while(token[size]!=':'){
		str[size]=token[size];
		size++;
	}
	str[size]='\0';
	str=trimStr(str);
	return str;
}

int isLigal(function *funct){               /*checking if this function is ligal according to the program terms*/
	 int op=getOpcode(getCommand(funct->myLine));
	 if(op>15){
		 return false;
	 }
	 if(op==0||op==1||op==2||op==4){
		 char* temp=funct->myLine;
		 temp+=3;
		 while(!isNLineOrEndStr(*temp)){
			temp++;
			 if(*temp==','){
				 return true;
			 }
		 }
		 return false;
	 }else{
		 if(op==5||op==9||op==12||op==13){
			 char* temp=funct->myLine;
			 temp+=3;
			 while(!isNLineOrEndStr(*temp)){
					temp++;
				    if(*temp==','){
						 return false;
						 }
					 }
		 }else{
			 if(op==14){
				 char* temp=funct->myLine;
				 temp+=3;
				 while(!isNLineOrEndStr(*temp)){
						temp++;
					    if(!isNullOrWhite(temp)){
							 return false;
							 }
						 }
				 return true;
			 }else{
				 if(op==15){
				 	 char* temp=funct->myLine;
				 	 temp+=4;
				 	 while(!isNLineOrEndStr(*temp)){
				 		temp++;
				 	    if(!isNullOrWhite(temp)){
						 return false;
				 				 }
				 			 }
				 	 return true;
				 	 }else{
				 		 return false;
				 	 }
			 }
		 }
	 }
return true;
}

int isLigalLabel(label *temp){               /*checking if this label is ligal according to the program terms*/
if(isNullOrWhite(temp->name)||isDigit(*temp->name)){
	/*good is ligal*/
	return false;
 }
int i=0;
while(temp->name[i]!='\0'){
	if(!isChar(temp->name[i])&&!isDigit(temp->name[i])){
		return false;
	}
	i++;
}
return true;
}

int isDoubleLabel(char* temp){               /*checking if this label is a double label according to the program terms*/
	label* plabel=labelsHead;
	while(plabel){
		if(strcmp(plabel->name,temp)==0){
			return true;
		}
		plabel=plabel->next;
	}
	return false;
}

void decryption(char *token,char *theLabel){               /* decryption the first execute according to the program terms*/
	char *comand=getCommand(token);
	if(getGuidance(comand)==1||getGuidance(comand)==2){
		if(isThereLabel){
			if(isDoubleLabel(theLabel)){
				error *err=(error*)malloc(sizeof(error));
				err->next=null;
				err->ErrLine=numberLine;
				char *errrr=(char*)malloc(50);
				strcpy(errrr,"the label in this line is double label");
				err->error=errrr;
				addToErrors(err);
			}else{
			label *newL=(label*)malloc(sizeof(label));
			newL->next=null;
			newL->address=IC;
			newL->name=theLabel;
			newL->DC=DC;
			char *data=(char*)malloc(5);
			strcpy(data,"data");
			newL->isDataOrCode=data;
			addToLabels(newL);
			}
		}
		DataEncoding(token);
	}else{
		if(getGuidance(comand)==3||getGuidance(comand)==4){
			if(getGuidance(comand)==4){
				label *newL=(label*)malloc(sizeof(label));
				newL->DC=0;
				newL->address=0;
				char *external=(char*)malloc(10);
				strcpy(external,"external");
				newL->isDataOrCode=external;
				newL->next=null;
				char *operand=trimStr(strtok(token,comand));
				newL->name=operand;
				addToLabels(newL);
			}
		}else{
			if(isThereLabel){
				if(isDoubleLabel(theLabel)){
					error *err=(error*)malloc(sizeof(error));
					err->next=null;
					err->ErrLine=numberLine;
					char *errrr=(char*)malloc(50);
					strcpy(errrr,"the label in this line is double label");
					err->error=errrr;
					addToErrors(err);
				}else{
					label *newL=(label*)malloc(sizeof(label));
					newL->next=null;
					newL->address=IC;
					newL->name=theLabel;
					newL->DC=-1;
					char *data=(char*)malloc(5);
					strcpy(data,"code");
					newL->isDataOrCode=data;
					addToLabels(newL);
						}
					}
			int opcode=getOpcode(comand);
			if(opcode==20){
				error *err=(error*)malloc(sizeof(error));
				err->next=null;
				err->ErrLine=numberLine;
				char *errrr=(char*)malloc(50);
				strcpy(errrr,"the comand in this line is not ligal");
				err->error=errrr;
				addToErrors(err);
			}else{
				function *newFun=(function*)malloc(sizeof(function));
				newFun->opcode=opcode;
				newFun->A=1;
				newFun->R=0;
				newFun->E=0;
				newFun->next=null;
				newFun->IC=IC++;
				newFun->L=0;
				newFun->Fword=null;
				newFun->Sword=null;
				newFun->myLine=token;
				newFun->funct=getFunct(comand);
				newFun->numLine=numberLine;
				newFun->sourceAdrres=0;
				newFun->goalReg=0;
				newFun->goalAdrres=0;
				newFun->sourceReg=0;
				if(opcode>-1&&opcode<5){

					char *temp1=(char*)malloc(strlen(token)+1);
					strcpy(temp1,token);
					char *fOp=trimStr(strtok(temp1,","));
					char *lOp=trimStr(strtok(null,","));
					fOp=trimStr(strtok(fOp,comand));
					if(lOp==null||fOp==null){
						error *err=(error*)malloc(sizeof(error));
						err->next=null;
						err->ErrLine=numberLine;
						char *errrr=(char*)malloc(50);
						strcpy(errrr,"the decryption is failed");
						err->error=errrr;
						addToErrors(err);
					}else{
						if(getAddressing(fOp)==2||getAddressing(lOp)==2){
							error *err=(error*)malloc(sizeof(error));
							err->next=null;
							err->ErrLine=numberLine;
							char *errrr=(char*)malloc(50);
							strcpy(errrr,"the operand's are ilegal");
							err->error=errrr;
							addToErrors(err);
						}else{
							if(getAddressing(fOp)!=3){
								if(getAddressing(fOp)==0){
									if(opcode!=4){
									fOp++;
									int val=stringToInt(fOp);
									if(val==0&&strcmp(fOp,"0")!=0){
										error *err=(error*)malloc(sizeof(error));
										err->next=null;
										err->ErrLine=numberLine;
										char *errrr=(char*)malloc(50);
										strcpy(errrr,"the number is ilegal");
										err->error=errrr;
										addToErrors(err);
									}else{
										word *newW=(word*)malloc(sizeof(word));
										newW->A=1;
										newW->R=0;
										newW->E=0;
										newW->addres=IC++;
										newW->word=val;
										newFun->Fword=newW;
										newFun->L++;
									 }
									}else{
										error *err=(error*)malloc(sizeof(error));
										err->next=null;
										err->ErrLine=numberLine;
										char *errrr=(char*)malloc(50);
										strcpy(errrr,"the operand's are ilegal");
										err->error=errrr;
										addToErrors(err);
									}
								}else{
									IC++;
									newFun->L++;
								}
							}
							if(getAddressing(lOp)!=3){
								if(getAddressing(lOp)==0){
									if(opcode!=1){
										error *err=(error*)malloc(sizeof(error));
										err->next=null;
										err->ErrLine=numberLine;
										char *errrr=(char*)malloc(50);
										strcpy(errrr,"the operand's are ilegal");
										err->error=errrr;
										addToErrors(err);
									}else{
										lOp++;
										int val=stringToInt(lOp);
										if(val==0&&strcmp(lOp,"0")!=0){
											error *err=(error*)malloc(sizeof(error));
											err->next=null;
											err->ErrLine=numberLine;
											char *errrr=(char*)malloc(50);
											strcpy(errrr,"the number is ilegal");
											err->error=errrr;
											addToErrors(err);
										}else{
											word *newW=(word*)malloc(sizeof(word));
											newW->A=1;
											newW->R=0;
											newW->E=0;
											newW->addres=IC++;
											newW->word=val;
											newFun->Sword=newW;
											newFun->L++;
										}
									}
								}else{
									IC++;
									newFun->L++;
								}
							}
						}
					}
				}else{
					if(opcode>4&&opcode<14){
						char *temp=(char*)malloc(strlen(token)+1);
        				strcpy(temp,token);
        				char *lOp=trimStr(strtok(temp,comand));
        				if(lOp==null){
        					error *err=(error*)malloc(sizeof(error));
        					err->next=null;
        					err->ErrLine=numberLine;
							char *errrr=(char*)malloc(50);
							strcpy(errrr,"the decryption is failed");
							err->error=errrr;
							addToErrors(err);
        				}else{
        					if(getAddressing(lOp)!=3){
        					if(getAddressing(lOp)==0){
        						if(opcode!=13){
        							error *err=(error*)malloc(sizeof(error));
        							err->next=null;
        							err->ErrLine=numberLine;
        							char *errrr=(char*)malloc(50);
        							strcpy(errrr,"operands is iligal");
        							err->error=errrr;
        							addToErrors(err);
        						}else{
        							lOp++;
        							int val=stringToInt(lOp);
        							if(val==0&&strcmp(lOp,"0")!=0){
        								error *err=(error*)malloc(sizeof(error));
        								err->next=null;
        								err->ErrLine=numberLine;
        								char *errrr=(char*)malloc(50);
        								strcpy(errrr,"the number is ilegal");
        								err->error=errrr;
        								addToErrors(err);
        							}else{
        								word *newW=(word*)malloc(sizeof(word));
        								newW->A=1;
        								newW->R=0;
        								newW->E=0;
        								newW->addres=IC++;
        								newW->word=val;
        								newFun->Sword=newW;
        								newFun->L++;
        							}
        						}
        					  }else{
        						  if(getAddressing(lOp)==2){
        							  if(opcode!=9){
        								 error *err=(error*)malloc(sizeof(error));
        								 err->ErrLine=numberLine;
        								 err->next=null;
        								 char *errr=(char*)malloc(50);
        								 strcpy(errr,"the operand is iligal one!!!");
        								 err->error=errr;
        								 addToErrors(err);
        							  }
        						  }
        						  IC++;
        						  newFun->L++;
        					  }
        					}
        				}
					}else{
						char *temp=(char*)malloc(strlen(token)+1);
						strcpy(temp,token);
						if(!isNullOrWhite(strtok(temp,comand))){
							error *err=(error*)malloc(sizeof(error));
							err->next=null;
							err->ErrLine=numberLine;
							char *errrr=(char*)malloc(50);
							strcpy(errrr,"the number of operands is iligal");
							err->error=errrr;
							addToErrors(err);
						}
					}
				}
				addToFunctions(newFun);
			}
		}
	}
}

void DataEncoding(char *str){                           /*encoding the data according to the terms*/
	char *temp=(char*)malloc(strlen(str)+1);
	strcpy(temp,str);
	char *dataOrStr=(char*)malloc(10);
	char *command=getCommand(temp);
	temp=trimStr(strtok(temp,command));
	if(getGuidance(command)==1){
		char *tok=strtok(temp,",");
		strcpy(dataOrStr,"data");
		while(tok){
			data* newData=(data*)malloc(sizeof(data));
			newData->next=null;
			newData->word=(dataWord*)malloc(sizeof(dataWord));
			newData->word->address=IC++;
			newData->word->DC=DC++;
			newData->word->word=stringToInt(tok);
			newData->word->isDataOrStr=dataOrStr;
			if(newData->word->word==0){
				if(strcmp(tok,"0")!=0){
					error *newE=(error*)malloc(sizeof(error));
					newE->next=null;
					newE->ErrLine=numberLine;
					char* err=(char*)malloc(line);
					strcpy(err,"one or more of the data is not a ligal number");
					newE->error=err;
					addToErrors(newE);
				}
			}
			tok=strtok(null,",");
			addToDatas(newData);
		}
	}else{
		if(getGuidance(command)==2){
			strcpy(dataOrStr,"string");
			if(isNullOrWhite(temp)){
				error *newE=(error*)malloc(sizeof(error));
				newE->next=null;
				newE->ErrLine=numberLine;
				char* err=(char*)malloc(line);
				strcpy(err,"the Guidance not a ligal one");
				newE->error=err;
				addToErrors(newE);
			}else{
				if(temp[0]!=34||temp[strlen(temp)-1]!=34){
					error *newE=(error*)malloc(sizeof(error));
					newE->next=null;
					newE->ErrLine=numberLine;
					char* err=(char*)malloc(line);
					strcpy(err,"the Guidance data not a ligal one");
					newE->error=err;
					addToErrors(newE);
				}else{
					temp++;
					temp[strlen(temp)-1]='\0';
					int i=0;
					while(temp[i]!='\0'){
						data *newDaata=(data*)malloc(sizeof(data));
						newDaata->next=null;
						newDaata->word=(dataWord*)malloc(sizeof(dataWord));
						newDaata->word->address=IC++;
						newDaata->word->DC=DC++;
						newDaata->word->word=temp[i];
						newDaata->word->isDataOrStr=dataOrStr;
						addToDatas(newDaata);
						i++;
					}
					data *newDaata=(data*)malloc(sizeof(data));
					newDaata->next=null;
					newDaata->word=(dataWord*)malloc(sizeof(dataWord));
					newDaata->word->address=IC++;
					newDaata->word->DC=DC++;
					newDaata->word->word=temp[i];
					newDaata->word->isDataOrStr=dataOrStr;
					addToDatas(newDaata);
					i++;
				}
			}
		}else{
			error *newE=(error*)malloc(sizeof(error));
			newE->next=null;
			newE->ErrLine=numberLine;
			char* err=(char*)malloc(line);
			strcpy(err,"the Guidance not a ligal one");
			newE->error=err;
			addToErrors(newE);
		}
	}
}


void execute2(char *token){                      /*the second executing*/
	numberLine++;
	if(isNullOrWhite(token)){
				/*dont save it in functions*/
		free(token);
	}else{
	token=trimStr(token);
	char* str=(char*)malloc(strlen(token)+1);
	strcpy(str,token);
	free(token);
	if(isComment(str)){
		free(str);
    }else{

	if(isHasLabel(str)){
		str=getPureFunction(str);
	}
	char *comand=getCommand(str);
	if(getGuidance(comand)==1||getGuidance(comand)==2||getGuidance(comand)==4){

	}else{
		if(getGuidance(comand)==3){
			char *theL=trimStr(strtok(str,comand));
			label *p=searchLabelByName(theL);
			if(p){
				char *entry=(char*)malloc(6);
				strcpy(entry,"entry");
				p->isDataOrCode=append(append(p->isDataOrCode,","),entry);

			}else{
				error *newEr=(error*)malloc(sizeof(error));
				char *err=(char*)malloc(line);
				strcpy(err,"The label isn't excist!!! ");
				newEr->next=null;
				newEr->ErrLine=numberLine;
				newEr->error=err;
				addToErrors(newEr);
			}
		}else{
			function *fun=searchFunctionByAddress(IC++);
			if(fun){
				if(fun->opcode>-1&&fun->opcode<5){
					char *temp=(char*)malloc(strlen(fun->myLine)+1);
					strcpy(temp,fun->myLine);
					temp=trimStr(strtok(temp,comand));
					char *fOp=trimStr(strtok(temp,","));
					char *lOp=trimStr(strtok(null,","));
					if(fOp==null||lOp==null){
						error *newEr=(error*)malloc(sizeof(error));
						char *err=(char*)malloc(line);
						strcpy(err,"error while decryption the data!!! ");
						newEr->next=null;
						newEr->ErrLine=numberLine;
						newEr->error=err;
						addToErrors(newEr);
					}else{
						if(getAddressing(fOp)!=3){
							if(getAddressing(fOp)!=0){
								if(getAddressing(fOp)==1){
									fun->sourceAdrres=1;
									word *newW=(word*)malloc(sizeof(word));
									newW->addres=IC++;
									newW->A=0;
									label *l=searchLabelByName(fOp);
									if(l){
										newW->word=l->address;
										if(strcmp(l->isDataOrCode,"external")!=0){
											newW->R=1;
											newW->E=0;
										}else{
											external *newExtern=(external*)malloc(sizeof(external));
											newExtern->next=null;
											newExtern->word=newW;
											char *name=(char*)malloc(strlen(l->name)+1);
											strcpy(name,l->name);
											newExtern->name=name;
											newW->E=1;
											newW->R=0;
											addToExternals(newExtern);
										}
									}else{
										error *newEr=(error*)malloc(sizeof(error));
										char *err=(char*)malloc(line);
										strcpy(err,"error while decryption the data!!! ");
										newEr->next=null;
										newEr->ErrLine=numberLine;
										newEr->error=err;
										addToErrors(newEr);
									}
									fun->Fword=newW;
								}
							}else{
								IC++;
							}
						}else{
							fun->sourceAdrres=3;
							if(getRigester(fOp)==-1){
								error *newEr=(error*)malloc(sizeof(error));
								char *err=(char*)malloc(line);
								strcpy(err,"error while decryption the data!!! ");
								newEr->next=null;
								newEr->ErrLine=numberLine;
								newEr->error=err;
								addToErrors(newEr);
							}else{
							fun->sourceReg=getRigester(fOp);}
						}
						if(getAddressing(lOp)!=3){
							if(getAddressing(lOp)!=0){
								if(getAddressing(lOp)==1){
									fun->goalAdrres=1;
									word *newW=(word*)malloc(sizeof(word));
									newW->A=0;
									newW->addres=IC++;
									label *l=searchLabelByName(lOp);
									if(l){
										newW->word=l->address;
										if(strcmp(l->isDataOrCode,"external")!=0){
											newW->E=0;
											newW->R=1;
										}else{
											external *newExtern=(external*)malloc(sizeof(external));
											newExtern->next=null;
											newExtern->word=newW;
											char *name=(char*)malloc(strlen(l->name)+1);
											strcpy(name,l->name);
											newExtern->name=name;
											newW->E=1;
											newW->R=0;
											addToExternals(newExtern);
										}
									}else{
										error *newEr=(error*)malloc(sizeof(error));
										char *err=(char*)malloc(line);
										strcpy(err,"error while decryption the data!!! ");
										newEr->next=null;
										newEr->ErrLine=numberLine;
										newEr->error=err;
										addToErrors(newEr);
									}
									fun->Sword=newW;
								}
							}else{
								IC++;
							}
						}else{
							int reg=getRigester(lOp);
							fun->goalAdrres=3;
							if(getRigester(lOp)==-1){
								error *newEr=(error*)malloc(sizeof(error));
								char *err=(char*)malloc(line);
								strcpy(err,"error while decryption the data!!! ");
								newEr->next=null;
								newEr->ErrLine=numberLine;
								newEr->error=err;
								addToErrors(newEr);
							}else{
							fun->goalReg=getRigester(lOp);}
						}
					}
				}else{
					if(fun->opcode>4&&fun->opcode<14){
						char *temp=(char*)malloc(strlen(fun->myLine)+1);
						strcpy(temp,fun->myLine);
						char *lOp=trimStr(strtok(temp,comand));
						if(lOp==null){
							error *newEr=(error*)malloc(sizeof(error));
							char *err=(char*)malloc(line);
							strcpy(err,"error while decryption the data!!! ");
							newEr->next=null;
							newEr->ErrLine=numberLine;
							newEr->error=err;
							addToErrors(newEr);
						}else{
							if(getAddressing(lOp)!=3){
								if(getAddressing(lOp)!=0){
									if(getAddressing(lOp)==1){
										fun->goalAdrres=1;
										word *newW=(word*)malloc(sizeof(word));
										newW->A=0;
										newW->addres=IC++;
										label *l=searchLabelByName(lOp);
										if(l){
											newW->word=l->address;
											if(strcmp(l->isDataOrCode,"external")!=0){
												newW->E=0;
												newW->R=1;
											}else{
												external *newExtern=(external*)malloc(sizeof(external));
												newExtern->next=null;
												newExtern->word=newW;
												char *name=(char*)malloc(strlen(l->name)+1);
												strcpy(name,l->name);
												newExtern->name=name;
												newW->E=1;
												newW->R=0;
												addToExternals(newExtern);
											}
										}else{
											error *newEr=(error*)malloc(sizeof(error));
											char *err=(char*)malloc(line);
											strcpy(err,"error while decryption the data!!! ");
											newEr->next=null;
											newEr->ErrLine=numberLine;
											newEr->error=err;
											addToErrors(newEr);
										}
										fun->Sword=newW;
									}else{
										if(getAddressing(lOp)==2){
										fun->goalAdrres=2;
										lOp++;
										word *newW=(word*)malloc(sizeof(word));
										newW->A=1;
										newW->E=0;
										newW->R=0;
										label *theLabel=searchLabelByName(lOp);
										if(theLabel){
											int adrr=theLabel->address;
											newW->word=adrr-IC+1;
											newW->addres=IC++;
											fun->Sword=newW;
										}else{
											newW->word=0;
											newW->addres=IC++;
											fun->Sword=newW;
											error *newEr=(error*)malloc(sizeof(error));
											char *err=(char*)malloc(line);
											strcpy(err,"error while decryption the data!!! ");
											newEr->next=null;
											newEr->ErrLine=numberLine;
											newEr->error=err;
											addToErrors(newEr);
										 }
										}else{
											error *newEr=(error*)malloc(sizeof(error));
											char *err=(char*)malloc(line);
											strcpy(err,"error while decryption the data!!! ");
											newEr->next=null;
											newEr->ErrLine=numberLine;
											newEr->error=err;
											addToErrors(newEr);
										}
									}
								}else{
									IC++;
								}
							}else{
								fun->goalAdrres=3;
								if(getRigester(lOp)==-1){
									error *newEr=(error*)malloc(sizeof(error));
									char *err=(char*)malloc(line);
									strcpy(err,"error while decryption the data!!! ");
									newEr->next=null;
									newEr->ErrLine=numberLine;
									newEr->error=err;
									addToErrors(newEr);
								}else{
									fun->goalReg=getRigester(lOp);}
							}
						}
					}
				}
			}else{
				error *newEr=(error*)malloc(sizeof(error));
				char *err=(char*)malloc(line);
				strcpy(err,"The function isn't excist!!! ");
				newEr->next=null;
				newEr->ErrLine=numberLine;
				newEr->error=err;
				addToErrors(newEr);
			}
		}
	}
  }
 }
}


void execute1(char *token){            /*the first executing*/
	numberLine++;
	if(isNullOrWhite(token)){
			/*dont save it in functions*/
				free(token);
	}else{
		token=trimStr(token);
		char* str=(char*)malloc(strlen(token)+1);
		strcpy(str,token);
		free(token);
		if(isComment(str)){
			free(str);
		}else{
			if(isHasLabel(str)){
				isThereLabel=true;
				char *label=getLabel(str);
				str=getPureFunction(str);
				decryption(str, label);
			}else{
				decryption(str,null);
			}
		}
	}
}




void addToFunctions(function *newFunction){                     /*adding a new function to the function's data structure*/
	if(isFunctionsEmpty()){
		functionsHead=newFunction;
	}else{
		function* temp=functionsHead;
		while(temp->next){
			temp=temp->next;
		}
		temp->next=newFunction;
		newFunction->next=null;
	}

}

void addToDatas(data *newData){                     /*adding a new data to the data's data structure*/
	if(isDatasEmpty()){
		datasHead=newData;
	}else{
		data* temp=datasHead;
		while(temp->next){
			temp=temp->next;
		}
		temp->next=newData;
		newData->next=null;
	}

}

void addToErrors(error *newError){                     /*adding a new error to the error's data structure*/
	if(isErrorsEmpty()){
		errorsHead=newError;
	}else{
		error* temp=errorsHead;
		while(temp->next){
			temp=temp->next;
		}
		temp->next=newError;
		newError->next=null;
	}

}

void addToExternals(external *newExternal){                     /*adding a new external label to the externals's data structure*/
	if(isExternalsEmpty()){
		externalsHead=newExternal;
	}else{
		external* temp=externalsHead;
		while(temp->next){
			temp=temp->next;
		}
		temp->next=newExternal;
		newExternal->next=null;
	}

}

void addNewError(function* fun){                                /*adding a new error to the error's data structure*/
	char *temp=(char*)malloc(strlen("error"));
	strcpy(temp,"error");
	error* newErr=(error*)malloc(sizeof(error));
	newErr->next=null;
	newErr->ErrLine=fun->numLine;
    newErr->error=temp;
	addToErrors(newErr);
}


int isExternalsEmpty(){                                /*checking if externals data structure empty*/
	if(externalsHead==null){
		return true;
	}
	return false;
}

int isFunctionsEmpty(){                                /*checking if functions data structure empty*/
	if(functionsHead==null){
		return true;
	}
	return false;
}

int isErrorsEmpty(){                                /*checking if errors data structure empty*/
	if(errorsHead==null){
		return true;
	}
	return false;
}

int isDatasEmpty(){                                /*checking if datas data structure empty*/
	if(datasHead==null){
		return true;
	}
	return false;
}

void clearAllFunctions(){                                /*clearing all the functions from the data structure*/
	function* p=functionsHead;
	while(!isFunctionsEmpty()){
		p=functionsHead;
		functionsHead=functionsHead->next;
		free(p);
	}
	functionsHead=null;
}

void clearAllErrors(){                                /*clearing all the errors from the data structure*/
	error* p=errorsHead;
	while(!isErrorsEmpty()){
		p=errorsHead;
		errorsHead=errorsHead->next;
		free(p);
	}
	errorsHead=null;
}

void clearAllExternals(){                                /*clearing all the externals from the data structure*/
	external* p=externalsHead;
	while(!isExternalsEmpty()){
		p=externalsHead;
		externalsHead=externalsHead->next;
		free(p);
	}
	externalsHead=null;
}

void clearAllDatas(){                                /*clearing all the datas from the data structure*/
	data* p=datasHead;
	while(!isDatasEmpty()){
		p=datasHead;
		datasHead=datasHead->next;
		free(p);
	}
	datasHead=null;
}

void freeAll(){    /*clearing all the data structures*/
	clearAllErrors();
	clearAllFunctions();
	clearAllLabels();
	clearAllExternals();
	clearAllDatas();
}

label *searchLabelByName(char* str){                                /*searching a label according to name*/
	label *p=labelsHead;
	char* chr;
	while(p!=null){
		chr=p->name;
			if(strcmp(str,chr)==0){
						return p;
					}
		p=p->next;
	}
	return null;
}

label* searchLabelByAddress(unsigned int addr){                                /*searching a label according to address*/
	struct labels *p=labelsHead;
	while(p!=null){
		if(p->address==addr){
			return p;
		}
		p=p->next;
	}
	return null;
}

function* searchFunctionByAddress(unsigned int addr){                                /*searching a function according to address*/
	function *p=functionsHead;
	while(p!=null){
		if(p->IC==addr){
			return p;
		}
		p=p->next;
	}
	return null;
}

data* searchDataByAddress(unsigned int addr){                                /*searching a data according to address*/
	data *p=datasHead;
	while(p!=null){
		if(p->word->address==addr){
			return p;
		}
		p=p->next;
	}
	return null;
}

void addToLabels(label *newLabel){                                /*adding a new label to the label's structure*/
	isThereLabel=false;
	if(!isLigalLabel(newLabel)){
		error *newErr=(error*)malloc(sizeof(error));
		char *err=(char*)malloc(50);
		newErr->next=null;
		strcpy(err,"the label in this lint is iligal");
		newErr->ErrLine=numberLine;
		newErr->error=err;
		addToErrors(newErr);
	}
	if(isLabelsEmpty()){
		labelsHead=newLabel;
	}else{
		label* temp=labelsHead;
		while(temp->next){
			temp=temp->next;
		}
		temp->next=newLabel;
		newLabel->next=null;
	}
}

void clearAllLabels(){                                /*clearing all the labels from the data structure*/
	label* p=labelsHead;
		while(!isLabelsEmpty()){
			p=labelsHead;
			labelsHead=labelsHead->next;
			free(p);
		}
		labelsHead=null;

}



int isLabelsEmpty(){                                 /*checking if the labels data structure is empty*/
	if(labelsHead==null){
		return true;
	}
	return false;
}

void printErrors(){                                 /*printing all errors*/
		error* p=errorsHead;
		while(p){
			printf("in file : %s  in line : %u\t%s\n",file_name,p->ErrLine,p->error);
			p=p->next;
		}

}



char* getPureFunction(const char* token){                     /*getting the string without the label*/
	while(*(token)!=':'){
		token++;
	}
	token++;
	return trimStr(token);
}

char* getCommand(char* token){                     /*getting the first token in this string */
	if(strcmp(token,"rts")==0||strcmp(token,"stop")==0){
		return token;
	}
	char* temp=(char*)malloc(strlen(token)+1);
	strcpy(temp,token);
	return trimStr(strtok(temp," "));
}

char* int2bin(int n,int size){                    /*converting integer number to binary string*/
	 int c, d, count;
	   char *pointer;

	   count = 0;
	   pointer = (char*)malloc(32+1);

	   if (pointer == NULL)
	      exit(EXIT_FAILURE);

	   for (c = size-1 ; c >= 0 ; c--)
	   {
	      d = n >> c;

	      if (d & 1)
	         *(pointer+count) = 1 + '0';
	      else
	         *(pointer+count) = 0 + '0';

	      count++;
	   }
	   *(pointer+count) = '\0';

	   return  pointer;
}

int hex2int(char *hex){                    /*converting hexa string to integer number*/
	int i=0;
	int result=0;
	while(hex[i]!='\0'){
		result=result+(getIntValue(hex[strlen(hex)-i-1])*power16(i));
		i++;
	}
	return result;
}

char* int2hex(int decimal){                    /*converting integer number to hexa string*/
	int j=1;
	char* result=(char*)malloc(j);
	if(decimal==0){
		free(result);
		return NULL;
	}else{
		int rest;
		int i=0;
		while(decimal>0){
			rest=decimal%16;
			decimal=decimal/16;
			result[i]=getHexValue(rest);
			j++;
			result=(char*)realloc(result,j);
			i++;
		}
		result[i]='\0';
	}

	return strrev(result);
}

char getHexValue(int rest){                    /*converting integer digit to hexa character*/
	switch(rest){
	case 0:return '0';
	case 1:return '1';
	case 2:return '2';
	case 3:return '3';
	case 4:return '4';
	case 5:return '5';
	case 6:return '6';
	case 7:return '7';
	case 8:return '8';
	case 9:return '9';
	case 10:return 'A';
	case 11:return 'B';
	case 12:return 'C';
	case 13:return 'D';
	case 14:return 'E';
	default:return 'F';
	}
}

char getHexValueFromChar(char *bin){                    /*converting binary string to hexa character*/
	if(strcmp(bin,"0000")==0){
			return '0';
		}
	if(strcmp(bin,"0001")==0){
			return '1';
		}
	if(strcmp(bin,"0010")==0){
			return '2';
		}
	if(strcmp(bin,"0011")==0){
			return '3';
		}
	if(strcmp(bin,"0100")==0){
			return '4';
		}
	if(strcmp(bin,"0101")==0){
			return '5';
		}
	if(strcmp(bin,"0110")==0){
			return '6';
		}
	if(strcmp(bin,"0111")==0){
			return '7';
		}
	if(strcmp(bin,"1000")==0){
			return '8';
		}
	if(strcmp(bin,"1001")==0){
			return '9';
		}
	if(strcmp(bin,"1010")==0){
			return 'A';
		}
	if(strcmp(bin,"1011")==0){
			return 'B';
		}
	if(strcmp(bin,"1100")==0){
			return 'C';
		}
	if(strcmp(bin,"1101")==0){
			return 'D';
		}
	if(strcmp(bin,"1110")==0){
			return 'E';
		}
	if(strcmp(bin,"1111")==0){
			return 'F';
		}
	return '*';
}

int char2int(char nrStr){                    /*converting character digit to integer digit*/
	switch(nrStr){
		case '0':return 0;
		case '1':return 1;
		case '2':return 2;
		case '3':return 3;
		case '4':return 4;
		case '5':return 5;
		case '6':return 6;
		case '7':return 7;
		case '8':return 8;
		case '9':return 9;
		default:return -1;
	}
}

int getIntValue(char hex){                    /*converting character hexa to integer number*/
	switch(hex){
	case '0':return 0;
	case '1':return 1;
	case '2':return 2;
	case '3':return 3;
	case '4':return 4;
	case '5':return 5;
	case '6':return 6;
	case '7':return 7;
	case '8':return 8;
	case '9':return 9;
	case 'A':return 10;
	case 'B':return 11;
	case 'C':return 12;
	case 'D':return 13;
	case 'E':return 14;
	default:return 15;
	}
}

int power16(int i){                        /*doing power to 16 of the number*/
	int result;
	if(i==0){
		result=1;
	}else{
		result=16;
		i--;
		while(i>0){
			result*=16;
			i--;
		}
	}
	return result;
}

int stringToInt(char* nrStr){                    /*converting string number to integer number*/
	return atoi(nrStr);
}


int power2(int i){                        /*doing power to 2 of the number*/
	int result;
		if(i==0){
			result=1;
		}else{
			result=2;
			i--;
			while(i>0){
				result*=2;
				i--;
			}
		}
		return result;
}

char getBinaryValue(int val){                       /*converting integer digit to binary character*/
	switch(val){
	case 0:return '0';
	case 1:return '1';
	default:return '*';
	}
}

int getOpcode(char* token){                       /*decryption the perfect opcode*/
	if(strcmp(token,"mov")==0){
		return 0;}
	if(strcmp(token,"cmp")==0){
		return 1;}
	if(strcmp(token,"sub")==0||strcmp(token,"add")==0){
		return 2;}
	if(strcmp(token,"lea")==0){
		return 4;}
	if(strcmp(token,"clr")==0||strcmp(token,"not")==0
			||strcmp(token,"inc")==0||strcmp(token,"dec")==0){
		return 5;}
	if(strcmp(token,"jmp")==0||strcmp(token,"bne")==0
			||strcmp(token,"jsr")==0){
			return 9;}
	if(strcmp(token,"red")==0){
			return 12;}
	if(strcmp(token,"prn")==0){
		return 13;}
	if(strcmp(token,"rts")==0){
		return 14;}
	if(strcmp(token,"stop")==0){
		return 15;}
	return 20;
}

int getFunct(char *token){                       /*decryption the perfect opcode*/
	    if(strcmp(token,"clr")==0||strcmp(token,"add")==0
	    		||strcmp(token,"jmp")==0)
	    	return 1;
		if(strcmp(token,"sub")==0||strcmp(token,"not")==0
				||strcmp(token,"bne")==0)
			return 2;
		if(strcmp(token,"inc")==0||strcmp(token,"jsr")==0)
			return 3;
		if(strcmp(token,"dec")==0)
			return 4;
		return 0;
}

int isNumber(char* ch){                       /*checking if this string a number*/
	int num=atoi(ch);
	if(num==0&&strcmp(ch,"0")!=0){
		return false;
	}
	return true;
}

int isChar(char ch){                       /*checking if this character a character*/
	if((ch>64&&ch<91)||(ch>96&&ch<123)){
		return true;
	}
	return false;
}

char* append(char* str1,char* str2){                       /*appending to strings*/
	char * new_str =null;
	if((new_str = malloc(strlen(str1)+strlen(str2)+1)) != NULL){
	    new_str[0] = '\0';   /* ensures the memory is an empty string*/
	    strcat(new_str,str1);
	    strcat(new_str,str2);
	} else {
	    perror("malloc failed!\n");
	    /* exit?*/
	}
	return new_str;
}


int getAddressing(char *ch){                       /*decryption the perfect addressing*/
	if(*ch=='#'){
		return 0;
	}
	if(searchLabelByName(ch)){
		return 1;
	}
	if(*ch=='&'){
		ch++;
		if(searchLabelByName(ch)){
			return 2;
		}else{
			return -1;
		}
	}
	if(strcmp(ch,"r1")==0||strcmp(ch,"r2")==0||strcmp(ch,"r3")==0||strcmp(ch,"r4")==0
			||strcmp(ch,"r7")==0||strcmp(ch,"r6")==0||strcmp(ch,"r5")==0
			||strcmp(ch,"r0")==0){
		return 3;
	}
	return -1;
}

int getRigester(char *ch){                       /*decryption the perfect regester*/
	if(strcmp(ch,"r0")==0){
		return 0;
	}
	if(strcmp(ch,"r1")==0){
			return 1;
		}
	if(strcmp(ch,"r2")==0){
			return 2;
		}
	if(strcmp(ch,"r3")==0){
			return 3;
		}
	if(strcmp(ch,"r4")==0){
			return 4;
		}
	if(strcmp(ch,"r5")==0){
			return 5;
		}
	if(strcmp(ch,"r6")==0){
			return 6;
		}
	if(strcmp(ch,"r7")==0){
			return 7;
		}
	return -1;
}

int isDigit(char ch){                       /*checking if this character a digit*/
	if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||
			ch=='7'||ch=='8'||ch=='9'||ch=='6'){
		return true;
	}
	return false;
}

void makeFiles(){                       /*making the externals , objects , entreis files and writing in them hexa code*/
	IC=100;
	DC=0;
	FILE *obFile;
	char *tempob=(char*)malloc(strlen(file_name)+1);
	char *tempext=(char*)malloc(strlen(file_name)+1);
	char *tempent=(char*)malloc(strlen(file_name)+1);
	strcpy(tempob,file_name);
	tempob=strtok(tempob,".");
	strcpy(tempext,tempob);
	strcpy(tempent,tempob);
	if(tempob){
		tempob=append(tempob, ".ob");
		tempext=append(tempext, ".ext");
		tempent=append(tempent, ".ent");
		obFile=fopen(tempob,"w");
	}else{
		perror("cannot write to file\n");
		return;
	}
	if(obFile){
	fprintf(obFile,"%d\t%d\n",ICF-100-DCF,DCF);
	while(IC<ICF){
		function *f=searchFunctionByAddress(IC);
		if(f){
			char *op=int2bin(f->opcode,6);
			char *sAdd=int2bin(f->sourceAdrres,2);
			char *sReg=int2bin(f->sourceReg,3);
			char *gAdd=int2bin(f->goalAdrres,2);
			char *gReg=int2bin(f->goalReg,3);
			char *funct=int2bin(f->funct,5);
			char A=getBinaryValue(f->A);
			char E=getBinaryValue(f->E);
			char R=getBinaryValue(f->R);
			if(strlen(op)<6){
				char correct[6-strlen(op)+1];
				int i=0;
				while(i<6-strlen(op)){
					correct[i]='0';
					i++;
				}
				correct[i]='\0';
				op=append(correct, op);
			}
			if(strlen(sReg)<3){
				char correct[3-strlen(sReg)+1];
				int i=0;
				while(i<3-strlen(sReg)){
					correct[i]='0';
					i++;
				}
				correct[i]='\0';
				sReg=append(correct, sReg);
			}
			if(strlen(gReg)<3){
				char correct[3-strlen(gReg)+1];
				int i=0;
				while(i<3-strlen(gReg)){
					correct[i]='0';
					i++;
				}
				correct[i]='\0';
				gReg=append(correct, gReg);
			}
			if(strlen(funct)<5){
				char correct[5-strlen(funct)+1];
				int i=0;
				while(i<5-strlen(funct)){
					correct[i]='0';
					i++;
				}
				correct[i]='\0';
				funct=append(correct, funct);
			}
			if(strlen(sAdd)<2){
				char correct[2-strlen(sAdd)+1];
				int i=0;
				while(i<2-strlen(sAdd)){
					correct[i]='0';
					i++;
				}
				correct[i]='\0';
				sAdd=append(correct, sAdd);
			}
			if(strlen(gAdd)<2){
				char correct[2-strlen(gAdd)+1];
				int i=0;
				while(i<2-strlen(gAdd)){
					correct[i]='0';
					i++;
				}
				correct[i]='\0';
				gAdd=append(correct, gAdd);
			}
			char *res=append(append(append(append(append(op, sAdd),sReg),gAdd),gReg),funct);
			if(A=='1'){
				res=append(res, "100");
			}else{
				if(R=='1'){
					res=append(res, "010");
				}else{
					res=append(res, "001");
				}
			}
			res=bin2hex(res,4);
			if(f->L==0){
				fprintf(obFile,"%s %s\n",getOutAddress(IC++),res);
			}
			if(f->L==1){
				fprintf(obFile,"%s %s\n",getOutAddress(IC++),res);
				if(f->Fword){
					char *wordres=int2bin(f->Fword->word,21);
					if(f->Fword->A){
						wordres=append(wordres, "100");
					}else{
						if(f->Fword->R){
							wordres=append(wordres, "010");
						}else{
							wordres=append(wordres, "001");
						}
					}
					if(strlen(wordres)<24){
						char correct[24-strlen(wordres)+1];
						int i=0;
						while(i<24-strlen(wordres)){
							correct[i]='0';
							i++;
						}
						correct[i]='\0';
						wordres=append(correct, wordres);
					}
					wordres=bin2hex(wordres,4);
					fprintf(obFile,"%s %s\n",getOutAddress(IC++),wordres);
				}else{
					if(f->Sword){
						char *wordres=int2bin(f->Sword->word,21);
						if(f->Sword->A){
							wordres=append(wordres, "100");
						}else{
							if(f->Sword->R){
								wordres=append(wordres, "010");
							}else{
								wordres=append(wordres, "001");
							}
						}
						if(strlen(wordres)<24){
							char correct[24-strlen(wordres)+1];
							int i=0;
							while(i<24-strlen(wordres)){
								correct[i]='0';
								i++;
							}
							correct[i]='\0';
							wordres=append(correct, wordres);
						}
						wordres=bin2hex(wordres,4);
						fprintf(obFile,"%s %s\n",getOutAddress(IC++),wordres);
					}else{
						perror("error while writing the object file!!");
					}
				}
			}
			if(f->L==2){
				fprintf(obFile,"%s %s\n",getOutAddress(IC++),res);
				if(f->Fword){
					char *wordres=int2bin(f->Fword->word,21);
					if(f->Fword->A){
						wordres=append(wordres, "100");
					}else{
						if(f->Fword->R){
							wordres=append(wordres, "010");
						}else{
							wordres=append(wordres, "001");
						}
					}
					if(strlen(wordres)<24){
						char correct[24-strlen(wordres)+1];
						int i=0;
						while(i<24-strlen(wordres)){
							correct[i]='0';
							i++;
						}
						correct[i]='\0';
						wordres=append(correct, wordres);
					}
					wordres=bin2hex(wordres,4);
					fprintf(obFile,"%s %s\n",getOutAddress(IC++),wordres);
				}else{
					perror("error while writing the object file!!");
				}
				if(f->Sword){
					char *wordres=int2bin(f->Sword->word,21);
					if(f->Sword->A){
						wordres=append(wordres, "100");
					}else{
						if(f->Sword->R){
							wordres=append(wordres, "010");
						}else{
							wordres=append(wordres, "001");
						}
					}
					if(strlen(wordres)<24){
						char correct[24-strlen(wordres)+1];
						int i=0;
						while(i<24-strlen(wordres)){
							correct[i]='0';
							i++;
						}
						correct[i]='\0';
						wordres=append(correct, wordres);
					}
					wordres=bin2hex(wordres,4);
					fprintf(obFile,"%s %s\n",getOutAddress(IC++),wordres);
				}else{
					perror("error while writing the object file!!");
				}
			}
		}else{
			data *d=searchDataByAddress(IC);
			while(d){
				char *wordres=int2bin(d->word->word,24);
				wordres=bin2hex(wordres,4);
				fprintf(obFile,"%s %s\n",getOutAddress(IC++),wordres);
				d=searchDataByAddress(IC);
			}
		}
	  }
	fclose(obFile);
	}else{
		perror("cannot write to file\n");
				return;
	}
	if(!isExternalsEmpty()){
		FILE *extFile;
		if(tempext){
			extFile=fopen(tempext,"w");
		}else{
			perror("cannot write to file\n");
			return;
		}
		if(extFile){
			external *p=externalsHead;
			while(p){
				fprintf(extFile,"%s %s\n",p->name,getOutAddress(p->word->addres));
				p=p->next;
			}
			fclose(extFile);
		}else{
			perror("cannot write to file\n");
							return;
		}
	}
	if(!isEntryEmpty()){
		FILE *entFile;
			if(tempent){
				entFile=fopen(tempent,"w");
			}else{
				perror("cannot write to file\n");
				return;
			}
			if(entFile){
				label *p=labelsHead;
				while(p){
					char *tok=(char*)malloc(strlen(p->isDataOrCode)+1);
					strcpy(tok,p->isDataOrCode);
					tok=strtok(tok,",");
					tok=strtok(null,",");
					if(tok){
						if(strcmp(tok,"entry")==0){
							fprintf(entFile,"%s %s\n",p->name,getOutAddress(p->address));
						}
					}
					p=p->next;
					free(tok);
				}
				fclose(entFile);
			}else{
				perror("cannot write to file\n");
								return;
			}
	}
}

char *getOutAddress(int IC){                 /*encoding and fixing the addresses to write them*/
	char *addressss=(char*)malloc(8);
	itoa(IC,addressss,10);
	if(strlen(addressss)<7){
		char correct[7-strlen(addressss)+1];
		int i=0;
		while(i<7-strlen(addressss)){
			correct[i]='0';
			i++;
		}
		correct[i]='\0';
		addressss=append(correct, addressss);
	}
		return addressss;
}


char *bin2hex(char *bin,int z){                 /*converting a binary string to hexa string*/
	if(isNullOrWhite(bin)){
		return null;
	}
	char *res=(char*)malloc(strlen(bin)/z+1);
	char *temp=(char*)malloc(z+1);
	int tempcounter=0,rescounter=0;
	int j,i=0;
	while(i<strlen(bin)){
		j=i;
		tempcounter=0;
		while(j<i+z){
			temp[tempcounter++]=bin[j];
			j++;
		}
		temp[tempcounter]='\0';
		res[rescounter++]=getHexValueFromChar(temp);
		i+=z;
	}
	res[rescounter]='\0';
	free(bin);
	return res;
}

int isEntryEmpty(){                 /*checking if there are no entry labels */
	label *p=labelsHead;
	while(p){
		char *tok=(char*)malloc(strlen(p->isDataOrCode)+1);
		strcpy(tok,p->isDataOrCode);
		tok=strtok(tok,",");
		tok=strtok(null,",");
		if(tok){
			if(strcmp(tok,"entry")==0){
				free(tok);
				return false;
			}
		}
		p=p->next;
		free(tok);
	}
	return true;
}
