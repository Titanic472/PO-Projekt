

struct Vector2{
	int x;
	int y;


    Vector2(int x, int y);


    Vector2 operator+=(const Vector2& other);


    Vector2 operator+(const Vector2& other);


    Vector2 operator*(const int scale);


    Vector2 operator*=(const int scale);
};