#include <stdint.h>
#include "scancodes.h"

uint8_t esc_scd_tbl[256];
uint8_t ascii_tbl[256];

uint8_t scd_to_kcd(uint8_t scd[], uint8_t length) {
    if (length == 1) {
        return SCD_MAPPABLE(scd[0]);
    }
    if (length == 2) {
        return esc_scd_tbl[SCD_MAPPABLE(scd[1])];
    }
    if (length == 3) {
        return KCD_PAUSE;
    }
    return 0;
}