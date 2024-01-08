//
//  JBPrimitive.cpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#include "JBPrimitive.hpp"
#include "JBMacros.h"

using namespace JBKit;

#pragma mark constructor
JBPrimitive::JBPrimitive(){
    //
}

JBPrimitive::~JBPrimitive(){
    //
}

#pragma mark private
bool JBPrimitive::hasRead64() const noexcept{
    return false;
}

bool JBPrimitive::hasRead32() const noexcept{
    return false;
}

bool JBPrimitive::hasReadGeneric() const noexcept{
    return false;
}

bool JBPrimitive::hasWrite64() const noexcept{
    return false;
}

bool JBPrimitive::hasWrite32() const noexcept{
    return false;
}

bool JBPrimitive::hasWriteGeneric() const noexcept{
    return false;
}

#pragma mark public
#pragma mark availability infos

bool JBPrimitive::hasRead() const noexcept{
    return hasReadGeneric() || hasRead64() || hasRead32();
}

bool JBPrimitive::hasWrite() const noexcept{
    return hasWriteGeneric() || hasWrite64() || hasWrite32();
}

bool JBPrimitive::hasExecute() const noexcept{
    return false;
}

#pragma mark primitives
uint64_t JBPrimitive::read64(kptr_t kaddr){
    uint64_t retval = 0;
    if (hasReadGeneric()) {
        size_t didread = read_generic(kaddr, &retval, sizeof(retval));;
        retcustomassure(JBException_incomplete_read_or_write, didread == sizeof(retval), "read64-generic read returned %zu (!= 8) bytes",didread);
    }else if (hasRead32()){
        uint32_t *r = (uint32_t*)&retval;
        r[0] = read32(kaddr);
        r[1] = read32(kaddr + sizeof(uint32_t));
    }else{
        retcustomerror(JBException_primitive_unavailable, "read is not implemented by the primitive");
    }
    return retval;
}

uint32_t JBPrimitive::read32(kptr_t kaddr){
    uint32_t retval = 0;
    if (hasReadGeneric()) {
        size_t didread = read_generic(kaddr, &retval, sizeof(retval));;
        retcustomassure(JBException_incomplete_read_or_write, didread == sizeof(retval), "read32-generic read returned %zu (!= 4) bytes",didread);
    }else if (hasRead64()){
        uint64_t r = read64(kaddr);
        retval = (uint32_t)r;
    }else{
        retcustomerror(JBException_primitive_unavailable, "read is not implemented by the primitive");
    }
    return retval;
}

size_t JBPrimitive::read_generic(kptr_t kaddr, void *dstbuf, size_t size, bool honorSizeLimit){
    bool hasr64 = hasRead64();
    bool hasr32 = hasRead32();
    size_t didRead = 0;
    uint8_t *dst = (uint8_t*)dstbuf;
    
    retcustomassure(JBException_primitive_unavailable, hasr64 || hasr32, "read is not implemented by the primitive");
    
    if (hasr64) {
        while (size - didRead > sizeof(uint64_t)) {
            uint64_t r = read64(kaddr + didRead);
            memcpy(&dst[didRead], &r, sizeof(r));
            didRead += sizeof(r);
        }
    }

    if (hasr32) {
        while (size - didRead > sizeof(uint32_t)) {
            uint32_t r = read32(kaddr + didRead);
            memcpy(&dst[didRead], &r, sizeof(r));
            didRead += sizeof(r);
        }
    }

    if (honorSizeLimit) return didRead;

    //we will perform an overread and return only as much bytes as requested
    size_t reminder = size - didRead;
    
    if (hasr64 && (reminder > sizeof(uint32_t) || !hasr32)) {
        uint64_t r = read64(kaddr + didRead);
        memcpy(&dst[didRead], &r, reminder);
        didRead += reminder;
    }else if (hasr32){
        
        if (reminder > sizeof(uint32_t)) reminder = sizeof(reminder);

        {
            uint32_t r = read32(kaddr + didRead);
            memcpy(&dst[didRead], &r, reminder);
            didRead += reminder;
        }
        
        reminder = size - didRead;
        if (reminder > sizeof(uint32_t)) reminder = sizeof(reminder);

        if (reminder){
            uint32_t r = read32(kaddr + didRead);
            memcpy(&dst[didRead], &r, reminder);
            didRead += reminder;
        }
    }
    
    return didRead;
}

void JBPrimitive::write64(kptr_t kaddr, uint64_t val){
    if (hasWriteGeneric()) {
        size_t didwrite = write_generic(kaddr, &val, sizeof(val));
        retcustomassure(JBException_incomplete_read_or_write, didwrite == sizeof(val), "write64-generic read returned %zu (!= 8) bytes",didwrite);
    }else if (hasWrite32()){
        uint32_t *r = (uint32_t*)&val;
        write32(kaddr, r[0]);
        write32(kaddr + sizeof(uint32_t), r[1]);
    }else{
        retcustomerror(JBException_primitive_unavailable, "write is not implemented by the primitive");
    }
}

void JBPrimitive::write32(kptr_t kaddr, uint32_t val){
    if (hasWriteGeneric()) {
        size_t didwrite = write_generic(kaddr, &val, sizeof(val));
        retcustomassure(JBException_incomplete_read_or_write, didwrite == sizeof(val), "write32-generic read returned %zu (!= 4) bytes",didwrite);
    }else if (hasWrite64()){
        uint64_t r = read64(kaddr);
        *(uint32_t*)r = val;
        write64(kaddr, r);
    }else{
        retcustomerror(JBException_primitive_unavailable, "write is not implemented by the primitive");
    }
}

size_t JBPrimitive::write_generic(kptr_t kaddr, const void *srcbuf, size_t size, bool honorSizeLimit){
    bool hasw64 = hasWrite64();
    bool hasw32 = hasWrite32();
    size_t didWrite = 0;
    const uint8_t *src = (const uint8_t*)srcbuf;
    
    retcustomassure(JBException_primitive_unavailable, hasw64 || hasw32, "write is not implemented by the primitive");
    
    if (hasw64) {
        while (size - didWrite > sizeof(uint64_t)) {
            uint64_t w = 0;
            memcpy(&w, &src[didWrite], sizeof(w));
            write64(kaddr + didWrite, w);
            didWrite += sizeof(w);
        }
    }
    
    if (hasw32) {
        while (size - didWrite > sizeof(uint64_t)) {
            uint32_t w = 0;
            memcpy(&w, &src[didWrite], sizeof(w));
            write32(kaddr + didWrite, w);
            didWrite += sizeof(w);
        }
    }
    
    if (honorSizeLimit) return didWrite;

    //we will perform an overwrite with previously read back bytes
    size_t reminder = size - didWrite;

    if (hasw64 && (reminder > sizeof(uint32_t) || !hasw32)) {
        uint64_t w = read64(kaddr + didWrite);
        memcpy(&w, &src[didWrite], reminder);
        write64(kaddr + didWrite, w);
        didWrite += reminder;
    }else if (hasw32){
        
        if (reminder > sizeof(uint32_t)) reminder = sizeof(reminder);
        {
            uint32_t w = read32(kaddr + didWrite);
            memcpy(&w, &src[didWrite], reminder);
            write32(kaddr + didWrite, w);
            didWrite += reminder;
        }

        reminder = size - didWrite;
        if (reminder > sizeof(uint32_t)) reminder = sizeof(reminder);

        if (reminder) {
            uint32_t w = read32(kaddr + didWrite);
            memcpy(&w, &src[didWrite], reminder);
            write32(kaddr + didWrite, w);
            didWrite += reminder;
        }
    }
    
    return didWrite;
}

void JBPrimitive::execute(kptr_t kaddr, std::vector<kptr_t> args){
    retcustomerror(JBException_primitive_unavailable, "execute is not implemented by the primitive");
}
