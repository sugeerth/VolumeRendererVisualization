#ifndef GL_CONFIG_H
#define GL_CONFIG_H

#ifdef __APPLE__
#include <QtOpenGL>
#include <OpenGL.h>
#else
//#define GLEW_STATIC
#include<GL/glew.h>
#include<GL/glut.h>

#endif

//#define NDEBUG
#include <cassert>

#include <QDebug>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "Mat.h"
#include "Vec.h"

#endif // GLCONFIG_H
