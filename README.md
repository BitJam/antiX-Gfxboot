antiX-Gfxboot
=============

gfxboot bootloader for antiX Linux and MX Linux

Directory Stucture
------------------

The Output directory structure mimics the structure on the iso
so you will see:

    Output/antiX/
        boot/isolinux/
        boot/syslinux/
        boot/grub/
        efi/

and so on.  The Input directory structure is different from this
because the /boot/isolinux and /boot/syslinux directories require
a lot of work to create.  Therefore under Input/antiX/ there is
an isolinux/ directory that contains much of what is needed for
making isolinux/ and syslinux/ in the output directory and there
is also an Input/antiX/iso/ directory that contains files that
get copied directly over the the output directory.

IoW: what was in Input/antiX/ is now in Input/antiX/isolinux
and all of the added "UEFI" files are under Input/antiX/iso/.
Same thing with Input/common and Input/MX.
