[![Stories in Ready](https://badge.waffle.io/lordadamson/Journal.png?label=ready&title=Ready)](https://waffle.io/lordadamson/Journal)
# Journal
a note taking application that is heavily inspired by OneNote.

# UML
![UML Diagram](/uml.png)

## Dependencies
This project is based on the wonderful Qt framework.

If you're on Windows download and install it here: https://www.qt.io/download-open-source/
If you're on Linux use your package manager.
### Ubuntu
`sudo apt install sudo apt-get install qt5-default qttools5-dev-tools` (I don't have ubuntu, let me know if there are more packages the needs to be installed please).
### Fedora
`sudo dnf install qt5-qt*`
### Arch
I don't know! If you have arch send a pull request to let the world know what commands to do!

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
*  `./Jounral`
