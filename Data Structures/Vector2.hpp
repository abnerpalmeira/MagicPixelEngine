//vector2.h
#ifndef _VECTOR_2
#define _VECTOR_2

#include <iostream>
#include <cmath>
#include <algorithm>

class Vector2 {
public:
    int x_;
    int y_;
    
    Vector2();
    Vector2(int x, int y);
    Vector2(const Vector2& otherVec);

    ~Vector2();

    //Vector addition
    Vector2 operator+(const Vector2& otherVec);

    Vector2& operator+=(const Vector2& otherVec);

    Vector2 operator+(int s);

    Vector2& operator+=(int s);


    //Vector subtraction
    Vector2 operator-(const Vector2& otherVec);

    Vector2& operator-=(const Vector2& otherVec);

    Vector2 operator-(int s);

    Vector2& operator-=(int s);


    //Vector multiplication
    Vector2 operator*(int s);

    Vector2& operator*=(int s);


    //Vector division
    Vector2 operator/(int s);

    Vector2& operator/=(int s);

    //Useful Vector Operations
    int Length() const;

    Vector2& Normalize();

    int Distance(Vector2 otherVec) const;

    static int Dot(Vector2 v1, Vector2 v2);

    static int Cross(Vector2 v1, Vector2 v2);
    
    static Vector2 Lerp(Vector2 a, Vector2 b, float t);
    
    static Vector2 Zero();
  

private:
    
    friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
};

std::ostream& operator<<(std::ostream& os, const Vector2& v);

//Vector comperison operators
bool operator<(const Vector2& lhs, const Vector2& rhs);

bool operator==(const Vector2& lhs, const Vector2& rhs);

bool operator!=(const Vector2& lhs, const Vector2& rhs);

bool operator<=(const Vector2& lhs, const Vector2& rhs);

bool operator>(const Vector2& lhs, const Vector2& rhs);

bool operator>=(const Vector2& lhs, const Vector2& rhs);



#endif
