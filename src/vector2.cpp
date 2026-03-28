#include "vector2.hpp"


Vector2::Vector2(int x, int y){
    this->x = x;
    this->y = y;
}


Vector2 Vector2::operator+=(const Vector2& other){
    return Vector2(this->x + other.x, this->y + other.x);
}


Vector2 Vector2::operator+(const Vector2& other){
    return Vector2(this->x + other.x, this->y + other.x);
}


Vector2 Vector2::operator*(const int scale){
    return Vector2(this->x * scale, this->y * scale);
}


Vector2 Vector2::operator*=(const int scale){
    return Vector2(this->x * scale, this->y * scale);
}