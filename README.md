## Make all the LEDs blink at the Burn

### installation
Make sure to get Arduino >1.6.5

Add https://www.pjrc.com/teensy/td_download.html

If doing trinket stuff, get trinket addons

### TODO 

- [x] link libraries and test led stuff
- [x] order power supplies, fan, power connectors
- [ ] get 10awg wire
- [ ] @willemave: poc of teensy + ir sensor, status: waiting on ir sensor, eta 8/6
- [ ] @willemave: upload schematics for led array


### Open Questions

- [x] ~~@mikelikespie: how many reels of led's do we have~~ **8 or 10**
- [ ] determine if https://github.com/PaulStoffregen/Audio + octows2811 works (it should)
- [ ] enough time to use audio library to modulate visualizations


### Camp design for LEDs

Current plan is a 8'x6' (4:3 ratio) LED array, using horizontal 30/m LED strips.

will use the OctoWS2811 and Teensy 3.1 to drive the LEDs.  Will be using an IR Sensor and IR libraries to select LED program.


### Inspiration:
https://www.pjrc.com/store/octo28_adaptor.html
https://www.pjrc.com/teensy/td_libs_OctoWS2811.html
