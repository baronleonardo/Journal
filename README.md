[![Stories in Ready](https://badge.waffle.io/lordadamson/Journal.png?label=ready&title=Ready)](https://waffle.io/lordadamson/Journal)
# Journal
a note taking application that is heavily inspired by OneNote.

# Class Diagram
![Class Diagram](/uml.png)

## Dependencies
This project is based on the wonderful Qt framework.

If you're on Windows download and install it here: https://www.qt.io/download-open-source/
If you're on Linux use your package manager.
### Ubuntu
`sudo apt install sudo apt-get install qt5-default qttools5-dev-tools mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev`
### Fedora
`sudo dnf install qt5-qt*`
### Arch

`sudo pacman -S qt5-base qt5-tools mesa cmake`
Also, you have to build and install the [git-lfs package](https://aur.archlinux.org/packages/git-lfs/) so the file **huge_dictionary.h** becomes available
for the build process.
You can use [Yaourt](https://archlinux.fr/yaourt-en) or other [AUR package helpers](https://wiki.archlinux.org/index.php/AUR_helpers) to make this
process easy. In the Yaourt case, you can just

`yaourt -S git-lfs`

This process is interactive, to make sure the git-lfs dependencies are also installed.
If you want to speed up the process add the --noconfirm option:

`yaourt -S git-lfs --noconfirm`

## Build

Journal uses qmake as its default build tool. The build it's pretty straightforward. In the directory of the same level
as Journal, create a build folder:

`cd $JOURNAL_HOME/..`
`mkdir build`
`qmake-qt5 ../Journal`
`make`

Depending of your linux distribution, your qmake program might be different. If you are not using `qtcreator` and
have other versions of `qt` installed (`qt4` for example), you should ensure that you are building with `qmake-qt5`.



## Setting up the development environment
I use [Qt Creator](https://www.qt.io/ide/) to develop and I recommend using it.

The project uses qmake, so import the project to qtcreator and it should be fine as long as you have a recent version of qt.

## Use the terminal to build and run
Do the following if you only want to try Journal. If you want to contribute code I strongly recommend Setting up the development environment.

Make sure you have the dependencies installed and then:
* go to the project directory `cd Journal`
* `mkdir build`
* `cd build`
*  if on Ubuntu: `qmake ..` if on Fedora `qmake-qt5 ..`
*  `make`
*  `./Journal`
