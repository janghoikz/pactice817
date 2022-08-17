﻿#include <iostream>

using namespace std;

//타입변환 

// malloc -> void*를 반환하고 이를 우리가 (타입변환)을 통해 사용함
class Knight
{
public:
    int _hp = 10;
};
class Dog
{
    //타입변환생성자
public:
    Dog()
    {

    }
    Dog(const Knight& knight)
    {
        _age = knight._hp;
    }
    //타입변환 연산자
    operator Knight()
    {
        return(Knight)(*this);
    }
public:
    int _age = 1;
    int _cuteness = 2;
};

class BullDog : public Dog
{
public:
    bool _french;
};

int main()
{
    // --------------- 타입변환 유형(비트열 재구성 여부) -------------

    // [1] 값 타입 변환
    // 특징) 의미를 유지하기 위해서, 원본객체와 다른 비트열 재구성
    {
        int a = 123456789;  // 2의 보수
        float b = (float)a; // 부동소수점(지수+유효숫자)
    }
    // [2] 참조 타입 변환
    // 특징) 비트열을 재구성 하지않고, '관점'만 바꾸는것
    //거의 쓸일은 없지만, 포인터 타입변환도 '참조 타입 변환' 동일한 룰을 따름
    {
        int a = 123456789;  // 2의 보수
        float b = (float&)a; // 부동소수점(지수+유효숫자)
    }

    //--------안전도분류-----------
    //[1]안전한 변환
    // 특징) 의미가 항상 100% 완전히 일치 하는경우
    // 같은 타입이면서 크기만 더 큰바구니로 이동
    // 작은 바구니 -> 큰 바구니로 이동 ok(업캐스팅)
    // ex) char -> short, short-> int 
    {
        int a = 123456789;
        _int64 b = a;
        cout << b << endl;
    }
    //[2]불안전한 변환
    // 특징) 의미가 항상 100% 일치한다고 보장하지 못하는 경우
    // 타입이 다르거나
    // 같은 타입이지만 큰 바구니 -> 작은바구니로 이동(다운캐스팅)
    {
        int a = 123456789;
        float b = a;
        short c = a;
        cout << b << endl;
    }
    // ----------프로그래머의 의도에 따라 분류 -----------
    //[1]암시적 변환
    // 특징) 이미 알려진 타입변환 규칙에 따라서 컴파일러'자동'으로 타입변환
    {
        int a = 123456789;
        float b = a; //암시적
    }
    //[2]명시적 변환
    {
        int a = 123456789;
        int* b = (int*)a; //명시적
    }
    // ----------아무런 연관 관계가 없는 클래스 사이의 변환-----------

    //[1]연관 없는 클래스 사이의 '값'타입 변환
    // 특징)일반적으로 안됨()
    //예외 : 타입변환 생성자, 타입변환 연산자를 만들어주면 가능
    {
        Knight knight;
        Dog dog = (Dog)knight;
        Knight knight2 = dog;
    }
    //[2]연관없는 클래스 차이의 참조 타입 변환
    // 특징) 명시적 변환만 가능
    {
        Knight knight;
        // 어셈블리 : 포인터 = 참조

        //[주소] -> [ Dog ]
        Dog& dog = (Dog&)knight;
        dog._cuteness = 12;
    }

    // ----------상속 관계에 있는클래스 사이의 변환-----------
    //[1] 상송 관계 클래스의 값 타입 변환
    //특징) 자식-> 부모로는 가능 //부모-> 자식으로는 불가능
    {
        //이건 안됨
        //Dog dog;
        //BullDog bulldog = dog;

        //반대로는 가능
        BullDog bulldog;
        Dog dog = bulldog;
    }

    //[2] 상속 관계 클래스의 참조타입변환
    {
        Dog dog;
    }
}