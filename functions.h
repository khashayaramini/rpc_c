#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

#define FUNC_DEF(func) { &func, #func },

// typedef struct func_arg{
//     void *val;
// } func_arg_t;

void my_add(void **args, void *res){
    int i1 = *reinterpret_cast<int*>(args[0]);
    int i2 = *reinterpret_cast<int*>(args[1]);
    int result = i1 + i2;
    std::cout << "answer: " << result << "\n";
    *(int *)res = result;
}

void my_sub(void **args, void *res){
    int i1 = *reinterpret_cast<int*>(args[0]);
    int i2 = *reinterpret_cast<int*>(args[1]);
    int result = i1 - i2;
    std::cout << "answer: " << result << "\n";
    *(int *)res = result;
}

struct {
    void (*fp)(void **args, void *res);
    const char * name;
} func_array[] = {
    FUNC_DEF(my_add)
    FUNC_DEF(my_sub)
};

int func_array_size = 2;

#endif // FUNCTIONS_H
