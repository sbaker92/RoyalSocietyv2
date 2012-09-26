#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"
#include "cinder/Color.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//Default constructor
Node::Node(){
	next = prev = this;
}

//Constructor with arguments
Node::Node(uint8_t* pixels, int centerx, int centery, int radius, int thickness, Color8u color){
	next = prev = this;
	rad = radius;
	x = centerx;
	y = centery;
	col = color;
	thick = thickness;
}

//drawNode method that should draw circles that are
//nodes, but doesn't.
void Node::drawNode(int textureSize, uint8_t* pixels){
	if (rad <= 0)
		return;
	// This is a lazy way to do the circles
	gl::drawSolidCircle(Vec2f(x,y), rad);
}

//Super awesome insertAfter method.
void Node::insertAfter(Node* afterMe, Node* toInsert){
	toInsert->next = afterMe->next;
	afterMe->next = toInsert;
	toInsert->next->prev = toInsert;
	toInsert->prev = afterMe;
}