#!/bin/bash
sudo apt-mark hold linux-image-4.14.0-qcomlt-arm64
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade
sudo apt-get install -y cmake xorg

# Install MRAA library
git clone https://github.com/intel-iot-devkit/mraa.git
mkdir -p mraa/build
cd mraa/build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
make -j4
sudo make install
sudo ldconfig /usr/local/lib

# Install Qt dependencies
sudo apt-get build-dep qt4-x11
sudo apt-get build-dep libqt5gui5
sudo apt-get install -y libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0
sudo mkdir /usr/local/qt5dragon
sudo chown linaro:linaro /usr/local/qt5dragon

