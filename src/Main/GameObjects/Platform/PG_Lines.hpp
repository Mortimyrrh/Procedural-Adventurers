//
//  PG_Lines.hpp
//
//  Created by Mortimer Pavlitski on 30/04/2018.
//

#ifndef PG_Lines_hpp
#define PG_Lines_hpp

#include <stdio.h>

#include "IPlatformGraphic.hpp"

class PG_Lines : public IPlatformGraphic {
public:
    PG_Lines();
    ~PG_Lines();
    
    void draw() override;
    
private:
};

#endif /* PG_Lines_hpp */
