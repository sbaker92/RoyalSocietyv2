#include "cinder/Color.h"

class Node{
public:
	Node(uint8_t* pixels, int centerx, int centery, int radius, int thickness, ci::Color8u color);
	Node();

	void drawNode(int textureSize, uint8_t* dataArray);

	Node* next;
	Node* prev;

	int rad;
	int x;
	int y;
	int thick;
	ci::Color8u col;
	
	void insertAfter(Node* afterMe, Node* toInsert); //inserts toInsert after afterMe
};

