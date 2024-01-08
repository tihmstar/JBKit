//
//  JBException.hpp
//  JBKit
//
//  Created by tihmstar on 08.01.24.
//

#ifndef JBException_hpp
#define JBException_hpp

#include <JBKit/JBMacros.h>

#include <exception>
#include <iostream>

#if defined(WIN32) && !__clang__
#   define JBKIT_VISIBLE_EXCEPTION_TYPEINFO __declspec( dllexport )
#else
#   ifdef HAVE_FVISIBILITY
#       define JBKIT_VISIBLE_EXCEPTION_TYPEINFO __attribute__((visibility("default")))
#   else
#       define JBKIT_VISIBLE_EXCEPTION_TYPEINFO
#   endif
#endif

#define EASY_BASE_EXCEPTION(name) \
class JBKIT_VISIBLE_EXCEPTION_TYPEINFO name : public JBKit::exception{ \
public: \
    using exception::exception; \
    /*this makes sure typeinfo works correcty in other libs!*/ \
    virtual const char *what() const noexcept override; \
}

#define EASY_EXCEPTION(name, base) \
class JBKIT_VISIBLE_EXCEPTION_TYPEINFO name : public JBKit::base{ \
    using base::base; \
}

#define EASY_BASE_EXCEPTION_DEF(name) \
JBKIT_VISIBLE_EXCEPTION_TYPEINFO const char *JBKit::name::what() const noexcept{ \
    /*this makes sure typeinfo works correcty in other libs!*/\
    return JBKit::exception::what();\
}

namespace JBKit {
    class JBKIT_VISIBLE_EXCEPTION_TYPEINFO exception : public std::exception{
        const char *_commit_count_str;
        const char *_commit_sha_str;
        int _line;
        std::string _filename;
        char *_err;
        
    public:
        exception(const char *commit_count_str, const char *commit_sha_str, int line, const char *filename, const char *err ...);
        exception(const char *commit_count_str, const char *commit_sha_str, int line, const char *filename, va_list ap, const char *err);

        exception(const exception &e); //copy constructor
        
        //custom error can be used
        virtual const char *what() const noexcept override;
        
        /*
         -first lowest two bytes of code is sourcecode line
         -next two bytes is strlen of filename in which error happened
         */
        int code() const;
        
        virtual void dump() const;
        virtual std::string dumpStr() const;

        //Information about build
        virtual std::string build_commit_count() const;
        virtual std::string build_commit_sha() const;
        
        ~exception();
    };

#pragma mark easy exception

EASY_BASE_EXCEPTION(JBException);

EASY_EXCEPTION(JBException_primitive_unavailable, JBException);
EASY_EXCEPTION(JBException_incomplete_read_or_write, JBException);
EASY_EXCEPTION(JBException_exploit_failed_needs_reboot, JBException);

};


#endif /* JBException_hpp */
