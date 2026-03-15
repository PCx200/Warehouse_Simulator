#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"
#include "Crate.h"
#include "Shelf.h"

//As a base I used GeeksForGeeks https://www.geeksforgeeks.org/cpp/program-to-implement-singly-linked-list-in-c-using-class/

//Warehouse = Node-Based Linked List for Shelves

class Warehouse {
private:
	Node<Shelf>* front;
	Node<Shelf>* rear;
	int currsize;
	static const int SHELF_LIMIT = 10;
	static const int SHELF_BULK_LIMIT = 4;

public:
	Warehouse() {
		this->front = this->rear = nullptr;
		this->currsize = 0;

		for (int i = 0; i < SHELF_LIMIT; i++) {
			Shelf shelf;
			add(shelf);
		}
	}

	void add(Shelf shelf) {
		Node<Shelf>* node = new Node<Shelf>(shelf);
		if (isEmpty()) {
			front = node;
			rear = node;
		}
		else {
			rear->next = node;
			rear = node;
		}
		currsize++;
	}

	void matrixPrint() {

		std::cout << "\n";
		int matrix[SHELF_LIMIT][SHELF_BULK_LIMIT];//Initialize the matrix
		std::string validShelvesArray[SHELF_LIMIT];//Print for GOOD or BAD
		Node<Shelf>* traverseNode = front;//Get the first shelf from the linked list and start traversing

		for (int i = 0; i < SHELF_LIMIT; i++) {
			for (int j = 0; j < SHELF_BULK_LIMIT; j++) {
				matrix[i][j] = 0;
			}
		}

		for (int i = 0; i < SHELF_LIMIT; i++) {
			Shelf& shelfInfo = traverseNode->data;// We get our Shelf object directly, no copy
			if (shelfInfo.isValid()) validShelvesArray[i] = "GOOD";
			else validShelvesArray[i] = "BAD";
			
			
			// From the Shelf object, we get the array with the crates
			for (int j = 0; j <= shelfInfo.getTopIndex(); j++) //We run through each crate in a shelf
			{
				matrix[i][j] = shelfInfo.getShelfArray()[j].weight;
			}

			traverseNode = traverseNode->next;
		}

		std::cout << "SHELF01 SHELF02 SHELF03 SHELF04 SHELF05" << std::endl;

		for (int col = SHELF_BULK_LIMIT - 1; col >= 0; col--)
		{
			for (int row = 0; row < SHELF_LIMIT / 2; row++)
			{
				if (matrix[row][col] > 0) printf("%-8d", matrix[row][col]);
				else printf("        ");
			}
			std::cout << "\n";		
		}
		printf("%-8s%-8s%-8s%-8s%-8s\n", 
			validShelvesArray[0].c_str(), 
			validShelvesArray[1].c_str(), 
			validShelvesArray[2].c_str(), 
			validShelvesArray[3].c_str(), 
			validShelvesArray[4].c_str());


		std::cout << "\n";

		std::cout << "SHELF06 SHELF07 SHELF08 SHELF09 SHELF10" << std::endl;

		for (int col = SHELF_BULK_LIMIT - 1; col >= 0; col--)
		{
			for (int row = SHELF_LIMIT / 2; row < SHELF_LIMIT; row++)
			{
				if (matrix[row][col] > 0) printf("%-8d", matrix[row][col]);
				else printf("        ");
			}
			std::cout << "\n";
		}
		printf("%-8s%-8s%-8s%-8s%-8s\n", 
			validShelvesArray[5].c_str(),
			validShelvesArray[6].c_str(),
			validShelvesArray[7].c_str(),
			validShelvesArray[8].c_str(),
			validShelvesArray[9].c_str());
	}

	void simplePrint() {
		Node<Shelf>* traverseNode = front;
		for (int i = 0; i < SHELF_LIMIT; i++) {
			traverseNode->data.simplePrint();
			traverseNode = traverseNode->next;
		}
	}

	void remove() {
		//Leave it like that because it doesnt do anything for us right now for HW1 Part 1
	}

	Node<Shelf>* getFront() {
		return front;
	}

	bool isEmpty() {
		return front == nullptr;
	}

	int getShelfLimit() {

		return SHELF_LIMIT;
	}
};



