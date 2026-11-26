cmake_minimum_required(VERSION 3.16)

project(OrderedSet LANGUAGES C)

add_executable(OrderedSet main.c)

include(GNUInstallDirs)
install(TARGETS OrderedSet
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
