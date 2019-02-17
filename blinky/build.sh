#!/bin/bash
compileserver=acer
compileroot=/home/varun/coding/c
project=$(basename "`pwd`")
avrdude=../../tools/avrdude

function fmake {
echo Project is $project
echo Syncing files with complie server : $compileserver
rsync -aP --delete --exclude=".*" --exclude="tmp" --exclude="bin"  ../$project varun@$compileserver:$compileroot
echo Running make on target
ssh acer "cd $compileroot/$project;make"
echo Copy binary back to us
rsync -a  acer:$compileroot/$project/bin/$project.hex bin/
}

function fburn {
$avrdude/avrdude.exe -CC:$avrdude/avrdude.conf -v -patmega328p -carduino -PCOM3 -b115200 -D -Uflash:w:bin/$project.hex:i
}

function fall {
	fmake
	fburn
}

if [ $# -eq 0 ]; then
	fall
else
	case "$1" in
		make)
			fmake
			;;
		burn)
			fburn
			;;
		*)
			echo Invalid Option
			;;
	esac
fi


