#pragma once

#include <iostream>
#include <string>
#include <sstream>

template <typename T>

class Node {
public:
	T data;
	Node<T>* next;

	Node(T data) {
		this->data = data;
		next = nullptr;
	}
};
