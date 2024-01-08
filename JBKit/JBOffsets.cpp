//
//  JBOffsets.cpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#include "JBOffsets.hpp"
#include <sys/stat.h>
#include <fcntl.h>
extern xpc_object_t xpc_create_from_plist(void *data, size_t size);

using namespace JBKit;

#pragma mark constructor
JBOffsets::JBOffsets(){
    _xdict = xpc_dictionary_create_empty();
}

JBOffsets::~JBOffsets(){
    xpc_release(_xdict);
}

#pragma mark public

void JBOffsets::setOffset(const char *name, kptr_t offset){
    xpc_dictionary_set_uint64(_xdict, name, offset);
}

kptr_t JBOffsets::getOffset(const char *name){
    return xpc_dictionary_get_uint64(_xdict, name);
}

void JBOffsets::saveOffsets(const char *path){
    FILE *f = fopen(path, "w");
    if (f) {
        fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n");
        xpc_dictionary_apply(_xdict, ^bool(const char * _Nonnull key, xpc_object_t  _Nonnull value) {
            uint64_t valueInt = xpc_uint64_get_value(value);
            fprintf(f, "\t<key>%s</key>\n\t<integer>%llu</integer>\n", key, valueInt);
            return true;
        });
        fprintf(f, "</dict>\n</plist>\n");
    }
}

void JBOffsets::loadOffsets(const char *path){
    struct stat s = { 0 };
    int fd = open(path, O_RDONLY);
    if (fd < 0) return;
    if (fstat(fd, &s) != 0) {
        close(fd);
        return;
    }

    size_t len = s.st_size;
    void *plistData = mmap(NULL, len, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
    if (plistData != MAP_FAILED) {
        _xdict = xpc_create_from_plist(plistData, len);
        munmap(plistData, len);
    }
    close(fd);
}

void JBOffsets::sendOffsets(mach_port_t dst){
    //TODO
}

void JBOffsets::recvOffsets(mach_port_t src){
    //TODO
}
