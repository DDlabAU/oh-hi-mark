#define NUM_BUTTONS 8

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
BUTTON eight;

//Make an array of pointers that point to the buttons above. this makes it easy to do bulk operations (with for loops),
//but also allows for manipulation of a single adressable item... the best of both worlds :)
//A quick explanation of struct pointers: http://www.eskimo.com/~scs/cclass/int/sx1d.html
BUTTON *buttonMap[NUM_BUTTONS]={&one,&two,&three,&four,&five,&six,&seven,&eight};

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
eight.arduinoPin=10;

/*one.keyBinding='0';
two.keyBinding='1';
three.keyBinding='2';
four.keyBinding='3';
five.keyBinding='4';
six.keyBinding='5';
seven.keyBinding='6';*/
//above block can be done with this oneliner:

for(int i = 0; i < NUM_BUTTONS; i++) buttonMap[i]->keyBinding=char(i+48); //dirty hack: ASCII-offset=48

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
		if(digitalRead(buttonMap[i]->arduinoPin) !=buttonMap[i]->lastState) //detect change
			{
				delay(50);
				buttonMap[i]->state=digitalRead(buttonMap[i]->arduinoPin);

  				if(!buttonMap[i]->state) //the buttons are active low, beeteedubs...
				{
					Serial1.println(buttonMap[i]->keyBinding); 		//send corresponding char
					Serial.println(buttonMap[i]->keyBinding);
					while(!digitalRead(buttonMap[i]->arduinoPin)); 	//wait for release
                }
                buttonMap[i]->lastState = buttonMap[i]->state; 	//update state


			}
	}
}