echo "installing seashell version 1.0"
gcc src/main.c out/main
sudo chmod a+x out/main
sudo cp out/main /bin/seashell
