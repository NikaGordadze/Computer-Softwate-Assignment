cmake_minimum_required(VERSION 3.16)

project(OrderedSet LANGUAGES C)

add_executable(OrderedSet main.c
    doubleLinkedList.c
    doubleLinkedList.h
    orderedIntSet.c
    orderedIntSet.h
    menu.c
    menu.h)

include(GNUInstallDirs)
install(TARGETS OrderedSet
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
