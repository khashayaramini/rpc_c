#ifndef RPC_MACROS
#define RPC_MACROS
#include <array>

#define RPC_FUNC_INC(func, type) { &func, #func, type },

#define RPC_GET_ARG(type,name) type name = *reinterpret_cast<type*>(arg)

#define RPC_FUNC_DEF(name) void name(void *arg, void *res)

#define RPC_RETURN(type,val) *(type *)res = val;

#define RPC_FUNC_ARRAY struct {\
    void (*fp)(void *arg, void *res);\
    const char * name;\
    const char * type;\
} func_array[] = 

#define RPC_FUNC_ARRAY_SIZE (std::end(func_array) - std::begin(func_array))

#endif
