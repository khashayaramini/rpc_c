#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "macros.h"
#include <cstdio>
#include <string>

typedef struct test_struct 
{
	int i;
	double j;
	char name[16];
} test_struct_t;

RPC_FUNC_DEF(my_add)
{
    RPC_GET_ARG(int*, ar);
	int i1 = ar[0];
	int i2 = ar[1];
    int result = i1 + i2;
    RPC_RETURN(int, result);
}

RPC_FUNC_DEF(my_sub)
{
    RPC_GET_ARG(int*, ar);
	int i1 = ar[0];
	int i2 = ar[1];
    int result = i1 - i2;
    RPC_RETURN(int, result);
}

RPC_FUNC_DEF(my_test1)
{
    RPC_GET_ARG(test_struct_t, ar);
    int i = ar.i;
    double j = ar.j;
	printf("%d\n", i);
	printf("%f\n", j);
	printf("%s\n", ar.name);
    RPC_RETURN(int, ar.i);
}


RPC_FUNC_ARRAY
{
    RPC_FUNC_INC(my_test1)
    RPC_FUNC_INC(my_add)
    RPC_FUNC_INC(my_sub)
};

#endif // FUNCTIONS_H
