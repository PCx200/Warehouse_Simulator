#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"

//As a base I used GeeksForGeeks https://www.geeksforgeeks.org/dsa/queue-linked-list-implementation/

//Arrival Queue = Node-Backed Queue

template <typename T>

class ArrivalQueue {
private:
	Node<T>* front;
	Node<T>* rear;
	int currsize;

public:
	ArrivalQueue()
	{
		this->front = this->rear = nullptr;
		this->currsize = 0;
	}

	void enqueue(T data)
	{
		Node<T>* node = new Node<T>(data);
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
	
	//Make sure to use isEmpty() before using dequeue()
	T dequeue()
	{
			Node<T>* temp = front;
			T removedData = temp->data;
			front = front->next;

			if (front == nullptr) rear = nullptr;

			currsize--;
			delete temp;
			return removedData;
	}

	bool isEmpty()
	{
		return front == nullptr;
	}
	
	T getFront()
	{
		return front->data;
	}

	int size() {
		return currsize;
	}
};

