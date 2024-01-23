from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeDeps, CMakeToolchain, CMake


class Ubee512Conan(ConanFile):
    name = "ubee512"
    version = "7.0.0-pre1"
    description = "A portable(-ish) emulator of the Microbee family of home computers"
    license = "GPL-2.0"
    author = "Chris Collins <kuroneko@sysadninjas.net>"
    topics = ("emulation", "microbee", "z80", "cpm")
    settings = "os", "arch", "compiler", "build_type"
    options = {}
    default_options = {}

    requires = [
        "sdl/2.28.5",
        "nuklear/4.12.0",
    ]

    export_sources = [
        "CMakeLists.txt",
        "LICENSE",
        "README.md",
        "config/*",
        "disks/*",
        "doc/*",
        "images/*",
        "libs/*",
        "patches/*",
        "src/*",
        "tools/*",
    ]

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
