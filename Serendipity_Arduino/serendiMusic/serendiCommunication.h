#include "Variables.h"
//라즈베리파이에게 요청할 mp3파일명을 생성하여 시리얼통신으로 요청
class serendiCommunication{
    public:
    serendiCommunication();

    //라즈베리파이에레 음악 재생 요청을함
    void makePlayQuery();


    private:
    //가변저항 값을 받아 재생을 요청을 음악 파일명을 생성하는 함수
    String musicNameByValue();

}

serendiCommunication::serendiCommunication(){
    Serial.begin(BAUD_RATE);


}