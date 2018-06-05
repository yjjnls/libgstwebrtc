#! /bin/bash
export GSTREAMER_ROOT=~/cerbero/build/dist/linux_x86_64/
mkdir -p build/dtls

pushd build/dtls
cmake ../../dtls
make 
make install

popd
mkdir -p build/webrtcbin

pushd build/webrtcbin
cmake ../../webrtc
make 
make install

popd
