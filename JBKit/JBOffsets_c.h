//
//  JBOffsets_c.hpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBOffsets_c_h
#define JBOffsets_c_h

#include <JBKit/JBTypes.h>
#include <mach/mach.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

typedef void* JBOffset_ctx_t;

JBOffset_ctx_t JBOffsets_offsets_new();
void JBOffsets_offsets_free(JBOffset_ctx_t ctx);

int JBOffsets_offsets_setOffset(JBOffset_ctx_t ctx, const char *name, kptr_t offset);
kptr_t JBOffsets_offsets_getOffset(JBOffset_ctx_t ctx, const char *name);

int JBOffsets_offsets_saveOffsets(JBOffset_ctx_t ctx, const char *path);
int JBOffsets_offsets_loadOffsets(JBOffset_ctx_t ctx, const char *path);

int JBOffsets_offsets_sendOffsets(JBOffset_ctx_t ctx, mach_port_t dst); //port with send right
int JBOffsets_offsets_recvOffsets(JBOffset_ctx_t ctx, mach_port_t src); //port with recv right

#ifdef __cplusplus
};
#endif //__cplusplus
#endif /* JBOffsets_c_h */
