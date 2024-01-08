//
//  JBOffsets.hpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBOffsets_hpp
#define JBOffsets_hpp
#ifdef __cplusplus

#include <JBKit/JBTypes.h>
#include <mach/mach.h>
#include <xpc/xpc.h>

namespace JBKit {

class JBOffsets {
private:
    xpc_object_t _xdict;
    
public:
    JBOffsets();
    ~JBOffsets();
    
    void setOffset(const char *name, kptr_t offset);
    kptr_t getOffset(const char *name);
    
    void saveOffsets(const char *path);
    void loadOffsets(const char *path);
    
    void sendOffsets(mach_port_t dst); //port with send right
    void recvOffsets(mach_port_t src); //port with recv right
};


}
#endif //__cplusplus

#endif /* JBOffsets_hpp */
