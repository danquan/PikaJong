#include <utils/utils.h>
#include <graphic/screen.h>

bool ObjectDetector::isScreen(Graphic* graphicObject) {
    Screen *res = dynamic_cast<Screen*>(graphicObject);
    if (res == NULL) {
        return false;
    }
    return res->isRoot();
}