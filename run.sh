clear
g++ -std=c++11 -DNDEBUG -Wall *.cpp

rm -rf assets/*

valgrind ./a.out

for file in assets/*.dot; do
    dot -Tpng "$file" -o "${file%.dot}.png"
done

rm -rf assets/*.dot
