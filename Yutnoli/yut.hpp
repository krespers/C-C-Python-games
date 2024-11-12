#include <cstdlib>
#include <string>
#include <vector>

#include <algorithm> // 추가된 헤더 파일

#ifndef __YUT_H_INCLUDED__
#define __YUT_H_INCLUDED__
using namespace std;

class YutName {
  public:
    YutName(const std::string& yuts) : name(yuts) {} // 생성자 새로 설정. yuts를 받아서 name에 저장

    string name;
    bool operator<(const YutName &other) const {
        //////////////////IMPLEMENT HERE//////////////////////////////////////
        vector<string> yut_order = {"back-do", "do", "gae", "geol", "yut", "mo"};
        return find(yut_order.begin(), yut_order.end(), name) < find(yut_order.begin(), yut_order.end(), other.name);
        //////////////////////////////////////////////////////////////////////
    }
    string getName() const { return name; };
    
};

class Yut {
    /////////Feel free to add or subtract functions or variables. //////////
  public:
    Yut(float prob) : prob(prob) {}
    friend class Player;
    friend class AnimalPlayer;

  private:
    float prob;
    int throwOneYut();
    string throwFourYuts();
};

#endif
