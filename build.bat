set PATH=C:\cerbero\build-tools\bin;%PATH%
set PKG_CONFIG_LIBDIR=C:\gstreamer\1.0\x86_64\lib\pkgconfig
set GSTREAMER_ROOT=C:/gstreamer/1.0/x86_64/

REM rd /s/q build

REM mkdir build\dtls
REM pushd build\dtls

REM cmake ../../dtls -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX="out" 
REM cmake --build . --target ALL_BUILD --config Debug -- /p:Platform=x64  
REM REM cmake --build . --target INSTALL   --config Debug -- /p:Platform=x64 
REM popd


mkdir build\webrtc
pushd build\webrtc

cmake ../../webrtc -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX="out" 
cmake --build . --target ALL_BUILD --config Debug -- /p:Platform=x64  
REM cmake --build . --target INSTALL   --config Debug -- /p:Platform=x64 
popd
