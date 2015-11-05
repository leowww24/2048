EXECUTABLE=game_start tcpcli tcpsrv

all:$(EXECUTABLE)

game_start:
	g++ -o game_start game.cpp

#insert.o:insert.cpp
	#g++ -c insert.cpp  -I/usr/include/mysql/ -L/usr/lib/mysql -lmysqlclient 

#get:getRecord.cpp
	#g++ getRecord.cpp -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -o getRecord

tcpcli:tcpcli.cpp
	g++ game4network.cpp tcpcli.cpp error.cpp writen.c readline.c -lpthread -I./ -o tcpcli

tcpsrv:tcpsrv.cpp
	g++ game4network.cpp tcpsrv.cpp error.cpp writen.c -lpthread -I./ -o tcpsrv

clean:
	rm *.o $(EXECUTABLE)
