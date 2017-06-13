TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt c++11


SOURCES += main.cpp \
    auxiliary.cpp \
    mesh.cpp \
    vertex.cpp \
    index.cpp \
    commonexception.cpp \
    meshexception.cpp \
    transforms.cpp \
    camera.cpp \
    shader.cpp \
    shaderexception.cpp \
    vertexshader.cpp \
    fragmentshader.cpp \
    program.cpp \
    programexception.cpp \
    shape.cpp \
    shapeexception.cpp \
    scene.cpp \
    renderer.cpp \
    rendertarget.cpp \
    rendererexception.cpp \
    appwindow.cpp \
    eventshandler.cpp \
    openglcontext.cpp \
    appwindowexception.cpp \
    openglcontextexception.cpp \
    engine.cpp \
    enginecontext.cpp \
    texture.cpp \
    enginecontextexception.cpp \
    engineexception.cpp \
    application.cpp \
    tasksmanager.cpp \
    light.cpp \
    directlight.cpp \
    pointlight.cpp \
    lightexception.cpp

include(deployment.pri)
qtcAddDeployment()


unix|win32: LIBS += -LC:/glew/lib/Release/Win32 -lglew32s -lglew32 \
                    -lopengl32

INCLUDEPATH += C:/glew/include/GL
DEPENDPATH += C:/glew/include/GL


unix|win32: LIBS += -LC:/SDL2/lib/x86 -lmingw32 -lSDL2main -lSDL2

INCLUDEPATH += C:/SDL2/include
DEPENDPATH += C:/SDL2/include


HEADERS += \
    commonincludings.h \
    auxiliary.h \
    mesh.h \
    vertex.h \
    commondefinitions.h \
    index.h \
    imesh.h \
    commonexception.h \
    meshexception.h \
    transforms.h \
    camera.h \
    icamera.h \
    shader.h \
    ishader.h \
    shaderexception.h \
    vertexshader.h \
    fragmentshader.h \
    program.h \
    iprogram.h \
    programexception.h \
    shape.h \
    ishape.h \
    shapeexception.h \
    scene.h \
    renderer.h \
    irenderer.h \
    rendertarget.h \
    rendererexception.h \
    openglapifunctions.h \
    appwindow.h \
    eventshandler.h \
    openglcontext.h \
    iappwindow.h \
    appwindowexception.h \
    ieventshandler.h \
    iopenglcontext.h \
    openglcontextexception.h \
    engine.h \
    enginecontext.h \
    texture.h \
    ienginecontext.h \
    enginecontextexception.h \
    engineexception.h \
    iengine.h \
    application.h \
    iapplication.h \
    tasksmanager.h \
    itasksmanager.h \
    light.h \
    ilight.h \
    directlight.h \
    pointlight.h \
    lightexception.h \
    commonshapes.h

OTHER_FILES += \
    shape.vsh \
    shape.fsh \
    framebufferobject.vsh \
    shaders/fragment/shape.fsh \
    shaders/vertex/shape.vsh \
    shaders/vertex/pointLight.vsh \
    shaders/fragment/pointLight.fsh \
    shaders/fragment/texture2DRenderer.fsh \
    shaders/vertex/texture2DRenderer.vsh \
    shaders/fragment/directLight.fsh \
    shaders/vertex/directLight.vsh \
    shaders/fragment/lightCombiner.fsh \
    shaders/vertex/lightCombiner.vsh \
    shaders/fragment/shadow.fsh \
    shaders/vertex/shadow.vsh \
    shaders/fragment/blurRange.fsh \
    shaders/vertex/blurRange.vsh

#win32 {
#    PWD_WIN = $${PWD}
#    DESTDIR_WIN = $${OUT_PWD}
#    PWD_WIN ~= s,/,\\,g
#    DESTDIR_WIN ~= s,/,\\,g
#
#    copyfiles.commands = $$quote(cmd /c xcopy /S /I $${PWD_WIN}\\shaders $${DESTDIR_WIN})
#}
#macx {
#    copyfiles.commands = cp -r $$PWD\\shaders $$OUT_PWD
#}
#linux {
#    copyfiles.commands = cp -r $$PWD\\shaders $$OUT_PWD
#}
#QMAKE_EXTRA_TARGETS += copyfiles
#POST_TARGETDEPS += copyfiles

#win32 {
#    copyfiles.commands = @call xcopy "/shaders" "$${DESTDIR}" /h /y /c /r /s /i
#}
#QMAKE_EXTRA_TARGETS += copyfiles
#POST_TARGETDEPS += copyfiles

#unix {
   PWD_SRC = $${PWD}
   DESTDIR_OUT = $${OUT_PWD}

   for(FILE, $${OTHER_FILES}){
       copyfiles.commands += $$QMAKE_COPY $$quote($${PWD_SRC}/$${FILE}) $$quote($${DESTDIR_OUT}) $$escape_expand(\\n\\t)
   }

   QMAKE_EXTRA_TARGETS += copyfiles
   POST_TARGETDEPS += copyfiles
#}





