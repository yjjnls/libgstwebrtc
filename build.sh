#! /bin/bash
mkdir -p build

pushd build
cmake ..
make 
make install

popd