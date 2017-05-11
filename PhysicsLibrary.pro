#name of .exe
TARGET=PhysicsLibrary


#INCLUDEPATH += $$PWD/include

#add SDL include path
#QMAKE_CXXFLAGS+=$$system(sdl2-config --cflags)
#LIBS+=$$system(sdl2-config --libs)
#LIBS+=-lGLU
#Other files



OBJECTS_DIR=obj
# core Qt Libs to use add more here if needed.
QT+=gui opengl core widgets

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}
# where to put moc auto generated files
MOC_DIR=moc
# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle

#Adds source file
SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/rigidBody.cpp \
         $$PWD/src/boundingSphere.cpp \
         $$PWD/src/intersectdata.cpp \
         $$PWD/src/aabb.cpp \
         $$PWD/src/plane.cpp \
         $$PWD/src/physicsengine.cpp \
         $$PWD/src/collider.cpp \
         $$PWD/src/NGLScene.cpp \
         $$PWD/src/NGLSceneMouseControls.cpp \
         $$PWD/src/rigidBodyFactory.cpp \
         $$PWD/src/sphere.cpp \
         $$PWD/src/StaticPlane.cpp \
    src/MainWindow.cpp



# same for the .h files
HEADERS+= $$PWD/include/NGLScene.h \
          $$PWD/include/WindowParams.h\
          $$PWD/include/rigidBody.h \
          $$PWD/include/boundingSphere.h \
          $$PWD/include/intersectdata.h \
          $$PWD/include/aabb.h \
          $$PWD/include/plane.h \
          $$PWD/include/physicsengine.h \
          $$PWD/include/collider.h \
          $$PWD/include/rigidBodyFactory.h \
          $$PWD/include/rigidBodyTypeInfo.h \
          $$PWD/include/sphere.h \
          $$PWD/include/StaticPlane.h \
    include/MainWindow.h


# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include
# where our exe is going to live (root of project)
DESTDIR=./
# add the glsl shader files
OTHER_FILES+= README.md\
              .gitignore\
              $$PWD/shaders/*.glsl
# were are going to default to a console app
CONFIG += console
# note each command you add needs a ; as it will be run as a single line
# first check if we are shadow building or not easiest way is to check out against current
#!equals(PWD, $${OUT_PWD}){
#	copydata.commands = echo "creating destination dirs" ;
#	# now make a dir
#	copydata.commands += mkdir -p $$OUT_PWD/shaders ;
#	copydata.commands += echo "copying files" ;
#	# then copy the files
#	copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;
#	# now make sure the first target is built before copy
#	first.depends = $(first) copydata
#	export(first.depends)
#	export(copydata.commands)
#	# now add it as an extra target
#	QMAKE_EXTRA_TARGETS += first copydata
#}
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}

FORMS += \
    UI/MainWindow.ui





