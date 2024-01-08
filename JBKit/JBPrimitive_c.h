//
//  JBPrimitive_c.hpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBPrimitive_c_h
#define JBPrimitive_c_h

#include <JBKit/JBOffsets_c.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

typedef void* JBPrimitive_ctx_t;

#pragma mark get primitive

/*
    Return:
        returns a null terminated list of char *
        caller needs to pass it to JBPrimitive_freeRegisteredPrimitivesList to free resources
 */
char **JBPrimitive_getRegisteredPrimitivesList();
void JBPrimitive_freeRegisteredPrimitivesList(char **list);

JBPrimitive_ctx_t JBPrimitive_getPrimitiveWithName(const char *name);

#pragma mark use #pragma mark use exploit
int JBPrimitive_primitive_init(JBPrimitive_ctx_t ctx, JBOffset_ctx_t offsets, readfunc_t func_read, writefunc_t func_write, execfunc_t func_exec);
int JBPrimitive_primitive_cleanup(JBPrimitive_ctx_t ctx);

const char * JBPrimitive_primitive_primitiveName(JBPrimitive_ctx_t ctx);

BOOLEAN JBPrimitive_primitive_hasRead(JBPrimitive_ctx_t ctx);
BOOLEAN JBPrimitive_primitive_hasWrite(JBPrimitive_ctx_t ctx);
BOOLEAN JBPrimitive_primitive_hasRead64(JBPrimitive_ctx_t ctx);
BOOLEAN JBPrimitive_primitive_hasRead32(JBPrimitive_ctx_t ctx);
BOOLEAN JBPrimitive_primitive_hasReadGeneric(JBPrimitive_ctx_t ctx);
BOOLEAN JBPrimitive_primitive_hasWrite64(JBPrimitive_ctx_t ctx);
BOOLEAN JBPrimitive_primitive_hasWrite32(JBPrimitive_ctx_t ctx);
BOOLEAN JBPrimitive_primitive_hasWriteGeneric(JBPrimitive_ctx_t ctx);
BOOLEAN JBPrimitive_primitive_hasExecute(JBPrimitive_ctx_t ctx);

int JBPrimitive_primitive_sendPrimitive(JBPrimitive_ctx_t ctx, mach_port_t dst); //port with send right
int JBPrimitive_primitive_recvPrimitive(JBPrimitive_ctx_t ctx, mach_port_t src); //port with recv right

uint64_t JBPrimitive_primitive_read64(JBPrimitive_ctx_t ctx, kptr_t kaddr);
uint32_t JBPrimitive_primitive_read32(JBPrimitive_ctx_t ctx, kptr_t kaddr);
size_t JBPrimitive_primitive_read_generic(JBPrimitive_ctx_t ctx, kptr_t kaddr, void *dstbuf, size_t size, BOOLEAN honorSizeLimit);

int JBPrimitive_primitive_write64(JBPrimitive_ctx_t ctx, kptr_t kaddr, uint64_t val);
int JBPrimitive_primitive_write32(JBPrimitive_ctx_t ctx, kptr_t kaddr, uint32_t val);
size_t JBPrimitive_primitive_write_generic(JBPrimitive_ctx_t ctx, kptr_t kaddr, const void *srcbuf, size_t size, BOOLEAN honorSizeLimit);

kptr_t JBPrimitive_primitive_execute(JBPrimitive_ctx_t ctx, kptr_t kaddr, callargs_t args);
#ifdef __cplusplus
};
#endif //__cplusplus
#endif /* JBPrimitive_c_h */
