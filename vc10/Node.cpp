#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "C:\Users\BassPanda\My Documents\CSE 274\RoyalSocietyv2\vc10\Node.h"
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
	for(int m = y - rad; m <= y + rad; m++){
		for(int n = x - rad; n <= x + rad; n++){
			int dist = (int)sqrt((double)((n-x)*(n-x) + (m-y)*(m-y)));
			if (dist <= rad && dist >= rad-thick){
				pixels[3*(x + y * textureSize)] = col.r;
				pixels[3*(x + y * textureSize) + 1] = col.g;
				pixels[3*(x + y * textureSize) + 2] = col.b;
			}
		}
	}
}

//Super awesome insertAfter method.
void Node::insertAfter(Node* afterMe, Node* toInsert){
	toInsert->next = afterMe->next;
	afterMe->next = toInsert;
	toInsert->next->prev = toInsert;
	toInsert->prev = afterMe;
}