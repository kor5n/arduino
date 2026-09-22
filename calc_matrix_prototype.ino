// C++ code
//
#include <Adafruit_LiquidCrystal.h>

#define BUTTON_FIRST 2
#define BUTTON_LAST 9

#define FIRST_ROW 8
#define LAST_ROW 9

#define FIRST_COL 2
#define LAST_COL 7

static const char func_matrix[LAST_ROW-FIRST_ROW+1][LAST_COL-FIRST_COL+2] = {
  "+-x/=r",
  "1234bc"
};

Adafruit_LiquidCrystal lcd_1(0);

char getInput()
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
  	
  
  	return '\0';
}

/*static const int maxint = 9999999999999999;
static char out[16];
static int x = -1;
static int y = -1;
static char operation = "R";

void calc()
{
  	// Operations requiring one value - sqrt
  	
  	if (x != -1 && y== -1 && operation="sqrt")
    {
    	
    }
  
	if (x == -1 || y == -1 || operation = "N")
    {
    	return;
    }
  
  	int tmp;
  	switch(operation)
    {
    	case "+":
      		tmp = String(x+y);
      		break;
      	case "-":
      		tmp = String(x-y);
      		break;
      	case "x":
      		tmp = String(x*y);
      		break;
      	case "/":
      		tmp = String(x/y);
      		break;
    }
  
  	
}*/

char *composeVal(char input, char out[16])
{
  int found = 0;
   
  for (int i = 0; i < LAST_COL-FIRST_COL+1; i++)
  {
  	if (input == func_matrix[1][i])
    {
    	found = 1;
        break;
    }
  }
  if (found == 1)
  {
    int len = strlen(out);
    if (input == 'b')
    {
		if (len > 0)
        {
        	out[len-1] = '\0';
        }
    	
    }else if (input == 'c')
    {
    	out[0] = '\0';
    }else
    {
      if (len < 15)
      {
      	out[len] = input;
    	out[len+1] = '\0';
      }
    	
    }
  	
  }
  
  return out;
}

static char out[16];
static char input;

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
	input = getInput();  
  Serial.println(input);
  if (input != '\0')
  {
    
    composeVal(input, out);
    
    lcd_1.clear();
    Serial.println(out);
    lcd_1.print(out);
    
    
  }
  //lcd_1.setBacklight(0);
  delay(250); // Wait for 500 millisecond(s)
}
