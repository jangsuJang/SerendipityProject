
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
    // serendiNeoPixel secondRing = serendiNeoPixel(SECOND_TOKEN_PIN , NUMBER_OF_PIXEL);
    // serendiNeoPixel thirdRing = serendiNeoPixel(THIRD_TOKEN_PIN , NUMBER_OF_PIXEL);

    // firstRing.isPlaying();






}

void serendipityMusic::start(){

}

void serendipityMusic::dialAttached(int PIN){
    //다이얼이 부착되면 해당 하는 링을 활성화 
    serendiNeoPixel activatedRing= serendiNeoPixel(PIN, NUMBER_OF_PIXEL);



}
