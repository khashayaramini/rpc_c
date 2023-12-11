#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "macros.h"

RPC_FUNC_DEF(my_add)
{
    RPC_GET_ARG(int, i1, 0);
    RPC_GET_ARG(int, i2, 1);
    int result = i1 + i2;
    RPC_RETURN(int, result);
}

RPC_FUNC_DEF(my_sub)
{
    RPC_GET_ARG(int, i1, 0);
    RPC_GET_ARG(int, i2, 1);
    int result = i1 - i2;
    RPC_RETURN(int, result);
}

struct {
    void (*fp)(void **args, void *res);
    const char * name;
} func_array[] = {
    RPC_FUNC_INC(my_add)
    RPC_FUNC_INC(my_sub)
};

int func_array_size = 2;

#endif // FUNCTIONS_H
