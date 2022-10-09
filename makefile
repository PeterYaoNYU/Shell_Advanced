all: shell

shell: shell.c utility.h makeargv.c parseandredirect.c execute_cmd.c
	gcc -o shell -g -Wall shell.c execute_cmd.c makeargv.c parseandredirect.c siginit.c
	# ./shell

# execute_cmd: makeargv parseandredirect execute_cmd.c utility.h
# 	gcc -o execute_cmd -g -Wall execute_cmd.c

# makeargv: makeargv.c utility.h
# 	gcc -o makeargv -g -Wall makeargv.c

# parseandredirect: utility.h parseandredirect.c
# 	gcc -o parseandredirect -g -Wall parseandredirect.c

clean:
	rm -f shell