//
// Created by /<R3/<(RR00T on 06.05.2026.
//

#ifndef SPACELABSTUDIO_VECTORS_H
#define SPACELABSTUDIO_VECTORS_H

#include <iostream>

namespace math {

    template<typename T>
    struct Vector2 {
        T x, y;
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
        os << "{" << v.x << ", " << v.y << "}";
        return os;
    }

    template<typename T>
    struct Vector3 {
        T x, y, z;
    };

    template<typename T>
    struct Vector4 {
        T x, y, z, w;
    };

}

#endif //SPACELABSTUDIO_VECTORS_H
