#########################################################################
# File Name: try.sh
# Created Time: 2014年05月07日 星期三 11时39分43秒
#########################################################################
#!/bin/bash
str="aaa bbb ccc ddd\ DDD"
for s in $str
do
	echo $s
done

echo
echo now change the '$IFS':
IFS='\'
for s in $str
do 
	echo $s
done
