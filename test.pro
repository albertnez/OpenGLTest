TEMPLATE = app
CONFIG += console
LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lGL
CONFIG -= qt

SOURCES += main.cpp \
    Game.cpp \
    Tools.cpp \
    Shader.cpp \
    Particle.cpp \
    ParticleEmitter.cpp \
    Scene.cpp

HEADERS += \
    Game.hpp \
    Tools.hpp \
    Shader.hpp \
    Particle.hpp \
    ParticleEmitter.hpp \
    Scene.hpp

OTHER_FILES += \
    shaders/Test.frag \
    shaders/Test.vert

