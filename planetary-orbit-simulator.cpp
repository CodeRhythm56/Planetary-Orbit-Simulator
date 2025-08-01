#include <iostream>
#include <cmath>
#include <graphics.h>
#include <conio.h>

using namespace std;

class OrbitSimulator {
private:
    float M;
    float m;
    float r;
    double theta;
    double omega;
    double dt;
    int center_x;
    int center_y;
    
    void drawOrbit() {
        setcolor(WHITE);
        circle(center_x, center_y, (int)r);
    }
    
    void drawStar() {
        int radius_star = (int)(10 + 5 * pow(M, 1.0 / 3.0));
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(center_x, center_y, radius_star, radius_star);
    }
    
    void drawPlanet() {
        double x = center_x + r * cos(theta);
        double y = center_y + r * sin(theta);
        int radius_planet = (int)(10 + 5 * pow(m, 1.0 / 3.0));
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        fillellipse((int)x, (int)y, radius_planet, radius_planet);
    }
    
    void displayText() {
        setcolor(WHITE);
        outtextxy(getmaxx() - 350, getmaxy() - 20, "This simulation is sped up by 1.2 million times");
    }
    
    void updatePosition() {
        theta += omega * dt;
    }

public:
    OrbitSimulator(float starMass, float planetMass, float distance)
        : M(starMass * 0.00202), m(planetMass * 0.847), r(distance * 300), theta(0), dt(0.1) {
        omega = sqrt(M / (r * r * r));
    }
    
    void initializeGraphics() {
        initwindow(1280, 720, "Planetary Orbit");
        center_x = getmaxx() / 2;
        center_y = getmaxy() / 2;
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    }
    
    void run() {
        while (!kbhit()) {
            cleardevice();
            drawOrbit();
            drawStar();
            drawPlanet();
            displayText();
            delay(5);
            updatePosition();
        }
        getch();
        closegraph();
    }
};

int main() {
    cout << "Note:\nMass of the sun = 1980000 x10^24KG\nMass of the Earth = 5.9 x10^24KG\n\n";
    float M, m, r;
    cout << "Enter mass of star (M) x10^24 KG: ";
    cin >> M;
    cout << "Enter mass of planet (m) x10^24 KG: ";
    cin >> m;
    cout << "Enter distance (r) in AU: ";
    cin >> r;
    
    OrbitSimulator sim(M, m, r);
    sim.initializeGraphics();
    sim.run();
    
    return 0;
}