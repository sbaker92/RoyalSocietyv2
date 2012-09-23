#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "C:\Users\BassPanda\My Documents\CSE 274\RoyalSocietyv2\vc10\Node.h"
#include "cinder/Text.h"
#include "cinder/Color.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RoyalSocietyv2App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	void prepareSettings(Settings* settings);

  private:
	Surface* mySurface;
	//uint8_t* pixels;
	Node* sentinel;
	void drawCircle(uint8_t* pixels, int centerx, int centery, int radius, int thickness, Color8u color);
	void keyDown(KeyEvent event);
	void reverse(Node* sentinel);
	
	Font* font;
	bool getText;

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

void RoyalSocietyv2App::keyDown(KeyEvent event){
	if(event.getChar() == '?'){
		if(getText == true){
			getText = false;
		}
		else if(getText == false){
			getText = true;
		}
	}
}
	
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
	mySurface = new Surface(textureSize, textureSize, false);

	getText = true;
	font = new Font("Comic Sans", 48);
	getText = true;

}

void RoyalSocietyv2App::mouseDown( MouseEvent event ){
}

void RoyalSocietyv2App::update(){
	uint8_t* dataArray = (*mySurface).getData();

	drawCircle(dataArray, appWidth/2, appHeight/2, 75, 5, Color8u(0, 255, 255));
	sentinel = new Node(dataArray, appWidth/2, appHeight/2, 25, 10);
}

void RoyalSocietyv2App::draw(){
	gl::draw(*mySurface);
	gl::color(Color(.7f, .1f, .8f));

	if(getText == true){
		//gl::drawString("Use the left arrow key to select objects and r to reverse order", Vec2f(50.0f,200.0f),Color(0.0f,0.5f,0.0f),*font);
		gl::drawStringCentered("Press '?' to remove text", Vec2f(appWidth/2, appHeight/2), Color(0.5f, 0.5f, 0.5f), *font);
	}
	else{
		gl::color(Color(.7f, .1f, .8f));
	}
}

CINDER_APP_BASIC( RoyalSocietyv2App, RendererGl )
