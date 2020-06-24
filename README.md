# Embedded Linux Test Project

## UDP Communication Project on Raspberry Pi

![3 phase power](img/noiselessphaseanimation.gif)

## Description

Testing User Datagram Protocol (UDP) communications on a [Raspberry Pi 3 Model B][raspberrypi]. The Raspberry Pi sends simulated 3-phase power data to a host device in a Local Area Network through an UDP port and the data is visualized real-time using Python.

---

## Overview

The executables (under the [bin directory](bin/)) for [`threephasegenerator`] and [`threephaseforwarder`] are first run on the Raspberry Pi to start listening on the specified UDP ports (6367 and 5367). The python script [`udp_3phase`] is then run on the host device to send an array of options for the simulated 3 phase power data, such as the added noise, time step, frequency and debug mode, to start the simulation. The [`threephaseforwarder`] script receives the array and acts as a gate to relay the communications to the [`threephasegenerator`] script. The simulated data is then sent back to [`threephaseforwarder`], which relays it back to the host device and is displayed real-time.

---

## Setup

### Host Development

The development of the host code happens on the host device. The host device is a Windows 10 desktop running [Windows Subsystem for Linux (v1)][wsl] with [Ubuntu 18.04.4 LTS][ubuntu] and [VSCode (v1.46.1)][vscode] with the [remote ssh developmnent][sshext], [C/C++][c++], and the [python extensions][pythonext].

### Embedded Development

The development of the embedded source code happens on the host device and the compilation happens on the Raspberry Pi.  Once the source code is updated on the host device, a [VSCode compound task][vstasks] uses [`rsync`] for synchronization and [`ssh`] commands for remote compilation using [`gcc`] (v4.9.2) on the Raspberry Pi. This remote compilation strategy was chosen over a emulator such as [qemu]

<!-- Links -->
[`threephasegenerator`]: src/threephasegenerator.c
[`threephaseforwarder`]: src/threephaseforwarder.c
[`udp_3phase`]: scripts/udp_3phase.py
[`liveplotter`]: scripts/liveplotter.py
[`getcmake`]: getcmake.sh
[vstasks]: .vscode/tasks.json
[qemu]: https://www.poftut.com/qemu-tutorial/
[`gcc`]: https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/
[`ssh`]: https://www.digitalocean.com/community/tutorials/ssh-essentials-working-with-ssh-servers-clients-and-keys
[raspberrypi]: https://www.raspberrypi.org/products/raspberry-pi-3-model-b/
[`rsync`]: https://www.digitalocean.com/community/tutorials/how-to-use-rsync-to-sync-local-and-remote-directories-on-a-vps
[wsl]: https://docs.microsoft.com/en-us/windows/wsl/install-win10
[ubuntu]: https://www.microsoft.com/en-us/p/ubuntu-1804-lts/9n9tngvndl3q
[vscode]: https://code.visualstudio.com/
[sshext]: https://code.visualstudio.com/docs/remote/ssh
[c++]: https://code.visualstudio.com/docs/languages/cpp
[pythonext]: https://code.visualstudio.com/docs/python/python-tutorial