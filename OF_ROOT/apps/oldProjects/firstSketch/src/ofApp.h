#pragma once

#include "ofMain.h"
#include "string.h"

class ofApp : public ofBaseApp{
public:

    class Leon {
    public:
        float xpos = 550;
        float ypos = 300;
        float xvel = 0;
        float yvel = 0;
        float xacc = 0;
        float yacc = 0;
        bool isOnPlatform = false;
        bool isMovingUp = false;
    };
    
    class Platform {
    public:
        Platform(){}
        Platform(float x, float y, float w, float h)
        {
            x_ = x;
            y_ = y;
            w_ = w;
            h_ = h;
        };
        
        float x_ = 0;
        float y_ = 0;
        float w_ = 0;
        float h_ = 0;
    };
    
    
    class InputControl {
    public:
        bool isUpKeyActive = false;
        bool isDownKeyActive = false;
        bool isLeftKeyActive = false;
        bool isRightKeyActive = false;
        
        bool isAButtonActive = false;
        bool isBButtonActive = false;
    };


    void calculateLeon() {
        
        // Apply Forcess
        // // F = M * A
        // Leon.xacc = force / mass
        
        // Input Control
        
        
        if (inputControl.isUpKeyActive && leon.isOnPlatform && !leon.isMovingUp)
            leon.yacc += 3;
            
            
        if (inputControl.isDownKeyActive)
            leon.yacc += -0.1;
                
        if (inputControl.isLeftKeyActive)
            leon.xacc += -0.12;
                    
        if (inputControl.isRightKeyActive)
            leon.xacc += 0.12;
                        
        // Gravity
        if (!leon.isOnPlatform)
            leon.yvel += -1.5;

        
        // Calculate Velocity
        
        // V = U + (T * A)
        leon.xvel = leon.xvel + (timePassed * leon.xacc);
        leon.yvel = leon.yvel + (timePassed * leon.yacc);
        
        // if (Leon.xvel > 50) {
        //     Leon.xvel = 50
        // }
        // if (Leon.xvel < -50) {
        //     Leon.xvel = -50
        // }
        // if (Leon.yvel > 50) {
        //     Leon.yvel = 50
        // }
        // if (Leon.yvel < -50) {
        //     Leon.yvel = -50
        // }
        
        // Set position
        leon.xpos += leon.xvel;
        leon.ypos += leon.yvel;
        
        
        // Colition detection
        leon.isOnPlatform = false;
        
        int numPlatforms = sizeof(platforms)/sizeof(platforms[0]);
        
        for (int i = 0; i < numPlatforms; i++) {
            if(leon.xpos > platforms[i].x_ && leon.xpos < platforms[i].x_ + platforms[i].w_ &&
            leon.ypos < platforms[i].y_ + platforms[i].h_ && leon.ypos > platforms[i].y_ - 10) {
                leon.ypos = platforms[i].y_ + platforms[i].h_;
                leon.isOnPlatform = true;
            }
        }
        
        
        //ofLog() << "Leon.isOnPlatform " << leon.isOnPlatform;
        
        // console.log("acc x " + Leon.xacc + "acc y " + Leon.yacc)
        // console.log("vel x " + Leon.xvel + "vel y " + Leon.yvel)
        
        // reset acceilration + vel
        leon.xvel *= 0.85;
        leon.yvel *= 0.85;
        leon.xacc = 0;
        leon.yacc = 0;
        
        if (leon.ypos < -1000) {
            //respawn
            leon.ypos = 200;
            leon.xpos = 200;
            
            leon.xacc = 0;
            leon.yacc = 0;
            
            leon.xvel = 0;
            leon.yvel = 0;
            
            leon.isOnPlatform = false;
        }
        
        // Save Direction of travel
        if(leon.yvel > 0 ) {
            leon.isMovingUp = true;
        }
        if(leon.yvel < 0 ) {
            leon.isMovingUp = false;
        }
        
        ofLog() << "xacc " << int(leon.xacc);
        ofLog() << "yacc " << int(leon.yacc);
        
    }

    ////

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // My public VArs
    
    // window
    float windowHeight = 900;
    float windowWidth = 1440;
    
    //time
    float timeStamp = 0;
    float lastTimeStamp = 0;
    float timePassed = 0;
    
    Leon leon;
    
    InputControl inputControl;
    
    Platform p1 = *new Platform(100, 100, 800, 10);
    Platform p2 = *new Platform(500, 200, 200, 10);
    Platform p3 = *new Platform(200, 350, 200, 10);

    Platform platforms[3]{
        Platform(100, 100, 800, 10),
        Platform(500, 200, 200, 10),
        Platform(200, 350, 200, 10)};
    
    
    // My graphics calls
    // ofDrawRectangle(100, windowHeight - 100, 100, - 100);

    void drawLeon(float x, float y) {
        ofSetColor(ofColor::green);
        ofDrawRectangle(x - 15, windowHeight - y, 30, - 50);
    };
    
    
    void drawPlatform(Platform p) {
        ofSetColor(ofColor::blue);
        ofDrawRectangle(p.x_, windowHeight - p.y_, p.w_, -p.h_);
    }
        

		
};
