const int LED_ARRAY[5] = {2, 3, 4, 5, 6};
const int SWITCH_ARRAY[6] = {A0, A1, A2, A3, A4, A5};
const int BUZZER_PIN = 9;
const int TIME_CONSTANT = 500; //in miliseconds

void setup()
{
  //Initiate Serial communication
  Serial.begin(9600);
  
  int i;

  //set all the pins
  for (i = 0; i < 5; i++)
  {
    pinMode(LED_ARRAY[i], OUTPUT);
  }
  pinMode(BUZZER_PIN, OUTPUT);

  for (i = 0; i < 6; i++)
  {
    pinMode(SWITCH_ARRAY[i], INPUT_PULLUP);
  }
}

void loop()
{
  int i;
  bool state[6];
  //1 for ON
  //2 for OFF

  for (i = 0; i < 6; i++)
  {
    state[i] = !digitalRead(SWITCH_ARRAY[i]);
  }

  //decide which mode should play
  if (state[2])
  {
    mode1(state[0], state[1]);
  }
  else if (state[3])
  {
    mode2(state[0], state[1]);
  }
  else if (state[4])
  {
    mode3(state[0], state[1]);
  }
  else
  {
    mode4(state[0], state[1]);
  }

  //reset the buzzer
  analogWrite(BUZZER_PIN, 0);
}

void mode1(bool lights, bool sound)
{
  //lights turn on consecutively
  int i;

  for (i = 0; i < 5; i++)
  {
    if (lights)
      digitalWrite(LED_ARRAY[i], HIGH);
    delay(TIME_CONSTANT);
    if (lights)
      digitalWrite(LED_ARRAY[i], LOW);
    if (sound)
      analogWrite(BUZZER_PIN, 10 + i * 30);
  }
}

void mode2(bool lights, bool sound)
{
  //lights turn on consecutively in pairs
  int i;

  for (i = 0; i < 4; i++)
  {
    if (lights)
    {
      digitalWrite(LED_ARRAY[i], HIGH);
      digitalWrite(LED_ARRAY[i+1], HIGH);
    }
    delay(TIME_CONSTANT);
    if (lights)
    {
      digitalWrite(LED_ARRAY[i], LOW);
      digitalWrite(LED_ARRAY[i+1], LOW);
    }
    if (sound)
      analogWrite(BUZZER_PIN, 10 + (i%2) * 30);
  }
}

void mode3(bool lights, bool sound)
{
  // first step xoxox
  //second step oxoxo
  //x on, o off
  int i;
  int j;

  for (i = 0; i < 2; i++)
  {
    if (sound)
      analogWrite(BUZZER_PIN, 10 + i * 30);
    for (j = i; j < 5 && lights; j = j + 2)
    {
      digitalWrite(LED_ARRAY[j], HIGH);
    }
    delay(TIME_CONSTANT);
    for (j = i; j < 5 && lights; j = j + 2)
    {
      digitalWrite(LED_ARRAY[j], LOW);
    }
  }
}

void mode4(bool lights, bool sound)
{
  //lights start turning on from the edges
  //then, they turn off in pairs
  //the last one finishes the squence
  int i;

  for (i = 0; i < 3; i++)
  {
    if (lights)
    {
      digitalWrite(LED_ARRAY[i], HIGH);
      if (i != 2)
        digitalWrite(LED_ARRAY[4-i], HIGH);
    }
    if (sound)
      analogWrite(BUZZER_PIN, 60 - i * 20);
    delay(TIME_CONSTANT);
    if (lights)
    {
      digitalWrite(LED_ARRAY[i], LOW);
      if (i != 2)
        digitalWrite(LED_ARRAY[4-i], LOW);
    }
  }
}
