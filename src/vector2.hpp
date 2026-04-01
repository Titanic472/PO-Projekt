#pragma once

struct Vector2{
	int x;
	int y;

    static const Vector2 ZERO;

    Vector2(int x, int y);


    Vector2(){}


    bool operator!=(const Vector2& other);


    Vector2 operator+(const Vector2& other);


    Vector2& operator+=(const Vector2& other);


    Vector2 operator*(const float scale);


    Vector2& operator*=(const int scale);
};
