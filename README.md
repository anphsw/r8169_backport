# r8169_backport
Kernel compatibility layer for backporting Realtek r8169 driver to older kernels.
Can be used for some other ethernet drivers with similar structure.

How to use:
- Copy r8169_compat.h and r8169.c to drivers/net/ethernet/realtek directory of your kernel source

OR

- Get your own copy of r8169.c from linux kernel source (3.2 ... 3.18) should work fine
- Add: #include "r8169_compat.h" to your r8169.c

Recompile kernel.
Tested by backporting r8169 from 3.10, 3.16, 3.18 to 3.2 linux kernel; others untested.
