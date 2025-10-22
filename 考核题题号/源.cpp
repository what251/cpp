#include <iostream>
#include"test1.h"
#include"test2.h"
#include"test3.h"
using namespace std;
//题一
int main() {
    string sentence;
    cout << "请输入英文句子（以句号结束）: ";
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
        // 移除单词末尾可能存在的标点符号（除了句号）
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

    cout << "\n统计结果：" << endl;
    cout << "单词总数: " << totalWords << endl;
    cout << "最长单词: " << longestWord << "，长度: " << maxLength << endl;

    sort(words.begin(), words.end(), compareByLength);

    cout << "按长度排序的单词:" << endl;
    for (const auto& info : words) {
        cout << info.word << " (长度: " << info.length << ")" << endl;
    }

    //题二
    double l1, w1, l2, w2;

    cout << "请输入第一个矩形的长和宽: ";
    cin >> l1 >> w1;

    cout << "请输入第二个矩形的长和宽: ";
    cin >> l2 >> w2;

    Rectangle rect1(l1, w1);
    Rectangle rect2(l2, w2);

    cout << "\n矩形1: ";
    rect1.display();
    cout << endl;

    cout << "矩形2: ";
    rect2.display();
    cout << endl;

    cout << "\n面积较大的矩形: ";
    if (rect1 > rect2) {
        cout << "长: " << rect1.getLength() << ", 宽: " << rect1.getWidth();
        cout << " (面积: " << rect1.area() << ")";
    }
    else if (rect2 > rect1) {
        cout << "长: " << rect2.getLength() << ", 宽: " << rect2.getWidth();
        cout << " (面积: " << rect2.area() << ")";
    }
    else {
        cout << "两个矩形面积相等";
        cout << "长: " << rect1.getLength() << ", 宽: " << rect1.getWidth();
    }
    cout << endl;
    //题三
    SpaceshipFleet fleet;
    fleet.run();
    return 0;
};