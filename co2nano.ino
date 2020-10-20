#include <Arduino.h>
#include <MHZ19.h>                                         // MH-Z19 CO2 sensor library                                        
#include <SoftwareSerial.h>                                // SoftwareSerial support to use hardware serial port for programming and debugging
#include <Adafruit_SSD1306.h>                              // SSD 1306 i2C OLED display support

#define RX_PIN 2                                           // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN 3                                           // Tx pin which the MHZ19 Rx pin is attached to
#define BAUDRATE 9600                                      // Device to MH-Z19 Serial baudrate (should not be changed)

MHZ19 myMHZ19;                                             // Constructor for library

SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // create serial device to MH-Z19 serial
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire); // constructor for OLED display

unsigned long getDataTimer = 0;                             // timestamp for polling interval

void setup()
{
    Serial.begin(9600);                                     // Device to serial monitor feedback

    mySerial.begin(BAUDRATE);                               // device to MH-Z19 serial start      
    myMHZ19.begin(mySerial);                                // *Serial(Stream) refence must be passed to library begin(). 

    myMHZ19.autoCalibration();                              // Turn auto calibration ON (OFF autoCalibration(false))

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);              // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
                                                            // Address 0x3C for 128x32  
    display.display();                                      // Show image buffer on the display hardware.
                                                            // Since the buffer is intialized with an Adafruit splashscreen
                                                            // internally, this will display the splashscreen.
}

void loop()
{
    if (millis() - getDataTimer >= 2000)
    {
        int CO2; 

        /* note: getCO2() default is command "CO2 Unlimited". This returns the correct CO2 reading even 
        if below background CO2 levels or above range (useful to validate sensor). You can use the 
        usual documented command with getCO2(false) */

        CO2 = myMHZ19.getCO2();                             // Request CO2 (as ppm)
        
        Serial.print("CO2 (ppm): ");                      
        Serial.println(CO2);                                

        int8_t Temp;
        char buf[40];
        Temp = myMHZ19.getTemperature();                     // Request Temperature (as Celsius)
        Serial.print("Temperature (C): ");                  
        Serial.println(Temp);                               
        
        display.clearDisplay();                              // Clear the buffer.

        // text display tests
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(20,3);
        display.setTextSize(4.7);
        /*
        show temperature and CO2 
        display.setTextSize(2);
        sprintf(buf, "CO2: %d\n  T: %d\11C", CO2, Temp);
        */
        sprintf(buf, "%d", CO2);
        display.print(buf);
        display.display();                                   // actually display all of the above
        
        getDataTimer = millis();
    }
}
