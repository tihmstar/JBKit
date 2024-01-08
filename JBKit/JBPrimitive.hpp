//
//  JBPrimitive.hpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBPrimitive_hpp
#define JBPrimitive_hpp

#include "JBTypes.h"
#include "JBOffsets.hpp"
#include <vector>

namespace JBKit {

class JBPrimitive{
    
public:
    JBPrimitive();
    virtual ~JBPrimitive();
    
#pragma mark public exploit init/cleanup
    virtual bool init(JBOffsets offsets) = 0;
    virtual void cleanup() = 0;
    
#pragma mark primitives
    //TODO
    virtual uint64_t read64(kptr_t kaddr);
    virtual uint32_t read32(kptr_t kaddr);

    virtual void write64(kptr_t kaddr, uint64_t val);
    virtual void write32(kptr_t kaddr, uint32_t val);

    virtual void execute(kptr_t kaddr, std::vector<kptr_t> args = {});
};

}
#endif /* JBPrimitive_hpp */
