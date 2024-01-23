cmake_minimum_required(VERSION 3.20)
project(ubee512 VERSION 7.0.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)
find_package(nuklear REQUIRED)
find_package(OpenGL REQUIRED)

# configure_file(src/ubee_config.h.in ubee_config.h)

add_executable(ubee512 WIN32
        src/ubee512.c
        # hardware emulation components
        src/crtc.c
        src/fdc.c
        src/keyb.c
        src/memmap.c
        src/vdu.c
        src/z80.c
        src/disk.c
        src/pio.c
        src/sound.c
        src/roms.c
        src/tape.c
        src/function.c
        src/async.c
        src/serial.c
        src/printer.c
        src/rtc.c
        src/clock.c
        src/scc.c
        src/z80debug.c
        src/options.c
        src/joystick.c
        src/console.c
        src/video.c
        src/ide.c
        src/hdd.c
        src/mouse.c
        src/beetalker.c
        src/sp0256.c
        src/beethoven.c
        src/ay38910.c
        src/dac.c
        src/sn76489an.c
        src/sn76489an_core.c
        src/compumuse.c

        src/keystd.c
        src/keytc.c

        # internal components
        src/tapfile.c
        src/gui.c
        src/osd.c
        src/md5.c
        src/getopt.c
        src/log.c
        src/support.c
        src/quickload.c
        src/audio.c
        src/font.c

        extern/glad/src/gl.c
        )
target_include_directories(ubee512 PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(ubee512 PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        nuklear::nuklear
        OpenGL::GL)
target_compile_definitions(ubee512 PRIVATE
        APPVER="${ubee512_VERSION}"
        TITLESTRING="uBee512 - v${ubee512_VERSION} - Microbee emulator"
        ICONSTRING="uBee512"
        COPYENDSTRING="2024"
        APPIDSTR="ubee512"
        USE_OPENGL=1
)
