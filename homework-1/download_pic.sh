#!/bin/bash

mkdir attachments
directory="./attachments"

width=800
height=400

count=20

if [ $1 != "" ]; then
	if [ $2 != "" ]; then
		width=$1
		height=$2
	else
		width=$1
		height=$width
	fi
fi

if [ $3 != "" ]; then
	count=$3
fi


for ((i=1; i<=$count; i++))
do
	curl "https://picsum.photos/$width/$height" -L > "$directory/photo-$i.png"
done