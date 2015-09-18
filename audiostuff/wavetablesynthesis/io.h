#ifndef __IO_H__
#define __IO_H__

#include "synth.h"

void midi_init();
void midi_terminate();
int midi_loop(void *userData);
void list_devices();

#endif /* __IO_H__ */