# Evc_pt2257
Arduino Library for using PT2257 - Electronic Volume Controller IC

Connect the IC to the following pins, you can change it in the .c file.  
Pull-up resistors are required on both pins (4K7 or 10K should be fine).  
 SCL -> A0  
 SDA -> A1  
 
 Datasheet - http://www.princeton.com.tw/Portals/0/Product/PT2257.pdf

```
Pinout

   |----._.----|
1 -| Lin   Rin |- 8
2 -| Lout Rout |- 7
3 -| Gnd    V+ |- 6
4 -| SDA   SCL |- 5
   |-----------|
```

## API

Volume Attenuation are expressed as **unsigned** integers  
e.g. : to set the attenuation to -21dB express it as `21`

- `void evc_init();`  
  Start the I2C communication  
  *Call this on setup(); to ensure a reliable initialization, this will delay for 200ms.*

- `void evc_setVolume(uint8_t dB);`  
  Set the attenuation on both channels (between 0dB and -79dB)

- `void evc_setVolumeLeft(uint8_t dB);`  
  Set the attenuation on the Left channel (between 0dB and -79dB)  
  Use this for implementing left/right balance offset.

- `void evc_setVolumeRight(uint8_t dB);`  
  Set the attenuation on the right channel (between 0dB and -79dB)  
  Use this for implementing left/right balance offset.

- `void evc_mute(bool toggle);`  
  **toggle**:
    - *true*: Mute both channels.  
      This mode have an effective attenuation of -95dB (+5/-2dB) 
    - *false*: Unmute both channels.
    
  **Note:** It will preserve the set Volume when mute is toggled 
  (This behavior is not documented on the datasheet).  

- `void evc_off();`  
  Function OFF (-79dB)  
  *The exact purpose of this instruction is not clear on the datasheet.*

----

## Initialization

The datasheet does not mention anything about it being volatile or not, but it seems to hold state after power cycle, I'm not sure about about if it's just an artifact, but I recommend setting it to a known state just after initialization, so you will not be in a situation that you are changing volume but nothing happens because you have mute on, after a power cycle. So does not expect it to be in a known state just after power on, handle it yourself.

```
void setup(){
    evc_init();
    
    //ensure power on consistency
    evc_setVolume(79);
    evc_mute(false);
	...
    /* recover state from arduino eeeprom if desired */
	//set the volume to stored state.
}
```

