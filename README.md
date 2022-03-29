# EKKO-sdk
Software Development Kit for [EKKO](https://github.com/mrdiogodias/ekko)


## Requirements
### Software
- [RISC-V GNU toolchain of lowRISC](https://github.com/lowRISC/lowrisc-toolchains/releases) (rv32imc) 
- [OpenOCD](https://github.com/openocd-org/openocd)
- [Visual Studio Code](https://code.visualstudio.com/) - If you want to launch gdb through an UI
### Hardware
- Debug probe (e.g [Jlink](http://www.segger.com/jlink.html) or [ST-Link](https://www.st.com/en/development-tools/st-link-v2.html))


## Build
Add the RISC-V toolchain bin folder `lowrisc-toolchain-gcc-rv32imc/bin` to the `PATH` environment variable.

Then, from the root directory call:
```
make
```
This should produce a `main.elf` file, which is the executable that will be loaded into the [EKKO](https://github.com/mrdiogodias/ekko) core.


## Program and Debug
Add the openocd src folder `openocd/src` to the `PATH` environment variable.

Afterwards, from the root directory call: 
```
openocd -f openocd/jlink.cfg -f openocd/ibex.cfg
```
Keep in mind that the command above will only work if you're using a jlink debug probe, which is the configuration provided. For other debuggers, use the respective configuration file provided by openocd and adapt the command accordingly. For example, if you are using an ft232r (a cheap ftdi which you can use), the command should be: 
```
openocd -f path_to_openocd/openocd/tcl/interface/ft232r.cfg -f openocd/ibex.cfg
```

If everything went fine, the output should be something similar to this: 

```
Open On-Chip Debugger 0.11.0+dev-00103-gff755a575-dirty (2021-04-21-21:13)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
Info : Hardware thread awareness created
Info : J-Link ARM V8 compiled Nov 28 2014 13:44:46
Info : Hardware version: 8.00
Info : VTarget = 3.267 V
Info : clock speed 3000 kHz
Info : JTAG tap: riscv.cpu tap/device found: 0x0494284d (mfg: 0x426 (Google Inc), part: 0x4942, ver: 0x0)
Info : datacount=2 progbufsize=8
Info : Examined RISC-V core; found 1 harts
Info : hart 0: XLEN=32, misa=0x40101104
Info : starting gdb server for riscv.cpu on 3333
Info : Listening on port 3333 for gdb connections
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
```

Now just open another terminal and program/debug the core though `riscv32-unknown-elf-gdb` on port 3333.

If you're using vscode, this repository also includes a launch.json file that'll enable you to use a graphical debugging mechanism from vscode, making it easy to put breakpoints and watchers as much as you want. To connect with the FPGA, just select on the debug mode of vsc the "EKKO" option, then gdb will start debugging.