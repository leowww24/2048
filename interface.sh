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
	~/code/git/2048_game/game_start
elif [ "$var" = $opt2 ]; then
	echo You have choosed: $var
	echo
	opt21="Server"
	opt22="Client"
	opt23="Back"
	opt2="$opt21/$opt22/$opt23"
	select var2 in $opt2;do
		if [ "$var2" = $opt21 ]; then
			echo You have choosed: $var2
			echo
			echo Wait for the client....
			~/code/git/2048_game/tcpsrv
		elif [ "$var2" = $opt22 ]; then
			echo You have choosed: $var2
			echo 
			echo -n "Input your host IP address:"
			read IPaddr
			echo Connecting to ths host $IPaddr ...
			sleep 1
			echo Try to input 'start game' to start the game!
			~/code/git/2048_game/tcpcli $IPaddr
		elif [ "$var2" = $opt23 ]; then
			echo You hava choosed: $var2
			echo
			break
		fi
	done
elif [ "$var" = $opt3 ];then
	echo You have choosed: $var
	~/code/git/2048_game/getRecord
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
