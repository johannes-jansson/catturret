Servo horizontal;
Servo vertical;
int led1 = D3;
int led2 = D7;
int horizontalPin = 1;
int verticalPin = 2;


void setup()
{

   // Here's the pin configuration, same as last time
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   // For input, we define the
  // pushbutton as an input-pullup
  // this uses an internal pullup resistor
  // to manage consistent reads from the device

   // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.

   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

   // For good measure, let's also make sure both LEDs are off when we start:
   digitalWrite(led1, LOW);
   digitalWrite(led2, LOW);

   horizontal.attach(horizontalPin);
   vertical.attach(verticalPin);




}


/* Last time, we wanted to continously blink the LED on and off
Since we're waiting for input through the cloud this time,
we don't actually need to put anything in the loop */

void loop()
{

  digitalWrite( led1, HIGH);
  digitalWrite( led2, HIGH);

  setHorizontal(random(0,180));
  setVertical(random(0, 180));
  delay(5000);
}

int setHorizontal(int value){
  int degree = constrain( value, 0 , 179);
  horizontal.write(degree);
  return 1;
}
int setVertical(int value){
  int degree = constrain( value, 0, 179);
  vertical.write(degree);
  return 1;
}
