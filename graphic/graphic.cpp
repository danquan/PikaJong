#include <graphic/graphic.h>
#include <main/controller.h>

Graphic::Graphic(std::string name, 
                 SDL_Rect position, 
                 SDL_Vector scaleRate, 
                 SDL_Vector velocity ) {
    this->name = name;
    this->graphicActive = false;
    this->position = position;
    this->scaleRate = scaleRate;
    this->velocity = velocity;
    Controller::getInstance().addGraphic(this);
}

int Graphic::process() {
    if (!isActive()) {
        return 0;
    }

    // Process all childs
    for (Graphic *g : childs) {
        if (!(g->process())) {
            return 1;
        }
    }

    return 0;
}

int Graphic::render() {
    if (!isActive()) {
        return 0;
    }

    // Render all childs
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

int Graphic::setParent(Graphic* parent) {
    parents.push_back(parent);
    return 0;
}

