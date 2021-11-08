

#include <IRremote.h>
#define MTR_AC 16734885
#define MTR_KAPA 16716015  
#define LED_AC 16718055
#define LED_KAPA 16730805
int RECV_PIN = 11;
int in1 = 5 ; 
int in2 = 6 ; 
int enable = 7 ; 
int role = 2 ; 
int flag1 = 0 ; 
int flag2 = 0 ; 
int solsw= 3; 
int sagsw = 4; 

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  

  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); 
  Serial.println("Enabled IRin");
   pinMode ( enable, OUTPUT ) ; 
   pinMode ( in1 , OUTPUT ) ; 
    pinMode ( role , OUTPUT ) ; 
   pinMode ( in2 , OUTPUT ) ; 
   digitalWrite( enable ,HIGH ) ;
    
}

void loop() {

      digitalWrite( role , HIGH        ) ; 

     if ( flag2== 1) {
         digitalWrite ( in1 , LOW ) ; 
         digitalWrite ( in2 , LOW ) ; 
         if (results.value == MTR_AC)
       {
           flag2=0 ; 
         digitalWrite ( in1 , HIGH ) ; 
         digitalWrite ( in2 , LOW  ) ;  
         Serial.println("kapalıyken acıldı"); 
       }
      
     }
     if ( flag1== 1) {
         digitalWrite ( in1 , LOW ) ; 
         digitalWrite ( in2 , LOW ) ; 
         if (results.value == MTR_KAPA)
       {
        
           flag1=0 ; 
         digitalWrite ( in1 , LOW) ; 
         digitalWrite ( in2 , HIGH ) ;  
         Serial.println("acıkken kapandı"); 
       }
      
     }
       
        
  

    if( (digitalRead(solsw) == LOW) && (flag1 == 0) ) 
  {
    Serial.println("solsw1 cek"); 
flag1 = 1; 
delay(20); 
  }
  
    if( (digitalRead(solsw) == HIGH) && (flag1 == 1) ) 
  {
    Serial.println("solsw1 bas"); 
flag1 = 0;
delay(20); 
  }
  
      if( (digitalRead(sagsw) == LOW) && (flag2 == 0) ) 
  {
    Serial.println("sagsw1 cek"); 
flag2 = 1; 
delay(20); 
  }
  
    if( (digitalRead(sagsw) == HIGH) && (flag2 == 1) ) 
  {
    Serial.println("sagsw1 bas"); 
flag2 = 0;
delay(20); 
  }  
  
  
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume(); 
  }
  delay(100);

if (irrecv.decode(&results))
  {

 
    
    if (results.value == MTR_AC)
       {

         digitalWrite ( in1 , HIGH ) ; 
         digitalWrite ( in2 , LOW  ) ;  
         Serial.println("motor döndü1"); 
       }
       if (results.value == MTR_KAPA)
       {
          Serial.println("motor döndü2"); 
         digitalWrite ( in1 , LOW ) ; 
         digitalWrite ( in2 , HIGH  ) ;  
       }
       if (results.value == LED_AC)
       {
            Serial.println("Led açıldı "); 
       digitalWrite( role ,HIGH ) ;  
       }
       if (results.value == LED_KAPA)
       {
      Serial.println("Led kapandı"); 
       digitalWrite( role ,LOW) ;  
       }

  }
 
  digitalWrite(solsw, HIGH);
  digitalWrite(sagsw, HIGH);
}
