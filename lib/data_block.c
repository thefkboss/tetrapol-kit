#include "data_block.h"

#include <stdio.h>
#include <string.h>

// http://ghsi.de/CRC/index.php?Polynom=10010
static void mk_crc5(uint8_t *res, const uint8_t *input, int input_len)
{
    uint8_t inv;
    memset(res, 0, 5);

    for (int i = 0; i < input_len; ++i)
    {
        inv = input[i] ^ res[0];

        res[0] = res[1];
        res[1] = res[2];
        res[2] = res[3] ^ inv;
        res[3] = res[4];
        res[4] = inv;
    }
}

bool data_block_check_crc(data_block_t *data_blk)
{
    if (data_blk->fr_type == FRAME_TYPE_AUTO) {
        data_blk->fr_type = data_blk->data[0];
    } else {
        if (data_blk->fr_type != data_blk->data[0]) {
            return false;
        }
    }

    if (data_blk->fr_type == FRAME_TYPE_DATA) {
        uint8_t crc[5];

        mk_crc5(crc, data_blk->data, 69);
        return !memcmp(data_blk->data + 69, crc, 5);
    }

    if (data_blk->fr_type == FRAME_TYPE_VOICE) {
        // TODO
        fprintf(stderr, "CRC checking for VOICE frames not implemented");
        return false;
    }
    return false;
}
