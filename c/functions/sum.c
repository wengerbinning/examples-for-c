#include "functions.h"

static int _sum(int a, int b);

int sum_int(int a, int b) {
    return _sum(a, b);
}

float sum_float(float a, float b) {
    return a + b;
}

int _sum(int a, int b) {
    return a + b;
}
