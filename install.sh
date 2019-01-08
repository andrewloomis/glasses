#!/bin/bash
BUILD_DIR=$PWD

sudo apt-mark hold linux-image-4.14.0-qcomlt-arm64
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get dist-upgrade -y
sudo apt-get install -y git cmake xorg autoconf build-essential \
    libtool-bin pkg-config

# Install libsoc library
if [ -e "/usr/lib/aarch64-linux-gnu/libsoc.so.2" ]; then
    echo "libsoc already installed"
else
    git clone https://github.com/jackmitch/libsoc.git
    cd libsoc
    autoreconf -i
    ./configure
    make -j$(nproc)
    sudo make install
    cd BUILD_DIR
    rm -rf libsoc
fi

# Install Qt dependencies
sudo apt-get build-dep -y qt4-x11
sudo apt-get build-dep -y libqt5gui5
sudo apt-get install -y libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0
sudo mkdir /usr/local/qt5dragon
sudo chown linaro:linaro /usr/local/qt5dragon

