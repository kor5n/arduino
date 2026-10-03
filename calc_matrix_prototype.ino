// C++ code
//
#include <Adafruit_LiquidCrystal.h>

#define BUTTON_FIRST 2
#define BUTTON_LAST 9

#define FIRST_ROW 8
#define LAST_ROW 9

#define FIRST_COL 2
#define LAST_COL 7

#define MAX_DIGITS 14

static const char func_matrix[LAST_ROW-FIRST_ROW+1][LAST_COL-FIRST_COL+2] = {
  "+-*/=r",
  "1234bc"
};

Adafruit_LiquidCrystal lcd_1(0);

static const double maxnum = 9999999999999.0;

static char display[16];
static char input;

static double x = maxnum;

static double y = maxnum;

static char oper = '\0';

static int xdefined = 0; // 0 == false, 1 == true

double roundDouble(double val)
{
	if (val == 0.0)
    {
    	return 0.0;
    }
  
 	double digits = floor(log10(fabs(val)));
  	double factor = pow(10, MAX_DIGITS - 1 - digits);
  
  	return round(val * factor)/factor;
}

double calc(double a, double b, char operation)
{
  	if (a == maxnum || b == maxnum)
    {
    	return round(maxnum);
    }
  	// dont forget to implement when the answer has more than 16 digits
	switch (operation)
    {
    	case '+':
      		return roundDouble(a+b);
      	case '-':
      		return roundDouble(a-b);
      	case '*':
      		return roundDouble(a*b);
        case '/':
      		if (b == 0) // illegal operation returns 0 for now
            {
            	return 0.0;
            }
      		return roundDouble(a/b);
     	case 'r':
      		double tmp;
      		if (xdefined)
            {
            	tmp = pow(a, 2);
            }else
            {
            	tmp = pow(b, 2);
            }
      		return roundDouble(tmp);
        default:
      		return 0.0;
    }
}

char getInput()
{
  	int tmp;
  
  	for (int r = FIRST_ROW; r < LAST_ROW+1; r++)
    {
    	pinMode(r, OUTPUT); //acting as ground
      	digitalWrite(r, LOW);
      	//Serial.println("GROUND "+String(r));
      	
      	for (int c = FIRST_COL; c < LAST_COL+1; c++)
        {
        	tmp = digitalRead(c);
          	if (tmp == LOW)
            {	
              	//Serial.println("Tapped "+ String(c));
              	pinMode(r, INPUT);
            	return func_matrix[r-FIRST_ROW][c-FIRST_COL];
            }
        }
      	pinMode(r, INPUT);
    }
  	
  
  	return '\0';
}

void switch_num(double val)
{
  	if (xdefined == 1)
    {
      y = val;
      xdefined = 0;
    }else if (xdefined == 0){
      x = val;
      xdefined = 1;
    }
}

void getOper(char val[16], char operation)
{
	oper = operation;
    double tmp = atof(val);
  	switch_num(tmp);
}

char *composeOut(char input, char out[16])
{
  int found = 0;
   
  for (int i = 0; i < LAST_COL-FIRST_COL+1; i++)
  {
  	for (int j = 0; i<LAST_ROW-FIRST_ROW+1; j++)
    {
    	if (func_matrix[i][j] == input)
        {
        	found = 1;
          	break;
        }
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
    }else if (input == '+' || input == '-' || input == '/' || input == '*' || input == 'r')
    {
      getOper(out, input);
      out[0] = '\0';
    }
    else if (input == '=')
    {
      	double ans = calc(x, y, oper);
    	dtostrf(ans, 1,MAX_DIGITS, out);
      	switch_num(ans);
      	
    }
    else
    {
      if (len < MAX_DIGITS)
      {
      	out[len] = input;
    	out[len+1] = '\0';
      }
    	
    }
  	
  }
  
  return out;
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
	input = getInput();  
  //Serial.println(input);
  Serial.println("X is " + String(x));
  Serial.println("Y is " + String(y));
  Serial.println("Operation " + oper);
  Serial.println("Xdefined " + String(xdefined));
  
  
  if (input != '\0')
  {
    lcd_1.clear();
    Serial.println(input);
    composeOut(input, display);
    
    lcd_1.setCursor(0, 0);
  	lcd_1.print(oper);
    
    lcd_1.setCursor(0, 1);
    lcd_1.print(display);
    
    
  }
  
  //lcd_1.setBacklight(0);
  delay(200); // Wait for 500 millisecond(s)
}
