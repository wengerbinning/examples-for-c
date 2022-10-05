#include <stdio.h>

int main(int argc, const char *argv[]) {
    // todo: you can do anything here.
    printf("start main\n");
    unsigned char *uchar_ptr = NULL;
    printf("unsigned char uchar_ptr: [%x](%x)\n", &uchar_ptr, uchar_ptr);
    *uchar_ptr = 'a';
    printf("unsigned char uchar_ptr: [%x](%x)\n", &uchar_ptr, uchar_ptr);
    return 0;
    // d
}
