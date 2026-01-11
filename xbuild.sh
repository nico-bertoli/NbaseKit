#!/bin/bash

echo ""
echo "-------------------- Building"
echo ""

mkdir build
cd build

 #================================ google tests
if [[ "$1" == "--test" ]]; then
    
    # set cmake BUILD_TESTING var to on
    cmake -DBUILD_TESTING=ON .. 
    make

    echo ""
    echo "-------------------- Running tests"
    echo ""

    ctest --output-on-failure   # Run tests with output on failure

    echo ""
    echo "All tests completed!"
    
#================================ normal build
else 
    cmake -S .. -B .
    make
    cpack
fi


