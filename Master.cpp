/* Wire Master Reader
 Demonstrates use of the Wire library
 Reads data from an I2C/TWI slave device
Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include "rgb_lcd.h"

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 107, 100, 250 );

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):

EthernetServer server(80);

rgb_lcd lcd;

const int colorR = 255;    //for color
const int colorG = 0;      //for color
const int colorB = 0;      //for color

void setup() {
  lcd.begin(16, 2);      //Start grove-LCD to diplay
  Wire.begin();          //join i2c bus (address optional for master)
  Serial.begin(9600);    // start serial for output
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection and the server:
 Ethernet.begin(mac, ip);
  server.begin(); 
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  lcd.setRGB(colorR, colorG, colorB); //set the bg_color for LCD

}

void loop()
{
  String A;
  String B;
  
         
          Wire.requestFrom(8,1);       // request 1 bytes from slave device #8
          lcd.setCursor(0, 0);         //set cursor for grove-LCD
          while (Wire.available())     //if slave connected or available
   {
   
      int val=Wire.read();       //read from slave device #8
      if (val == 0 || val == 1) 
    {
     String x="Street1 is Full!";
      //lcd.write(x);      //write on display
      
      A=x;
   
   }
   
      else
    {  
   String x1="Street1 is Empty";
    
      
      A=x1;
   
   }  
   char a[20];
   A.toCharArray(a,20);
   lcd.write(a);  
   }
  Wire.requestFrom(9,1);        // request 1 bytes from slave device #9
  lcd.setCursor(0,1);           //set cursor for grove-LCD
  
  while (Wire.available())      //if slave connected or available
  {  
    
    int val=Wire.read();
      if (val == 0 || val == 1)
   {   
      String y ="Street2 is Full!";
     B=y;
     
  } 
      else
      {
         String y1="Street2 is Empty";
     
         B=y1;
      }
      char b[20];
      B.toCharArray(b,20);
      lcd.write(b);
      }
       EthernetClient client = server.available();
  
if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
  while(client.connected()){
      if (client.available()) {
       
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
         // client.println("HTTP/1.1 200 OK");
         // client.println("Content-Type: text/html");
          //client.println("Connection: close");  // the connection will be closed after completion of the response
          //client.println("Refresh: 1");  // refresh the page automatically every 5 sec
          client.println();}
          client.println("<!DOCTYPE HTML>");
          client.println("<html><head><meta http-equiv=\"refresh\" content=\"1\" />");
          client.println("<link rel=\"stylesheet\"
href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">");
          client.println("</head><body>");
          client.println("<div class='container text-center'>");
         if(A=="Street1 is Empty"){
          client.println("<button type='button' class='btn btn-success btn-lg'>");
          client.println(A);
          client.println("</button>");}
          else{
            client.println("<button type='button' class='btn btn-danger btn-lg'>");
          client.println(A+" Go to Street 2");
          client.println("</button>");
          }
          client.println("</div><div class='container text-center'>");
          if(B=="Street2 is Empty"){
          client.println("<button type='button' class='btn btn-success btn-lg'>");
          client.println(B);
          client.println("</button>");}
          else{
            client.println("<button type='button' class='btn btn-danger btn-lg'>");
          client.println(B+ " Go to street 1");
          client.println("</button>");
          }
          client.println("</div>");
          client.println("</body></html>");         
          currentLineIsBlank=false;
      }
      
      if(!currentLineIsBlank){
        break;
      }
    }
          
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    
    Serial.println("client disconnected");
      }
      
      // listen for incoming clients
    
  }
