#include "cinder/Color.h"

class Node{
public:
	struct Node(uint8_t* pixels, int centerx, int centery, int radius, int thickness);
	
	Node* next;
	Node* prev;
};

void insertAfter(Node* afterMe, Node* toInsert); //inserts toInsert after afterMe