#include "Arduino.h"
#include "VectorUtils.h"

// operator for comparing two Vector structs
bool operator ==(const Vector& v1, const Vector& v2){
    return v1.x == v2.x && v1.y == v2.y;
}
// operator for comparing two Vector structs
bool operator !=(const Vector& v1, const Vector& v2){
    return v1.x != v2.x || v1.y != v2.y;
}
