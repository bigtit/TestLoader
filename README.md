## Some notes:

### About the driver

The signed driver file (`204.sys`) is extracted from an old plugin (`天使插件`).
The plugin binary (`TSPlugin.dll`) has been publicly usable for some years.
Though its developers claimed to publish its source code on some BBS,
the driver and handler had been removed from their open sourced codes.
Surprisingly the driver file can be found and extracted by 7-zip from a built-in directory with an obvious name.

By decompiling the driver file using IDA Pro,
I found the driver itself is nothing more than a regular keyboard/mouse filter driver whose approach has been widely utilized.
The approach is to create a kernel driver in order to get and invoke the function `KeyboardClassServiceCallback` in `Kdbclass.sys`.
The function can send different keystrokes contained in a `KEYBOARD_INPUT_DATA` structure.
The driver also exposes an interface for user space applications to interact with it by function `DeviceIoControl`.
In brief, the workflow of the driver is like follows:
```
+--------------------------------------------------------------+--------------+
| (application)                                                |              |
|       |                                                      |  user space  |
|       | DeviceIoControl()                                    |              |
+-------+------------------------------------------------------+--------------+
|       |       KeyboardClassServiceCallback()                 |              |
|   (204.sys) --------------------------------> (kdbclass.sys) | kernel space |
|                                                              |              |
+--------------------------------------------------------------+--------------+
```
The driver, however is signed, so you can use it in a normal Windows machine, without disabling the driver signature enforcement,
which is the reason why I use the driver, instead of creating one.

### About the service manager

I just copy and paste the service management codes from the [MSDN sample](https://learn.microsoft.com/en-us/windows/win32/services/the-complete-service-sample),
while there are two pitfalls for this program:
1. In function `SvcInstall`, function `CreateService` will use `SERVICE_KERNEL_DRIVER` rather than `SERVICE_WIN32_OWN_PROCESS`.
2. The argument `szPath` for `CreateService` cannot be quoted for kernel driver objects/files, though the above [MSDN sample](https://learn.microsoft.com/en-us/windows/win32/services/the-complete-service-sample) `Svc.cpp` gives a misleading comment that quotes are necessary to avoid spaces in paths. The issue is referred to only in a [stackoverflow thread](https://stackoverflow.com/questions/50954450/createservice-and-quotes-for-lpbinarypathname-parameter).
3. Function `CreateService` can still succeed to create a service, even if the path (`szPath`) to its object is invalid. And this issue cannot be found in most service related procedures (like stop, enable, disable, change properties of the service), until starting the service by calling `StartService`, which will lead to error code `123 (ERROR_INVALID_NAME)`.

### About the driver interface

In order to to press keys using the driver, some `DeviceIoControl` arguments need to be specified:

`dwIoControlCode`:
- keydown: `0x80102110`
- keyup: `0x80102130`

`lpInBuffer`:
- key scan code (`int`) of length 4

These argument specifications can be found in decompiled codes using IDA Pro.
