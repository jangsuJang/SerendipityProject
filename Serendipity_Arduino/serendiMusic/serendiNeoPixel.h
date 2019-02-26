#include <Adafruit_NeoPixel.h>

class serendiNeoPixel {

    public:
    void neoPixel_init();
    void neoPixel_start();
    serendiNeoPixel(int pin, int numberOfPixel);


    private:
    //음악이 재생중이지 않을때
    void pause();
    //토큰이 재생중일때 실행되는 함수
    void isPlaying(); 
    //회전을 표현하는 함수
    void ledRotation();
    //현재 탐색중인 위치룰 표시하는 함수
    void highlightPoint();




};

serendiNeoPixel::serendiNeoPixel(int pin, NUMBER_OF_PIXEL){
    return
}