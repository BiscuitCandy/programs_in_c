all : mytree.x mytime.x mymtimes.x

mytree.x : mytree.c
	gcc mytree.c -o mytree.x
	
mytime.x : mytime.c
	gcc mytime.c -o mytime.x
	
mymtimes.x : mymtimes.c
	gcc mymtimes.c -o mymtimes.x
	
clean : 
	rm -f mytree.x mytime.x mymtimes.x
