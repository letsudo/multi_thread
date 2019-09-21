#!/bin/sh
echo Clean
./clean.sh

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo ==== Current machine is ${machine} ! =====

if [ ${machine} == "Mac" ]; then 
	echo Strat build MacOS project
	mkdir DemoProject
	cd DemoProject
	cmake .. -G "Xcode"
elif [ ${machine} == "Linux" ]; then
	echo Strat build CentOS project
	#make
	mkdir DemoProject
	cd DemoProject
	cmake .. -DLINUX_DISTRIBUTION="centos"
	make
	./DemoProject
elif [ ${machine} == "MinGw" ]; then
	echo Strat build Windows project
	echo BuildWinProject
	mkdir DemoProject
	cd DemoProject
	cmake .. -G "Visual Studio 15 2017 Win64"
else
   echo Unsupport Platform !
fi


