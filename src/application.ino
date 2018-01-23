const int PIR_SENSOR_IP = D0;
const int LED1_OP = D7;
const int TIME_THRESHOLD = 30;
const String EVENT_NAME = String("ROOM_STATUS");

bool occupyPublished;
int timer;

SerialLogHandler sLogHandler;

int readSensor(){
  return digitalRead(PIR_SENSOR_IP);
}

bool isRoomOccupied(){
  return readSensor()==HIGH? true: false;
}

void setup(){
  //Log.info(String::format("**** %s ****",__FUNCTION__));
  pinMode(LED1_OP, OUTPUT);pinMode(PIR_SENSOR_IP, INPUT);
  occupyPublished = false;
}

void loop(){
  if(isRoomOccupied()){
    digitalWrite(LED1_OP, HIGH);//Set on board LED HIGH to indiacate room occupied
    timer = 0;
    if(!occupyPublished){
      bool status = Particle.publish(EVENT_NAME,"ROOM_OCCUPIED");
      occupyPublished = true;	
      Log.info(String::format("Publishing room Occupied result = %d ", status));
    }
    Log.info("Room occupied detected");
  }else{
    if(++timer >= TIME_THRESHOLD && occupyPublished){
      bool status = Particle.publish(EVENT_NAME,"ROOM_UNOCCUPIED");
      occupyPublished = false;
      digitalWrite(LED1_OP, LOW);//Set on board LED LOW to indiacate room unoccupied
      Log.info(String::format("Publishing room Unoccupied result = %d ", status));      
    }
    Log.info(String::format("Room unoccupied detected for %d seconds",timer));
  }
  delay(1000);//delay 1 second
}
