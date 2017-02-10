randmain: randmain.o randcpuid.o
	gcc -ldl -Wl,-rpath=$(PWD) -o randmain randmain.o randcpuid.o

randlibhw.so: randlibhw.c
	gcc $(CFLAGS) -fPIC randlibhw.c -shared -o randlibhw.so

randlibsw.so: randlibsw.c
	gcc $(CFLAGS) -fPIC randlibsw.c -shared -o randlibsw.so


