
Debian
====================
This directory contains files used to package satoshishiftd/satoshishift-qt
for Debian-based Linux systems. If you compile satoshishiftd/satoshishift-qt yourself, there are some useful files here.

## satoshishift: URI support ##


satoshishift-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install satoshishift-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your satoshishiftqt binary to `/usr/bin`
and the `../../share/pixmaps/satoshishift128.png` to `/usr/share/pixmaps`

satoshishift-qt.protocol (KDE)

