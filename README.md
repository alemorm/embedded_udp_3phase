# Embedded Linux Test Project

## UDP Communication Project on Raspberry Pi

![3 phase power][clean3phase]

## Description

Testing User Datagram Protocol (UDP) communications on a [Raspberry Pi 3 Model B][raspberrypi]. The Raspberry Pi sends simulated 3-phase power data to a host device in a Local Area Network through an UDP port and the data is visualized real-time using Python.

---

## Overview

The executables (under the [bin directory](bin/)) for [`threephasegenerator`] and [`threephaseforwarder`] are first run on the Raspberry Pi to start listening on the specified UDP ports (6367 and 5367). The python script [`udp_3phase`] is then run on the host device to send an array of options for the simulated 3 phase power data, such as the added noise, time step, frequency and debug mode, to start the simulation. The [`threephaseforwarder`] script receives the array and acts as a gate to relay the communications to the [`threephasegenerator`] script. The simulated data is then sent back to [`threephaseforwarder`], which relays it back to the host device and is displayed real-time.

---

## Setup

### Host Code Development

The development of the host code happens on the host device. The host device is a Windows 10 desktop running [Windows Subsystem for Linux (v1)][wsl] with [Ubuntu 18.04.4 LTS][ubuntu] and [VSCode (v1.46.1)][vscode] with the [remote SSH developmnent][sshext], [C/C++][c++], and the [Python extensions][pythonext]. The Python extension uses a [`conda (v4.8.3)`][conda] [environment] (provided).

### Embedded Code Development

The development of the embedded source code happens on the host device and the compilation happens on the Raspberry Pi.  Once the source code is updated on the host device, a [VSCode compound task][vstasks] uses [`rsync`] for synchronization and [`ssh`] commands for remote compilation using [`cmake`] (v3.6.2) on the Raspberry Pi. This remote compilation strategy was chosen over a emulator such as [qemu] due to the emulator performance decrease, which could impact the build time for more complex projects.

### Getting Started

To replicate this project, follow these steps:

- `git clone https://github.com/alemorm/embedded_udp_3phase.git ~/`

- *Optional*: Either compile the code using the VSCode build task using `CTRL + SHIFT + B` or use the pre-compiled binaries provided (ARM v7).

- SSH to the Raspberry Pi and run the newly created binaries by:

  - `cd ~/embedded_udp_3phase/`
  - `bin/threephaseforwarder &`
  - `bin/threephasegenerator &`

- On the host device, run the python script `udp_3phase` by:

  - `cd ~/embedded_udp_3phase/`
  - `conda env create -f environment.yml`
  - `conda activate embeddedudp`
  - `python scripts/udp_3phase.py`

### Alternative Visualizations

![noisy 3 phase power][noisy3phase]

<!-- Links -->
[`threephasegenerator`]: src/threephasegenerator.c
[`threephaseforwarder`]: src/threephaseforwarder.c
[`udp_3phase`]: scripts/udp_3phase.py
[`liveplotter`]: scripts/liveplotter.py
[clean3phase]: img/noiselessphaseanimation.gif
[noisy3phase]: img/phaseanimation.gif
[vstasks]: .vscode/tasks.json
[qemu]: https://www.poftut.com/qemu-tutorial/
[`cmake`]: https://cmake.org/cmake/help/latest/guide/tutorial/index.html
[`ssh`]: https://www.digitalocean.com/community/tutorials/ssh-essentials-working-with-ssh-servers-clients-and-keys
[raspberrypi]: https://www.raspberrypi.org/products/raspberry-pi-3-model-b/
[`rsync`]: https://www.digitalocean.com/community/tutorials/how-to-use-rsync-to-sync-local-and-remote-directories-on-a-vps
[wsl]: https://docs.microsoft.com/en-us/windows/wsl/install-win10
[ubuntu]: https://www.microsoft.com/en-us/p/ubuntu-1804-lts/9n9tngvndl3q
[vscode]: https://code.visualstudio.com/
[sshext]: https://code.visualstudio.com/docs/remote/ssh
[c++]: https://code.visualstudio.com/docs/languages/cpp
[pythonext]: https://code.visualstudio.com/docs/python/python-tutorial
[conda]: https://docs.conda.io/en/latest/miniconda.html
[environment]: environment.yml
