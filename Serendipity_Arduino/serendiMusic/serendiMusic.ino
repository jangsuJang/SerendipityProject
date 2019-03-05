
#include "serendipityMusic.h"

serendipityMusic player;

void setup(){
    Serial.begin(9600);
    player.ready();
    Serial.println("ready function is done");
}

void loop(){
    Serial.println("hello");
    player.start();
    Serial.println("hello");
}