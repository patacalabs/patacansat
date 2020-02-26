#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;
double Po=1013.25;
void setup() {
  // Iniciamos a comunicación por Serie
  Serial.begin(9600);
 //Iniciamos o sensor
  if (bmp180.begin())
    Serial.println("BMP180 iniciado correctamenten");
  else
  {
    Serial.println("Error al iniciar el BMP180");
    while(1); // bucle infinito
  }
  //miramos canto tempo tarda o sensor e facer as medidas
  double status;
  status = bmp180.startTemperature();//Inicio de lectura de temperatura: tempo de medida en milisegundos
  Serial.println(status);
  status= bmp180.startPressure(3); //Inicio de lectura de temperatura: devolve o tempo, en milisegundos, que tarda en medir tres veces a presión.
  Serial.println(status);
}

void loop() {
  //declaramos variables para facer as medidas
  char status; 
  double T,P,A;
  //Inicio de lectura de temperatura
  status = bmp180.startTemperature();
  if(status !=0)
    {
      delay(status); 
      status= bmp180.getTemperature(T);
      //Inicio de lectura de Presión
      if (status !=0);
      {
        status=bmp180.startPressure(3);
        if (status !=0)
        {
          delay(status);
          status=bmp180.getPressure(P,T);
          //sacamos todos os datos polo porto serie
          if (status !=0)
          {
            Serial.print("Temperatura: ");
            Serial.print(T,2);
            Serial.print(" oC ; ");
            Serial.print("Presion: ");
            Serial.print(P,2);
            Serial.print(" mbar");     
            A=bmp180.altitude(P,Po);
            Serial.print("; Altitud: ");
            Serial.print(A);
            Serial.println(" metros");  
           
          }
        }
      }
    }
    //Esperamos un segundo entre medidas
    delay(1000);
       
  
}
