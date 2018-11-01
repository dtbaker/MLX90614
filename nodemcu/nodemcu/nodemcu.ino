#include <Wire.h>
#include "i2c.h"
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
 
void setup() 
{
  Serial.begin(9600);
  mlx.begin();  
}
 
void loop() 
{
  mlx.setAddress(0x2A);
  double Amb2A = mlx.readAmbientTempC();
  double Obj2A = mlx.readObjectTempC();
  mlx.setAddress(0x2B);
  double Amb2B = mlx.readAmbientTempC();
  double Obj2B = mlx.readObjectTempC();
  
  Serial.print(Amb2A); 
  Serial.print("/"); 
  Serial.print(Amb2B); 
  Serial.print("   "); 
  Serial.print(Obj2A); 
  Serial.print("/"); 
  Serial.print(Obj2B); 
  Serial.println("   "); 
  delay(200);

}
