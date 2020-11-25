//
//  GameController.hpp
//  PhysicsGameEngineTesting
//
//  Created by Mortimer Pavlitski on 24/01/2018.
//

#ifndef GameController_hpp
#define GameController_hpp

#include "ofMain.h"
#include <stdio.h>

// Takes care of keyboard input

class GameController {
public:
    GameController(){}
    ~GameController(){}
    
    void keyDown(int key);
    void keyUp(int key);
    
    bool getIsUpPressed();
    bool getIsDownPressed();
    bool getIsLeftPressed();
    bool getIsRightPressed();
    
    bool getIsSpacePressed();
        
private:
    bool isUpPressed_;
    bool isDownPressed_;
    bool isLeftPressed_;
    bool isRightPressed_;
    
    bool isSpacePressed_;
};

#endif /* GameController_hpp */
