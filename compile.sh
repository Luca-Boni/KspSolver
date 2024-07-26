curPath=$(dirname $0)

for file in $curPath/obj/*.o
do
    rm $file
done

if [ ! -d $curPath'/obj' ]
then
    mkdir $curPath'/obj'
fi

if [ ! -d $curPath'/bin' ]
then
    mkdir $curPath'/bin'
fi

for file in $curPath/src/*.cpp
do
    filename=${file##*/}
    filename=${filename%.*}
    g++ -c $file -o $curPath'/obj/'$filename'.o' -I $curPath'/include'
done

obj=''

for file in $curPath/obj/*.o
do
    obj=$obj' '$file
done

g++ -o $curPath/bin/kspSolver $obj