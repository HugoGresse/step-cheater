#include <AccelStepper.h> 

int stepsPerRevolution = 3200; // 3200
int degreePerRevolution = 200; // 200

AccelStepper stepper(1, 3, 2);

# Step simulation going back and forth
void setup() {
  Serial.begin(9600);        
  Serial.println("starting");

  stepper.setMaxSpeed(3000);  
  stepper.setAcceleration(12000);  
}

int randomStartDegree = 0;
int randomEndDegree = 20;
int randomRange = 3;

int stepsIndex = 0;
int runCount = 0;
int currentDestination = 0;

void loop() {
  // If the stepper isn't moving and doesn't have to go any distance
  if (!stepper.isRunning() && stepper.distanceToGo() == 0) {

    if(stepsIndex == 0) {
      currentDestination = random(randomEndDegree - randomRange, randomEndDegree + randomRange);
      stepsIndex = 1;
    } else {
      currentDestination = random(randomStartDegree - randomRange, randomStartDegree + randomRange);
      stepsIndex = 0;
    }

    
    stepper.moveTo(degToSteps(currentDestination));

    //delay(random(60,130));
    runCount++;

    if(runCount % 10 == 0){
      stepper.setAcceleration(random(8000,20000));  
    }
    
  }

  stepper.run();

}

/*
 * Converts degrees to steps
 * 
 * 28BYJ-48 motor has 5.625 degrees per step
 * 360 degrees / 5.625 = 64 steps per revolution
 * 
 * Example with degToSteps(45):
 * (64 / 5.625) * 45 = 512 steps
 */
float degToSteps(float deg) {
  return (stepsPerRevolution / degreePerRevolution) * deg;
}
