# Embedded Linux Test Project

## UDP Communication Project on Raspberry Pi

## Description

Testing User Datagram Protocol (UDP) communications on a Raspberry Pi 3 Model B. The Raspberry Pi sends simulated 3-phase power data to another device in a Local Area Network through an UDP port and the data is visualized real-time using Python.

## Overview

The executables (under the [bin directory](bin/)) for [`threephasegenerator`] and [`threephaseforwarder`] are first run on the Raspberry Pi to start listening on the specified ports (Port:6367). The python script [`udp_3phase`] is then run on the host machine to send an array of options for the simulated 3 phase power data such as the added noise, time step, frequency and debug mode to start the simulation. The [`threephaseforwarder`] script receives the array and acts as a gate to relay the communications to the [`threephasegenerator`] script. The simulated data is then sent back to [`threephaseforwarder`], which relays it back to host machine and displayed real-time.

## Embedded Development

The development of the embedded source code happens on the host machine and the compilation happens on the Raspberry Pi. The host machine running Windows Subsystem for Linux and VSCode uses a [VSCode compound task][vstasks] with [`rsync`] for synchronization and [`ssh`] commands for compilation using [`gcc`] (v4.9.2) on the Raspberry Pi.

[`ssh`]: https://www.digitalocean.com/community/tutorials/ssh-essentials-working-with-ssh-servers-clients-and-keys
[`rsync`]: https://www.digitalocean.com/community/tutorials/how-to-use-rsync-to-sync-local-and-remote-directories-on-a-vps
[`gcc`]: https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/
[vstasks]: .vscode/tasks.json
[`threephasegenerator`]: src/threephasegenerator.c
[`threephaseforwarder`]: src/threephaseforwarder.c
[`udp_3phase`]: scripts/udp_3phase.py
[`liveplotter`]: scripts/liveplotter.py
[`getcmake`]: getcmake.sh