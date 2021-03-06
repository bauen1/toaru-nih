# ToaruOS-NIH

![screenshot](https://i.imgur.com/vwVV7sG.png)

ToaruOS-NIH is a distribution of ToaruOS which contains no third-party components. Its bootloader, kernel, modules, C library, and userspace applications are all written by the ToaruOS development team and direct contributors.

This distribution aims to eventually replace the core of the mainline ToaruOS, with the various third-party components building against our own C library. This is a long-term project, and developing the C library to the point where it is useful for this purpose is not expected to be completed for quite some time.

## Implementation Details

All source code for the entire operating system is included in this repository.

### Kernel

The NIH kernel is essentially the same as the mainline kernel, though the PCI vendor and device ID list has been replaced with our own slimmed down version. This was the only third-party element of the ToaruOS kernel. Additionally, the headers for the kernel have been relocated from their original directories to facilitate a cleaner build. The NIH kernel should be considered the latest version of the ToaruOS kernel.

### Bootloader

Mainline ToaruOS shipped with GRUB, which provided a multiboot-compatible ELF loader. To that end, our native bootloader also implements multiboot. However, as writing a feature-complete bootloader is not a goal of this project, the native bootloader is very limited, supporting only ATAPI CDs on systems with El Torito "no-emulation" support. It is not guaranteed to work on real hardware, but has been tested in QEMU, Bochs, VirtualBox, and VMware Player.

### Userspace

The userspace includes a work-in-progress C standard library, the ToaruOS native libraries, the compositor (using only in-house graphics routines), and various other first-party utilities and applications.

## Building

First, ensure you have the necessary build tools, which are mostly the same as mainline ToaruOS: `yasm`, `xorriso`, `genext2fs` (with Debian patches), `python`.

Run `make` and you will be prompted to build a toolchain. Reply `y` and allow the toolchain to build.

## Rationale

ToaruOS's kernel is entirely in-house. Its userspace, however, is built on several third-party libraries and tools, such as the Newlib C library, Freetype, Cairo, libpng, and most notably Python. While the decision to build ToaruOS on these technologies is not at all considered a mistake, the possibility remains to build a userspace entirely from scratch.

## Goals

- **Write a basic C library.**

  To support building the native ToaruOS libraries and port some basic software, a rudimentary C library is required.

- **Remove Cairo as a dependency for the compositor.**

  Cairo is a major component of the modern ToaruOS compositor, but is the only significant third-party dependency. This makes the compositor, which is a key part of what makes ToaruOS "ToaruOS", an important inclusion in this project. Very basic work has been done to allow the compositor to build and run without Cairo, but it is a naïve approach and remains very slow. Implementing Cairo's clipping and SSE-accelerated blitting operations is a must.

- **Write a vector font library.**

  Support for TrueType/OpenType TBD, but vector fonts are critical to the visual presentation of ToaruOS.

- **Support a compressed image format.**

  ToaruOS used a lot of PNGs, but maybe writing our own format would be fun.

## Roadmap

1. Enough C to port the dynamic loader. (Done)

2. Get the VGA terminal building. (Done)

3. Get the shell running. (Done)

4. De-Cairo-tize the compositor. (Done, but more work planned)

6. Enough C to port Python. (In progress)

7. Enough C to port GCC. (In progress)

## Project Layout

- **apps** - Userspace applications, all first-party.
- **base** - Ramdisk root filesystem staging directory. Includes C headers in `base/usr/include`, as well as graphical resources for the compositor and window decorator.
- **boot** - Bootloader.
- **kernel** - The ToaruOS kernel.
- **lib** - Userspace libraries.
- **libc** - C standard library implementation.
- **linker** - Userspace dynamic linker/loader, implements shared library support.
- **modules** - Kernel modules/drivers.
- **util** - Utility scripts, staging directory for the toolchain (binutils/gcc).
