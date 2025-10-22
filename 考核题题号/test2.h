#include <iostream>
using namespace std;
class Rectangle {
private:
    double length;
    double width;

public:
    // 构造函数
    Rectangle(double l = 0, double w = 0) : length(l), width(w) {}

    // 计算面积
    double area() const {
        return length * width;
    }

    // 显示矩形信息
    void display() const {
        cout << "长: " << length << ", 宽: " << width << ", 面积: " << area();
    }

    // 重载 > 运算符，比较面积
    bool operator>(const Rectangle& other) const {
        return this->area() > other.area();
    }

    // 获取长和宽（用于输出）
    double getLength() const { return length; }
    double getWidth() const { return width; }
};
