//
// Created by aeols on 09.12.2022.
//

#ifndef TJOHEISTYRING_UTILITY_H
#define TJOHEISTYRING_UTILITY_H


#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)

namespace Utility {
    constexpr char Program_name[]{STRINGIZE(ProjName) " " __DATE__ " " __TIME__};

    inline void copy_bytes(uint8_t *buffer, int value) {
        *buffer++ = 0xFFu & ((uint32_t) value >> 24u);
        *buffer++ = 0xFFu & ((uint32_t) value >> 16u);
        *buffer++ = 0xFFu & ((uint32_t) value >> 8u);
        *buffer = 0xFFu & ((uint32_t) value);
    }

}
#endif //TJOHEISTYRING_UTILITY_H
