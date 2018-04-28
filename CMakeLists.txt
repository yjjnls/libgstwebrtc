cmake_minimum_required(VERSION 2.8)
project(libgstwebrtc)

macro( project_group source_files sgbd_cur_dir)
    if(MSVC)
        foreach(sgbd_file ${${source_files}})

            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
			string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
			
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
			
            source_group(${sgbd_group_name} FILES ${sgbd_file})
			
        endforeach(sgbd_file)
    endif()
endmacro(project_group)


file(GLOB_RECURSE  LWS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ext/*.[ch] ${CMAKE_CURRENT_SOURCE_DIR}/src/ext/*.c)
project_group(LWS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})

find_package(PkgConfig 0.29.1 REQUIRED)

pkg_check_modules(GST_MODULES  REQUIRED
                  gstreamer-1.0>=1.14.0
                  gstreamer-base-1.0>=1.14.0
                  )

include_directories($ENV{GSTREAMER_ROOT}/include)
include_directories($ENV{GSTREAMER_ROOT}/include/gstreamer-1.0)
include_directories($ENV{GSTREAMER_ROOT}/include/glib-2.0)
include_directories($ENV{GSTREAMER_ROOT}/lib/glib-2.0/include)
include_directories($ENV{GSTREAMER_ROOT}/include/nice)

link_directories($ENV{GSTREAMER_ROOT}/lib $ENV{GSTREAMER_ROOT}/bin)

add_library(libgstwebrtc  SHARED ${LWS_SOURCES})
target_link_libraries(libgstwebrtc  gstreamer-1.0.lib
                                    gobject-2.0.lib
                                    glib-2.0.lib
                                    gstsdp-1.0.lib
                                    nice.lib
                                    intl.lib
                                    gio-2.0.lib
                                    ws2_32.lib
                                    gstwebrtc-1.0)
                
ADD_DEFINITIONS( -DGST_USE_UNSTABLE_API  )
ADD_DEFINITIONS( -DVERSION="1.14.0"  )
ADD_DEFINITIONS( -DPACKAGE="gst-plugins-bad"  )
ADD_DEFINITIONS( -DGST_PACKAGE_NAME="GStreamer Bad Plug-ins source release"  )
ADD_DEFINITIONS( -DGST_PACKAGE_ORIGIN="Unknown package origin"  )

install(TARGETS libgstwebrtc
		RUNTIME DESTINATION $ENV{GSTREAMER_ROOT}/lib/gstreamer-1.0
        )