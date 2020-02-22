#include <stdio.h>
#include <stdint.h>
#include "foo.h"


static void foo(const char* message, uint8_t repeat)
{
    uint8_t i;
    for (i = 0; i < repeat; i++)
    {
        printf("%s\n\r", message);
    }
}

void(*fooPtr)(void) = (void(*)(void))&foo;
