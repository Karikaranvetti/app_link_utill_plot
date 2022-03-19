#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "app_deff.h" 




// Function to Create A New Node
Node* newNode(device_data d)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = d;
	temp->priority = d.ts;
	temp->next = NULL;

	return temp;
}
// Function to check is list is empty
int isEmpty(Node** head)
{
	return (*head) == NULL;
}
// Return the value at head
device_data peek(Node** head)
{
	return (*head)->data;
}

// Removes the element with the
// highest priority form the list
void pop(Node** head)
{
	Node* temp = *head;
	(*head) = (*head)->next;
	free(temp);
}

// Function to push according to priority
void push(Node** head, device_data d)
{
	Node* start = (*head);

	// Create new Node
	Node* temp = newNode(d);

	// Special Case: The head of list has lesser
	// priority than new node. So insert new
	// node before head node and change head node.

    if(isEmpty(head)){
        *head=temp;

    }else if ((*head)->priority > d.ts) {

		// Insert New Node before head
		temp->next = *head;
		(*head) = temp;
	}
	else {

		// Traverse the list and find a
		// position to insert new node
		while (start->next != NULL &&
			start->next->priority < d.ts) {
			start = start->next;
		}

		// Either at the ends of the list
		// or at required position
		temp->next = start->next;
		start->next = temp;
	}
}


void data_process(){
    data_count[1].count=0;
    data_count[0].count=0;
	device_data data;
    while (true)
    {   
        
        flag=0; 
		while(!isEmpty(&buffer_que2)){
			data=peek(&buffer_que2);
			pop(&buffer_que2);
			data_que[0][data_count[0].count].app_id=data.app_id;
			data_que[0][data_count[0].count].device_id=data.device_id;
			data_que[0][data_count[0].count].recived_data=data.recived_data;
			data_que[0][data_count[0].count].send_data=data.send_data;
			data_que[0][data_count[0].count].ts=data.ts;
			printf("The data time is :%d\nThe device id is :%d\nThe App id is :%d\nThe recive data is :%ld\nThe device send data is :%ld\nthe count1 %d and count2 %d\n",data.ts,data.device_id,data.app_id,data.recived_data,data.send_data,data_count[0].count,data_count[1].count);
			data_count[0].count++;
		}
        sleep(10);
        flag=1; 
		while(!isEmpty(&buffer_que1)){
			data=peek(&buffer_que1);
			pop(&buffer_que1);
			data_que[0][data_count[0].count].app_id=data.app_id;
			data_que[0][data_count[0].count].device_id=data.device_id;
			data_que[0][data_count[0].count].recived_data=data.recived_data;
			data_que[0][data_count[0].count].send_data=data.send_data;
			data_que[0][data_count[0].count].ts=data.ts;
			printf("The data time is :%d\nThe device id is :%d\nThe App id is :%d\nThe recive data is :%ld\nThe device send data is :%ld\nthe count1 %d and count2 %d\n",data.ts,data.device_id,data.app_id,data.recived_data,data.send_data,data_count[0].count,data_count[1].count);
			data_count[0].count++;
		}

        sleep(10);
    }
    
}

