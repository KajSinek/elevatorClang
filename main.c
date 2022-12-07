#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


//struct of elevator
typedef struct Elevator {
	int floor;
	bool up;
	bool down;
} elevator;

//max & min floor
const int MaxFloors = 5;
const int MinFloors = 0;

void callEle(int actFloor, int persFloor, int sameFloor, int exit);
void emergency();
int verification(char id[9]);


int main(int argc, char *argv[]) {
	elevator first; 
	char repeat, idCard[9];
	int persFloor = 0, i = 0, nextFloor;
	
	srand(time(NULL));
	
	printf("Welcome in the simulation of elevator by Majstri s.r.o building.\n\n");
	printf("You have entered the building and you are going to the elevator. The building has %d floors. Call the elevator and choose the floor.\n", MaxFloors);

	first.floor = rand()%((MaxFloors+1)-MinFloors) + MinFloors; //random number of floor for elevator
	
	do {
		
		//If elevator is not on the same floor like person
		if(persFloor != first.floor) {
			printf("You are calling the elevator. You are on the %d. floor.\n", persFloor);
			callEle(first.floor, persFloor, 0, 0); //calling elevator if it's not on the same floor
		}
		
		
		printf("Which floor do you want to go to?\n");
		printf("For administration floor, please insert your idCard\n");
		scanf("%s", &idCard);
		int verified = verification(idCard);
		printf("------------------------------------------------------\n");
		
		//list of floors
		for(i = MinFloors ; i <= MaxFloors ; i++) {
			printf("%d ", i);
			if(i != MaxFloors) {
				printf("- ");
			}
		}
		printf("\n------------------------------------------------------\n");
		
		do {
			do{
			
			fflush(stdin); //clean buffer
			scanf("%d", &nextFloor);
			if(nextFloor < MinFloors || nextFloor > MaxFloors) {
				printf("Invalid selection, please repeat your selection!\n");
			}
			
			if(nextFloor == 5 && verified != 0) {
				printf("You don't have permission for this floor, please repeat your selection!\n");
			}
			
			}while(nextFloor == 5 && verified != 0); //verify if someone has permissions to 5th floor
			
		}while((nextFloor < MinFloors || nextFloor > MaxFloors)); //check if selected floor is between min and max floor of building
		
		first.floor = persFloor;
		int equalFloor = 0;
	
		if(first.floor == persFloor) {
			equalFloor = 1;
		}
		persFloor = nextFloor;
		callEle(first.floor, persFloor, equalFloor, 1); //using elevator
		
		do {
			printf("Do you want to continue? T/F\n");
			fflush(stdin);
			scanf("%c", &repeat);
			if(repeat != 't' && repeat != 'T' && repeat != 'f' && repeat != 'F') {
				printf("Invalid selection, please repeat your selection!\n");
			}	
		}while(repeat != 't' && repeat != 'T' && repeat != 'f' && repeat != 'F'); //check if someone want to use again this simulation

		
		int sameFloor = rand()%((1+1)-0) + 0; //1:2 possibility that the elevator is not on the same floor
		
		if(sameFloor) {
			first.floor = rand()%((MaxFloors+1)-MinFloors) + MinFloors; //random set floor of the elevator
		} else {
			first.floor = nextFloor;
		}
		
		printf("\n\n\n");
		
	} while(repeat == 't' || repeat == 'T');
	
	
	printf("Bye");
	return 0;
}
	
void callEle(int elevFloor, int persFloor, int sameFloor, int exit) {
	
	while(elevFloor != persFloor) {
		if(persFloor <= elevFloor) {
			printf("Elevator - floor = %d \n", elevFloor);
			
			if(sameFloor){
				int possDamage = rand()%((10+1)-1) + 1; //1:10 possibility that elevator has failure
				
				if(possDamage == 1) {
					emergency();
				}
			}
			
			elevFloor = --elevFloor;
			sleep(1);
		} else if(persFloor >= elevFloor) {
			printf("Elevator - floor = %d \n", elevFloor);
			
			if(sameFloor){
				int possDamage = rand()%((10+1)-1) + 1; //1:10 possibility that elevator has failure
				
				if(possDamage == 1) {
					emergency();
				}
			}
			
			elevFloor = ++elevFloor;
			sleep(1);
		}
	}
	
	elevFloor = persFloor;
	printf("Elevator - floor = %d \n", elevFloor);
	if(exit) {
		printf("You have left of the elevator. The doors are closing.\n");
	} else {
		printf("You have entered the elevator. The doors are closing.\n");
	}
	
	
}

void emergency() {
	printf("Emergency is on the way! Help is comming!\n");
	int minutesWait = rand()%((100+1)-10) + 10; //random generator of time for time
	
	printf("Help will come in %d minutes.\n", minutesWait);
	sleep(minutesWait/10); //set to seconds (in 1-10s) and "sleep"
	
	printf("Help has come to the place of the call.\n");
	int randSolution = rand()%((1+1)-0) + 0; //1:2 possibility of succesful elevator repair
	
	if(randSolution) {
		printf("You have been saved and the elevator was not repaired. Please use the stairs next to the elevator.\n");
		_Exit(0);
	}
	
	if(!randSolution) printf("The elevator was repaired\n");
}

int verification(char id[9]) {
	FILE *fp;
	char c, str[9];;
	char* ids;
	int i = 0, j = 0, verified = 0;
	
	fp = fopen("idCards.txt", "r");
	ids = malloc((100*8) * sizeof(char));
	
	if (fp == NULL){
        printf("Cannot open the file. \n");
        _Exit(0);
    }
    
    if(ids == NULL) {
    	printf("The memory was not allocated. \n");
    	_Exit(0);
	}
	
	c = fgetc(fp);
	
	//reading file
    while (c != EOF){
    	if(c == '\n') {
    		j++;
    		i = 0;
    		c = fgetc(fp);
			continue;
		}
        ids[j*8+i] = c;
        c = fgetc(fp);
        i++;
    }
    
    //using values from files
    for(j = 0 ; j < 3 ; j++) {
    	for(i= 0 ; i < 8 ; i++) {
			str[i] = ids[j*8+i];
		}
		str[8] = '\0';
		verified = strcmp(str, id);
		if(!verified) break;
	}
   	
	fclose(fp);
	free(ids);
	
	printf("\n");
	
	return verified;
}
