# include "iGraphics.h"
#include<math.h>
#include<time.h>

double degtorad(double ang)
{
    double rad;
    rad=3.14159262654/180;
    rad=rad*ang;
    return rad;
}

int cx=250, cy=250;
double  secx, secy, angs;
double  minx, miny, angm;
double  hrx, hry, angh;
void iDraw() {

	iClear();
	//iShowBMP(0,0,"bg.bmp");
	//iShowBMP(cx-100,cy-100,"b.bmp");
	iSetColor(255,255,255);
	iFilledRectangle(0,0,525,525);
	iSetColor(255, 0, 0);
	iText(120,500,"iGraphicsOffline1. PRESS Q TO QUIT");
	iSetColor(255, 0, 0);
	iLine(cx, cy, secx, secy);
	iSetColor(0, 255, 0);
	iLine(cx, cy, minx, miny);
	iSetColor(0, 0, 255);
	iLine(cx, cy, hrx, hry);
	iSetColor(0, 0, 0);
	iCircle(cx, cy, 225);
	iCircle(cx, cy, 220);
	iCircle(cx, cy, 200);
	iSetColor(255, 0, 0);
	iText(245, 455, "12");
	iText(245, 40, "6");
	iText(40,245, "9");
	iText(455, 245, "3");
	iText(cx-(200*cos(degtorad(30)))-10,355,"10");
	iText(cx+(200*cos(degtorad(30)))+5,355,"2");
	iText(cx-(200*cos(degtorad(30)))-15,145,"8");
	iText(cx+(200*cos(degtorad(30)))+5,145,"4");
	iText(cx-100-10,cy+(200*cos(degtorad(30)))+5,"11");
	iText(cx+100+5,cy+(200*cos(degtorad(30))),"1");
	iText(cx-100-10,cy-(200*cos(degtorad(30)))-10,"7");
	iText(cx+100+5,cy-(200*cos(degtorad(30)))-10,"5");




}
void iMouseMove(int mx, int my) {

}
void iMouse(int button, int state, int mx, int my) {

}
void iKeyboard(unsigned char key) {
	if (key == 'q') {
            exit(0);

	}

}
void iSpecialKeyboard(unsigned char key) {

}

void timchng() {
	minx = 250 + 140 * cos(angm);
	miny = 250 + 140 * sin(angm);
	angm = angm - degtorad(0.1);
	secx = 250 + 190 * cos(angs);
	secy = 250 + 190 * sin(angs);
	angs = angs - degtorad(6.0);
	hrx = 250 + 110 * cos(angh);
	hry = 250 + 110 * sin(angh);
	angh = angh - degtorad(1 / 120.0);

}

int main() {
	time_t rawtime;
	time(&rawtime);
	tm * csetm;
	csetm = localtime(&rawtime);
	double ho, mo, so;
	ho = (csetm->tm_hour) % 24;
	mo = csetm->tm_min;
	so = (csetm->tm_sec);
	angh = (3 - ho)*30.0 - mo / 2.0 -  so / 120.0;
	angh=degtorad(angh);
	angm = (15 - mo)*6.0 - so / 60.0  ;
	angm=degtorad(angm);
	angs = (15 - so)*6.0 ;
	angs=degtorad(angs);
	minx = 250 + 140 * cos(angm);
	miny = 250 + 140 * sin(angm);
	secx = 250 + 190 * cos(angs);
	secy = 250 + 190 * sin(angs);
	hrx = 250 + 110 * cos(angh);
	hry = 250 + 110 * sin(angh);
	iSetTimer(1000, timchng);
	iInitialize(525, 525, "iGraphicsOffline1");
	return 0;
}
