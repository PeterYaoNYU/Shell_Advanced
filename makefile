all: parseandredirect

parseandredirect: utility.h parseandredirect.c
	gcc -o parseandredirect -g -Wall parseandredirect.c
