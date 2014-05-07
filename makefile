all:a.o insert.o
	g++ a.o insert.o  -I/usr/include/mysql/ -L/usr/lib/mysql -lmysqlclient -o game_start

a.o:a.cpp	
	g++ -c a.cpp
insert.o:insert.cpp
	g++ -c insert.cpp  -I/usr/include/mysql/ -L/usr/lib/mysql -lmysqlclient 

get:getRecord.cpp
	g++ getRecord.cpp -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -o getRecord


c:
	rm *.o
