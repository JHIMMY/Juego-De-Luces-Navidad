 /******************************************************************************************************************************
 * DESCRIPCION: Este es una demostración de algunos juegos de luces que se pueden usar en la epoca navideña
 * para tiras led direccionables y compatibles con neopixel o fastled.
 * CANAL YOUTUBE: https://www.youtube.com/c/jadsatv
 * © 2021
 *******************************************************************************************************************************/

#include <FastLED.h>

const byte dataPin = 7;
const byte numLeds = 100;
const unsigned int timePause = 1000;
CRGB leds[numLeds];


void setup()
{
  Serial.begin(115200);

  FastLED.addLeds<WS2812B, dataPin, GRB>(leds, numLeds).setCorrection( TypicalLEDStrip );
  //FastLED.setBrightness(xxx);  
  
} // EOF setup


void loop()
{    

  Serial.println("Color Mixture");  
  ColorMixture(4);
  
  pause();

  Serial.println("Running Lights");
  // Running Lights - Color (red, green, blue), wave dealy
  RunningLights(0xff, 0x00, 0x00, 50); // red
  RunningLights(0xff, 0xff, 0xff, 50); // white
  RunningLights(0x00, 0xff, 0x00, 50); // green
  
  pause();

  Serial.println("Twinkle");
  // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
  Twinkle(0xff, 0x00, 0x00, 70, 50, false);
  Twinkle(0xff, 0xff, 0xff, 70, 50, false);
  Twinkle(0x00, 0xff, 0x00, 70, 50, false);

  pause();

  Serial.println("Meteor Rain");
  // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
  meteorRain(0xff, 0xff, 0xff, 12, 64, true, 60);

  pause();

  Serial.println("Rainbow Cycle");
  // rainbowCycle - speed delay
  rainbowCycle(15);

  Serial.println("Sparkle");
  setAll(0, 0, 0);
  showStrip();
  // Sparkle - Color (red, green, blue), speed delay
  Sparkle(0xff, 0xff, 0xff, 200, 30); // jad changes dealy from 0 to 70

  pause();

  pause();

  Serial.println("Fade In Out");
  FadeInOut(0xff, 0x00, 0x00); // red
  FadeInOut(0x00, 0xff, 0x00); // green
  FadeInOut(0xff, 0xff, 0xff); // white

  pause();

  Serial.println("Twinkle Random");
  // TwinkleRandom - twinkle count, speed delay, only one (true/false)
  TwinkleRandom(200, 60, false);

  pause();

  Serial.println("Color Wipe");
  // colorWipe - Color (red, green, blue), speed delay
  setAll(0, 0, 0);
  showStrip();
  colorWipe(0x00, 0xff, 0x00, 30);
  colorWipe(0x00, 0x00, 0x00, 30);
  colorWipe(0xff, 0x00, 0x00, 30);
  colorWipe(0x00, 0x00, 0x00, 30);

  pause();

  Serial.println("Snow Sparkle");
  // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
  SnowSparkle(0x10, 0x10, 0x10, 50, 30, random(50, 500)); // delay to 30 from 20

  pause();

  Serial.println("RGB Loop");
  // RGBLoop - no parameters
  RGBLoop();

  pause();
} // eof loop




// *************************
// ** LEDEffect Functions **
// *************************

void pause(){
  delay(timePause);
}

void ColorMixture(int count)
{
  // assign colors
  for (int i = 0; i < numLeds; i++)
  {
    int result = i % 4; // 4 colors
    if (result == 0)
      setPixel(i, 0xff, 0x00, 0x00); // rojo
    else if (result == 1)
      setPixel(i, 0xff, 0xff, 0xff); //blanco
    else if (result == 2)
      setPixel(i, 0x00, 0xff, 0x00); // verde
    else if (result == 3)
      setPixel(i, 0x00, 0x00, 0xff); // azul
  }

  // fade in
  for (int n = 0; n < count; n++)
  {
    for (int i = 0; i < 256; i++)
    {
      FastLED.setBrightness(i);
      showStrip();
      delay(15);
    }

    // fade out
    for (int i = 255; i >= 0; i -= 2)
    {
      FastLED.setBrightness(i);
      showStrip();
      delay(15);
    }
  }
  FastLED.setBrightness(150);
}


void RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    // Fade IN
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

void FadeInOut(byte red, byte green, byte blue){
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
}

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(numLeds),red,green,blue);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(numLeds),random(0,255),random(0,255),random(0,255));
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void Sparkle(byte red, byte green, byte blue, int count, int SpeedDelay) {
  for (int i = 0; i < count; i++)
  {
    int Pixel = random(numLeds);
    setPixel(Pixel,red,green,blue);
    showStrip();
    delay(SpeedDelay);
    setPixel(Pixel,0,0,0);
  }
}

void SnowSparkle(byte red, byte green, byte blue, int count, int SparkleDelay, int SpeedDelay)
{
  for (int i = 0; i < count; i++)
  {
    setAll(red, green, blue);

    int Pixel = random(numLeds);
    setPixel(Pixel, 0xff, 0xff, 0xff);
    showStrip();
    delay(SparkleDelay);
    setPixel(Pixel, red, green, blue);
    showStrip();
    delay(SpeedDelay);
  }
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<numLeds; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<numLeds; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
  }
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<numLeds; i++) {
      setPixel(i, red, green, blue);
      showStrip();
      delay(SpeedDelay);
  }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*3; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< numLeds; i++) {
      c=Wheel(((i * 256 / numLeds) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

// used by rainbowCycle and theaterChaseRainbow
byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}


void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
  
  for(int i = 0; i < numLeds+numLeds; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<numLeds; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <numLeds) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}

// used by meteorrain
void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

// *** REPLACE TO HERE ***



// ***************************************
// ** FastLed/NeoPixel Common Functions **
// ***************************************

// Apply LED color changes
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

// Set a LED color (not yet visible)
void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

// Set all LEDs to a given color and apply it (visible)
void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < numLeds; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
