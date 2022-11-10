### Some notes:
**About the driver**

The signed driver file (`204.sys`) is extracted from an old plugin (`��ʹ���`).
The plugin binary (`TSPlugin.dll`) has been publicly usable for some years.
Though its developers claimed to publish its source code on some BBS,
the driver and handler had been removed from their open sourced codes.
Surprisingly the driver file can be found and extracted by 7-zip from a built-in directory with an obvious name.

By decompiling the driver file using IDA Pro,
I found the driver itself is nothing more than a regular keyboard/mouse filter driver whose approach has been widely utilized.
The approach is to create a kernel driver in order to get and invoke the function `KeyboardClassServiceCallback` in `Kdbclass.sys`.
The function can send different keystroke contained in a KEYBOARD_INPUT_DATA structure.
The driver also exposes an interface for user space applications to interact with it by function `DeviceIoControl`.
In brief, the workflow of the driver is like follows:
```
user application
        |                                                    user space
        | DeviceIoControl
--------+-----------------------------------------------------------------
        |      KeyboardClassServiceCallback                  kernel space
   the driver ------------------------------> kdbclass.sys
```
The driver, however is signed, so you can use it in a normal Windows machine, without disabling the driver signature enforcement,
which is the reason why I use the driver, instead of creating one.

**About the service manager**

I just copy and paste the service management codes from MSDN: [click me](https://learn.microsoft.com/en-us/windows/win32/services/the-complete-service-sample),
while there are two pitfalls for this program: