#include <iostream>
#include"test1.h"
#include"test2.h"
#include"test3.h"
using namespace std;
//��һ
int main() {
    string sentence;
    cout << "������Ӣ�ľ��ӣ��Ծ�Ž�����: ";
    getline(cin, sentence);


    if (!sentence.empty() && sentence.back() == '.') {
        sentence.pop_back();
    }

    stringstream ss(sentence);
    string word;
    vector<WordInfo> words;

    int totalWords = 0;
    string longestWord;
    int maxLength = 0;

    while (ss >> word) {
        // �Ƴ�����ĩβ���ܴ��ڵı����ţ����˾�ţ�
        if (!word.empty() && ispunct(word.back())) {
            word.pop_back();
        }

        if (!word.empty()) {
            WordInfo info;
            info.word = word;
            info.length = word.length();
            words.push_back(info);

            totalWords++;

            if (word.length() > maxLength) {
                maxLength = word.length();
                longestWord = word;
            }
        }
    }

    cout << "\nͳ�ƽ����" << endl;
    cout << "��������: " << totalWords << endl;
    cout << "�����: " << longestWord << "������: " << maxLength << endl;

    sort(words.begin(), words.end(), compareByLength);

    cout << "����������ĵ���:" << endl;
    for (const auto& info : words) {
        cout << info.word << " (����: " << info.length << ")" << endl;
    }

    //���
    double l1, w1, l2, w2;

    cout << "�������һ�����εĳ��Ϳ�: ";
    cin >> l1 >> w1;

    cout << "������ڶ������εĳ��Ϳ�: ";
    cin >> l2 >> w2;

    Rectangle rect1(l1, w1);
    Rectangle rect2(l2, w2);

    cout << "\n����1: ";
    rect1.display();
    cout << endl;

    cout << "����2: ";
    rect2.display();
    cout << endl;

    cout << "\n����ϴ�ľ���: ";
    if (rect1 > rect2) {
        cout << "��: " << rect1.getLength() << ", ��: " << rect1.getWidth();
        cout << " (���: " << rect1.area() << ")";
    }
    else if (rect2 > rect1) {
        cout << "��: " << rect2.getLength() << ", ��: " << rect2.getWidth();
        cout << " (���: " << rect2.area() << ")";
    }
    else {
        cout << "��������������";
        cout << "��: " << rect1.getLength() << ", ��: " << rect1.getWidth();
    }
    cout << endl;
    //����
    SpaceshipFleet fleet;
    fleet.run();
    return 0;
};