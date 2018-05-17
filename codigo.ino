const int sensorPIN = A0;
const int sampleWindow = 50; // Ancho ventana en mS (50 mS = 20Hz)
const int ledPinVerde = 13;
const int ledPinAmarillo = 10;
const int ledPinRojo = 4;
const int threshold1 = 15;
const int threshold2 = 40;
const int pinBuzzer = 9;

void setup() {
  pinMode(ledPinVerde, OUTPUT);
  pinMode(ledPinAmarillo, OUTPUT);
  pinMode(ledPinRojo, OUTPUT);
  Serial.begin(9600);
}
void loop() { 
     unsigned long startMillis= millis();
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // Recopilar durante la ventana
   unsigned int sample;
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(sensorPIN);
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // Actualizar máximo
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // Actualizar mínimo
         }
      }
   }
   unsigned int peakToPeak = signalMax - signalMin;  // Amplitud del sonido
   double volts = (peakToPeak * 5.0)*10*5 / 1024;  // Convertir a tensión
   Serial.println(volts);

  if (volts < threshold1){
    digitalWrite(ledPinVerde, HIGH);
    digitalWrite(ledPinAmarillo, LOW);
    digitalWrite(ledPinRojo, LOW);
      noTone(pinBuzzer);
  }
  else {
    if (volts < threshold2){
      digitalWrite(ledPinVerde,LOW);
      digitalWrite(ledPinAmarillo, HIGH);
      digitalWrite(ledPinRojo,LOW);
        noTone(pinBuzzer);
    }
      else { 
             digitalWrite(ledPinVerde,LOW);
             digitalWrite(ledPinAmarillo, LOW);
             digitalWrite(ledPinRojo,HIGH);
             tone(pinBuzzer, 12000);
             delay(5000);   
}
  }
}
