# objetivo : dependencias
#	comandos
#	comandos2
#	comandos3 etc


bin/Jacobi.exe : src/Main.cpp
	@echo COmpilando codigo fuente
	g++ -o bin/Jacobi	src/Main.cpp -Iinclude
run: bin/Jacobi2
	bin/Jacobi2
clean:
	@echo Se Borraron todos los archivos .exe
	rm -f bin/*.exe