//for thread
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Adafruit_NeoPixel.h>
#include "serendiTimer.h"
#include <Bounce2.h>


class serendiNeoPixel {

    public:



    void neoPixel_init();
    void neoPixel_start();
    void isPlaying(); 
    void setHighlightPoint(int);

    static int ledSelection;


    private:
    SemaphoreHandle_t xSerialSemaphore;
    static Adafruit_NeoPixel firstPixels;
    static Adafruit_NeoPixel secondPixels;
    static Adafruit_NeoPixel thirdPixels;
    static Adafruit_NeoPixel* pixels;

    static TaskHandle_t xRotationHandle;

    static int delayVal;
    static int numberOfPixel;
    static int highlightPoint;
    int currentPoint = 0;
    bool playing = false;

    

    //음악이 재생중이지 않을때
    void pause();
    //토큰이 재생중일때 실행되는 함수
    //회전을 표현하는 함수
    static void firstLedRotation(void *pvParameters);
    static void TaskDigitalRead(void *pvParameters);
    static void AnalogListener(void *pvParameters);

};

int serendiNeoPixel::delayVal = 15;
int serendiNeoPixel::numberOfPixel=24;
static TaskHandle_t serendiNeoPixel::xRotationHandle;


Adafruit_NeoPixel* serendiNeoPixel::pixels;
Adafruit_NeoPixel serendiNeoPixel::firstPixels = Adafruit_NeoPixel(numberOfPixel ,3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel serendiNeoPixel::secondPixels = Adafruit_NeoPixel(numberOfPixel ,4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel serendiNeoPixel::thirdPixels = Adafruit_NeoPixel(numberOfPixel ,5, NEO_GRB + NEO_KHZ800);

void serendiNeoPixel::isPlaying(){
    //음악 재생 요청 

    //led 회전과 탐색 하이라이트를 하는 스레드를 생성
    //세마포어 생성

    // LED 링을 계속 회전하게 만들어 주는 스레드
    xTaskCreate(
      this->firstLedRotation,
      (const portCHAR *) "LedRotation",
      128,
      this,
      4,
      &xRotationHandle
    );
    Serial.println("all task created");

    //인풋이 생기면 ledSelection을 조절하여 기존의 스레드를 종료하고 새로운 스레드를 생성
    xTaskCreate(
      this->TaskDigitalRead,
      (const portCHAR *) "Button Test",
      128,
      this,
      4,
      NULL
    );
    Serial.println("all task created");

    xTaskCreate(
      this->AnalogListener,
      (const portCHAR *) "Detect rotation",
      128,
      this,
      4,
      NULL
    );
    Serial.println("all task created");

    // vTaskStartScheduler();
    Serial.println("all task created");

    //이벤트 리스터 생성

}
void serendiNeoPixel::TaskDigitalRead(void *pvParameters __attribute__((unused))){
  Serial.println("Digital Listener was created");

  int pushButton = 13;
  pinMode(pushButton,INPUT);

  Bounce debouncer = Bounce(); //Instantiate a Bounce object
  debouncer.attach(pushButton,INPUT_PULLUP);
  debouncer.interval(25);


    for(;;){
      debouncer.update();
      if(debouncer.fell()){

        serendiNeoPixel::ledSelection+= 1;
        Serial.println(ledSelection);
        
        if(serendiNeoPixel::ledSelection> 4){
          serendiNeoPixel::highlightPoint = 3;

          vTaskDelay(3);
          xTaskCreate(
            firstLedRotation,
            (const portCHAR *) "LedRotation",
            128,
            NULL,
            3,
            &xRotationHandle
          );
          Serial.println("created");

          //기존 테스크가 죽을떄 동안 무한 루프
        }
      }



    }

}



// Tasks for rotation feed back (now Playing)
void serendiNeoPixel::firstLedRotation(void *pvParameters __attribute__((unused))){
  //처음에 점점빨라지는 형식으로 구현하기 
  (void) pvParameters;
  Serial.println("Rotation is created");

  // pixels = Adafruit_NeoPixel(numberOfPixel ,3, NEO_GRB + NEO_KHZ800);

  if(ledSelection==3){

    firstPixels.begin();
    const TickType_t xFrequency = 1;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    // serendiTimer a = serendiTimer();


    //A task shall never return or exit.
    int i = 0;
    for(;;){

      if(ledSelection!=3){
        //turn off all light
        firstPixels.clear();
        firstPixels.show();
        Serial.println("deleting");
        vTaskDelete(xRotationHandle);
        Serial.println("deleted");

      }

        i = (i > numberOfPixel) ? 0 : i;

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        firstPixels.clear();
        firstPixels.setPixelColor(i, firstPixels.Color(0,150,0)); // Moderately bright green color.
        firstPixels.setPixelColor(highlightPoint, firstPixels.Color(150,0,0));
        // Serial.println(highlightPoint);
        firstPixels.show(); // This sends the updated pixel color to the hardware.

        vTaskDelayUntil(&xLastWakeTime,xFrequency);
        i++;
    }
  }
  else if(ledSelection==4){

    secondPixels.begin();
    const TickType_t xFrequency = 1;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    // serendiTimer a = serendiTimer();


    //A task shall never return or exit.
    int i = 0;
    for(;;){

        i = (i > numberOfPixel) ? 0 : i;

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        secondPixels.clear();
        secondPixels.setPixelColor(i, secondPixels.Color(0,150,0)); // Moderately bright green color.
        secondPixels.setPixelColor(highlightPoint, secondPixels.Color(150,0,0));
        // Serial.println(highlightPoint);
        secondPixels.show(); // This sends the updated pixel color to the hardware.

        vTaskDelayUntil(&xLastWakeTime,xFrequency);


        i++;
    }
  }

}

void serendiNeoPixel::AnalogListener(void *pvParameters){
  Serial.println("AnalogListener is created");
  int rotaryEncoder = A0;
  int prevVal = -1;
  int tempVal;
  for(;;){
    tempVal = analogRead(rotaryEncoder);
    serendiNeoPixel::highlightPoint = map(tempVal,
                                          0, 1024,
                                          1, numberOfPixel);
    tempVal = serendiNeoPixel::highlightPoint;
    if(prevVal != tempVal){
      prevVal = tempVal;
      Serial.println(prevVal);
      prevVal = serendiNeoPixel::highlightPoint;
    }
  }






}

int serendiNeoPixel::highlightPoint=0;

int serendiNeoPixel::ledSelection=3;


 void serendiNeoPixel::setHighlightPoint(int hp){
   highlightPoint = hp;

 }

