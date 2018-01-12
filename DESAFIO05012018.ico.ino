#include <Keypad.h> 
#include <Servo.h>
#include <LiquidCrystal.h>  
#include <NewPing.h>  

// Definimos las 2 claves
String codeOne = "103D";
String codeTwo = "104B";

String codeInserted = "";

//  Configuraciones para el keypad
const byte f = 4;
const byte c = 4;
byte row[f] = {A0, A1, A2, A3};
byte col[c] = {3,4,5,6};
char keys[f][c] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};  
char codigo[4];
int contador = 0;


//  Configuracion del keypad
Keypad keypad = Keypad( makeKeymap(keys), row, col, f, c );  
//  Configuracion del Servo
Servo servo1;


//  Configuracion de la pantalla de cristal
LiquidCrystal lcd(9, 10, 11, 12, A4, A5); 
int pin = 0;

//  Configuración para el sendor ultrasonico
#define TRIGGER_PIN  7 
#define ECHO_PIN     8   
#define MAX_DISTANCE 200  
NewPing sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);   

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  //  Inicializamo el numero de columnas y filas para el LCD
  lcd.begin(200, 100);
  //  Conf e Inalizacion del servo motor
  servo1.attach(2);
  servo1.write(90);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();       
  lcd.setCursor(0, 0);       
  lcd.print("Insertar clave:");
  // Obtenemos el valor de la tecla presionada
  char key = keypad.getKey();

  // Ejecutar opciones hasta recibir un asterisco
  if ((key=='*') && (contador==3))
  {
    codeInserted = str(codigo);
    // asignamos a nuestra variable codeInserted el valor concatenado del array codigo
    switch (codeInserted) { // Compara el codigo para escoger un caso
      case "103D":
        lcd.setCursor(0, 0);
        lcd.print("CONTROL SERVO MOTOR:");
        lcd.setCursor(0, 1);
        lcd.print("NUMERO DE 00-99");
        char 
        break;
      case "104D":
        lcd.setCursor(0, 1);
        lcd.print("LECTURA ULTRASONIDO:");
        lcd.setCursor(0, 1);
        Serial.print("Medida: ");  
        int medida= sensor.ping_cm();   
        lcd.print(medida);
        // Serial.print(medida);    
        // Serial.println(" cm");    
        break;
      default:
        lcd.setCursor(0, 1);
        lcd.print("ERROR, OTRA VEZ...");
        break;       
    }
    contador =0;
  } else { 
    // Asignamos a nuestro array el valor de la tecla hasta haber obtenido 4 digitos
    codigo[contador] = key;
    contador++;
  }



}
