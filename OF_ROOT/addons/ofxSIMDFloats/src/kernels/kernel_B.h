

#ifndef OFX_SIMDFLOATS_KERNEL_B_H_INCLUDED
#define OFX_SIMDFLOATS_KERNEL_B_H_INCLUDED

#include "../functions.h"

namespace ofx {
    
    struct kernel_B
    {
    public:
        enum { BLOCK_SIZE = 16 }; // this defines how many elements of the array are processed by a single call to block()
        kernel_B(){};
        
        inline_f  void operator()(float* a, const float* b) const {
            (*a) = (*b);
        }


        inline_f  void block(float* a, const float* b) const {
            
            // load elements 
            f128 x0  = m_load(b);
            f128 x4  = m_load(b+4);
            f128 x8  = m_load(b+8);
            f128 x12 = m_load(b+12);           
            
            
            // store the results
            m_store(a,    x0);
            m_store(a+4,  x4);
            m_store(a+8,  x8);
            m_store(a+12, x12); 
        }

        
    };
}





#endif  // OFX_SIMDFLOATS_KERNEL_B_H_INCLUDED
