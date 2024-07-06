clear
g++ -std=c++11 -DNDEBUG -Wall *.cpp

rm -rf assets/*

./a.out

for file in assets/*.dot; do
    dot -Tpng "$file" -o "${file%.dot}.png"
done