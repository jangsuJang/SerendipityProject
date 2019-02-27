//for thread
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include <Adafruit_NeoPixel.h>
class serendiNeoPixel {

    public:

    serendiNeoPixel(int pin, int numberOfPixel);


    void neoPixel_init();
    void neoPixel_start();
    void isPlaying(); 


    private:
    SemaphoreHandle_t xSerialSemaphore;
    static Adafruit_NeoPixel pixels;

    static int delayVal;
    static int numberOfPixel;
    int currentPoint = 0;
    bool playing = false;

    

    //음악이 재생중이지 않을때
    void pause();
    //토큰이 재생중일때 실행되는 함수
    //회전을 표현하는 함수
    static void ledRotation(void *pvParameters);
    //현재 탐색중인 위치룰 표시하는 함수
    static void highlightPoint(void *pvParameters);

};

serendiNeoPixel::serendiNeoPixel(int pin, int numberOfPixel){
    pixels = Adafruit_NeoPixel(numberOfPixel ,pin, NEO_GRB + NEO_KHZ800);
    this->numberOfPixel = numberOfPixel;
    this->delayVal = 500;
    pixels.begin();
}


void serendiNeoPixel::isPlaying(){
    //음악 재생 요청 

    //led 회전과 탐색 하이라이트를 하는 스레드를 생성
    //세마포어 생성

    xTaskCreate(
      this->ledRotation,
      (const portCHAR *) "LedRotation",
      128,
      this,
      3,
      NULL
      );

    // xTaskCreate(
    //   &serendiNeoPixel::highlightPoint,
    //   (const portCHAR*) "LightHighlight",
    //   128,
    //   NULL,
    //   2,
    //   NULL
    // );

}

// Tasks for rotation feed back (now Playing)
void serendiNeoPixel::ledRotation(void *pvParameters __attribute__((unused)) ){

  for(int i=0;i<numberOfPixel;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayVal); // Delay for a period of time (in milliseconds).

  }


}

void serendiNeoPixel::highlightPoint(void *pvParameters __attribute__((unused)) ){

}

