/*
  Evc_pt2257.h - Library for using PT2257 - Electronic Volume Controller IC.
  Created by Victor NPB, December 9, 2014.
*/

#ifndef Evc_pt2257_h
#define Evc_pt2257_h

#include "Arduino.h"

void evc_init();

void evc_setVolume(uint8_t dB);
void evc_setVolumeLeft(uint8_t dB);
void evc_setVolumeRight(uint8_t dB);
void evc_mute(bool toggle);
void evc_off();

#endif

