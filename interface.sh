#########################################################################
# File Name: interface.sh
# Created Time: 2014年05月07日 星期三 10时24分11秒
#########################################################################
#!/bin/bash

opt1="Single play"
opt2="Network head2head"
opt3="High scores"
opt4="How to paly"
opt5="Exit"

clear
echo "Welcome to my tiny game!"
echo "Give you order by input the number of the choices..."
echo 

IFS='/'
opt="$opt1/$opt2/$opt3/$opt4/$opt5"
select var in $opt;do
if [ "$var" = $opt1 ]; then
	echo You have choosed: $var
	echo
	echo After 3 seconds the game will begin...
	echo
	sleep 3
	~/code/git/2048_game/a
elif [ "$var" = $opt2 ]; then
	echo You have choosed: $var
	echo -e "\nWait for version2.0\nI will add this function...\n"
elif [ "$var" = $opt3 ];then
	echo You have choosed: $var
	echo -e "\nwait for mysql or file\n"
elif [ "$var" = $opt4 ];then
	echo You have choosed: $var
	echo -e "\nwait for the file\n"
elif [ "$var" = $opt5 ];then
	exit
else
	echo Unknow input!
	echo -e "\nAfter 1 seconds,you can input again...\n"
	sleep 1
fi
done
IFS=' '

exit 0
