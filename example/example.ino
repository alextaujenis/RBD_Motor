// Arduino Motor Example - Try all motor functions in real-time via serial commands (controls led 13 by default)
// Copyright 2015 Alex Taujenis
// MIT License

#include <Timer.h>
#include <Motor.h>

#define BAUD 11500
Motor motor(13);
String serial_buffer = "";
int _cmd;
unsigned long _param1, _param2;

void setup() {
  Serial.begin(BAUD);
}

void loop() {
  // keep running in real-time
  motor.update();

  // serial connection
  if (Serial.available()) {
    // capture incoming data
    serial_buffer += char(Serial.read());

    // find end of command
    if (serial_buffer.indexOf(';') > -1) {
      // capture command and parameters
      _cmd    = split(serial_buffer,',',0).toInt();
      _param1 = split(serial_buffer,',',1).toInt();
      _param2 = split(serial_buffer,',',2).toInt();

      //fire the correct action with the parameters
      performAction(_cmd, _param1, _param2);

      // clear the buffer
      serial_buffer = "";
    }
  }
}

void performAction(int cmd, long param1, long param2) {
  switch(cmd) {
    case 1: // ON
      motor.on();
      Serial.println("Motor ON");
      break;
    case 2: // OFF
      motor.off();
      Serial.println("Motor OFF");
      break;
    case 3: // TIMED_ON
      motor.timedOn(param1);
      Serial.print("Motor TIMED ON for ");
      Serial.print(param1);
      Serial.println("ms");
      break;
    case 4: // IS_ON
      Serial.print("Motor IS ON: ");
      Serial.println(motor.isOn());
      break;
    case 5: // IS_OFF
      Serial.print("Motor IS OFF: ");
      Serial.println(motor.isOff());
      break;
    case 6: // GET_PWM_VALUE
      Serial.print("Motor GET PWM VALUE: ");
      Serial.println(motor.getPwm());
      break;
    case 7: // GET_PWM_PERCENT
      Serial.print("Motor GET PWM PERCENT: ");
      Serial.print(motor.getPwmPercent());
      Serial.println("%");
      break;
    case 8: // PWM
      motor.setPwm(param1);
      Serial.print("Motor PWM: ");
      Serial.println(param1);
      break;
    case 9: // PWM_PERCENT
      motor.setPwmPercent(param1);
      Serial.print("Motor PWM PERCENT: ");
      Serial.print(param1);
      Serial.println("%");
      break;
    case 10: // RAMP_UP
      motor.rampUp(param1);
      Serial.print("Motor RAMP UP in ");
      Serial.print(param1);
      Serial.println("ms");
      break;
    case 11: // RAMP_DOWN
      motor.rampDown(param1);
      Serial.print("Motor RAMP DOWN in ");
      Serial.print(param1);
      Serial.println("ms");
      break;
    case 12: // RAMP
      motor.ramp(param1, param2);
      Serial.print("Motor RAMP to ");
      Serial.print(param1);
      Serial.print(" in ");
      Serial.print(param2);
      Serial.println("ms");
    case 13: // RAMP_PERCENT
      motor.rampPercent(param1, param2);
      Serial.print("Motor RAMP PERCENT to ");
      Serial.print(param1);
      Serial.print("% in ");
      Serial.print(param2);
      Serial.println("ms");
  }
}

// helper method to split a string
String split(String data, char separator, int index)
{
  int max_index = data.length()-1;
  String chunk = "";
  int x = 0;
  for(int i = 0; i <= max_index && x <= index; i++) {
    chunk.concat(data[i]);
    if(data[i] == separator) {
      x++;
      if(x > index) {
        chunk.trim();
        return chunk;
      }
      chunk = "";
    }
  }
}
