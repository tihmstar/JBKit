//
//  JBTypes.h
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBTypes_h
#define JBTypes_h

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stdint.h>
#include <stdlib.h>

typedef uint64_t kptr_t;
typedef int BOOLEAN;
#define TRUE 1
#define FALSE 0

typedef struct{
    kptr_t args[32];
} callargs_t;

typedef size_t readfunc_t(kptr_t kaddr, void *dstbuf, size_t size, BOOLEAN honorSizeLimit);
typedef size_t writefunc_t(kptr_t kaddr, const void *srcbuf, size_t size, BOOLEAN honorSizeLimit);
typedef kptr_t execfunc_t(kptr_t kaddr, callargs_t args);

#ifdef __cplusplus
};
#endif //__cplusplus
#endif /* JBTypes_h */
