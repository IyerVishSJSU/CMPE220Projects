/*
 * bestcpudesign.c
 *
 *  Created on: Sep 16, 2016
 *      Author: Vishwanath
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*Defining the memory size and Register count*/
#define MEMSIZE 4095
#define REGCNT 8
#define OS_LIMIT 127
#define INST_LIMIT 1023
#define INST_LEN 20

/*Creating arrays to store the values of memory. Basic data type for
 * registers,flags and instruction pointer*/
int mem[MEMSIZE+1];
int r0,r1,r2,r3,r4,r5,r6,r7;
int flagreg=0;
uint16_t instptr=0;

/*
Function declaration
 */

void init_memory();
void init_registers();
void display();
int loadreg();
int storereg();

//main method
int main(void){
	//Variables for input
		int inst_num;
		char userinst[INST_LEN];
		char *loc1,*loc2,*off,*oper,*tempstr;

		init_memory();
		printf("Memory loaded with initial values.\n");
		init_registers();
		printf("Registers loaded with initial values.\n");

		//display();

		//Asking user Input
		printf("Enter an instruction number 1. Load 2. Store 3. Exit\n");
		scanf("%d",&inst_num);
		getchar();

		//Give Further instructions to the user
		switch(inst_num){
		case 1:
			printf("\nYou have selected Load. Instruction should be of the form lw reg,(off)mem\n");
			break;
		case 2:
			printf("\nYou have selected Store. Instruction should be of the form sw reg,(off)mem\n");
			break;
		case 3:
			printf("\nYou have selected Exit. Exiting the program\n");
			break;
		}

		fgets(userinst,INST_LEN,stdin); //User Instruction is stored here

		int len = strlen(userinst);
		userinst[len-1]='\0';

		//Breaking the Instruction and storing values for Load/Store
		oper=strtok(userinst," ");
		tempstr= strtok(NULL," ");
		loc1=strtok(tempstr,",(");

		tempstr= strtok(NULL,",(");
		off=strtok(tempstr,")");

		tempstr= strtok(NULL,")");
		loc2=tempstr;

		//Displaying the values from User Instruction
		printf("Operation:%s\n",oper);
		printf("Reg:%s Offset:%s Memory:%s\n",loc1,off,loc2);
	getchar();
	return 0;
}


//Function to initialize memory locations to 1
void init_memory(){
	int i;
	for(i=0;i<=OS_LIMIT;i++){
		mem[i]=0;
	}

	for(i=OS_LIMIT+1;i<MEMSIZE+1;i++){
		mem[i]=1;
	}

}

//Function to initialize register values to 0
void init_registers(){
	r0=r1=r2=r3=r4=r5=r6=r7=0;

}

//Function to display values at a given time
void display(){
	int x=0,y=0;
	printf("\n\nValues in Instruction Memory\n\n");
	printf("Loc  Value  Loc  Value  Loc  Value  Loc  Value  Loc  Value  Loc  Value\n");

	for(x=OS_LIMIT+1,y=1;x<=INST_LIMIT;x++,y++){
		printf("%d\t%d   ",x,mem[x]);
		if(y%6==0){
			printf("\n");
		}
	}
	//getchar();
	printf("\n\nValues in Main Memory\n\n");
	printf("Loc  Value  Loc  Value  Loc  Value  Loc  Value  Loc  Value  Loc  Value\n");

	for(x=INST_LIMIT+1,y=1;x<=MEMSIZE+1;x++,y++){
		printf("%d\t%d   ",x,mem[x]);
		if(y%6==0){
			printf("\n");
		}
	}
	//getchar();
	printf("\n\nThe register values are as follows:\n\n");
	printf("Reg0:%d\tReg1:%d\tReg2:%d\tReg3:%d\tReg4:%d\tReg5:%d\tReg6:%d\tReg7:%d\t\n",r0,
			r1,r2,r3,r4,r5,r6,r7);

	printf("\nThe flag value is:%d\n",flagreg);

	getchar();
}
