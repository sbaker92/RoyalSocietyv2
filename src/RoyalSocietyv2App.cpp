/*@author Stephanie Baker
This satisfies requirement B, part of requirement A, and
hopefully requirements C and E (but I can't be too sure).
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
//Had to include the full filepath for Node.h to keep
//the errors away. Probably won't be the same for everyone.
#include "Node.h"
#include "cinder/Text.h"
#include "cinder/Color.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RoyalSocietyv2App : public AppBasic {
  public:
	void setup();
	void mouseDown(MouseEvent event);	
	void mouseUp(MouseEvent event);
	void update();
	void draw();

	void prepareSettings(Settings* settings);

  private:
	Vec2i mousePos;
	Surface* mySurface;
	uint8_t* dataArray;
	Node* sentinel;
	void drawCircle(uint8_t* pixels, int centerx, int centery, int radius, int thickness, Color8u color);
	void keyDown(KeyEvent event);
	void reverse(Node* sentinel);
	
	Font* font;
	bool getText;
	bool mouseIsDown;

	static const int appWidth = 800;
	static const int appHeight = 600;
	static const int textureSize = 1024;
	
};

//Window size and all that jazz.
void RoyalSocietyv2App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

// The drawCircle method! With variable line thickness, just for the fun of it.
// Borrowed from my HW01App.
// Actually has no purpose with the way I ended up trying to do this.
void RoyalSocietyv2App::drawCircle(uint8_t* pixels, int centerx, int centery, int radius, int thickness, Color8u color){
	if (radius <= 0) 
		return;
	for(int y = centery - radius; y <= centery + radius; y++){
		for(int x = centerx - radius; x <= centerx + radius; x++){
			int dist = (int)sqrt((double)((x-centerx)*(x-centerx) + (y-centery)*(y-centery)));
			if (dist <= radius && dist >= radius-thickness){
				pixels[3*(x + y * textureSize)] = color.r;
				pixels[3*(x + y * textureSize) + 1] = color.g;
				pixels[3*(x + y * textureSize) + 2] = color.b;
			}
		}
	}
}

//Pressing buttons does stuff.
void RoyalSocietyv2App::keyDown(KeyEvent event){
	//Toggle text!
	if(event.getChar() == '?'){
		if(getText == true){
			getText = false;
		}
		else if(getText == false){
			getText = true;
		}
	}

	//Reverse the list when 'r' is pressed
	if(event.getChar() == 'r'){
		reverse(sentinel);
	}
}
	
// Logic for reversing the list. Unfortunately, we can't
//see this in action because of some silly drawNode() issue
void RoyalSocietyv2App::reverse(Node* sentinel){
	Node* temp = sentinel;
	do{
		Node* swap = temp->next;
		temp->next = temp->prev;
		temp->prev = swap;

		temp = temp->prev;

	}
	while(temp != sentinel);
}

void RoyalSocietyv2App::setup(){
	//The surface!
	mySurface = new Surface(textureSize, textureSize, false);

	//Default nodes that you can't see
	sentinel = new Node(dataArray, appWidth/2, appHeight/2, 25, 10, Color8u(0, 0, 0));
	sentinel->insertAfter(sentinel, new Node(dataArray, appWidth/2, appHeight/2, 25, 25, Color8u(0, 255, 0)));

	//Some text stuff
	getText = true;
	font = new Font("MV Boli", 48);
}

//This used to draw circles when you left clicked, but that
//turned out to be pointless. I couldn't get the node rendering
//to work, but right clicking is supposed to theoretically
//add a new node where you click.
void RoyalSocietyv2App::mouseDown( MouseEvent event ){
	mouseIsDown = true;
	if(event.isLeft()){
		int x = mousePos.x;
		int y = mousePos.y;
		//drawCircle(dataArray, x, y, 30, 25, Color8u(0, 50, 200));
	}
	if(event.isRight()){

		//Your mousePos variable was never set so I changed mousePos to event.getX/Y
		//So a right click gives you a new circle at the mouse position
		int x = event.getX();
		int y = event.getY();

		Node* node = new Node(dataArray, x, y, 30, 25, Color8u(255, 0, 0));
		node->insertAfter(sentinel->prev, node);
		//You dont need to call draw here as it will get drawn later when the main draw method gets called
		//node->drawNode(textureSize, dataArray);
	}
}

void RoyalSocietyv2App::mouseUp(MouseEvent event){
	mouseIsDown = false;
}

void RoyalSocietyv2App::update(){
	dataArray = (*mySurface).getData();

	//sentinel->drawNode(textureSize, dataArray);
}

//Draw method! For some reason, doesn't actually draw
//my nodes. Go figure.
void RoyalSocietyv2App::draw(){
	gl::draw(*mySurface);
	gl::color(Color(1.0f, .1f, .8f));

	//Render loop for those nasty nodes
	Node* temp = sentinel->prev;
	do{
		temp->drawNode(textureSize, dataArray);
		temp = temp->prev;
	}while(temp != sentinel->prev);

	//More text stuff
	if(getText == true){
		gl::drawStringCentered("Press 'r' to reverse the order of the list", Vec2f(appWidth/2, appHeight/3), Color(0.5f, 0.5f, 0.5f), *font);
		gl::drawStringCentered("Press '?' to toggle text", Vec2f(appWidth/2, appHeight/2), Color(0.5f, 0.5f, 0.5f), *font);
	}
	else{
		gl::color(Color(.7f, .1f, .8f));
	}
}

CINDER_APP_BASIC( RoyalSocietyv2App, RendererGl )
