//
//  PG_BlueBox.hpp
//
//  Created by Mortimer Pavlitski on 30/04/2018.
//

#ifndef PG_BlueBox_hpp
#define PG_BlueBox_hpp

#include <stdio.h>
#include "IPlatformGraphic.hpp"

class PG_BlueBox : public IPlatformGraphic {
public:
    PG_BlueBox();
    ~PG_BlueBox();
    
    void draw() override;
    
private:
};

#endif /* PG_BlueBox_hpp */
