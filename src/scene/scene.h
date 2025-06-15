//
// Created by MacBook on 25-6-15.
//

#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <model.h>

class scene {
public:
  scene();
  void render();
  private:
    std::vector<Model> objects;
};



#endif //SCENE_H
