#pragma once
#include <stdint.h>

#define FOO_DEFAULT_SIZE        5

#define Foo(...)                {\
                                    void* __stack; \
                                    __asm {mov __stack, esp}; \
                                    __asm {push FOO_DEFAULT_SIZE}; \
                                    fooPtr(__VA_ARGS__); \
                                    __asm {cmp __stack, esp}; \
                                    __asm {je $ + 12}; \
                                    __asm {pop eax}; \
                                    __asm {jmp $ - 10}; \
                                }

extern void(*fooPtr)(void);





/*
__asm {je $+12};    // JE(5) + POP(2) + JMP(5)
__asm {jmp $-10};   // POP(2) + JE(5) + CMP(3)
*/