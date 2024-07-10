#include <graphic.h>
#include <controller.h>

Graphic::Graphic(std::string name, SDL_Rect position) {
    this->name = name;
    this->graphicActive = false;
    this->position = position;
    Controller::getInstance().addGraphic(this);
}

int Graphic::render() {
    for (Graphic *g : childs) {
        if (!(g->render())) {
            return 1;
        }
    }
    
    return 0;
}

void Graphic::active() {
    graphicActive = true;
    
    for (Graphic *g : childs) {
        g->active();
    }
}

void Graphic::deactive() {
    graphicActive = false;
    
    for (Graphic *g : childs) {
        g->deactive();
    }
}

int Graphic::addChild(Graphic* child) {
    childs.push_back(child);
    return 0;
}

int Graphic::removeChild(Graphic* child) {
    for (int i = 0; i < childs.size(); i++) {
        if (childs[i] == child) {
            childs[i] = childs.back();
            childs.pop_back();

            return 0;
        }
    }

    return 1;
}

