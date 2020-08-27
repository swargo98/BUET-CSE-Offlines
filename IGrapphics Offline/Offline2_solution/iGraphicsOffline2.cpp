# include "iGraphics.h"
char str[100], str2[100];
int len=0, plen=0, x[100],cr=7,cb=8,cg=9, j,i;
int mode ;
int pos=10;

void setpos(int len, int in)
{
    x[0]=in;
    for(j=1; j<len; j++) x[j]=x[j-1]+50;
}

void colorchng()
{
    cr=(cr*2)%255;
    cb=(cb*3)%255;
    cg=(cg*4)%255;
}

void poschng()
{
    int lst=x[plen-1]+40;
    for(j=0; j<plen; j++)
    {
        if(lst<1)
        {
            setpos(plen,400);
        }
        else x[j]--;

    }


}

void drawTextBox()
{
    iSetColor(150, 150, 150);
    iRectangle(50, 250, 300, 30);
}


void drawhorizonup(int b)
{
    iFilledRectangle(b,180, 40, 5);
}
void drawhorizonmid(int b)
{
    iFilledRectangle(b,140, 40, 5);
}
void drawhorizondn(int b)
{
    iFilledRectangle(b,100, 40, 5);
}

void drawvertlu(int b)
{
    iFilledRectangle(b,140, 5, 45);
}

void drawvertld(int b)
{
    iFilledRectangle(b,100, 5, 45);
}

void drawvertru(int b)
{
    iFilledRectangle(b+35,140, 5, 45);
}

void drawvertrd(int b)
{
    iFilledRectangle(b+35,100, 5, 45);
}

/*
	function iDraw() is called again and again by the system.
	*/
void iDraw()
{
    //place your drawing codes here

    iClear();

    drawTextBox();

    if (mode == 1)
    {
        iSetColor(255, 255, 255);
        iText(55, 260, str);
    }

    iSetColor(cr, cg, cb);
    //else
    //{
        for(i=0; i<plen; i++)
        {
            if(str2[i]=='B'||str2[i]=='8')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                drawhorizondn(x[i]);
                drawvertld(x[i]);
                drawvertlu(x[i]);
                drawvertrd(x[i]);
                drawvertru(x[i]);

            }
            if(str2[i]=='A')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                //drawhorizondn(a[i]);
                drawvertld(x[i]);
                drawvertlu(x[i]);
                drawvertrd(x[i]);
                drawvertru(x[i]);
            }
            if(str2[i]=='b')
            {
                //drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                drawhorizondn(x[i]);
                drawvertld(x[i]);
                drawvertlu(x[i]);
                drawvertrd(x[i]);
                //drawvertru(a[i]);
            }
            if(str2[i]=='C')
            {
                drawhorizonup(x[i]);
                //drawhorizonmid(a[i]);
                drawhorizondn(x[i]);
                drawvertld(x[i]);
                drawvertlu(x[i]);
                //drawvertrd(a[i]);
                //drawvertru(a[i]);
            }
            if(str2[i]=='D'||str2[i]=='0')
            {
                drawhorizonup(x[i]);
                //drawhorizonmid(a[i]);
                drawhorizondn(x[i]);
                drawvertld(x[i]);
                drawvertlu(x[i]);
                drawvertrd(x[i]);
                drawvertru(x[i]);
            }
            if(str2[i]=='E')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                drawhorizondn(x[i]);
                drawvertld(x[i]);
                drawvertlu(x[i]);
                //drawvertrd(a[i]);
                //drawvertru(a[i]);
            }
            if(str2[i]=='F')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                //drawhorizondn(a[i]);
                drawvertld(x[i]);
                drawvertlu(x[i]);
                //drawvertrd(a[i]);
                //drawvertru(a[i]);
            }
            if(str2[i]=='1')
            {
                //drawhorizonup(a[i]);
                //drawhorizonmid(a[i]);
                //drawhorizondn(a[i]);
                //drawvertld(a[i]);
                //drawvertlu(a[i]);
                drawvertrd(x[i]);
                drawvertru(x[i]);
            }
            if(str2[i]=='2')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                drawhorizondn(x[i]);
                drawvertld(x[i]);
                //drawvertlu(a[i]);
                //drawvertrd(a[i]);
                drawvertru(x[i]);
            }
            if(str2[i]=='3')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                drawhorizondn(x[i]);
                //drawvertld(a[i]);
                //drawvertlu(a[i]);
                drawvertrd(x[i]);
                drawvertru(x[i]);
            }
            if(str2[i]=='4')
            {
                //drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                //drawhorizondn(a[i]);
                //drawvertld(a[i]);
                drawvertlu(x[i]);
                drawvertrd(x[i]);
                drawvertru(x[i]);
            }
            if(str2[i]=='5')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                drawhorizondn(x[i]);
                //drawvertld(a[i]);
                drawvertlu(x[i]);
                drawvertrd(x[i]);
                //drawvertru(a[i]);
            }
            if(str2[i]=='6')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                drawhorizondn(x[i]);
                drawvertld(x[i]);
                drawvertlu(x[i]);
                drawvertrd(x[i]);
                //drawvertru(a[i]);
            }
            if(str2[i]=='7')
            {
                drawhorizonup(x[i]);
                //drawhorizonmid(a[i]);
                //drawhorizondn(a[i]);
                //drawvertld(a[i]);
                //drawvertlu(a[i]);
                drawvertrd(x[i]);
                drawvertru(x[i]);
            }
            if(str2[i]=='9')
            {
                drawhorizonup(x[i]);
                drawhorizonmid(x[i]);
                //drawhorizondn(a[i]);
                //drawvertld(a[i]);
                drawvertlu(x[i]);
                drawvertrd(x[i]);
                drawvertru(x[i]);
            }
        }


    //}
    iSetColor(255, 255, 255);
    iText(10, 10, "Click to activate the box, enter to finish.");
}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (mx >= 50 && mx <= 300 && my >= 250 && my <= 280 && mode == 0)
        {
            mode = 1;
        }
    }
}

void iKeyboard(unsigned char key)
{
    int i;
    if (mode == 1)
    {
        if (key == '\r')
        {
            mode = 0;
            strcpy(str2, str);
            //printf("%s\n", str2);
            for (i = 0; i < len; i++)
                str[i] = 0;
            plen=len;
            len = 0;
            setpos(plen, 400);
        }
        else
        {
            str[len] = key;
            len++;
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }

}

int main()
{
    //place your own initialization codes here.
    len = 0;
    mode = 0;
    str[0] = 0;
    iSetTimer(1,poschng);
    iSetTimer(50,colorchng);
    iInitialize(400, 350, "iGraphicsOffline2");
    return 0;
}
