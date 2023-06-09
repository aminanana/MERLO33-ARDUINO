#include <Servo.h>

Servo bras;  // creer les servos qu'on va utiliser, 1 pour bras et 1 pour couteau
Servo cut;

#define A1 9  // Motor A pins
#define A2 8
#define B1 7 // Motor B pins
#define B2 6

int  input = 0;
int vit_high = 255;
int vit_low = 80;
int vit_mid = 195;
int bras_pos = 0;  // variable qui store la position du servo pour le bras
char commande;  //déclare variable commande qui va recevoir les donnes envoyees par le hc-05

void setup() {
  Serial.begin(9600); // permet au Arduino de communiquer avec le téléphone a 9600 bits/sec
  bras.attach(3);  // (pin, min, max)
  cut.attach(12);  // (pin, min, max)

  pinMode(A1, OUTPUT); //A1 avec pin 6
  pinMode(A2, OUTPUT); //A2 avec pin 7
  pinMode(B1, OUTPUT); //B1 avec pin 8
  pinMode(B2, OUTPUT); //B2 avec pin 9


}

void loop() 
{
  if (Serial.available() > 0) //serial.available lit le nb de bits donc dès qu'il y en a plus que 0, la loop s'execute. peut aussi remplacer par boucle IF
  {
  commande = Serial.read(); // lit un bit et le store dans la variable val
  Serial.println(commande); //la valeur de val(en bits) est convertie en texte ASCII
  }
   //Moteurs des roues:
   if( commande == 'B') // Backward. Ce code s'execute qd on execute le bouton B sur l'application
    {
    analogWrite(A1, vit_high);
    analogWrite(B1, vit_high); 
    }
    else if(commande == 'F') // Forward
    {         
    analogWrite(A2, vit_high);
    analogWrite(B2, vit_high);
    }

    else if(commande == 'L') //Left
    {
    analogWrite(B1, vit_high);
    analogWrite(A2, vit_high);
    }
    else if(commande == 'R') //Right
    {
    analogWrite(B2, vit_high);
    analogWrite(A1, vit_high);
    }  

    else if(commande == 'S') //Stop
    {              
    digitalWrite(A2, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(B1, LOW);
    digitalWrite(B2, LOW);
    }

    //Servos moteurs:
    else if(commande == 'u') //bras DESCEND (bouton back lights on)
    {
    for(int i = 32; i <= 85; i++) {  // augmente la position du servo graduellement
      bras.write(i);  
      delay(20);  // att 20 ms que le bras atteigne la position
    }
    }
    //Position intermédiaire
    else if(commande == 'V') //bras MONTE pour déposer roche (bouton horn on)
    {
    for(int i = 27; i <= 55; i++) {  // augmente la position du servo graduellement
      bras.write(i);  
      delay(20);  // att 20 ms que le bras atteigne la position
    }
    }
    else if(commande == 'v') //bras DESCEND pour déposer roche (bouton horn oFF)
    {
    for(int i = 55; i >= 27; i--) {  // augmente la position du servo graduellement
      bras.write(i);  
      delay(20);  // att 20 ms que le bras atteigne la position
    }
    }
    /*{ 
    bras.write(85); 
    }    
    */
    else if(commande == 'U') //bras MONTE (bouton back lights off)
    { 
    for(int i = 85; i >= 32; i--) { 
      bras.write(i);  
      delay(20);  
    }
    }  
    /*{ 
    bras.write(27);
    }  
    */
   else if(commande == 'w') //couteau FERME (bouton front lights on sur app)
    { 
    cut.write(80);
    }  

   else if(commande == 'W') //couteau OUVRE (bouton front lights off sur app)
    { 
    cut.write(0);
    }  



}




