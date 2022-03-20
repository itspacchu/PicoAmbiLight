// based on https://github.com/adafruit/Adalight/tree/master/Arduino
//
#include<pico/stdio.h>
#include<pico/stdlib.h>
#include "PicoLed.hpp"

#define NUM_LEDS 51
#define LED_DATA_PIN 0

uint8_t prefix[] = {'A','d','a'};
uint8_t hi,lo,chk;
char r,g,b;

void loop(auto ledstrip);

int main(){
    auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_DATA_PIN, NUM_LEDS, PicoLed::FORMAT_GRB);
    stdio_init_all();
    ledStrip.fill(PicoLed::RGB(255, 50, 50));
    ledStrip.show();sleep_ms(1000);
    ledStrip.fill(PicoLed::RGB(50, 255, 50));
    ledStrip.show();sleep_ms(1000);
    ledStrip.fill(PicoLed::RGB(50, 50, 255));
    ledStrip.show();sleep_ms(1000);
    printf("Ada\n");
    for(;;){
        loop(ledStrip);
    }
}

void loop(auto ledStrip){
    //wait for Magic word.
    if(stdio_usb_connected()){
        for(int i=0;i<sizeof(prefix);){
            char buf = getchar();
            if(buf == PICO_ERROR_TIMEOUT){
                loop(ledStrip);
            }
            if(buf == prefix[i]){
                i++;
            }else{
                i=0;
            }
        }
        hi = getchar();
        lo = getchar();
        chk = getchar();

        if(chk != (hi^lo^0x55)){
            loop(ledStrip);
        }

        for(uint8_t i=0;i<NUM_LEDS;i++){
            r = getchar();
            g = getchar();
            b = getchar();

            if(r == ' ' || g == ' ' || b == ' '){
                loop(ledStrip);
            }
            ledStrip.fill(PicoLed::RGB((u_int8_t)r,(u_int8_t)g,(u_int8_t)b),i);
            ledStrip.show();
        } 
    }
}