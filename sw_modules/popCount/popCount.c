#include "popCount.h"


uint8_t popCount(uint8_t input) {
    uint8_t count = 0;
    for (; input != 0; input &= input - 1) {
        count++;
    }
    return count;
}