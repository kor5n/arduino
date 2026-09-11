// C++ code
//
#include <Adafruit_LiquidCrystal.h>

#define BUTTON_FIRST 2
#define BUTTON_LAST 9

#define FIRST_ROW 8
#define LAST_ROW 9

#define FIRST_COL 2
#define LAST_COL 7

static char *func_matrix[LAST_ROW-FIRST_ROW+1][LAST_COL-FIRST_COL+1] = {
  {"+", "-", "x", "/", "=", "sqrt"},
  {"1", "2", "3", "4", "back", "c"}
};

Adafruit_LiquidCrystal lcd_1(0);

char *getInput()
{
  	int tmp;
	int row;
  	int col;
  	int count = 0;
  
  	for (int i=BUTTON_FIRST; i<BUTTON_LAST+1;i++)
    {
      	Serial.println("WAITING "+ String(i));
    	tmp = digitalRead(i);
      	if (tmp == LOW)
        {
          Serial.println("AAAAAA " + String(i));
          count += 1;
          if (i >= FIRST_COL && i <= LAST_COL )
          {
          		col = i;
          }else if(i >= FIRST_ROW && i <= LAST_ROW)
          {
          	row = i;
          }
        }
    }
  
  	if (count != 2)
    {
    	return NULL;
    }
  
  	char *value = func_matrix[row-FIRST_ROW][col-FIRST_COL];
  
  	return value;
}

void setup()
{
  lcd_1.begin(16, 2);

  lcd_1.print("Operation");
  
  for (int i=BUTTON_FIRST;i<=BUTTON_LAST;i++)
  {
	  pinMode(i, INPUT_PULLUP);
  }
  
  Serial.begin(9600);
  lcd_1.setCursor(0, 1);
}

void loop()
{
	char* input = getInput();  
  if (input != NULL)
  {
  	lcd_1.print(input);
  }
  //lcd_1.setBacklight(0);
  delay(1); // Wait for 500 millisecond(s)
}
