//
//  JBMacros.h
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBMacros_h
#define JBMacros_h

#include <JBKit/JBException.hpp>

#ifndef VERSION_COMMIT_COUNT
#   define VERSION_COMMIT_COUNT "VERSION_COMMIT_COUNT_not_set"
#endif
#ifndef VERSION_COMMIT_SHA
#   define VERSION_COMMIT_SHA "VERSION_COMMIT_SHA_not_set Build: " __DATE__ " " __TIME__
#endif

#ifdef STRIP_ASSURES
#   define JBKIT__FILE__ "<file>"
#   define JBKIT_ERRSTR(errstr ...) "<errstr>"
#else //STRIP_ASSURES
#   define JBKIT__FILE__ __FILE__
#   define JBKIT_ERRSTR(errstr ...) errstr
#endif //STRIP_ASSURES

#ifndef EXPECTIONNAME
#    define EXPECTIONNAME exception
#endif

#define assure(cond) do{ if ((cond) == 0) throw JBKit::EXPECTIONNAME(VERSION_COMMIT_COUNT, VERSION_COMMIT_SHA, __LINE__, JBKIT__FILE__, JBKIT_ERRSTR("assure failed")); } while(0)
#define retassure(cond, errstr ...) do{ if ((cond) == 0) throw JBKit::EXPECTIONNAME(VERSION_COMMIT_COUNT, VERSION_COMMIT_SHA, __LINE__,JBKIT__FILE__,JBKIT_ERRSTR(errstr)); } while(0)
#define customassure(custom_except, cond) do{ if ((cond) == 0) throw JBKit::custom_except(VERSION_COMMIT_COUNT, VERSION_COMMIT_SHA, __LINE__, JBKIT__FILE__, JBKIT_ERRSTR("assure failed")); } while(0)
#define retcustomassure(custom_except, cond, errstr ...) do{ if ((cond) == 0) throw JBKit::custom_except(VERSION_COMMIT_COUNT, VERSION_COMMIT_SHA, __LINE__, JBKIT__FILE__, JBKIT_ERRSTR(errstr)); } while(0)
#define reterror(errstr ...) do{ throw JBKit::EXPECTIONNAME(VERSION_COMMIT_COUNT, VERSION_COMMIT_SHA, __LINE__, JBKIT__FILE__, JBKIT_ERRSTR(errstr)); } while(0)
#define retcustomerror(custom_except,errstr ...) do{ throw JBKit::custom_except(VERSION_COMMIT_COUNT, VERSION_COMMIT_SHA, __LINE__, JBKIT__FILE__, JBKIT_ERRSTR(errstr)); } while(0)
#define doassure(cond,code) do {if (!(cond)){(code);assure(cond);}} while(0)

#define safeFree(ptr) ({if (ptr) {free(ptr); ptr=NULL;}})
#define safeFreeCustom(ptr,func) ({if (ptr) {func(ptr); ptr=NULL;}})
#define safeFreeConst(ptr) ({if(ptr){void *fbuf = (void*)ptr;ptr = NULL; free(fbuf);}})
#define safeClose(fd) ({if (fd != -1) {close(fd); fd=-1;}})
#define safeCloseCustom(fd,func) ({if (fd != -1) {func(fd); fd=-1;}})

#ifdef __cplusplus
#   define safeDelete(ptr) ({if (ptr) {delete ptr; ptr=NULL;}})
#endif //__cplusplus

#endif /* JBMacros_h */
