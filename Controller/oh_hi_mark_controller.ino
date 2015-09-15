#define NUM_BUTTONS 7

typedef struct //create own type definition, which contains all relevant data for one button
{
  char keyBinding;
  int arduinoPin;
  bool state=false;
  bool lastState=false;
} BUTTON;

//create one instance of the above struct for each button:
BUTTON one;
BUTTON two;
BUTTON three;
BUTTON four;
BUTTON five;
BUTTON six;
BUTTON seven;

//Make an array of pointers that point to the buttons above. this makes it easy to do bulk operations (with for loops),
//but also allows for manipulation of a single adressable item... the best of both worlds :)
//A quick explanation of struct pointers: http://www.eskimo.com/~scs/cclass/int/sx1d.html
BUTTON *buttonMap[NUM_BUTTONS]={&one,&two,&three,&four,&five,&six,&seven};

void setup() {
Serial1.begin(9600); //for communication with xbee
Serial.begin(9600);

one.arduinoPin=9;
two.arduinoPin=3;
three.arduinoPin=4;
four.arduinoPin=5;
five.arduinoPin=6;
six.arduinoPin=7;
seven.arduinoPin=8;

/*one.keyBinding='1';
two.keyBinding='2';
three.keyBinding='3';
four.keyBinding='4';
five.keyBinding='5';
six.keyBinding='6';
seven.keyBinding='7';*/
//above block can be done with this oneliner:

for(int i = 0; i < NUM_BUTTONS; i++) buttonMap[i]->keyBinding=char(i+49); //dirty hack: ASCII-offset=48 array-index-offset=1, 48+1=49

for(int i = 0; i < NUM_BUTTONS; i++) //setup GPIO
{
  pinMode(buttonMap[i]->arduinoPin, INPUT_PULLUP);
  buttonMap[i]->state = digitalRead(buttonMap[i]->arduinoPin);
  buttonMap[i]->lastState=buttonMap[i]->state;
}



}

void loop() {
	for(int i = 0; i < NUM_BUTTONS; i++)
	{
		buttonMap[i]->state = digitalRead(buttonMap[i]->arduinoPin);

		if(buttonMap[i]->lastState != buttonMap[i]->state) //detect change
			{
				if(!buttonMap[i]->state) //the buttons are active low, beeteedubs...
				{
					Serial1.println(buttonMap[i]->keyBinding); 		//send corresponding char
                    Serial.println(buttonMap[i]->keyBinding);
                    delay(20); 										//debounce
					while(!digitalRead(buttonMap[i]->arduinoPin)); 	//wait for release
                }
                buttonMap[i]->lastState = buttonMap[i]->state; 	//update state
			}
	}
}