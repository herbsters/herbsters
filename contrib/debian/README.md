
Debian
====================
This directory contains files used to package herbstersd/herbsters-qt
for Debian-based Linux systems. If you compile herbstersd/herbsters-qt yourself, there are some useful files here.

## herbsters: URI support ##


herbsters-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install herbsters-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your herbsters-qt binary to `/usr/bin`
and the `../../share/pixmaps/herbsters128.png` to `/usr/share/pixmaps`

herbsters-qt.protocol (KDE)

