[![Stories in Ready](https://badge.waffle.io/lordadamson/Journal.png?label=ready&title=Ready)](https://waffle.io/lordadamson/Journal)
# Journal
a note taking application that is heavily inspired by OneNote.

# Class Diagram
![Class Diagram](/uml.png)

## Dependencies
### Qt5
This project is uses the wonderful Qt framework.

Download and install it from the [official Qt download page](https://www.qt.io/download-open-source/).

If you're on Linux you could use your package manager to install Qt like below, though you most probably won't get the latest version.

#### Ubuntu

```bash
sudo apt-get install qt5-default qttools5-dev-tools mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev
```

#### Fedora

```bash
sudo dnf install qt5-qt*
```

#### Arch

```bash
sudo pacman -S qt5-base qt5-tools mesa
```

### Git LFS
You'll need to install the [Git LFS package](https://git-lfs.github.com/).

on **Arch** you can install the [git-lfs package](https://aur.archlinux.org/packages/git-lfs/) using [Yaourt](https://archlinux.fr/yaourt-en) or other [AUR package helpers](https://wiki.archlinux.org/index.php/AUR_helpers) to make this
process easy. In the Yaourt case, you can just

```bash
yaourt -S git-lfs
```

This process is interactive, to make sure the git-lfs dependencies are also installed.
If you want to speed up the process add the --noconfirm option:

```bash
yaourt -S git-lfs --noconfirm
```

## Build

Journal uses qmake as its default build tool and it's pretty straightforward, but depending of your linux distribution,
your qmake program might be different. If you are not using `qtcreator` and have other versions of `qt` installed
(`qt4` for example), you should ensure that you are building with `qmake-qt5`.


### Setting up the development environment
If you want to contribute code I strongly recommend using [Qt Creator](https://www.qt.io/ide/) to develop.
The project uses qmake, so import the project to qtcreator and it should be fine as long as you have a version of Qt5.

To proper import, Open QtCreator and in the top menu, go to File > Open File or Project and open the repository `Journal.pro` file.

You're good to go!

### Use the terminal to build and run
Do the following if you only want to try Journal.
Make sure you have the dependencies installed and then:

```bash
cd $JOURNAL_HOME
mkdir build && cd build
qmake ..
make
./Journal
```

Where `$JOURNAL_HOME` is the folder that you cloned the Journal repository into and qmake is the Qt5 compactible qmake tool.
