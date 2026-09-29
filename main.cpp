#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

// animation
float birdOffset = 0.0f;
float sunAngle = 0.0f;
bool isNight = false;
float bulbBlink = 0.0f;
bool bulbState = true;

// Rickshaw animation
float rickshawX = 10.0f;
float rickshawSpeed = 0.6f;
bool rickshawMoving = false;

// Boat animation
float boatX = 60.0f;
float boatSpeed = 0.5f;
bool boatMoving = false;
float boatWaveOffset = 0.0f;

// Window dimensions
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 1200;

// Function to draw a filled circle
void drawCircle(float cx, float cy, float r, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Func draw a filled rectangle
void drawRect(float x1, float y1, float x2, float y2, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Func draw a line
void drawLine(float x1, float y1, float x2, float y2, float red, float green, float blue, float width) {
    glColor3f(red, green, blue);
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// draw sky
void drawSky() {
    if (isNight) {
        glBegin(GL_QUADS);
        glColor3f(0.02f, 0.02f, 0.10f);
        glVertex2f(0.0f, 200.0f);
        glColor3f(0.05f, 0.05f, 0.15f);
        glVertex2f(200.0f, 200.0f);
        glColor3f(0.08f, 0.08f, 0.20f);
        glVertex2f(200.0f, 95.0f);
        glColor3f(0.08f, 0.08f, 0.20f);
        glVertex2f(0.0f, 95.0f);
        glEnd();

        glColor3f(1.00f, 1.00f, 0.90f);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        for (int i = 0; i < 30; i++) {
            float x = 5.0f + (i * 31 % 190);
            float y = 115.0f + (i * 53 % 65);
            glVertex2f(x, y);
        }
        glEnd();

        drawCircle(170.0f, 182.0f, 9.0f, 0.95f, 0.92f, 0.75f);
        drawCircle(174.0f, 184.0f, 7.0f, 0.05f, 0.05f, 0.12f);
    } else {
        glBegin(GL_QUADS);
        glColor3f(0.20f, 0.50f, 0.85f);
        glVertex2f(0.0f, 200.0f);
        glColor3f(0.40f, 0.70f, 0.95f);
        glVertex2f(200.0f, 200.0f);
        glColor3f(0.70f, 0.85f, 1.00f);
        glVertex2f(200.0f, 95.0f);
        glColor3f(0.70f, 0.85f, 1.00f);
        glVertex2f(0.0f, 95.0f);
        glEnd();
    }
}

// Draw static clouds (only during day)
void drawClouds() {
    if (!isNight) {
        glColor3f(1.0f, 1.0f, 1.0f);

        // Cloud 1
        drawCircle(20.0f, 176.0f, 8.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(28.0f, 178.0f, 9.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(36.0f, 175.0f, 8.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(26.0f, 172.0f, 7.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(33.0f, 170.0f, 6.0f, 1.0f, 1.0f, 1.0f);

        // Cloud 2
        drawCircle(84.0f, 178.0f, 7.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(92.0f, 180.0f, 8.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(100.0f, 177.0f, 6.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(90.0f, 174.0f, 6.0f, 1.0f, 1.0f, 1.0f);

        // Cloud 3
        drawCircle(144.0f, 182.0f, 6.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(151.0f, 183.0f, 7.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(158.0f, 181.0f, 6.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(150.0f, 178.0f, 5.0f, 1.0f, 1.0f, 1.0f);

        // Cloud 4
        drawCircle(176.0f, 168.0f, 5.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(183.0f, 169.0f, 6.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(189.0f, 167.0f, 4.0f, 1.0f, 1.0f, 1.0f);
        drawCircle(180.0f, 165.0f, 4.0f, 1.0f, 1.0f, 1.0f);
    }
}

// Func draw birds
void drawBirds() {
    if (!isNight) {
        glColor3f(0.10f, 0.10f, 0.10f);
        glLineWidth(2.0f);

        glBegin(GL_LINE_STRIP);
        glVertex2f(65.0f, 168.0f);
        glVertex2f(68.0f, 166.0f);
        glVertex2f(71.0f, 168.0f);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex2f(125.0f, 172.0f);
        glVertex2f(128.0f, 170.0f);
        glVertex2f(131.0f, 172.0f);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex2f(100.0f, 176.0f);
        glVertex2f(103.0f, 174.0f);
        glVertex2f(106.0f, 176.0f);
        glEnd();
    }
}

// draw mountains
void drawMountains() {
    if (isNight) {
        glColor3f(0.18f, 0.22f, 0.15f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 95.0f);
        glVertex2f(28.0f, 155.0f);
        glVertex2f(56.0f, 95.0f);
        glEnd();

        glColor3f(0.12f, 0.18f, 0.10f);
        glBegin(GL_TRIANGLES);
        glVertex2f(10.0f, 95.0f);
        glVertex2f(40.0f, 168.0f);
        glVertex2f(70.0f, 95.0f);
        glEnd();

        glColor3f(0.15f, 0.20f, 0.12f);
        glBegin(GL_TRIANGLES);
        glVertex2f(150.0f, 95.0f);
        glVertex2f(175.0f, 145.0f);
        glVertex2f(200.0f, 95.0f);
        glEnd();
    } else {
        glColor3f(0.45f, 0.55f, 0.45f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 95.0f);
        glVertex2f(28.0f, 155.0f);
        glVertex2f(56.0f, 95.0f);
        glEnd();

        glColor3f(0.30f, 0.45f, 0.28f);
        glBegin(GL_TRIANGLES);
        glVertex2f(10.0f, 95.0f);
        glVertex2f(40.0f, 168.0f);
        glVertex2f(70.0f, 95.0f);
        glEnd();

        glColor3f(0.38f, 0.50f, 0.40f);
        glBegin(GL_TRIANGLES);
        glVertex2f(150.0f, 95.0f);
        glVertex2f(175.0f, 145.0f);
        glVertex2f(200.0f, 95.0f);
        glEnd();
    }
}

// draw river
void drawRiver() {
    if (isNight) {
        drawRect(0.0f, 0.0f, 200.0f, 28.0f, 0.05f, 0.10f, 0.25f);
    } else {
        drawRect(0.0f, 0.0f, 200.0f, 28.0f, 0.20f, 0.50f, 0.85f);
    }
}

// draw boat
void drawBoat(float x, float y) {
    if (isNight) {
        glColor3f(0.35f, 0.22f, 0.10f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 10.0f, y);
        glVertex2f(x - 7.0f, y + 6.0f);
        glVertex2f(x + 7.0f, y + 6.0f);
        glVertex2f(x + 10.0f, y);
        glVertex2f(x + 8.0f, y - 2.0f);
        glVertex2f(x - 8.0f, y - 2.0f);
        glEnd();

        glColor3f(0.28f, 0.18f, 0.08f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 8.0f, y - 2.0f);
        glVertex2f(x + 8.0f, y - 2.0f);
        glVertex2f(x + 6.0f, y - 4.0f);
        glVertex2f(x - 6.0f, y - 4.0f);
        glEnd();

        drawRect(x - 8.0f, y + 1.0f, x + 8.0f, y + 4.0f, 0.60f, 0.48f, 0.28f);

        glColor3f(0.25f, 0.15f, 0.07f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
        for (int i = -6; i <= 6; i += 3) {
            glVertex2f(x + i, y + 2.0f);
            glVertex2f(x + i, y + 4.0f);
        }
        glEnd();

        drawRect(x - 1.0f, y + 4.0f, x + 1.0f, y + 21.0f, 0.40f, 0.28f, 0.15f);

        glColor3f(0.92f, 0.94f, 0.88f);
        glBegin(GL_POLYGON);
        glVertex2f(x + 1.0f, y + 20.0f);
        glVertex2f(x + 11.0f, y + 10.0f);
        glVertex2f(x + 10.0f, y + 8.0f);
        glVertex2f(x + 1.0f, y + 8.0f);
        glEnd();

        glColor3f(0.85f, 0.86f, 0.81f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 1.0f, y + 19.0f);
        glVertex2f(x - 10.0f, y + 10.0f);
        glVertex2f(x - 9.0f, y + 8.0f);
        glVertex2f(x - 1.0f, y + 8.0f);
        glEnd();
    } else {
        glColor3f(0.55f, 0.35f, 0.18f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 10.0f, y);
        glVertex2f(x - 7.0f, y + 6.0f);
        glVertex2f(x + 7.0f, y + 6.0f);
        glVertex2f(x + 10.0f, y);
        glVertex2f(x + 8.0f, y - 2.0f);
        glVertex2f(x - 8.0f, y - 2.0f);
        glEnd();

        glColor3f(0.44f, 0.28f, 0.14f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 8.0f, y - 2.0f);
        glVertex2f(x + 8.0f, y - 2.0f);
        glVertex2f(x + 6.0f, y - 4.0f);
        glVertex2f(x - 6.0f, y - 4.0f);
        glEnd();

        drawRect(x - 8.0f, y + 1.0f, x + 8.0f, y + 4.0f, 0.85f, 0.70f, 0.45f);

        glColor3f(0.38f, 0.25f, 0.13f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
        for (int i = -6; i <= 6; i += 3) {
            glVertex2f(x + i, y + 2.0f);
            glVertex2f(x + i, y + 4.0f);
        }
        glEnd();

        drawRect(x - 1.0f, y + 4.0f, x + 1.0f, y + 21.0f, 0.60f, 0.45f, 0.25f);

        glColor3f(1.00f, 0.98f, 0.95f);
        glBegin(GL_POLYGON);
        glVertex2f(x + 1.0f, y + 20.0f);
        glVertex2f(x + 11.0f, y + 10.0f);
        glVertex2f(x + 10.0f, y + 8.0f);
        glVertex2f(x + 1.0f, y + 8.0f);
        glEnd();

        glColor3f(0.92f, 0.90f, 0.87f);
        glBegin(GL_POLYGON);
        glVertex2f(x - 1.0f, y + 19.0f);
        glVertex2f(x - 10.0f, y + 10.0f);
        glVertex2f(x - 9.0f, y + 8.0f);
        glVertex2f(x - 1.0f, y + 8.0f);
        glEnd();
    }

    glColor3f(0.70f, 0.70f, 0.75f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(x + 1.0f, y + 18.0f);
    glVertex2f(x + 10.0f, y + 10.0f);
    glVertex2f(x + 1.0f, y + 16.0f);
    glVertex2f(x + 8.0f, y + 10.0f);
    glVertex2f(x + 1.0f, y + 14.0f);
    glVertex2f(x + 7.0f, y + 10.0f);
    glVertex2f(x + 1.0f, y + 12.0f);
    glVertex2f(x + 6.0f, y + 10.0f);
    glVertex2f(x - 1.0f, y + 17.0f);
    glVertex2f(x - 8.0f, y + 10.0f);
    glVertex2f(x - 1.0f, y + 15.0f);
    glVertex2f(x - 7.0f, y + 10.0f);
    glVertex2f(x - 1.0f, y + 13.0f);
    glVertex2f(x - 6.0f, y + 10.0f);
    glEnd();

    glColor3f(0.50f, 0.35f, 0.15f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(x - 2.0f, y + 6.0f);
    glVertex2f(x - 10.0f, y + 16.0f);
    glEnd();

    glLineWidth(6.0f);
    glBegin(GL_LINES);
    glVertex2f(x - 9.0f, y + 15.0f);
    glVertex2f(x - 11.0f, y + 16.0f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(x - 9.0f, y + 15.0f);
    glVertex2f(x - 10.0f, y + 14.0f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(x + 3.0f, y + 6.0f);
    glVertex2f(x + 8.0f, y + 14.0f);
    glEnd();
}

// draw ground
void drawGround() {
    if (isNight) {
        drawRect(0.0f, 52.0f, 200.0f, 95.0f, 0.08f, 0.22f, 0.06f);

        glBegin(GL_QUADS);
        glColor3f(0.28f, 0.22f, 0.12f);
        glVertex2f(0.0f, 32.0f);
        glVertex2f(200.0f, 32.0f);
        glVertex2f(200.0f, 52.0f);
        glVertex2f(0.0f, 52.0f);
        glEnd();

        glColor3f(0.15f, 0.30f, 0.10f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, 52.0f);
        glVertex2f(200.0f, 52.0f);
        glVertex2f(0.0f, 32.0f);
        glVertex2f(200.0f, 32.0f);
        glEnd();

        glColor3f(0.50f, 0.45f, 0.20f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        for (float x = 10.0f; x <= 190.0f; x += 14.0f) {
            glVertex2f(x, 41.4f);
            glVertex2f(x + 6.0f, 41.4f);
        }
        glEnd();

        drawRect(0.0f, 28.0f, 200.0f, 32.0f, 0.06f, 0.18f, 0.05f);
    } else {
        drawRect(0.0f, 52.0f, 200.0f, 95.0f, 0.20f, 0.55f, 0.18f);

        glBegin(GL_QUADS);
        glColor3f(0.55f, 0.45f, 0.28f);
        glVertex2f(0.0f, 32.0f);
        glVertex2f(200.0f, 32.0f);
        glVertex2f(200.0f, 52.0f);
        glVertex2f(0.0f, 52.0f);
        glEnd();

        glColor3f(0.30f, 0.55f, 0.22f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, 52.0f);
        glVertex2f(200.0f, 52.0f);
        glVertex2f(0.0f, 32.0f);
        glVertex2f(200.0f, 32.0f);
        glEnd();

        glColor3f(0.95f, 0.85f, 0.25f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        for (float x = 10.0f; x <= 190.0f; x += 14.0f) {
            glVertex2f(x, 41.4f);
            glVertex2f(x + 6.0f, 41.4f);
        }
        glEnd();

        drawRect(0.0f, 28.0f, 200.0f, 32.0f, 0.16f, 0.44f, 0.14f);
    }
}

// draw sun
void drawSun() {
    if (!isNight) {
        float cx = 178.0f, cy = 184.0f;
        drawCircle(cx, cy, 9.0f, 1.00f, 0.82f, 0.00f);

        glColor3f(1.00f, 0.85f, 0.00f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        for (int i = 0; i < 12; i++) {
            float a = i * 30.0f * 3.14159f / 180.0f;
            float x1 = cx + cos(a) * 11.0f;
            float y1 = cy + sin(a) * 11.0f;
            float x2 = cx + cos(a) * 19.0f;
            float y2 = cy + sin(a) * 19.0f;
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
        glEnd();
    }
}

// draw tree
void drawTree(float bx, float by) {
    if (isNight) {
        drawRect(bx - 2.0f, by, bx + 2.0f, by + 15.0f, 0.20f, 0.12f, 0.05f);
        drawCircle(bx, by + 26.0f, 8.0f, 0.06f, 0.22f, 0.05f);
        drawCircle(bx - 4.0f, by + 21.0f, 7.0f, 0.08f, 0.22f, 0.07f);
        drawCircle(bx + 4.0f, by + 21.0f, 7.0f, 0.08f, 0.22f, 0.07f);
    } else {
        drawRect(bx - 2.0f, by, bx + 2.0f, by + 15.0f, 0.40f, 0.25f, 0.10f);
        drawCircle(bx, by + 26.0f, 8.0f, 0.10f, 0.55f, 0.12f);
        drawCircle(bx - 4.0f, by + 21.0f, 7.0f, 0.12f, 0.55f, 0.14f);
        drawCircle(bx + 4.0f, by + 21.0f, 7.0f, 0.12f, 0.55f, 0.14f);
    }
}

// draw brick house
void drawBrickHouse(float ox, float oy, float brickR, float brickG, float brickB, float roofR, float roofG, float roofB) {
    drawRect(ox, oy, ox + 28.0f, oy + 25.0f, brickR, brickG, brickB);

    glColor3f(brickR * 0.6f, brickG * 0.6f, brickB * 0.6f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (int row = 1; row <= 5; row++) {
        float yLine = oy + row * 5.0f;
        glVertex2f(ox, yLine);
        glVertex2f(ox + 28.0f, yLine);
    }
    glEnd();

    glBegin(GL_LINES);
    for (int row = 0; row < 5; row++) {
        float yBottom = oy + row * 5.0f;
        float yTop = yBottom + 5.0f;
        int brickOffset = (row % 2 == 0) ? 0 : 4;

        for (float x = ox + 2.0f + brickOffset; x < ox + 28.0f; x += 5.0f) {
            glVertex2f(x, yBottom);
            glVertex2f(x, yTop);
        }
    }
    glEnd();

    glColor3f(roofR, roofG, roofB);
    glBegin(GL_TRIANGLES);
    glVertex2f(ox - 3.0f, oy + 25.0f);
    glVertex2f(ox + 14.0f, oy + 45.0f);
    glVertex2f(ox + 31.0f, oy + 25.0f);
    glEnd();

    glColor3f(roofR * 0.7f, roofG * 0.7f, roofB * 0.7f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (int i = 1; i <= 4; i++) {
        float t = i / 5.0f;
        float leftX = (ox - 3.0f) * (1 - t) + (ox + 14.0f) * t;
        float rightX = (ox + 31.0f) * (1 - t) + (ox + 14.0f) * t;
        float y = oy + 25.0f + t * 20.0f;
        glVertex2f(leftX, y);
        glVertex2f(rightX, y);
    }
    glEnd();

    if (isNight) {
        drawRect(ox + 10.0f, oy, ox + 18.0f, oy + 12.0f, 0.35f, 0.22f, 0.15f);

        glColor3f(0.45f, 0.30f, 0.18f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 10.0f, oy);
        glVertex2f(ox + 18.0f, oy);
        glVertex2f(ox + 18.0f, oy + 12.0f);
        glVertex2f(ox + 10.0f, oy + 12.0f);
        glEnd();

        drawCircle(ox + 16.0f, oy + 6.0f, 0.4f, 0.85f, 0.70f, 0.20f);

        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 11.0f, oy + 1.0f);
        glVertex2f(ox + 14.0f, oy + 1.0f);
        glVertex2f(ox + 14.0f, oy + 5.0f);
        glVertex2f(ox + 11.0f, oy + 5.0f);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 14.0f, oy + 1.0f);
        glVertex2f(ox + 17.0f, oy + 1.0f);
        glVertex2f(ox + 17.0f, oy + 5.0f);
        glVertex2f(ox + 14.0f, oy + 5.0f);
        glEnd();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.00f, 0.85f, 0.45f, 0.70f);
        drawRect(ox + 3.0f, oy + 10.0f, ox + 8.0f, oy + 18.0f, 1.00f, 0.85f, 0.45f);
        drawRect(ox + 20.0f, oy + 10.0f, ox + 25.0f, oy + 18.0f, 1.00f, 0.85f, 0.45f);
        glDisable(GL_BLEND);

        glColor3f(0.40f, 0.35f, 0.30f);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 3.0f, oy + 10.0f);
        glVertex2f(ox + 8.0f, oy + 10.0f);
        glVertex2f(ox + 8.0f, oy + 18.0f);
        glVertex2f(ox + 3.0f, oy + 18.0f);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 20.0f, oy + 10.0f);
        glVertex2f(ox + 25.0f, oy + 10.0f);
        glVertex2f(ox + 25.0f, oy + 18.0f);
        glVertex2f(ox + 20.0f, oy + 18.0f);
        glEnd();
    } else {
        drawRect(ox + 10.0f, oy, ox + 18.0f, oy + 12.0f, 0.55f, 0.35f, 0.22f);

        glColor3f(0.70f, 0.50f, 0.28f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 10.0f, oy);
        glVertex2f(ox + 18.0f, oy);
        glVertex2f(ox + 18.0f, oy + 12.0f);
        glVertex2f(ox + 10.0f, oy + 12.0f);
        glEnd();

        drawCircle(ox + 16.0f, oy + 6.0f, 0.4f, 0.85f, 0.70f, 0.20f);

        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 11.0f, oy + 1.0f);
        glVertex2f(ox + 14.0f, oy + 1.0f);
        glVertex2f(ox + 14.0f, oy + 5.0f);
        glVertex2f(ox + 11.0f, oy + 5.0f);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 14.0f, oy + 1.0f);
        glVertex2f(ox + 17.0f, oy + 1.0f);
        glVertex2f(ox + 17.0f, oy + 5.0f);
        glVertex2f(ox + 14.0f, oy + 5.0f);
        glEnd();

        drawRect(ox + 3.0f, oy + 10.0f, ox + 8.0f, oy + 18.0f, 0.70f, 0.85f, 1.00f);
        drawRect(ox + 20.0f, oy + 10.0f, ox + 25.0f, oy + 18.0f, 0.70f, 0.85f, 1.00f);

        glColor3f(0.45f, 0.35f, 0.25f);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 3.0f, oy + 10.0f);
        glVertex2f(ox + 8.0f, oy + 10.0f);
        glVertex2f(ox + 8.0f, oy + 18.0f);
        glVertex2f(ox + 3.0f, oy + 18.0f);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f(ox + 20.0f, oy + 10.0f);
        glVertex2f(ox + 25.0f, oy + 10.0f);
        glVertex2f(ox + 25.0f, oy + 18.0f);
        glVertex2f(ox + 20.0f, oy + 18.0f);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(ox + 5.5f, oy + 10.0f);
        glVertex2f(ox + 5.5f, oy + 18.0f);
        glVertex2f(ox + 3.0f, oy + 14.0f);
        glVertex2f(ox + 8.0f, oy + 14.0f);
        glVertex2f(ox + 22.5f, oy + 10.0f);
        glVertex2f(ox + 22.5f, oy + 18.0f);
        glVertex2f(ox + 20.0f, oy + 14.0f);
        glVertex2f(ox + 25.0f, oy + 14.0f);
        glEnd();
    }

    drawRect(ox + 22.0f, oy + 25.0f, ox + 26.0f, oy + 37.0f,
             isNight ? 0.50f : 0.75f, isNight ? 0.30f : 0.45f, isNight ? 0.25f : 0.40f);

    glColor3f(isNight ? 0.30f : 0.50f, isNight ? 0.20f : 0.35f, isNight ? 0.18f : 0.30f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 1; i <= 3; i++) {
        float yLine = oy + 25.0f + i * 4.0f;
        glVertex2f(ox + 22.0f, yLine);
        glVertex2f(ox + 26.0f, yLine);
    }
    glEnd();

    if (!isNight) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.60f, 0.60f, 0.65f, 0.40f);
        drawCircle(ox + 24.0f, oy + 38.0f, 2.0f, 0.60f, 0.60f, 0.65f);
        drawCircle(ox + 25.0f, oy + 40.0f, 1.5f, 0.55f, 0.55f, 0.60f);
        drawCircle(ox + 23.0f, oy + 41.0f, 1.0f, 0.50f, 0.50f, 0.55f);
        glDisable(GL_BLEND);
    }
}

// Original Brick House
void drawHouse(float ox, float oy) {
    if (isNight) {
        drawBrickHouse(ox, oy, 0.45f, 0.25f, 0.22f, 0.50f, 0.20f, 0.18f);
    } else {
        drawBrickHouse(ox, oy, 0.72f, 0.40f, 0.35f, 0.85f, 0.35f, 0.30f);
    }
}

// Black Brick House
void drawBlackBrickHouse(float ox, float oy) {
    if (isNight) {
        drawBrickHouse(ox, oy, 0.15f, 0.15f, 0.15f, 0.35f, 0.25f, 0.22f);
    } else {
        drawBrickHouse(ox, oy, 0.25f, 0.25f, 0.25f, 0.55f, 0.45f, 0.40f);
    }
}

// hospital
void drawHospital(float ox, float oy) {
    float floorHeight = 12.0f;
    float buildingWidth = 28.0f;
    float buildingHeight = 5.0f * floorHeight;

    if (isNight) {
        drawRect(ox, oy, ox + buildingWidth, oy + buildingHeight, 0.35f, 0.35f, 0.38f);

        glColor3f(0.25f, 0.25f, 0.28f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        for (int floor = 1; floor <= 4; floor++) {
            float yLine = oy + floor * floorHeight;
            glVertex2f(ox, yLine);
            glVertex2f(ox + buildingWidth, yLine);
        }
        glEnd();

        for (int floor = 0; floor < 5; floor++) {
            float floorY = oy + floor * floorHeight + 2.0f;
            for (int col = 0; col < 3; col++) {
                float wx = ox + 4.0f + col * 8.4f;
                float wy = floorY;

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f(1.00f, 0.85f, 0.45f, 0.70f);
                drawRect(wx, wy, wx + 5.0f, wy + 4.0f, 1.00f, 0.85f, 0.45f);
                glDisable(GL_BLEND);

                glColor3f(0.40f, 0.40f, 0.45f);
                glLineWidth(1.0f);
                glBegin(GL_LINE_LOOP);
                glVertex2f(wx, wy);
                glVertex2f(wx + 5.0f, wy);
                glVertex2f(wx + 5.0f, wy + 4.0f);
                glVertex2f(wx, wy + 4.0f);
                glEnd();

                glBegin(GL_LINES);
                glVertex2f(wx + 2.5f, wy);
                glVertex2f(wx + 2.5f, wy + 4.0f);
                glVertex2f(wx, wy + 2.0f);
                glVertex2f(wx + 5.0f, wy + 2.0f);
                glEnd();
            }
        }

        drawRect(ox + 10.4f, oy, ox + 17.6f, oy + 9.0f, 0.30f, 0.35f, 0.40f);
    } else {
        drawRect(ox, oy, ox + buildingWidth, oy + buildingHeight, 0.95f, 0.95f, 0.95f);

        glColor3f(0.50f, 0.50f, 0.55f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        for (int floor = 1; floor <= 4; floor++) {
            float yLine = oy + floor * floorHeight;
            glVertex2f(ox, yLine);
            glVertex2f(ox + buildingWidth, yLine);
        }
        glEnd();

        for (int floor = 0; floor < 5; floor++) {
            float floorY = oy + floor * floorHeight + 2.0f;
            for (int col = 0; col < 3; col++) {
                float wx = ox + 4.0f + col * 8.4f;
                float wy = floorY;

                drawRect(wx, wy, wx + 5.0f, wy + 4.0f, 0.70f, 0.85f, 1.00f);
                glColor3f(0.35f, 0.35f, 0.40f);
                glLineWidth(1.0f);
                glBegin(GL_LINE_LOOP);
                glVertex2f(wx, wy);
                glVertex2f(wx + 5.0f, wy);
                glVertex2f(wx + 5.0f, wy + 4.0f);
                glVertex2f(wx, wy + 4.0f);
                glEnd();

                glBegin(GL_LINES);
                glVertex2f(wx + 2.5f, wy);
                glVertex2f(wx + 2.5f, wy + 4.0f);
                glVertex2f(wx, wy + 2.0f);
                glVertex2f(wx + 5.0f, wy + 2.0f);
                glEnd();
            }
        }

        drawRect(ox + 10.4f, oy, ox + 17.6f, oy + 9.0f, 0.45f, 0.65f, 0.80f);
    }

    glColor3f(0.40f, 0.40f, 0.40f);
    glLineWidth(1.2f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(ox + 10.4f, oy);
    glVertex2f(ox + 17.6f, oy);
    glVertex2f(ox + 17.6f, oy + 9.0f);
    glVertex2f(ox + 10.4f, oy + 9.0f);
    glEnd();

    drawCircle(ox + 16.4f, oy + 4.5f, 0.4f, 0.80f, 0.70f, 0.20f);

    glColor3f(0.50f, 0.50f, 0.55f);
    glLineWidth(1.2f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 180; i += 15) {
        float angle = i * 3.14159f / 180.0f;
        float dx = 3.6f * cos(angle);
        float dy = 3.6f * sin(angle);
        glVertex2f(ox + 14.0f + dx, oy + 9.0f + dy);
    }
    glEnd();

    drawRect(ox - 1.0f, oy + buildingHeight, ox + buildingWidth + 1.0f, oy + buildingHeight + 4.0f,
             isNight ? 0.40f : 0.65f, isNight ? 0.40f : 0.65f, isNight ? 0.42f : 0.70f);

    glColor3f(0.85f, 0.00f, 0.00f);
    glLineWidth(3.0f);
    float crossX = ox + buildingWidth / 2.0f;
    glBegin(GL_LINES);
    glVertex2f(crossX, oy + buildingHeight + 4.0f);
    glVertex2f(crossX, oy + buildingHeight + 12.0f);
    glVertex2f(crossX - 2.5f, oy + buildingHeight + 8.0f);
    glVertex2f(crossX + 2.5f, oy + buildingHeight + 8.0f);
    glEnd();

    drawRect(ox + 6.0f, oy + 9.0f, ox + 22.0f, oy + 12.0f,
             isNight ? 0.35f : 0.55f, isNight ? 0.35f : 0.55f, isNight ? 0.38f : 0.60f);

    drawRect(ox + 7.0f, oy + 9.0f, ox + 8.0f, oy + 12.0f, 0.50f, 0.50f, 0.50f);
    drawRect(ox + 20.0f, oy + 9.0f, ox + 21.0f, oy + 12.0f, 0.50f, 0.50f, 0.50f);
}

// shop
void drawShop(float ox, float oy) {
    if (isNight) {
        drawRect(ox, oy, ox + 24.0f, oy + 20.0f, 0.45f, 0.38f, 0.25f);
        drawRect(ox - 1.0f, oy + 20.0f, ox + 25.0f, oy + 23.0f, 0.30f, 0.20f, 0.12f);
        drawRect(ox + 2.0f, oy + 16.0f, ox + 22.0f, oy + 20.0f, 0.55f, 0.30f, 0.10f);

        glColor3f(0.90f, 0.85f, 0.50f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(ox + 3.6f, oy + 17.4f);
        glVertex2f(ox + 11.0f, oy + 17.4f);
        glVertex2f(ox + 3.6f, oy + 18.6f);
        glVertex2f(ox + 10.0f, oy + 18.6f);
        glVertex2f(ox + 13.0f, oy + 17.4f);
        glVertex2f(ox + 20.4f, oy + 17.4f);
        glVertex2f(ox + 13.0f, oy + 18.6f);
        glVertex2f(ox + 19.6f, oy + 18.6f);
        glEnd();

        glColor3f(0.55f, 0.20f, 0.18f);
        glBegin(GL_QUADS);
        glVertex2f(ox - 2.0f, oy + 15.0f);
        glVertex2f(ox + 26.0f, oy + 15.0f);
        glVertex2f(ox + 24.0f, oy + 11.6f);
        glVertex2f(ox + 0.4f, oy + 11.6f);
        glEnd();

        glColor3f(0.70f, 0.35f, 0.30f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        for (int i = 0; i < 6; i++) {
            float xa = ox + 2.8f + i * 3.8f;
            float xb = ox + 2.0f + i * 3.8f;
            glVertex2f(xa, oy + 15.0f);
            glVertex2f(xb, oy + 11.6f);
        }
        glEnd();

        drawRect(ox + 1.0f, oy, ox + 23.0f, oy + 11.6f, 0.12f, 0.10f, 0.08f);
        drawRect(ox + 1.0f, oy + 5.6f, ox + 23.0f, oy + 7.2f, 0.35f, 0.22f, 0.10f);

        float itemColors[5][3] = {
            {0.85f*0.55f, 0.25f*0.55f, 0.20f*0.55f},
            {0.30f*0.55f, 0.65f*0.55f, 0.30f*0.55f},
            {0.90f*0.55f, 0.75f*0.55f, 0.15f*0.55f},
            {0.20f*0.55f, 0.45f*0.55f, 0.80f*0.55f},
            {0.80f*0.55f, 0.50f*0.55f, 0.20f*0.55f},
        };
        for (int k = 0; k < 5; k++) {
            float ix = ox + 2.0f + k * 4.2f;
            drawRect(ix, oy + 7.2f, ix + 2.8f, oy + 11.2f,
                     itemColors[k][0], itemColors[k][1], itemColors[k][2]);
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.00f, 0.80f, 0.30f, 0.25f);
        glBegin(GL_QUADS);
        glVertex2f(ox + 1.0f, oy);
        glVertex2f(ox + 23.0f, oy);
        glVertex2f(ox + 23.0f, oy + 11.6f);
        glVertex2f(ox + 1.0f, oy + 11.6f);
        glEnd();
        glDisable(GL_BLEND);

        drawRect(ox + 1.0f, oy, ox + 2.4f, oy + 11.6f, 0.30f, 0.20f, 0.10f);
        drawRect(ox + 21.6f, oy, ox + 23.0f, oy + 11.6f, 0.30f, 0.20f, 0.10f);
        drawRect(ox + 2.0f, oy - 2.0f, ox + 22.0f, oy, 0.35f, 0.32f, 0.22f);
    } else {
        drawRect(ox, oy, ox + 24.0f, oy + 20.0f, 0.92f, 0.80f, 0.50f);
        drawRect(ox - 1.0f, oy + 20.0f, ox + 25.0f, oy + 23.0f, 0.60f, 0.35f, 0.18f);
        drawRect(ox + 2.0f, oy + 16.0f, ox + 22.0f, oy + 20.0f, 0.95f, 0.55f, 0.10f);

        glColor3f(1.00f, 0.95f, 0.80f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(ox + 3.6f, oy + 17.4f);
        glVertex2f(ox + 11.0f, oy + 17.4f);
        glVertex2f(ox + 3.6f, oy + 18.6f);
        glVertex2f(ox + 10.0f, oy + 18.6f);
        glVertex2f(ox + 13.0f, oy + 17.4f);
        glVertex2f(ox + 20.4f, oy + 17.4f);
        glVertex2f(ox + 13.0f, oy + 18.6f);
        glVertex2f(ox + 19.6f, oy + 18.6f);
        glEnd();

        glColor3f(0.85f, 0.20f, 0.18f);
        glBegin(GL_QUADS);
        glVertex2f(ox - 2.0f, oy + 15.0f);
        glVertex2f(ox + 26.0f, oy + 15.0f);
        glVertex2f(ox + 24.0f, oy + 11.6f);
        glVertex2f(ox + 0.4f, oy + 11.6f);
        glEnd();

        glColor3f(1.00f, 0.45f, 0.30f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        for (int i = 0; i < 6; i++) {
            float xa = ox + 2.8f + i * 3.8f;
            float xb = ox + 2.0f + i * 3.8f;
            glVertex2f(xa, oy + 15.0f);
            glVertex2f(xb, oy + 11.6f);
        }
        glEnd();

        drawRect(ox + 1.0f, oy, ox + 23.0f, oy + 11.6f, 0.25f, 0.22f, 0.18f);
        drawRect(ox + 1.0f, oy + 5.6f, ox + 23.0f, oy + 7.2f, 0.65f, 0.42f, 0.22f);

        float itemColors[5][3] = {
            {0.85f, 0.25f, 0.20f},
            {0.30f, 0.65f, 0.30f},
            {0.90f, 0.75f, 0.15f},
            {0.20f, 0.45f, 0.80f},
            {0.80f, 0.50f, 0.20f},
        };
        for (int k = 0; k < 5; k++) {
            float ix = ox + 2.0f + k * 4.2f;
            drawRect(ix, oy + 7.2f, ix + 2.8f, oy + 11.2f,
                     itemColors[k][0], itemColors[k][1], itemColors[k][2]);
        }

        drawRect(ox + 1.0f, oy, ox + 2.4f, oy + 11.6f, 0.55f, 0.38f, 0.20f);
        drawRect(ox + 21.6f, oy, ox + 23.0f, oy + 11.6f, 0.55f, 0.38f, 0.20f);
        drawRect(ox + 2.0f, oy - 2.0f, ox + 22.0f, oy, 0.65f, 0.60f, 0.45f);
    }
}

// blinking bulb
void drawPole(float px, float py) {
    if (isNight) {
        glColor3f(0.15f, 0.10f, 0.05f);
        glLineWidth(5.0f);
        glBegin(GL_LINES);
        glVertex2f(px, py);
        glVertex2f(px, py + 42.0f);
        glEnd();

        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(px - 6.0f, py + 38.0f);
        glVertex2f(px + 6.0f, py + 38.0f);
        glEnd();

        if (bulbState) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.00f, 0.95f, 0.40f, 0.50f);
            drawCircle(px, py + 30.0f, 5.4f, 1.00f, 0.95f, 0.40f);
            glDisable(GL_BLEND);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.00f, 0.90f, 0.30f, 0.80f);
            drawCircle(px, py + 30.0f, 3.2f, 1.00f, 0.90f, 0.30f);
            glDisable(GL_BLEND);

            drawCircle(px, py + 30.0f, 1.8f, 1.00f, 0.95f, 0.25f);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.00f, 0.90f, 0.50f, 0.20f);
            glBegin(GL_TRIANGLES);
            glVertex2f(px - 10.0f, py + 28.0f);
            glVertex2f(px, py - 25.0f);
            glVertex2f(px + 10.0f, py + 28.0f);
            glEnd();
            glDisable(GL_BLEND);
        } else {
            drawCircle(px, py + 30.0f, 1.8f, 0.45f, 0.40f, 0.18f);
        }
    } else {
        glColor3f(0.25f, 0.18f, 0.08f);
        glLineWidth(5.0f);
        glBegin(GL_LINES);
        glVertex2f(px, py);
        glVertex2f(px, py + 42.0f);
        glEnd();

        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(px - 6.0f, py + 38.0f);
        glVertex2f(px + 6.0f, py + 38.0f);
        glEnd();

        drawCircle(px, py + 30.0f, 1.8f, 0.55f, 0.50f, 0.25f);
    }
}

// draw rickshaw
void drawRickshaw(float x, float y) {
    glColor3f(1.00f, 0.85f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(x - 8.0f, y + 8.0f);
    glVertex2f(x + 8.0f, y + 8.0f);
    glVertex2f(x + 8.0f, y + 20.0f);
    glVertex2f(x - 8.0f, y + 20.0f);
    glEnd();

    glColor3f(0.80f, 0.60f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(x - 10.0f, y + 20.0f);
    glVertex2f(x + 10.0f, y + 20.0f);
    glVertex2f(x + 8.0f, y + 26.0f);
    glVertex2f(x - 8.0f, y + 26.0f);
    glEnd();

    glColor3f(0.90f, 0.70f, 0.20f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 5.0f, y + 26.0f);
    glVertex2f(x + 5.0f, y + 26.0f);
    glVertex2f(x, y + 30.0f);
    glEnd();

    drawRect(x - 7.0f, y + 8.0f, x + 7.0f, y + 12.0f, 0.60f, 0.30f, 0.10f);
    drawRect(x - 7.0f, y + 12.0f, x - 4.0f, y + 19.0f, 0.70f, 0.35f, 0.12f);
    drawRect(x - 3.0f, y + 13.0f, x + 3.0f, y + 18.0f, 0.20f, 0.70f, 0.30f);

    drawCircle(x + 11.0f, y + 3.0f, 4.4f, 0.20f, 0.20f, 0.20f);
    drawCircle(x + 11.0f, y + 3.0f, 3.0f, 0.60f, 0.60f, 0.60f);
    drawCircle(x + 11.0f, y + 3.0f, 1.2f, 0.80f, 0.80f, 0.80f);

    glColor3f(0.30f, 0.30f, 0.30f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float angle = i * 45.0f * 3.14159f / 180.0f;
        float dx = cos(angle) * 2.4f;
        float dy = sin(angle) * 2.4f;
        glVertex2f(x + 11.0f, y + 3.0f);
        glVertex2f(x + 11.0f + dx, y + 3.0f + dy);
    }
    glEnd();

    drawCircle(x - 7.0f, y + 3.0f, 3.8f, 0.20f, 0.20f, 0.20f);
    drawCircle(x - 7.0f, y + 3.0f, 2.4f, 0.60f, 0.60f, 0.60f);
    drawCircle(x - 7.0f, y + 3.0f, 1.0f, 0.80f, 0.80f, 0.80f);

    glColor3f(0.30f, 0.30f, 0.30f);
    glBegin(GL_LINES);
    for (int i = 0; i < 6; i++) {
        float angle = i * 60.0f * 3.14159f / 180.0f;
        float dx = cos(angle) * 2.0f;
        float dy = sin(angle) * 2.0f;
        glVertex2f(x - 7.0f, y + 3.0f);
        glVertex2f(x - 7.0f + dx, y + 3.0f + dy);
    }
    glEnd();

    glColor3f(0.40f, 0.40f, 0.40f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(x - 6.0f, y + 6.0f);
    glVertex2f(x + 10.0f, y + 6.0f);
    glEnd();

    drawRect(x + 4.0f, y + 4.0f, x + 9.0f, y + 7.0f, 0.50f, 0.50f, 0.50f);

    glColor3f(1.00f, 0.50f, 0.00f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(x - 8.0f, y + 25.0f);
    glVertex2f(x - 10.0f, y + 28.0f);
    glVertex2f(x + 8.0f, y + 25.0f);
    glVertex2f(x + 10.0f, y + 28.0f);
    glEnd();
}

// Main display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glClearColor(0.53f, 0.81f, 0.98f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawClouds();
    drawBirds();
    drawMountains();
    drawGround();
    drawRiver();
    drawSun();

    drawBoat(boatX, 13.0f);

    drawTree(12.0f, 95.0f);
    drawTree(55.0f, 92.0f);
    drawTree(135.0f, 92.0f);
    drawTree(185.0f, 95.0f);
    drawTree(30.0f, 110.0f);

    drawHouse(8.0f, 95.0f);
    drawHospital(80.0f, 95.0f);
    drawShop(116.0f, 95.0f);
    drawBlackBrickHouse(148.0f, 95.0f);
    drawPole(42.0f, 94.0f);
    drawRickshaw(rickshawX, 44.0f);

    glutSwapBuffers();
}

// Timer function for animation
void timer(int value) {
    if (rickshawMoving) {
        rickshawX += rickshawSpeed;
        if (rickshawX > 220.0f) rickshawX = -40.0f;
    }

    if (boatMoving) {
        boatX += boatSpeed;
        if (boatX > 220.0f) boatX = -30.0f;
    }

    bulbBlink += 0.025f;
    if (bulbBlink >= 1.0f) {
        bulbBlink = 0.0f;
        bulbState = !bulbState;
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

// Mouse click handler
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            isNight = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            isNight = true;
        }
    }
    glutPostRedisplay();
}

// Keyboard handler
void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
            break;
        case 'r':
        case 'R':
            rickshawMoving = true;
            break;
        case 'w':
        case 'W':
            rickshawMoving = false;
            break;
        case 'b':
        case 'B':
            boatMoving = true;
            break;
        case 't':
        case 'T':
            boatMoving = false;
            break;
    }
    glutPostRedisplay();
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.53f, 0.81f, 0.98f, 1.00f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 200.0, 0.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    srand(time(NULL));
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(80, 60);
    glutCreateWindow("Bangladesh Current Village");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
