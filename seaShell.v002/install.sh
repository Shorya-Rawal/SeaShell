mkdir out
gcc src/main.c -o out/main
gcc bin/a.c -o bin/a
gcc bin/b.c -o bin/b
gcc bin/c.c -o bin/c

echo Installation complete.
./out/main
