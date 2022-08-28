#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ubox/list.h>

#define PATH "/usr/sbin"

int main (int argc, const char *argv[]) {
    char **params =NULL;

//    printf("[DEBUG] params in %p, size is %dB, content is %#x;\n",
//                &params, sizeof(params), params);
//
//    params = calloc(3, sizeof(char*));
//
//    if ( params != NULL ) {
//        printf("[DEBUG] calloc memory for 3 character pointer, %dB per, addr is %p\n",
//                sizeof(*params), params);
//
//        printf("[DEBUG] params in %p, size is %dB, content is %#x;\n"
//               "        fist element in %p, size is %d, content is %#x\n"
//               "        second element in %p, size is %d, content is %#x\n"
//               "        third element in %p, size is %d, content is %#x\n",
//                &params, sizeof(params), params,
//                &params[0], sizeof(params[0]), params[0],
//                &params[1], sizeof(params[1]), params[1],
//                &params[2], sizeof(params[2]), params[2]);
//    }
 
//    params[0] = malloc(11);
//
//    if ( params[0] != NULL ) {
//        printf("[DEBUG] malloc memory for 11  character., %dB per, addr is %p\n",
//                sizeof(*params[0]), params[0]);
//
//        printf("[DEBUG] params in %p, size is %dB, content is %#x;\n"
//               "        fist element in %p, size is %d, content is %#x, string is %s\n"
//               "        second element in %p, size is %d, content is %#x\n"
//               "        third element in %p, size is %d, content is %#x\n",
//                &params, sizeof(params), params,
//                &params[0], sizeof(params[0]), params[0], params[0],
//                &params[1], sizeof(params[1]), params[1],
//                &params[2], sizeof(params[2]), params[2]);
//    }
//
//    memcpy(params[0], "ABCDEFGHIJKLMN", 11);
//
//    printf("[DEBUG] params in %p, size is %dB, content is %#x;\n"
//           "        fist element in %p, size is %d, content is %#x, string is %s\n"
//           "        second element in %p, size is %d, content is %#x\n"
//           "        thrid element in %p, size is %d, content is %#x\n",
//            &params, sizeof(params), params,
//            &params[0], sizeof(params[0]), params[0], params[0],
//            &params[1], sizeof(params[1]), params[1],
//            &params[2], sizeof(params[2]), params[2]);

    va_list list;



    return 0;
}
