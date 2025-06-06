#include <stdio.h>
#include <stdlib.h>

struct Node {
    int total_size;
    int free_size;
    int process_size;
    struct Node* next;
};

struct Node* head = NULL;

struct Node* createBlock(int size) {
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->total_size = size;
    newnode->free_size = size;
    newnode->process_size = 0;
    newnode->next = NULL;

    if (head == NULL) { 
        head = newnode;
    } else {
        struct Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
    }
    return newnode;
}

//function to allocate using first-fit strategy
int allocate(int process_size) {
	struct Node* ptr = head;
	while(ptr) {
		if (process_size < ptr->free_size) {
					ptr->process_size = ptr->process_size + process_size;
					ptr->free_size = (ptr->free_size - process_size);
					return 1;
					}
		ptr = ptr->next;
		}
	return 0; //Allocation unsuccessful
	
	}
					
			


void printStatus() {
    struct Node* current = head;
    while (current) {
        printf("\nBlock Size: %d \tProcess Size: %d \tFree Size: %d \t", 
                current->total_size, current->process_size, current->free_size);
        current = current->next;  
        }
        printf("\n\n");
        
}

int main() {
    createBlock(200);
    createBlock(500);
    createBlock(300);
    createBlock(100);
    
    printStatus();
    int choice,size;
    
    while(1) {
		printf("\n --------MENU------- \n 1.Allocate \n2.Display \n3.Exit\n");
		printf("Enter the choice : ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Enter the size of the process to be allocated......");
				scanf("%d",&size);
				if(allocate(size))
					printf("Process successfullyy allocated....");
				else
					printf("Unsuccessful allocation....");
				break;
			
			case 2:
				printf("Printing current memory status.....");
				printStatus();
				break;
			case 3:
				exit(0);
			default:
				printf("Invalid choice....");
				}
			}
				
					
				
    return 0;
}

