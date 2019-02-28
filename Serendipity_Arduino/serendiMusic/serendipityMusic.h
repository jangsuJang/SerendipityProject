
// For arduino

#include "serendiNeoPixel.h"
#include "Variables.h"

class serendipityMusic {
    public:
    void ready();
    void start();

    private:
    //다이얼이 부착되었을때 동작할 함수
    void dialAttached(int);


};

void serendipityMusic::ready(){

    // setting for RFID 

    // settting for Neopixel
    serendiNeoPixel secondRing = serendiNeoPixel();
    // serendiNeoPixel thirdRing = serendiNeoPixel(THIRD_TOKEN_PIN , NUMBER_OF_PIXEL);

    Serial.println("hello");
    secondRing.isPlaying();
    Serial.println("isPlaying is done");

    // firstRing.isPlaying();

    // this->dialAttached(3);






}

void serendipityMusic::start(){
    Serial.println(serendiNeoPixel::ledSelection);

}

void serendipityMusic::dialAttached(int PIN){
    //다이얼이 부착되면 해당 하는 링을 활성화 


}
