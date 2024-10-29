/*
ASSIGNMENT LINK:
https://docs.google.com/document/d/1OyD3zhrcfqp2BxjtjjxRy3-1zKaSE4bKpFtxIOjl5rY/edit?usp=sharing

PROJECT TITLE: Employee Database
DESCRIPTION: This program loads data from a text file and allows an admin to easily access and make changes to the data. It then saves the modified data back to the text file.

CHANGE LOG:
-------------------------------------------------------------------------------------------------------
DATE		VERSION		PROGRAMMER	CHANGES	
-------------------------------------------------------------------------------------------------------
2020-10-12	1.0			RH			Stub project created.
2020-03-18  1.1         DG/KM       First working version (as far as we're concerned).
-------------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strlib.h"

#define BOOL int
#define TRUE 1
#define FALSE 0
// Structure for the elements of the linked list
typedef struct Employee {
	int id;
	char* firstName;
	char* lastName;
	char* jobTitle;
	char* department;
	int isTail;
	struct Employee* prevEmployee;
	struct Employee* nextEmployee;
}Employee;

// Pointer to the head of the linked list.
static struct Employee* head;

// Function that gets the number of digits in a number. Accepts the number and returns the number of digits
int numDigits(int);

// Frees the pointers in the lined list
void closeAll();

// Saves the data fro the linked list to the data.txt file.
void saveFile();

// Allows the user to edit the data of an employee
void editEmployee();

// Sorts the linked list. Accepts the head of the list and a string representing how to sort it.
// Generously donated by Mr.H
void sortList(struct Employee*, char*);

// Loads all the employee data from the data.txt file and connects the pointers to the head
void loadEmployee();

// Function which adds a new employee based on the user
// Must have a unique ID
void loadNewEmployee();

// Function which appends a new element to the end of the linked list
void append(struct Employee** head_ref, int id, char* lastName, char* firstName, char* jobTitle, char* department);

// Function to find the length of the linked list
int length();

// Function for the main menu, where every choice is made
int mainMenu();

// Function which swaps two elements in a linked list
// Generously donated by Mr.H
void swapPtr(struct Employee* temp, struct Employee* temp2);

// Function which prints a formatted list of all Employees
void printList();

// Function for printing out spaces
// Accepts the number of spaces to be printed.
void printSpaces (int numSpaces);

// Function which deletes an Employee given their ID
void deleteEmployee();

int main() {
	loadEmployee();
	mainMenu();
	return 0;
}

int mainMenu() {
	saveFile();
	system("clear");
	char input[8];
	char response; 
	int invalid = 1;
	printf("Employee Database\n-------------------------------------------\n");
	printf("[a] List employees by ID number.\n");
	printf("[b] List employees by last name.\n");
	printf("[c] List employees by first name.\n");
	printf("[d] List employees by job title.\n");
	printf("[e] List employees by department.\n");
	printf("[f] Add an employee to the database.\n");
	printf("[g] Remove an employee from the database.\n");
	printf("[h] Edit an existing employee.\n");
	printf("[i] Exit the program.\n");
	while (invalid) {
		printf("Selection: ");
		fgets(input, 7, stdin);
		sscanf(input, "%c", &response);
		if (response > 105 || response < 96) {
			printf("Invalid input!\n");
			invalid = 1;
		}
		else if (response == 'i') {
			closeAll();
			system("clear");
			printf("Goodbye!\n");
			exit(0);
		}
		else if (response == 'a') {
			sortList(head, "id");
			printList();
			mainMenu();
		}
		else if (response == 'b') {
			sortList(head, "lastName");
			printList();
			mainMenu();
		}
		else if (response == 'c') {
			sortList(head, "firstName");
			printList();
			mainMenu();
		}
		else if (response == 'd') {
			sortList(head, "jobTitle");
			printList();
			mainMenu();
		}
		else if (response == 'e') {
			sortList(head, "department");
			printList();
			mainMenu();
		}
		else if (response == 'f') {
			loadNewEmployee();
			mainMenu();
		}
        else if (response == 'g') {
            deleteEmployee();
            mainMenu();
        }
		else if (response == 'h') {
			editEmployee();
			mainMenu();
		}
		else {
			invalid = 0;
		}
	}
	return 0;
}

void loadEmployee() {
	char input[64];
	int n;
	char* token;
	char* lastName = malloc(sizeof(char) * 64);
	char* firstName = malloc(sizeof(char) * 64);
	char* jobTitle = malloc(sizeof(char) * 64);
	char* department = malloc(sizeof(char) * 64);
	FILE* file = fopen("data.txt","r");
	append(&head, 0, " ", " ", " ", " ");
	while (fgets(input, 63, file) != NULL) {
		token = strtok(input, ", ");
		// scan for id
		sscanf(token, "%d", &n);
		token = strtok(NULL, ", ");
		// scan for lastName
		sscanf(token, "%s", lastName);
		token = strtok(NULL, ",");
		// scan for firstName
		sscanf(token, "%s", firstName);
		token = strtok(NULL, ",");
		// scan for jobTitle
		sscanf(token, "%99[^=]", jobTitle);
		token = strtok(NULL, ",");
		// scan for department
		sscanf(token, "%99[^\n]", department);

		append(&head, n, lastName, firstName, jobTitle, department);
	}
    free(lastName);
    free(firstName);
    free(jobTitle);
    free(department);
	append(&head, 99999999, "zzzzzzzzzz", "zzzzzzzzzz", "zzzzzzzzzz", "zzzzzzzzz");
	fclose(file);
}

void append(struct Employee** head_ref, int id, char* lastName, char* firstName, char* jobTitle, char* department) { 
    struct Employee* newEmployee = (struct Employee*) malloc(sizeof(struct Employee)); 
    struct Employee *last = *head_ref;
    newEmployee->id = id;
	// malloc for memory
	newEmployee->lastName = malloc(sizeof(char) * 64);
	newEmployee->firstName = malloc(sizeof(char) * 64);
	newEmployee->jobTitle = malloc(sizeof(char) * 64);
	newEmployee->department = malloc(sizeof(char) * 64);
	// setting the linked list values
	strcpy(newEmployee->lastName, lastName);
	strcpy(newEmployee->firstName, firstName);
	strcpy(newEmployee->jobTitle, jobTitle);
	strcpy(newEmployee->department, department);
    newEmployee->nextEmployee = NULL; 
	newEmployee->isTail = 1;
    if (*head_ref == NULL) { 
       *head_ref = newEmployee; 
       return; 
    }   
    while (last->nextEmployee != NULL) {
        last = last->nextEmployee; 
	}
    last->nextEmployee = newEmployee; 
	newEmployee->prevEmployee = last;
	newEmployee->prevEmployee->isTail = 0;  
} 

int length() {
	int length = 0;
	struct Employee *current;
	for(current = head; current != NULL; current = current->nextEmployee) {
		length++;
	}
  	return length;
}

void swapPtr(Employee* emp1, Employee* emp2) {
    Employee* emp0 = emp1->prevEmployee;
    Employee* emp3 = emp2->nextEmployee;
    emp2->nextEmployee = emp1;
    emp1->prevEmployee = emp2;
    emp1->nextEmployee = emp3;
   	emp3->prevEmployee = emp1;
    emp0->nextEmployee = emp2;
    emp2->prevEmployee = emp0;
}

void sortList(Employee* head, char* type) {
    int comparison;
    Employee* current = head->nextEmployee;
    Employee* temp = current;
	Employee* temp2 = current->nextEmployee;
    int numSwaps = 0;
    do {
        current = head->nextEmployee;
        numSwaps = 0;
        while (current->nextEmployee != NULL && current->nextEmployee->isTail != 1) {
            temp = current;
            temp2 = current->nextEmployee;
            if (strcmp(type, "id") == 0) {
				comparison = 0;
				if (current->id > current->nextEmployee->id) {
					comparison = 1;
				}
			}
            else if (strcmp(type, "lastName") == 0) comparison = strcmp(current->lastName, current->nextEmployee->lastName) > 0;
            else if (strcmp(type, "firstName") == 0) comparison = strcmp(current->firstName, current->nextEmployee->firstName) > 0;
            else if (strcmp(type, "jobTitle") == 0) comparison = strcmp(current->jobTitle, current->nextEmployee->jobTitle) > 0;
            else if (strcmp(type, "department") == 0) comparison = strcmp(current->department, current->nextEmployee->department) > 0;
            if (comparison) {
                swapPtr(current, current->nextEmployee);
                numSwaps++;
            }
            current = current->nextEmployee;
        }
    } while (numSwaps > 0);
}

void printList() {
    system("clear");
    printf("ID        LAST NAME       FIRST NAME       JOB TITLE           DEPARTMENT\n");
    printf("----------------------------------------------------------------------------------\n");
    int numSpaces = 0;
    struct Employee *currentEmployee = head;
	int numEmployees = length();
    for (int i = 1; i < numEmployees - 1; i++) {
        currentEmployee = currentEmployee->nextEmployee;
        printf("%d", currentEmployee->id);
        numSpaces = 10 - numDigits(currentEmployee->id);
        printSpaces(numSpaces);
        printf("%s", currentEmployee->lastName);
        numSpaces = 16 - getLength(currentEmployee->lastName);
        printSpaces(numSpaces);
        printf("%s", currentEmployee->firstName);
        numSpaces = 16 - getLength(currentEmployee->firstName);
        printSpaces(numSpaces);
        printf("%s", currentEmployee->jobTitle);
        numSpaces = 20 - getLength(currentEmployee->jobTitle);
        printSpaces(numSpaces);
        printf("%s", currentEmployee->department);
        printf("\n");
    }
    printf("----------------------------------------------------------------------------------\n\n");
    printf("Press ENTER to continue");
    getchar();
}

void printSpaces (int numSpaces) {
    for (int i = 0; i < numSpaces; i++) {
        printf(" ");
    }
    return;
}

void loadNewEmployee() {
	char input[64];
	int n; int invalidId = 1;
	Employee* emp = head;
	char* lastName = malloc(sizeof(char) * 64);
	char* firstName = malloc(sizeof(char) * 64);
	char* jobTitle = malloc(sizeof(char) * 64);
	char* department = malloc(sizeof(char) * 64);
	char* job = create(" ");
	char* dep = create(" ");
    BOOL inputReceived = TRUE;
    system("clear");
	while (invalidId) {
		inputReceived = TRUE;
		invalidId = 0;
		printf("Adding a new employee...\n");
		printf("ID: ");
		fgets(input, 63, stdin);
		sscanf(input, "%d", &n);
		while (emp->nextEmployee != NULL) {
			if (emp->id == n) {
				system("clear");
				printf("Someone with that ID already exists!\n\n");
                inputReceived = FALSE;
				invalidId = 1;
				break;
			}
			emp = emp->nextEmployee;
		} 
        if (inputReceived) {
            printf("Last name: ");
            fgets(input, 63, stdin);
            sscanf(input, "%99[^\n]", lastName);
            printf("First name: ");
            fgets(input, 63, stdin);
            sscanf(input, "%99[^\n]", firstName);
            printf("Job title: ");
            fgets(input, 63, stdin);
            sscanf(input, "%99[^\n]", jobTitle);
            strcat(job, jobTitle);
            printf("Department: ");
            fgets(input, 63, stdin);
            sscanf(input, "%99[^\n]", department);
            strcat(dep, department);
        }
	}
	free(emp->prevEmployee->nextEmployee);
	emp->prevEmployee->nextEmployee = NULL;
	append(&head, n, lastName, firstName, job, dep);
	append(&head, 99999999, "zzzzzzzzzz", "zzzzzzzzzz", "zzzzzzzzzz", "zzzzzzzzz");
	printf("\n\nAdded employee...\nID: %d\nLast name: %s\nFirst name: %s\nJob title: %s\nDepartment: %s\n\nPress ENTER to continue.", n, lastName, firstName, jobTitle, department);
	free(lastName);
    free(firstName);
    free(jobTitle);
    free(department);
    getchar();
}

void deleteEmployee() {
    system("clear");
    char inputBuffer[64];
    int input;
    BOOL inputReceived = FALSE;
    int index = 0;
    int i = 1;
    Employee* tempEmp = head;
    while (!inputReceived) {
        printf("Removing an employee...\nID: ");
        fgets(inputBuffer, 63, stdin);
        sscanf(inputBuffer, "%d", &input);
        while(tempEmp->nextEmployee != NULL) {
            tempEmp = tempEmp->nextEmployee;
            if (input == tempEmp->id) {
                inputReceived = TRUE;
                Employee* before = tempEmp->prevEmployee;
                Employee* after = tempEmp->nextEmployee;
                tempEmp->prevEmployee->nextEmployee = after;
                tempEmp->nextEmployee->prevEmployee = before;
                printf ("\nEmployee removed...\n");
                printf("ID: %d\n", tempEmp->id);
                printf("Last Name: %s\n", tempEmp->lastName);
                printf("First Name: %s\n", tempEmp->firstName);
                printf("Job Title: %s\n", tempEmp->jobTitle);
                printf("Department: %s\n", tempEmp->department);
                free(tempEmp);
            }
            i++;
        }
        if (!inputReceived) {
            system("clear");
            printf("ID number not valid.\n\n");
			tempEmp = head;
        }
    }
    printf("\nPress ENTER to continue."); getchar();
    return;
}

void editEmployee() {
    system("clear");
    char inputBuffer[64];
    int input;
    char editingSelection[4];
    char editingInput[64];
	char* editInput = malloc(sizeof(char) * 64);
    char selection;
    BOOL inputReceived = FALSE;
    BOOL editing = TRUE;
    int index = 0;
    int i = 1;
    Employee* tempEmp = head;
    while (!inputReceived) {
        printf("Editing an employee...\nID: ");
        fgets(inputBuffer, 63, stdin);
        sscanf(inputBuffer, "%d", &input);
        while(tempEmp->nextEmployee != NULL) {
            tempEmp = tempEmp->nextEmployee;
            if (input == tempEmp->id) {
                inputReceived = TRUE;
                system("clear");
                while (editing) {
                    selection = ' ';
                    printf("Editing an employee...\n");
                    printf("ID: %d\n", tempEmp->id);
                    printf("Last Name: %s\n", tempEmp->lastName);
                    printf("First Name: %s\n", tempEmp->firstName);
                    printf("Job Title:%s\n", tempEmp->jobTitle);
                    printf("Department:%s\n\n", tempEmp->department);
                    printf("[a] Edit last name.\n");
                    printf("[b] Edit first name\n");
                    printf("[c] Edit job title\n");
                    printf("[d] Edit department\n");
					printf("[e] Exit.\n");
                    printf("Selection: ");
                    fgets(editingSelection, 3, stdin);
                    sscanf(editingSelection, "%c", &selection);

                    if (selection == 'a') {
                        printf("\nLast name: ");
                        fgets(editingInput, 63, stdin);
						sscanf(editingInput, "%63[^\n]", editInput);
                        strcpy(tempEmp->lastName, editInput);
                        system("clear"); 
                    }
                    else if (selection == 'b') {
                        printf("\nFirst name: ");
                        fgets(editingInput, 63, stdin);
						sscanf(editingInput, "%63[^\n]", editInput);
                        strcpy(tempEmp->firstName, editInput);
                        system("clear"); 
                    }
                    else if (selection == 'c') {
						char* job = create(" ");
                        printf("\nJob title: ");
                        fgets(editingInput, 63, stdin);
						sscanf(editingInput, "%63[^\n]", editInput);
						strcat(job, editInput);
                        strcpy(tempEmp->jobTitle , job);
                        system("clear"); 
                    }
                    else if (selection == 'd') {
						char* department = create(" ");
                        printf("\nDepartment: ");
                        fgets(editingInput, 63, stdin);
						sscanf(editingInput, "%63[^\n]", editInput);
						strcat(department, editInput);
                        strcpy(tempEmp->department, department);
                        system("clear"); 
                    }
                    else if (selection == 'e') {
                        editing = FALSE;
                    }
                    else {
                        system("clear");
                        printf("Input not valid.\n\n");
                    }
                }
            }
            i++;
        }
        if (!inputReceived) {
            system("clear");
            printf("ID number not valid.\n\n");
			tempEmp = head;
        }
    }
    free(editInput);
    printf("\nPress ENTER to continue."); getchar();
    return;
}

void saveFile() {
	Employee* emp = head->nextEmployee;
	FILE* file = fopen("data.txt","w");
	while (emp->nextEmployee != NULL) {
		fprintf(file, "%d, %s, %s,%s,%s\n", emp->id, emp->lastName, emp->firstName, emp->jobTitle, emp->department);
		emp = emp->nextEmployee;
	}
	fclose(file);
}

int numDigits (int num) {
    int temp = num;
    int count = 0;
    while (temp != 0) {
        temp /= 10;
        count++;
    }
    return count;
}

void closeAll() {
	Employee* emp = head;
	Employee* tempEmp;
	while (emp->nextEmployee != NULL) {
		emp = emp->nextEmployee;
	}
	while (emp->prevEmployee != NULL) {
		tempEmp = emp->prevEmployee;
		free(emp);
		emp = tempEmp;
	}
	free(emp);
}