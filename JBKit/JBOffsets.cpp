//
//  JBOffsets.cpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#include "JBOffsets.hpp"
#include "JBMacros.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <xpc/xpc.h>

extern "C" xpc_object_t xpc_create_from_plist(void *data, size_t size);

using namespace JBKit;

#pragma mark constructor
JBOffsets::JBOffsets(){
    assure(_xdict = xpc_dictionary_create_empty());
}

JBOffsets::~JBOffsets(){
    safeFreeCustom(_xdict, xpc_release);
}

#pragma mark public

void JBOffsets::setOffset(const char *name, kptr_t offset){
    xpc_dictionary_set_uint64(_xdict, name, offset);
}

kptr_t JBOffsets::getOffset(const char *name){
    return xpc_dictionary_get_uint64(_xdict, name);
}

void JBOffsets::saveOffsets(const char *path){
    FILE *f = NULL;
    cleanup([&]{
        safeFreeCustom(f, fclose);
    });
    assure(f = fopen(path, "w"));
    
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n");
    xpc_dictionary_apply(_xdict, ^bool(const char * _Nonnull key, xpc_object_t  _Nonnull value) {
        uint64_t valueInt = xpc_uint64_get_value(value);
        fprintf(f, "\t<key>%s</key>\n\t<integer>%llu</integer>\n", key, valueInt);
        return true;
    });
    fprintf(f, "</dict>\n</plist>\n");
}

void JBOffsets::loadOffsets(const char *path){
    int fd = -1;
    size_t plistDataLen = 0;
    void *plistData = NULL;
    cleanup([&]{
        if (plistData) {
            munmap(plistData, plistDataLen);plistData = NULL;
        }
        safeClose(fd);
    });
    struct stat s = { 0 };

    assure((fd = open(path, O_RDONLY)) != -1);
    assure(!fstat(fd, &s));

    plistDataLen = s.st_size;
    assure((plistData = mmap(NULL, plistDataLen, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) != MAP_FAILED);
    safeFreeCustom(_xdict, xpc_release);
    assure(_xdict = xpc_create_from_plist(plistData, plistDataLen));
}

void JBOffsets::sendOffsets(mach_port_t dst){
    //TODO
}

void JBOffsets::recvOffsets(mach_port_t src){
    //TODO
}
