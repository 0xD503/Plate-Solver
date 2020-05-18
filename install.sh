
##  Installation prequisitions
echo 'Creating the neccesary directories...'
mkdir ./obj
mkdir ./obj/Debug
mkdir ./obj/Debug/src
mkdir ./bin
mkdir ./bin/Debug

##  Compilation
echo 'Compiling...'
make

##  Installation
#echo 'Installing'


##  Creating run.sh file
'./bin/Debug/Plate-Solver\n' > ./run.sh

##
echo 'Installation status: SUCCESS'
