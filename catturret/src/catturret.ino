Servo horizontal;
Servo vertical;
int led1 = D2;
int led2 = D7;

bool goBananas = false;
bool laser = false;


void setup()
{

   // Here's the pin configuration, same as last time
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);

   // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("setLaser",setLaser);
   Particle.function("getLaser",getLaser);
   Particle.function("horizontal",cloudSetHorizontal);
   Particle.function("vertical",cloudSetVertical);
   Particle.function("setGoBananas",cloudSetGoBananas);
   Particle.function("getGoBananas",getGoBananas);

   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

   // For good measure, let's also make sure both LEDs are off when we start:
   digitalWrite(led1, LOW);
   digitalWrite(led2, LOW);

   horizontal.attach(1);
   vertical.attach(1);

}


/* Last time, we wanted to continously blink the LED on and off
Since we're waiting for input through the cloud this time,
we don't actually need to put anything in the loop */

void loop()
{
  if(goBananas==true){
    setHorizontal(random(0,180));
    delay(5000);
  }
}

int setLaser(String command) {
    if (command=="true") {
        laser = true;
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        return 1;
    }
    else if (command=="false") {
        laser = false;
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        return 0;
    }
    else {
        return -1;
    }
}

int getLaser(String command) {
  if(laser) {
    return 1;
  } else {
    return 0;
  }
}

int cloudSetGoBananas(String value){
  if (value=="true") {
    goBananas = true;
    return 1;
  }
  else if (value == "false") {
    goBananas = false;
    return 0;
  }
  else {
      return -1;
  }
}

int getGoBananas(String value) {
  if (goBananas) {
    return 1;
  } else {
    return 0;
  }
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

int cloudSetHorizontal(String value){
  return setHorizontal(value.toInt());
}
int cloudSetVertical(String value){
  return setVertical(value.toInt());
}
