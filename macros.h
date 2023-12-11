#ifndef RPC_MACROS
#define RPC_MACROS

#define RPC_FUNC_INC(func) { &func, #func },

#define RPC_GET_ARG(type,name,index) type name = *reinterpret_cast<type*>(args[index])

#define RPC_FUNC_DEF(name) void name(void **args, void *res)

#define RPC_RETURN(type,val) *(type *)res = val;
#endif
