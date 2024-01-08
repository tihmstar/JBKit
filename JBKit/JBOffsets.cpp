//
//  JBOffsets.cpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#include "JBOffsets.hpp"

using namespace JBKit;

#pragma mark constructor
JBOffsets::JBOffsets(){
    //TODO constructor
}

JBOffsets::~JBOffsets(){
    //TODO destructor
}

#pragma mark public

void JBOffsets::setOffset(const char *name, kptr_t offset){
    //TODO
}

kptr_t JBOffsets::getOffset(const char *name){
    //TODO
    return 0;
}

void JBOffsets::saveOffsets(const char *path){
    //TODO
}

void JBOffsets::loadOffsets(const char *path){
    //TODO
}

void JBOffsets::sendOffsets(mach_port_t dst){
    //TODO
}

void JBOffsets::recvOffsets(mach_port_t src){
    //TODO
}
