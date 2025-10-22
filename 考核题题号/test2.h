#include <iostream>
using namespace std;
class Rectangle {
private:
    double length;
    double width;

public:
    // ���캯��
    Rectangle(double l = 0, double w = 0) : length(l), width(w) {}

    // �������
    double area() const {
        return length * width;
    }

    // ��ʾ������Ϣ
    void display() const {
        cout << "��: " << length << ", ��: " << width << ", ���: " << area();
    }

    // ���� > ��������Ƚ����
    bool operator>(const Rectangle& other) const {
        return this->area() > other.area();
    }

    // ��ȡ���Ϳ����������
    double getLength() const { return length; }
    double getWidth() const { return width; }
};
