#!/bin/bash
for i in {1..5}; do
    echo "make day $i:"
    cd day$i
    make
    echo "make day $i done"
    echo "run:"
    ../build/day$i
    echo "run of day$i complete"
    cd ..
done

# for i in {2..5}; do
#     cd day$i
#     echo "run day $i:"
#     ../build/day$i
#     cd ..
# done
