## Make all the LEDs blink at the Burn

### installation
we use git submodules to dependent libraries

`git submodule update --recursive` 

install platformio makes building stuff easy

`[sudo] python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"`

`platformio run -e teensy31 -t upload`

If you want to listen to serial: 

`platformio serialports monitor`

Directory structure:
* `camp/` Folder for CAMP Led's
* `bike/` Willems bike
* `lib/` shared stuff, sym linked to each project folder
* `hoola/` kj's hoola stuff
* `libraries/` for use with Arduino ide (boo)


### Open Questions

- [x] ~~@mikelikespie: how many reels of led's do we have~~ **8 or 10**
- [x] determine if https://github.com/PaulStoffregen/Audio + octows2811 works (it should) not necessary
- [ ] enough time to use audio library to modulate visualizations


### Camp design for LEDs

Current plan is a 8'x6' (4:3 ratio) LED array, using horizontal 30/m LED strips.

will use the OctoWS2811 and Teensy 3.1 to drive the LEDs.  Will be using an IR Sensor and IR libraries to select LED program.  @mikelikespie will try and get a DMX controller to work

### Inspiration:
https://www.pjrc.com/store/octo28_adaptor.html
https://www.pjrc.com/teensy/td_libs_OctoWS2811.html
