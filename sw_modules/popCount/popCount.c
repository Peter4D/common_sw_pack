#include "popCount.h"


uint_fast8_t popCount(uint_fast8_t input) {
    uint_fast8_t count = 0;
    for (; input != 0; input &= input - 1) {
        count++;
    }
    return count;
}