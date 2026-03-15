#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Crate.h"

//As a base I used GeeksForGeeks https://www.geeksforgeeks.org/dsa/implement-stack-using-array/

//Arrival Queue = Array-Backed Queue


class Shelf {
private:
	Crate* shelfArray;
	int topIndex;
	int weight;
	int BULK_LIMIT = 4;
	int WEIGHT_LIMIT = 1000;

public:
	Shelf() {
		this->shelfArray = new Crate[BULK_LIMIT];
		this->topIndex = -1;
		this->weight = 0;
	}

	void push(Crate crate) {
		if (topIndex + 1 == BULK_LIMIT) return;
		else if (weight + crate.weight > WEIGHT_LIMIT) return;
		else if (topIndex != -1 && crate.weight > shelfArray[topIndex].weight) return;
		else {
			topIndex++;
			shelfArray[topIndex] = crate;
			weight += crate.weight;
		}
	}

	//Use only after seeing if it is empty
	Crate pop() {
			Crate temp = shelfArray[topIndex];
			weight -= shelfArray[topIndex].weight;
			topIndex--;
			return temp;
	}

	void simplePrint() {
		std::cout << "SHELF ";
		for (int i = 0; i < BULK_LIMIT; i++)
		{
			std::cout << shelfArray[i].weight << " ";
		}

		std::cout << std::endl;
	}

	//Use isEmpty() before this function
	Crate peekLast() {
		return shelfArray[topIndex];
	}

	//Use isEmpty() before this function
	Crate peekUUID(std::string uuid) {
		Crate searchedCrate;
		for (int i = 0; i < BULK_LIMIT; i++)
		{
			if (uuid == shelfArray[i].uuid) {
				searchedCrate = shelfArray[i];
				break;
			}
		}
		return searchedCrate;
	}

	bool isValid() {
		if (topIndex + 1 > BULK_LIMIT) return false;
		if (weight > WEIGHT_LIMIT) return false;
		for (int i = 0; i < topIndex - 1; i++) {
			if (shelfArray[i].weight < shelfArray[i + 1].weight) return false;
		}
		return true;
	}
	
	bool isEmpty() {
		return topIndex == -1;
	}

	bool isFull() {
		return topIndex == BULK_LIMIT - 1;
	}

	int getTopIndex() {
		return topIndex;
	}

	int getCurrentWeight() {
		return this->weight;
	}

	int getCurrentSize() {
		return topIndex + 1;
	}

	int getBulkLimit() {
		return BULK_LIMIT;
	}

	int getWeightLimit() {
		return WEIGHT_LIMIT;
	}

	Crate* getShelfArray() {
		return shelfArray;
	}
};
