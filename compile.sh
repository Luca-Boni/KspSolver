curPath=$(dirname $0)

if [ ! -d $curPath'/bin' ]
then
    mkdir $curPath'/bin'
fi

src=''

for file in $curPath/src/*.cpp
do
    src=$src' '$file
done

g++ $src -I include/ -O3 -o $curPath/bin/kspSolver