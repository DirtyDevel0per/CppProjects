#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cmath>
#include <time.h>
using namespace std;
double SyncTime;
int Pr = 0;
const int Ws = 2000, Hs = 2000;


class cmpl{
    double Re, Im;
public:
    cmpl(double a, double b) : Re(a), Im(b) {

    }
    cmpl operator*(cmpl z2)const {
        return cmpl(Re * z2.Re - Im *z2.Im, Re * z2.Im + Im * z2.Re);
    }
    double operator!()const {
        return sqrt(Re * Re + Im * Im);
    }
    cmpl operator/(double n)const {
        return cmpl(Re / n, Im / n);
    }
    cmpl operator*(int n)const {
        return cmpl(Re * n, Im * n);
    }
    cmpl operator-(double n)const {
        return cmpl(Re - n, Im);
    }
    cmpl operator/(cmpl z2)const {
        double l = z2.Re * z2.Re + z2.Im * z2.Im;
        return cmpl((Re * z2.Re + Im * z2.Im) / l, (Im * z2.Re - Re * z2.Im) / l);
    }
    cmpl operator-(cmpl z2)const {
        return cmpl(Re - z2.Re, Im - z2.Im);
    }
    cmpl operator+(double z2)const {
        return cmpl(Re + z2, Im);
    }
    cmpl operator+(cmpl z2)const {
        return cmpl(Re + z2.Re, Im + z2.Im);
    }
    double sinus()const {
        Pr = 0;
        return Im / !cmpl(Re, Im);
    }
    double cosinus()const {
        Pr = 1;
        return Re / !cmpl(Re, Im);
    }
    int Newton1()const {
        int n = 0;
        cmpl Z(Re, Im);
        cmpl Zl = Z;

        while (n < 255 && !Z < 2)
        {
            Z = Zl - (Zl * Zl * Zl - 1) / 3 / Zl / Zl;
            Zl = Z;
            ++n;
        }

        return n;
    }
    int Newton2()const {
        int n = 0;
        cmpl Z(Re, Im);
        cmpl Zl = Z;

        while (n < 255 && !Z < 2)
        {
            if (Pr)
                Z = Zl - Zl.cosinus() / Zl.sinus() * -1;
            else
                Z = Zl - Zl.sinus() / Zl.cosinus();
            Zl = Z;
            ++n;
        }

        return n;
    }
    int Newton3()const {
        int n = 0;
        cmpl Z(Re, Im);
        cmpl Zl = Z;

        while (n < 255 && !Z < 2)
        {
            Z = Zl + (Zl * Zl * Zl * Zl * Zl - 1) / 5 / (Zl * Zl * Zl * Zl);
            Zl = Z;
            ++n;
        }

        return n;
    }
    int Julia(const cmpl C)const {
        int n = 0;
        cmpl Z(Re, Im);
        cmpl Zl = Z;

        while (n < 255 && !Z < 2)
        {
            Z = Zl * Zl * Zl * Zl * Zl + C;
            Zl = Z;
            ++n;
        }
        return n;
    }
    int Mandelbrot(const cmpl C)const {
        int n = 0;
        cmpl Zl(Re, Im);
        cmpl Z = Zl;

        while (n < 255 && !Z < 2) {
            Z = Zl * Zl + C;
            Zl = Z;
            ++n;
        }
        return n;
    }
};

class frame {
    unsigned char Image[Hs][Ws][3];

    void PutPixel (int x, int y, int r, int g , int b) {
        Image[y][x][0] = b;
        Image[y][x][1] = g;
        Image[y][x][2] = r;
    }

public :
    frame (double a) {
    double x0 = -3, y0 = -3, x1 = 3, y1 = 3, n;
    cmpl z(0, 0);

    for (int y = 0; y < Hs; y++)
        for (int x = 0; x < Ws; x++)
        {
            z = cmpl(x * (x1 - x0) / Ws + x0, y * (y1 - y0) / Hs + y0);
            n = z.Newton1();
            PutPixel(x, y, n * 300, n * 130, n * 1);
        }
}
    frame (int a) {
        double x0 = -3, y0 = -3, x1 = 3, y1 = 3, n;
        cmpl z(0, 0);

        for (int y = 0; y < Hs; y++)
            for (int x = 0; x < Ws; x++)
            {
                z = cmpl(x * (x1 - x0) / Ws + x0, y * (y1 - y0) / Hs + y0);
                n = z.Newton2();
                PutPixel(x, y, n * 30, n * 130, n * 14);
            }
    }
    frame (int a, int b) {
        double x0 = -3, y0 = -3, x1 = 3, y1 = 3, n;
        cmpl z(0, 0);

        for (int y = 0; y < Hs; y++)
            for (int x = 0; x < Ws; x++)
            {
                z = cmpl(x * (x1 - x0) / Ws + x0, y * (y1 - y0) / Hs + y0);
                n = z.Newton3();
                PutPixel(x, y, n * 300, n * 18, n * 80);
            }
    }
    frame (int a, int b, int c) {
        double x0 = -3, y0 = -3, x1 = 3, y1 = 3, n;
        cmpl z(0, 0);
        cmpl C(sin(SyncTime), cos(SyncTime) * 1.5);

        for (int y = 0; y < Hs; y++)
            for (int x = 0; x < Ws; x++)
            {
                z = cmpl(x * (x1 - x0) / Ws + x0, y * (y1 - y0) / Hs + y0);
                n = z.Julia(C);
                PutPixel(x, y, n * 100, n * 10, n * 30);
            }
    }
    frame (int a, int b, int c, int d) {
        double x0 = -3, y0 = -3, x1 = 3, y1 = 3, n;
        cmpl z(0, 0);
        cmpl C(0.5, 0.25);

        for (int y = 0; y < Hs; y++)
            for (int x = 0; x < Ws; x++)
            {
                z = cmpl(x * (x1 - x0) / Ws + x0, y * (y1 - y0) / Hs + y0);
                n = z.Mandelbrot(C);
                PutPixel(x, y, n * 100, n * 610, n * 230);
            }
    }
    void Draw()const {
        glDrawPixels(Ws, Hs, GL_BGR_EXT, GL_UNSIGNED_BYTE, Image);
    }
};
//frame sn(2);
//frame p3(0.1);
frame p5(1, 2);
//frame j(1, 2, 3);
//frame md(1, 2, 3, 4);
class animation {
private :
    animation(int argc, char*argv []) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowSize(Ws, Hs);
        glutCreateWindow("Fractal");
        glutDisplayFunc(Display);
        glutIdleFunc(Idle);
    }
   static void Display() {

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glRasterPos2d(-1, 1);
        glPixelZoom(0.4, -0.4);
        //j.Draw();
        //sn.Draw();
        //p3.Draw();
        //md.Draw();
        p5.Draw();
        glFinish();
        glutSwapBuffers();

    }
    static void Idle() {
    SyncTime = clock();
    SyncTime = 1. * SyncTime / CLOCKS_PER_SEC;
    glutPostRedisplay();
}
public :
    static animation& get(int argc, char* argv[]) {
        static animation Insert(argc, argv);
        return Insert;
    }
    void run() {
        glutMainLoop();
    }
};

int main (int argc, char* argv[]) {
    animation MyAnim = animation::get(argc, argv);
    MyAnim.run();
    return 0;
}

