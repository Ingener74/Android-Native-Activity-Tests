#!/bin/sh
echo '========================================================================='
echo '> Install OGRE Dependencies...'
echo '========================================================================='
sudo apt-get install build-essential automake libtool
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get install nvidia-cg-toolkit libois-dev libboost-thread-dev
sudo apt-get install doxygen graphviz libcppunit-dev
echo '========================================================================='
echo '> Done'
echo '========================================================================='

echo '========================================================================='
echo '> Install OpenCV Dependencies...'
echo '========================================================================='
sudo apt-get install ant
echo '========================================================================='
echo '> Done'
echo '========================================================================='
