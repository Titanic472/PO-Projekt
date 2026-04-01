#include "vector2.hpp"


const Vector2 Vector2::ZERO(0, 0);


Vector2::Vector2(int x, int y){
    this->x = x;
    this->y = y;
}


bool Vector2::operator!=(const Vector2& other){
    return (this->x != other.x || this->y != other.y);
}


Vector2& Vector2::operator+=(const Vector2& other){
    x += other.x;
    y += other.y;
    return *this;
}


Vector2 Vector2::operator+(const Vector2& other){
    return Vector2(this->x + other.x, this->y + other.y);
}


Vector2 Vector2::operator*(const float scale){
    return Vector2(this->x * scale, this->y * scale);
}


Vector2& Vector2::operator*=(const int scale){
    x *= scale;
    y *= scale;
    return *this;
}