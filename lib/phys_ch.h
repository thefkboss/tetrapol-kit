#pragma once

#include <stdint.h>

void mod_set(int m);

typedef struct _tetrapol_phys_ch_t tetrapol_phys_ch_t;

tetrapol_phys_ch_t *tetrapol_phys_ch_create(void);
void tetrapol_phys_ch_destroy(tetrapol_phys_ch_t *t);
int tetrapol_phys_ch_process(tetrapol_phys_ch_t *t);

/**
  Eat some data from buf into channel decoder.

  @return number of bytes consumed
*/
int tetrapol_recv2(tetrapol_phys_ch_t *t, uint8_t *buf, int len);
