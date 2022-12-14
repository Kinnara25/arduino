#include <Arduino.h>
#include <SPI.h>
#include <DMD2.h>
#include "font/SystemFont5x7.h"
#include "font/ArialRoundedMTBold16b.h"

const int WIDTH =2; // jumlah panel led matrik yang digunakan
const uint8_t *FONT =ArialRoundedMTBold16b;


const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;


SoftDMD dmd(WIDTH,1); 
DMD_TextBox box(dmd,5,0); //untuk mengatur jumlah panel yang kamu pakai



void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
    dmd.setBrightness(255);
    dmd.selectFont(FONT);
    dmd.begin();
   
}


void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }

        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx =0;
            newData = true;
        }
    }
}
                                       

void sensor1(){ 
     if (newData == true) {
        Serial.print("This just in ... ");  
        Serial.println(receivedChars);
        newData = false;
        box.print(receivedChars);
        
    }
}
        
    
void loop() {

    recvWithEndMarker();
    sensor1();
    //delay(2000);

  
}