// include files
#include <Timer.h>
#include <Motor.h>

#define CMD_ON              1
#define CMD_OFF             2
#define CMD_TIMED_ON        3
#define CMD_IS_ON           4
#define CMD_IS_OFF          5
#define CMD_GET_PWM_VALUE   6
#define CMD_GET_PWM_PERCENT 7
#define CMD_PWM             8
#define CMD_PWM_PERCENT     9
#define CMD_RAMP_UP         10
#define CMD_RAMP_DOWN       11
#define CMD_RAMP            12
#define CMD_RAMP_PERCENT    13

// static values
int BAUD = 11500;
int _cmd, _param1, _param2;

// variables
String serial_buffer = "";
Motor motor(13);

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

    // find newline
    if (serial_buffer.indexOf(';') > -1) {
      // capture command and parameters
      _cmd    = split(serial_buffer,',',0).toInt();
      _param1 = split(serial_buffer,',',1).toInt();
      _param2 = split(serial_buffer,',',2).toInt();

      //fire the action with the parameters
      performAction(_cmd, _param1, _param2);

      // clear the buffer
      serial_buffer = "";
    }
  }
}

void performAction(int cmd, int param1, int param2) {
  switch(cmd) {
    case CMD_ON: // 1
      motor.on();
      Serial.println("Motor ON");
      break;
    case CMD_OFF: // 2
      motor.off();
      Serial.println("Motor OFF");
      break;
    case CMD_TIMED_ON: // 3
      motor.timedOn(param1);
      Serial.print("Motor TIMED ON for ");
      Serial.print(param1);
      Serial.println("ms");
      break;
    case CMD_IS_ON: // 4
      Serial.print("Motor IS ON: ");
      Serial.println(motor.isOn());
      break;
    case CMD_IS_OFF: // 5
      Serial.print("Motor IS OFF: ");
      Serial.println(motor.isOff());
      break;
    case CMD_GET_PWM_VALUE: // 6
      Serial.print("Motor GET PWM VALUE: ");
      Serial.println(motor.getPwm());
      break;
    case CMD_GET_PWM_PERCENT: // 7
      Serial.print("Motor GET PWM PERCENT: ");
      Serial.print(motor.getPwmPercent());
      Serial.println("%");
      break;
    case CMD_PWM: // 8
      motor.setPwm(param1);
      Serial.print("Motor PWM: ");
      Serial.println(param1);
      break;
    case CMD_PWM_PERCENT: // 9
      motor.setPwmPercent(param1);
      Serial.print("Motor PWM PERCENT: ");
      Serial.print(param1);
      Serial.println("%");
      break;
    case CMD_RAMP_UP: // 10
      motor.rampUp(param1);
      Serial.print("Motor RAMP UP in ");
      Serial.print(param1);
      Serial.println("ms");
      break;
    case CMD_RAMP_DOWN: // 11
      motor.rampDown(param1);
      Serial.print("Motor RAMP DOWN in ");
      Serial.print(param1);
      Serial.println("ms");
      break;
    case CMD_RAMP: // 12
      motor.ramp(param1, param2);
      Serial.print("Motor RAMP to ");
      Serial.print(param1);
      Serial.print(" in ");
      Serial.print(param2);
      Serial.println("ms");
    case CMD_RAMP_PERCENT: // 13
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
