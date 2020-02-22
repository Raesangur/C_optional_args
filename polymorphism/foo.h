#pragma once
#include <stdint.h>

#define Foo(...)                \
/* Open new scope              */{\
/* Create stack variable       */    void* stack__; \
                                  \
/* Copy program's stack        */ \
/* pointer to stack__ variable */   __asm {mov stack__, esp}; \
                                  \
/* Inject default argument in  */ \
/* the program's stack         */   __asm {push FOO_DEFAULT_SIZE}; \
                                  \
/* Call function through       */ \
/* function pointer, with      */ \
/* variadic arguments          */   fooPtr(__VA_ARGS__); \
                                  \
/* Compare current stack       */ \
/* pointer with copied stack   */ \
/* pointer (in stack__)        */   __asm {cmp stack__, esp}; \
                                  \
/* If stack is back to normal, */ \
/* skip the following steps    */ \
/* and return to normal        */ \
/* program execution           */   __asm {je $ + 12}; \
                                  \
/* Pop the stack               */   __asm {pop eax}; \
                                  \
/* Return to comparison        */ \
/* (on line 22)                */   __asm {jmp $ - 10}; \
                                  \
/* Exit scope                  */}

extern void(*fooPtr)(void);





/*
__asm {je $+12};    // JE(5) + POP(2) + JMP(5)
__asm {jmp $-10};   // POP(2) + JE(5) + CMP(3)
*/
