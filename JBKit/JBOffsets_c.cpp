//
//  JBOffsets_c.cpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#include "JBOffsets_c.h"
#include "JBOffsets.hpp"
#include "JBMacros.h"

using namespace JBKit;


extern "C"
JBOffset_ctx_t JBOffsets_offsets_new(){
    try {
        return (JBOffset_ctx_t)new JBOffsets;
    } catch (...) {
        return NULL;
    }
}

extern "C"
void JBOffsets_offsets_free(JBOffset_ctx_t ctx){
    JBOffsets *obj = (JBOffsets*)ctx;
    safeDelete(obj);
}

extern "C"
int JBOffsets_offsets_setOffset(JBOffset_ctx_t ctx, const char *name, kptr_t offset){
    JBOffsets *obj = (JBOffsets*)ctx;
    try {
        obj->setOffset(name, offset);
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
kptr_t JBOffsets_offsets_getOffset(JBOffset_ctx_t ctx, const char *name){
    JBOffsets *obj = (JBOffsets*)ctx;
    try {
        return obj->getOffset(name);
    } catch (...) {
        return 0;
    }
}

extern "C"
int JBOffsets_offsets_saveOffsets(JBOffset_ctx_t ctx, const char *path){
    JBOffsets *obj = (JBOffsets*)ctx;
    try {
        obj->saveOffsets(path);
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
int JBOffsets_offsets_loadOffsets(JBOffset_ctx_t ctx, const char *path){
    JBOffsets *obj = (JBOffsets*)ctx;
    try {
        obj->loadOffsets(path);
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
int JBOffsets_offsets_sendOffsets(JBOffset_ctx_t ctx, mach_port_t dst){
    JBOffsets *obj = (JBOffsets*)ctx;
    try {
        obj->sendOffsets(dst);
        return 0;
    } catch (...) {
        return -1;
    }
}

extern "C"
int JBOffsets_offsets_recvOffsets(JBOffset_ctx_t ctx, mach_port_t src){
    JBOffsets *obj = (JBOffsets*)ctx;
    try {
        obj->recvOffsets(src);
        return 0;
    } catch (...) {
        return -1;
    }
}
