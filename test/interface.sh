#########################################################################
# File Name: test_interface.sh
# Title: 
# Description: 
# Created Time: 2015年11月01日 星期日 10时43分56秒
#########################################################################
#!/bin/bash

opt1="single"
opt2="multiple"
opt3='exit'

clear
IFS='/'
opt="$opt1/$opt2/$opt3"
select var in $opt
do
	if [ "$var" = $opt1 ]
	then
		echo "you choose single!"
		echo "$var"
	else
		exit
	fi
done
