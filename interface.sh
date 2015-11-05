#########################################################################
# File Name: interface.sh
# Created Time: 2014年05月07日 星期三 10时24分11秒
#########################################################################
#!/bin/bash

opt1="Single Player"
opt2="Network Head2Head"
opt3="High Scores"
opt4="How To Play"
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
	./game_start
elif [ "$var" = $opt2 ]; then
	echo You have choosed: $var
	echo
	opt21="Choose To Be Server"
	opt22="Choose To Be Client"
	opt23="Go Back"
	optin2="$opt21/$opt22/$opt23"
	select var2 in $optin2;do
		if [ "$var2" = $opt21 ]; then
			echo You have choosed: $var2
			echo
			echo Wait for the client....
			./tcpsrv
		elif [ "$var2" = $opt22 ]; then
			echo You have choosed: $var2
			echo 
			echo -n "Input your host IP address:"
			read IPaddr
			echo Connecting to ths host $IPaddr ...
			sleep 1
			echo Try to input \'start game\' to start the game!
			./tcpcli $IPaddr
		elif [ "$var2" = $opt23 ]; then
			echo You hava choosed: $var2
			echo
			break
		fi
	done
elif [ "$var" = $opt3 ];then
	echo You have choosed: $var
#	./getRecord
elif [ "$var" = $opt4 ];then
	echo You have choosed: $var
	echo
	less res/howToPlay
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
