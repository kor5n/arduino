// C++ code
//
#include <Adafruit_LiquidCrystal.h>

#define BUTTON_FIRST 2
#define BUTTON_LAST 9

#define FIRST_ROW 8
#define LAST_ROW 9

#define FIRST_COL 2
#define LAST_COL 7

static const char *func_matrix[LAST_ROW-FIRST_ROW+1][LAST_COL-FIRST_COL+1] = {
  {"+", "-", "x", "/", "=", "sqrt"},
  {"1", "2", "3", "4", "back", "c"}
};

Adafruit_LiquidCrystal lcd_1(0);

const char *getInput()
{
  	int tmp;
  
  	for (int r = FIRST_ROW; r < LAST_ROW+1; r++)
    {
    	pinMode(r, OUTPUT); //acting as ground
      	digitalWrite(r, LOW);
      	Serial.println("GROUND "+String(r));
      	
      	for (int c = FIRST_COL; c < LAST_COL+1; c++)
        {
        	tmp = digitalRead(c);
          	if (tmp == LOW)
            {	
              	Serial.println("Tapped "+ String(c));
              	pinMode(r, INPUT);
            	return func_matrix[r-FIRST_ROW][c-FIRST_COL];
            }
        }
      	pinMode(r, INPUT);
    }
  	
  
  	return NULL;
}

void setup()
{
  lcd_1.begin(16, 2);

  lcd_1.print("Operation");
  
  for (int i=FIRST_COL;i<=LAST_COL;i++)
  {
	  pinMode(i, INPUT_PULLUP);
  }
  
  for (int i = FIRST_ROW; i<=LAST_ROW; i++)
  {
  	pinMode(i, INPUT);
  }
  
  Serial.begin(9600);
  lcd_1.setCursor(0, 1);
}

void loop()
{
	const char* input = getInput();  
  if (input != NULL)
  {
    lcd_1.clear();
  	lcd_1.print(input);
  }
  //lcd_1.setBacklight(0);
  delay(1); // Wait for 500 millisecond(s)
}
