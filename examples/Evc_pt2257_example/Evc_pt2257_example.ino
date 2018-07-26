/*
 Sketch example for using PT2257 - Electronic Volume Controller IC.
 Created by Victor NPB, December 9, 2014.

 Connect the IC to the following pins, you can change it in the .c file.
 Pull-up resistors are required on both pins (4K7 or 10K should be fine).

 SCL -> A0
 SDA -> A1

 Volume Attenuation are expressed as unsigned integers

 evc_setVolume(0) 	set both channels to 0dB of attenuation (max volume)
 evc_setVolume(79)	set both channels to -79dB of attenuation (min volume)

 evc_setVolumeRight() same as above but set just one channel
 evc_setVolumeLeft()  same as above but set just one channel

 evc_mute(true)     mute both channels to -95dB
 evc_mute(false)    unmute both channels to last set attenuation

 evc_off()          off (-79dB)

*/

#include <Evc_pt2257.h>

void setup() {
  // put your setup code here, to run once:
  evc_init();
}

void loop() {
  static int i = 0;
  
  evc_setVolume(i++%79);
  //evc_setVolumeRight(i++%79);
  //evc_setVolumeLeft(i++%79);
  
  //evc_mute(i%2==0);
  //evc_off();
  
  delay(500);
}
