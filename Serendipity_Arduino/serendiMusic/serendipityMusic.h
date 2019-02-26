
// For arduino
#include "serendiNeoPixel.h"
#include "Variables.h"

class serendipityMusic {
    public:
    void ready();
    void start();

    private:


};

void serendipityMusic::ready(){
    // setting for RFID

    // settting for Neopixel
    serendiNeoPixel firstRing = serendiNeoPixel(FIRST_TOKEN_PIN , NUMBER_OF_PIXEL);
    serendiNeoPixel secondRing = serendiNeoPixel(SECOND_TOKEN_PIN , NUMBER_OF_PIXEL);
    serendiNeoPixel thirdRing = serendiNeoPixel(THIRD_TOKEN_PIN , NUMBER_OF_PIXEL);


}

void serendipityMusic::start(){

}
