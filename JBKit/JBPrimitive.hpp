//
//  JBPrimitive.hpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBPrimitive_hpp
#define JBPrimitive_hpp
#ifdef __cplusplus

#include <JBKit/JBTypes.h>
#include <JBKit/JBOffsets.hpp>

#include <vector>
#include <iostream>

namespace JBKit {

class JBPrimitive{
    
public:
    JBPrimitive();
    virtual ~JBPrimitive();
    
#pragma mark public exploit init/cleanup
    virtual bool initPrimitive(JBOffsets offsets, readfunc_t func_read, writefunc_t func_write, execfunc_t func_exec = NULL) = 0;
    virtual void cleanupPrimitive() = 0;
    
#pragma mark infos
    virtual const char *primitiveName() = 0;
    
#pragma mark availability infos
    bool hasRead() const noexcept;
    bool hasWrite() const noexcept;
    virtual bool hasRead64() const noexcept;
    virtual bool hasRead32() const noexcept;
    virtual bool hasReadGeneric() const noexcept;
    virtual bool hasWrite64() const noexcept;
    virtual bool hasWrite32() const noexcept;
    virtual bool hasWriteGeneric() const noexcept;
    virtual bool hasExecute() const noexcept;

#pragma mark primitives
    virtual uint64_t read64(kptr_t kaddr);
    virtual uint32_t read32(kptr_t kaddr);
    virtual size_t read_generic(kptr_t kaddr, void *dstbuf, size_t size, BOOLEAN honorSizeLimit = FALSE);

    virtual void write64(kptr_t kaddr, uint64_t val);
    virtual void write32(kptr_t kaddr, uint32_t val);
    virtual size_t write_generic(kptr_t kaddr, const void *srcbuf, size_t size, BOOLEAN honorSizeLimit = FALSE);

    virtual kptr_t execute(kptr_t kaddr, callargs_t args = {});
    
    virtual kptr_t getKernelBase();

#pragma mark transfer
    virtual void sendPrimitive(mach_port_t dst); //port with send right
    virtual void recvPrimitive(mach_port_t src); //port with recv right

#pragma mark static
    static void registerPrimitive(JBPrimitive *prim) noexcept;
    static JBPrimitive *getPrimitiveWithName(const char *name) noexcept;
    static std::vector<std::string> listRegisteredPrimitives() noexcept;
};

}

#endif //__cplusplus
#endif /* JBPrimitive_hpp */
