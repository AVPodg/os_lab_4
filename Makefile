all: lib1.so lib2.so program1 program2

# Библиотека для π
lib1.so: lib1.c
	gcc -shared -fPIC -o lib1.so lib1.c -lm

# Библиотека для e
lib2.so: lib2.c
	gcc -shared -fPIC -o lib2.so lib2.c -lm

# Программа 1 - статическое связывание с ОБЕИМИ библиотеками
program1: program1.c lib1.c lib2.c
	gcc -o program1 program1.c lib1.c lib2.c -lm

# Программа 2 - динамическая загрузка
program2: program2.c
	gcc -o program2 program2.c -ldl

# Запуск
run1: program1
	./program1

run2: program2 lib1.so lib2.so
	LD_LIBRARY_PATH=./ ./program2

# Очистка
clean:
	rm -f program1 program2 *.so

help:
	@echo "Команды:"
	@echo "  make all   - собрать всё"
	@echo "  make run1  - запустить program1"
	@echo "  make run2  - запустить program2"
	@echo "  make clean - удалить файлы"