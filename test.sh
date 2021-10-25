#!bash

clean() {
    cd src
    make clean
    cd ..
    rm STLSet/stl_set generator/generator input my_set.out stl_set.out
}

case "$1" in
    clean)
        clean
        exit 0;;
    
esac

cd src
make
cd ..

g++ -o STLSet/stl_set STLSet/stl_set.cpp

gcc -o generator/generator generator/generator.c

./generator/generator > input

./src/my_set < input > my_set.out
./STLSet/stl_set < input > stl_set.out

diff my_set.out stl_set.out

if [ $? -eq 0 ] ; then
    echo "No Error!"
else
    echo "Error! Please check the log!"
fi

echo "Check finished!"