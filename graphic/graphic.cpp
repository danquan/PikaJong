#include <graphic.h>
#include <main/controller.h>

Graphic::Graphic(std::string name, SDL_Rect position) {
    this->name = name;
    this->graphicActive = false;
    this->position = position;
    this->scaleRate = {1, 1};
    this->velocity = {0, 0};
    Controller::getInstance().addGraphic(this);
}

int Graphic::process() {
    if (!isActive()) {
        return 0;
    }

    // Render this object
    if (!render()) {
        return 1;
    }

    // Process all childs
    for (Graphic *g : childs) {
        if (!(g->process())) {
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

