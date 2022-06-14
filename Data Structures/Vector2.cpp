//vector2.cpp

#include "Vector2.hpp"

Vector2::Vector2() = default;
Vector2::Vector2(int x, int y) : x_(x), y_(y) {}
Vector2::Vector2(const Vector2& otherVec) : x_(otherVec.x_), y_(otherVec.y_) {}

Vector2::~Vector2() = default;

//Vector addition
Vector2 Vector2::operator+(const Vector2& otherVec) {
    Vector2 temp;
    temp.x_ = x_ + otherVec.x_;
    temp.y_ = y_ + otherVec.y_;
    return temp;
}

Vector2& Vector2::operator+=(const Vector2& otherVec) {
    x_ += otherVec.x_;
    y_ += otherVec.y_;
    return *this;
}

Vector2 Vector2::operator+(int s) {
    Vector2 temp;
    temp.x_ = x_ + s;
    temp.y_ = y_ + s;
    return temp;
}

Vector2& Vector2::operator+=(int s) {
    x_ += s;
    y_ += s;
    return *this;
}


//Vector subtraction
Vector2 Vector2::operator-(const Vector2& otherVec) {
    Vector2 temp;
    temp.x_ = x_ - otherVec.x_;
    temp.y_ = y_ - otherVec.y_;
    return temp;
}

Vector2& Vector2::operator-=(const Vector2& otherVec) {
    x_ -= otherVec.x_;
    y_ -= otherVec.y_;
    return *this;
}

Vector2 Vector2::operator-(int s) {
    Vector2 temp;
    temp.x_ = x_ - s;
    temp.y_ = y_ - s;
    return temp;
}

Vector2& Vector2::operator-=(int s) {
    x_ -= s;
    y_ -= s;
    return *this;
}


//Vector multiplication
Vector2 Vector2::operator*(int s) {
    Vector2 temp;
    temp.x_ = x_*s;
    temp.y_ = y_*s;
    return temp;
}

Vector2& Vector2::operator*=(int s) {
    x_ *= s;
    y_ *= s;
    return *this;
}


//Vector division
Vector2 Vector2::operator/(int s) {
    Vector2 temp;
    temp.x_ = x_/s;
    temp.y_ = y_/s;
    return temp;
}

Vector2& Vector2::operator/=(int s) {
    x_ /= s;
    y_ /= s;
    return *this;
}

//Useful Vector Operations
int Vector2::Length() const {
    return std::sqrt(x_*x_ + y_*y_);
}

Vector2& Vector2::Normalize() {
    int magnitude = Length();
    if (magnitude == 0) return *this;
    return (*this)/=magnitude;
}

int Vector2::Distance(Vector2 otherVec) const {
    Vector2 d(otherVec.x_-x_, otherVec.y_-y_);
    return d.Length();
}

int Vector2::Dot(Vector2 v1, Vector2 v2) {
    return (v1.x_ * v2.x_ )+ (v1.y_ * v2.y_);
}

int Vector2::Cross(Vector2 v1, Vector2 v2) {
    return (v1.x_ * v2.y_) - (v1.y_ * v2.x_);
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t){
    return (a*(1-t) + b*t);

}

Vector2 Vector2::Zero(){
    return Vector2(0,0);
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    return os << "(" << v.x_ << ", " << v.y_ << ")";
}

bool operator<(const Vector2& lhs, const Vector2& rhs) {
    return ((lhs.x_ < rhs.x_) || (lhs.x_ == rhs.x_ && lhs.y_ < rhs.y_));
}

bool operator>(const Vector2& lhs, const Vector2& rhs) {
    return operator<(rhs, lhs);
}

bool operator==(const Vector2& lhs, const Vector2& rhs) {
    return (lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_);
}

bool operator!=(const Vector2& lhs, const Vector2& rhs) {
    return !operator==(lhs,rhs);
}

bool operator<=(const Vector2& lhs, const Vector2& rhs) {
    return !operator>(lhs, rhs);
}

bool operator>=(const Vector2& lhs, const Vector2& rhs) {
    return !operator<(lhs,rhs);
}
