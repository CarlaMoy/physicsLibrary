#name of .exe
TARGET=PhysicsLibrary
#Adds source file
SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/rigidBody.cpp \
         $$PWD/src/boundingSphere.cpp \
    src/intersectdata.cpp \
    src/aabb.cpp \
    src/plane.cpp \
    src/physicsobject.cpp \
    src/physicsengine.cpp \
    src/collider.cpp \
    src/OpenGLWindow.cpp

#Adds header files
HEADERS+=$$PWD/include/rigidBody.h \
         $$PWD/include/boundingSphere.h \
    include/intersectdata.h \
    include/aabb.h \
    include/plane.h \
    include/physicsobject.h \
    include/physicsengine.h \
    include/collider.h \
    include/OpenGLWindow.h


INCLUDEPATH += $$PWD/include

#add SDL include path
QMAKE_CXXFLAGS+=$$system(sdl2-config --cflags)
LIBS+=$$system(sdl2-config --libs)
LIBS+=-lGLU
#Other files
OTHER_FILES+=.gitignore
OB




