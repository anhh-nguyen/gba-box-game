# gba-box-game
This is a C program that will run on a Game Boy Advance emulator. This program use DMA, waitForVblank(), and Mode 3 video.

To reset the game to title screen AT ANY TIME, use backspace key. 
To continue to the game, use return key
To move an image across the screen, using the arrow keys.

```.gba``` files can be found under the releases section.

Instructions are for Ubuntu 18.04.

Dependencies
This project requires Brandon Whitehead's PPA.
```
$ sudo add-apt-repository ppa:tricksterguy87/ppa-gt-cs2110
$ sudo apt install gcc-arm-none-eabi cs2110-vbam-sdl mednafen cs2110-gba-linker-script nin10kit
```
Build
```
$ make
```


![Screen Shot 2022-06-06 at 9 13 14 PM](https://user-images.githubusercontent.com/90353674/172524314-76cfbc6b-9368-4732-b870-7e0a34692687.png)
