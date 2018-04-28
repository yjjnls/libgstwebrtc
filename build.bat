set PATH=C:\cerbero\build-tools\bin;%PATH%
set PKG_CONFIG_LIBDIR=C:\gstreamer\1.0\x86_64\lib\pkgconfig
set GSTREAMER_ROOT=C:/gstreamer/1.0/x86_64/

rd /s/q build

mkdir build
pushd build

cmake .. -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX="out" 
cmake --build . --target ALL_BUILD --config Debug -- /p:Platform=x64  
cmake --build . --target INSTALL   --config Debug -- /p:Platform=x64 
popd
