#include <stdio.h>

#define AUTHOR 

#define STR(x) _STR(x)
#define _STR(x) #x

int main() {
    
    printf(_STR(AUTHOR)"\n");
    return 0;
}
