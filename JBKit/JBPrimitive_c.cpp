//
//  JBPrimitive_c.cpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#include "JBPrimitive_c.h"
#include "JBPrimitive.hpp"

using namespace JBKit;

#pragma mark get primitive

extern "C"
char **JBPrimitive_getRegisteredPrimitivesList(){
    char **retval = NULL;
    std::vector<std::string> list;
    try {
        list = JBPrimitive::listRegisteredPrimitives();
    } catch (...) {
        return NULL;
    }
    retval = (char**)calloc(list.size()+1, sizeof(char*));
    {
        char **ri = retval;
        for (auto e : list) {
            *ri++ = strdup(e.c_str());
        }
    }
    return retval;
}

extern "C"
void JBPrimitive_freeRegisteredPrimitivesList(char **list){
    for (char **ri = list; *ri; ri++) {
        free(*ri);
    }
    free(list);
}

extern "C"
JBPrimitive_ctx_t JBPrimitive_getPrimitiveWithName(const char *name){
    try {
        return (JBPrimitive_ctx_t)JBPrimitive::getPrimitiveWithName(name);
    } catch (...) {
        return NULL;
    }
}

#pragma mark use #pragma mark use exploit

extern "C"
int JBPrimitive_primitive_initPrimitive(JBPrimitive_ctx_t ctx, JBOffset_ctx_t offsets, readfunc_t func_read, writefunc_t func_write, execfunc_t func_exec){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    JBOffsets *obj_offsets = (JBOffsets *)offsets;
    
    try {
        return obj->initPrimitive(*obj_offsets, func_read, func_write, func_exec) ? 0 : -2;
    } catch (...) {
        return -1;
    }
}

extern "C"
int JBPrimitive_primitive_cleanupPrimitive(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        obj->cleanupPrimitive();
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
const char * JBPrimitive_primitive_primitiveName(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->primitiveName();
    } catch (...) {
        return NULL;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasRead(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasRead();
    } catch (...) {
        return false;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasWrite(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasWrite();
    } catch (...) {
        return false;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasRead64(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasRead64();
    } catch (...) {
        return false;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasRead32(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasRead32();
    } catch (...) {
        return false;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasReadGeneric(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasReadGeneric();
    } catch (...) {
        return false;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasWrite64(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasWrite64();
    } catch (...) {
        return false;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasWrite32(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasWrite32();
    } catch (...) {
        return false;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasWriteGeneric(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasWriteGeneric();
    } catch (...) {
        return false;
    }
}

extern "C"
BOOLEAN JBPrimitive_primitive_hasExecute(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->hasExecute();
    } catch (...) {
        return false;
    }
}

extern "C"
int JBPrimitive_primitive_sendPrimitive(JBPrimitive_ctx_t ctx, mach_port_t dst){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        obj->sendPrimitive(dst);
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
int JBPrimitive_primitive_recvPrimitive(JBPrimitive_ctx_t ctx, mach_port_t src){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        obj->recvPrimitive(src);
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
uint64_t JBPrimitive_primitive_read64(JBPrimitive_ctx_t ctx, kptr_t kaddr){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->read64(kaddr);
    } catch (...) {
        return 0;
    }
}

extern "C"
uint32_t JBPrimitive_primitive_read32(JBPrimitive_ctx_t ctx, kptr_t kaddr){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->read32(kaddr);
    } catch (...) {
        return 0;
    }
}

extern "C"
size_t JBPrimitive_primitive_read_generic(JBPrimitive_ctx_t ctx, kptr_t kaddr, void *dstbuf, size_t size, BOOLEAN honorSizeLimit){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->read_generic(kaddr, dstbuf, size, honorSizeLimit);
    } catch (...) {
        return 0;
    }
}

extern "C"
int JBPrimitive_primitive_write64(JBPrimitive_ctx_t ctx, kptr_t kaddr, uint64_t val){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        obj->write64(kaddr,val);
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
int JBPrimitive_primitive_write32(JBPrimitive_ctx_t ctx, kptr_t kaddr, uint32_t val){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        obj->write32(kaddr,val);
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
size_t JBPrimitive_primitive_write_generic(JBPrimitive_ctx_t ctx, kptr_t kaddr, const void *srcbuf, size_t size, BOOLEAN honorSizeLimit){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->write_generic(kaddr, srcbuf, size, honorSizeLimit);
    } catch (...) {
        return 0;
    }
}

extern "C"
kptr_t JBPrimitive_primitive_execute(JBPrimitive_ctx_t ctx, kptr_t kaddr, callargs_t args){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->execute(kaddr,args);
    } catch (...) {
        return 0;
    }
}

extern "C"
kptr_t JBPrimitive_primitive_getKernelBase(JBPrimitive_ctx_t ctx){
    JBPrimitive *obj = (JBPrimitive *)ctx;
    try {
        return obj->getKernelBase();
    } catch (...) {
        return 0;
    }
}
