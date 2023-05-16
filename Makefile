CC = gcc

all: my_shells my_storage_use my_userid

my_shells: my_shells.c
	$(CC) -o my_shells my_shells.c

my_storage_use: my_storage_use.c
	$(CC) -o my_storage_use my_storage_use.c

my_userid: my_userid.c
	$(CC) -o my_userid my_userid.c

clean:
	rm -f my_shells my_storage_use my_userid my_storage_details.txt
