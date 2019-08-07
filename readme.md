## NXP LPC11U35 LED Blink example

The LPC series of processors are interesting. An ARM Cortex M0 32 bit core, they are quite cheap and have great performance. Especially LPC11U35 has direct USB hardware, 64kB FLASH, 8kb RAM (+2kb RAM for USB use), as well as a full lineup of peripheral devices.

However, it is troubled by a not-so clearly written reference manual and features such as ROM image being required to pass a checksum so that the processor can start running. All of these make it a difficult processor for newbies to use. Mbed comes into the picture right there. All the required libraries, toolchain etc are already included in the web interface, and it becomes a simple matter to use modules to accomplish your requirement. However, for advanced users, Mbed can be cumbersome, and especially the libraries (most importantly USB related ones) are difficult to trace and simplify. A local environment can be desireable for more serious work.

GCC to the rescue. [GNU ARM Embedded](https://launchpad.net/gcc-arm-embedded) toolchain can be used for this and simplifies the work immensely. However, many other stuff remains.

In this repo, I present how to build a project for the LPC11U35 from scratch using open source libraries and tools. It is the compulsory LED blink with a twist; it is based on the SysTick timer interrupt and non-blocking. The board I used is a clone of the [Embedded Artists LPC11U35 Quickstart board](https://www.embeddedartists.com/products/lpc11u35-quickstart/); this one from [Akizuki Denshi of Akihabara, Tokyo](http://akizukidenshi.com/catalog/g/gK-12144/).

The requirements are:
- [GCC ARM Embedded toolchain](https://launchpad.net/gcc-arm-embedded)
- Lib_CMSISv2p00_LPC11Uxx 
- Lib_MCU from NXP (From 2010)
 ([Both can be found as a part of this archive](https://www.embeddedartists.com/wp-content/uploads/2018/07/qsb_lpc11u35_120509.zip)
- The linker script and startup scripts have been adapted from those for other processors (the vector table that can be found in on the Internet supposedly for LPC11U35 is actually for another processor and the ISR's are not located properly).
- The checksum for the binary is created by [lpcpatchelf](https://github.com/nPipen/lpcpatchelf)

Finally, all come together using the Makefile supplied as a part of this bundle. To compile the project:
- Download and install all the components above, including lpcpatchelf
- Edit the Makefile so that the paths to the various libraries and locations are correct (this project was build on a Linux machine)
- run: '$ make'
  This will compile the program to the binary image, modify the binary image to the 
- To flash the processor, connect the USB port, put it into boot mode (power up with ISP_EN PIO0-1 held low) and do:
  '$ make uflash'
   A reset is needed before your code will run.
   
   This is a rough guide. If you need any further explanation, please let me know.
   
