cmake -S src -B build
cd build
compiledb make
./$(find . -perm +111 -type f -maxdepth 1)
