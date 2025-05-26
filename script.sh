#!/usr/bin/env bash

CODE_DIR="./src/APPRO"
DATA_DIR="./resource/testcases/TSP"

find "$CODE_DIR" -type f | while IFS= read -r src;
do
	src_name="${src##*/}"
	out_name="${src_name%%.*}.out"
	echo "$src_name"
	g++ "$src" -o "$out_name"

	find "$DATA_DIR" -type f | while IFS= read -r file;
    do
    	file_name="${file##*/}"
    	txt=".txt"
    	ans="-ans.txt"
    	if [[ $file_name == *$txt* ]] && ! [[ $file_name == *$ans* ]]
    	then
    		echo "$file_name"
    		"./$out_name" < "$file" > "./result/${src_name%%.*}-${file_name%%.*}.txt"
    	fi

    done
done



