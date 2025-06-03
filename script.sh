#!/usr/bin/env bash

CODE_DIR="./src/APPRO"
DATA_DIR="./3023244222-1-3/data"
RES_DIR="./3023244222-1-3/experiments"

if [ -d "$RES_DIR" ]
then
	rm -r "$RES_DIR"
fi

mkdir "$RES_DIR"

find "$CODE_DIR" -type f | while IFS= read -r src;
do
	src_name="${src##*/}"
	out_name="${src_name%%.*}.out"
	echo "ready to compile $src_name and run..."
	g++ "$src" -o "$out_name"

	find "$DATA_DIR" -type f | while IFS= read -r file;
    do
    	file_name="${file##*/}"
    	txt=".txt"
    	ans="-ans.txt"
    	if [[ $file_name == *$txt* ]] && ! [[ $file_name == *$ans* ]]
    	then
    		echo "-testing $file_name"
    		"./$out_name" < "$file" > "$RES_DIR/${src_name%%.*}_${file_name%%.*}.txt"
    	fi
    done
done
