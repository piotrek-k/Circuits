class RGB;

class HSL;

#define GREEN 9
#define BLUE 5
#define RED 6
#define POTENTIOMETER A5
#define BUTTON 7
#define delayTime 20

void setup()
{
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(RED, OUTPUT);
	pinMode(BUTTON, INPUT_PULLUP);
	digitalWrite(GREEN, HIGH);
	digitalWrite(BLUE, HIGH);
	digitalWrite(RED, HIGH);
	Serial.begin(9600);
}



class HSL
{
public:
	int H; //0-360 degrees
	float S; //0%-100%
	float L; //0%-100%

	HSL(int h, float s, float l)
	{
		H = h;
		S = s;
		L = l;
	}

	bool Equals(HSL hsl)
	{
		return (H == hsl.H) && (S == hsl.S) && (L == hsl.L);
	}
};


class RGB
{
public:
	int R; //0-255
	int G; //0-255
	int B; //0-255

	RGB(int r, int g, int b)
	{
		R = r;
		G = g;
		B = b;
	}

	bool Equals(RGB rgb)
	{
		return (R == rgb.R) && (G == rgb.G) && (B == rgb.B);
	}

	RGB HSLToRGB(HSL hsl) {
		int r = 0;
		int g = 0;
		int b = 0;

		if (hsl.S == 0)
		{
			r = g = b = (int)(hsl.L * 255);
		}
		else
		{
			float v1, v2;
			float hue = (float)hsl.H / 360;

			v2 = (hsl.L < 0.5) ? (hsl.L * (1 + hsl.S)) : ((hsl.L + hsl.S) - (hsl.L * hsl.S));
			v1 = 2 * hsl.L - v2;

			r = (int)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
			g = (int)(255 * HueToRGB(v1, v2, hue));
			b = (int)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
		}

		return RGB(r, g, b);
	}
};

float HueToRGB(float v1, float v2, float vH) {
	if (vH < 0)
		vH += 1;

	if (vH > 1)
		vH -= 1;

	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);

	if ((2 * vH) < 1)
		return v2;

	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

	return v1;
}



int redVal;
int blueVal;
int greenVal;

int whatToChange = 0;
HSL chosenColor = HSL(0, 0.0f, 0.0f);

void loop()
{
	int pValue = analogRead(A5);

	if (digitalRead(BUTTON) == LOW) {
		whatToChange++;
		if (whatToChange > 2) {
			whatToChange = 0;
		}
		delay(1000);
	}

	if (whatToChange == 0) {
		chosenColor.H = 360 * ((pValue + 1) / 1024);
	}
	else if (whatToChange == 1) {
		chosenColor.S = 100 * ((pValue + 1) / 1024);
	}
	else if (whatToChange == 2) {
		chosenColor.L = 100 * ((pValue + 1) / 1024);
	}
	//int[] colors = hslToRgb(2, 2, 2);
	HSL data = HSL(138, 0.50f, 0.76f);
	RGB value = value.HSLToRGB(data);

	Serial.println("whatToChange" + whatToChange);
	Serial.println("pValue" + pValue);
	Serial.println("value.R" + value.R);
	Serial.println("value.G" + value.G);
	Serial.println("value.B" + value.B);

	/*analogWrite(RED, rgb.r);
	analogWrite(GREEN, rgb.g);
	analogWrite(BLUE, rgb.b);*/
}