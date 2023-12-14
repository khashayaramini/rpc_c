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

typedef struct nums_struct {
    int num1;
    int num2;
} nums;

RPC_FUNC_DEF(my_add)
{
    RPC_GET_ARG(nums, mynums);
	int i1 = mynums.num1;
	int i2 = mynums.num2;
    int result = i1 + i2;
    RPC_RETURN(int, result);
}

RPC_FUNC_DEF(my_sub)
{
    RPC_GET_ARG(nums, mynums);
	int i1 = mynums.num1;
	int i2 = mynums.num2;
    int result = i1 - i2;
    RPC_RETURN(int, result);
}

RPC_FUNC_DEF(my_test1)
{
    RPC_GET_ARG(test_struct_t, ar);
    int i = ar.i;
    double j = ar.j;
    RPC_RETURN(double, ar.j);
}


RPC_FUNC_ARRAY
{
    RPC_FUNC_INC(my_test1, "double")
    RPC_FUNC_INC(my_add, "int")
    RPC_FUNC_INC(my_sub, "int")
};

#endif // FUNCTIONS_H
