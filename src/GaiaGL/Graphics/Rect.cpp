#include "Rect.h"

namespace ga {
    Rect::Rect()
        : size({1, 1})
    {
    }

    Rect::~Rect() {
        delete this->vb;
        delete this->ib;
        delete this->bld;
        delete this->va;
    }
};
