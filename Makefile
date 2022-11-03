OS_Assignment:
	gcc ls.c -o ls
	gcc date.c -o date
	gcc cat.c -o cat
	gcc rm.c -o rm
	gcc mkdir.c -o mkdir
	gcc laksh.c -o laksh
	./laksh

clean:
	rm ls date cat rm mkdir laksh