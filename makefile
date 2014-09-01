all:a.o insert.o
	g++ a.o insert.o  -I/usr/include/mysql/ -L/usr/lib/mysql -lmysqlclient -o game_start

a.o:a.cpp	
	g++ -c a.cpp
insert.o:insert.cpp
	g++ -c insert.cpp  -I/usr/include/mysql/ -L/usr/lib/mysql -lmysqlclient 

get:getRecord.cpp
	g++ getRecord.cpp -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -o getRecord

tcpcli:tcpcli.cpp
	g++ tcpcli.cpp error.cpp writen.c readline.c -I./ -o tcpcli

tcpsrv:tcpsrv.cpp
	g++ a2.cpp tcpsrv.cpp error.cpp writen.c -I./ -o tcpsrv

c:
	rm *.o
