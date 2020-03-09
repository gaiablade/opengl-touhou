#include "Rect.h"

namespace ga {
    Rect::Rect()
        : size({1, 1}), vb(nullptr), va(nullptr), bld(nullptr), ib(nullptr)
    {
    }

    Rect::~Rect() {
        delete this->vb;
        delete this->ib;
        delete this->bld;
        delete this->va;
    }
};
