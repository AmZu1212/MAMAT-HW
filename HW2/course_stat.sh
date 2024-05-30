#!/bin/bash


if [[ $# -ne 1 ]]; then
	echo "Wrong number of arguments" >&2
	exit 0
fi

if [[ ! -f $1".txt" ]]; then
	echo "Course not found" >&2
	exit 0
fi

if [[  -f "prog.exe" ]]; then
	rm "prog.exe"
fi


if [[ -d $1"_stat" ]]; then
	rm -r $1"_stat"
fi

mkdir $1"_stat"

awk -F'	' '{if (NR>1) print $2}' $1".txt" > grades.txt
mv grades.txt $1"_stat"

gcc -g -Wall calc_statistics.c -o prog.exe

./prog.exe $1

cd $1"_stat"/
cat course_statistics.txt