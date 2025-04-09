#ifndef CPP4_3DVIEWER_OPENGLFASAD_H
#define CPP4_3DVIEWER_OPENGLFASAD_H

#include "OpenGL.h"

namespace s21 {

class OpenGLFasad {
 private:
  OpenGL &openGL;

 public:
  OpenGLFasad();
  void init();
  void draw();
  void disable();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_OPENGLFASAD_H
