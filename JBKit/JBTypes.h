//
//  JBTypes.h
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBTypes_h
#define JBTypes_h

#include <stdint.h>
#include <stdlib.h>
#include <vector>

typedef uint64_t kptr_t;

typedef size_t readfunc_t(kptr_t kaddr, void *dstbuf, size_t size, bool honorSizeLimit);
typedef size_t writefunc_t(kptr_t kaddr, const void *srcbuf, size_t size, bool honorSizeLimit);
typedef kptr_t execfunc_t(kptr_t kaddr, std::vector<kptr_t> args);


#endif /* JBTypes_h */
