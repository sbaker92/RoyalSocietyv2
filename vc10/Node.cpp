#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "C:\Users\BassPanda\My Documents\CSE 274\RoyalSocietyv2\vc10\Node.h"
#include "cinder/Color.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Node::Node(uint8_t* pixels, int centerx, int centery, int radius, int thickness){
	next = prev = this;
}

void insertAfter(Node* afterMe, Node* toInsert){
	toInsert->next = afterMe->next;
	afterMe->next = toInsert;
	toInsert->next->prev = toInsert;
	toInsert->prev = afterMe;
}