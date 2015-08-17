# Evc_pt2257
Library for using PT2257 - Electronic Volume Controller IC

`void evc_init();`
> Start the I2C communication

`void evc_setVolume(uint8_t dB);`  
> Set the attenuation on both channels (between 0dB to -79dB)

`void evc_setVolumeLeft(uint8_t dB);`
> Set the attenuation on the Left channel (between 0dB to -79dB)

`void evc_setVolumeRight(uint8_t dB);`
> Set the attenuation on the right channel (between 0dB to -79dB)

`void evc_mute(bool toggle);`
> Set the attenuation on both channels to channel to -95dB  
> *Non documented behavior, but it will preserve the set Volume when mute is toggled.

`void evc_off();`
> Function OFF (-79dB)
