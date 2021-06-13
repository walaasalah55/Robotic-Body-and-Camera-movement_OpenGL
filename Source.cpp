#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14

static int head = 0, trunk = 0, leftleg = 0, leftlegz = 0, lowerleftleg = 0, leftfoot = 0, rightleg = 0, rightlegz = 0, lowerrightleg = 0, rightfoot = 0,
leftarm = 0, leftarmz = 0, leftelbow = 0, rightarmz = 0, rightarm = 0, rightelbow = 0, rightelbowz = 0, leftelbowz = 0, lfingerBase1 = 0, rfingerBase1 = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */
double eye[] = { 0.0, 0.0, 10.0 };
double center[] = { 0.0 ,0.0, 0.0 };
double up[] = { 0.0, 1.0, 0.0 };


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);                                       // new
    gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);     // new
}


void rotatePoint(double a[], double theta, double p[])  // up , angle ,eye
{
    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}


void lookRight()
{
    rotatePoint(up, PI / 12, eye);
}

void lookLeft()
{
    rotatePoint(up, -PI / 12, eye);
}


void lookUp()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI / 12, eye);
    rotatePoint(horizontal, PI / 12, up);
}

void lookDown()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI / 12, eye);
    rotatePoint(horizontal, -PI / 12, up);
}
void moveForward()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    float speed = 0.1;
    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;
}

void moveBackword()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    float speed = 0.1;
    eye[0] -= direction[0] * speed;
    eye[1] -= direction[1] * speed;
    eye[2] -= direction[2] * speed;

    center[0] -= direction[0] * speed;
    center[1] -= direction[1] * speed;
    center[2] -= direction[2] * speed;
}

void reset()
{
    double e[] = { 0.0, 0.0, 7.0 };
    double c[] = { 0.0, 1, 0.0 };
    double u[] = { 0.0, 1.0, 0.0 };
    for (int i = 0; i < 3; i++)
    {
        eye[i] = e[i];
        center[i] = c[i];
        up[i] = u[i];
    }
}




void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        lookLeft();
        break;
    case GLUT_KEY_RIGHT:
        lookRight();
        break;
    case GLUT_KEY_UP:
        lookUp();
        break;
    case GLUT_KEY_DOWN:
        lookDown();
        break;
    }
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        up[0], up[1], up[2]);
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, .8, 0.0);
    //head
    glPushMatrix();
    glTranslatef(0.0, 1.9, 0.0);
    glColor3f(2.0, 2.0, 0.0);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
    glPopMatrix();
    //trunk
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glColor3f(0.1, 1.0, 0.5);
    glScalef(1.4, 4.0, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    //right arm
    glPushMatrix();
    glTranslatef(-0.8, 1.9, 0);
    glRotatef(rightarmz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightarm, 1.0, 0.0, 0.0);
    glTranslatef(0, -0.45, 0);
    glColor3f(0.1, 1.0, 1.0);
    glPushMatrix();
    glScalef(0.2, 1.0, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    //right elbow 
    glTranslatef(0, -0.45, 0.0);
    glRotatef((GLfloat)rightelbowz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightelbow, 1.0, 0.0, 0.0);
    glTranslatef(0, -0.55, 0.0);
    glColor3f(2.0, 2.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 1.0, 0.5);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 1 
    glRotatef((GLfloat)rfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(-0.05, -0.65, 0.2);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 2 
    glRotatef((GLfloat)rfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -0.13);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 3
    glRotatef((GLfloat)rfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -0.13);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 4 
    glRotatef((GLfloat)rfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -0.13);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 5
    glRotatef((GLfloat)rfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0.1, 0, 0.13);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    //left arm
    glPushMatrix();
    glTranslatef(0.8, 1.9, 0);
    glRotatef(leftarmz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftarm, 1.0, 0.0, 0.0);
    glTranslatef(0, -0.45, 0);
    glColor3f(0.1, 1.0, 1.0);
    glPushMatrix();
    glScalef(0.2, 1.0, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    //left elbow 
    glTranslatef(0, -0.5, 0.0);
    glRotatef((GLfloat)leftelbowz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftelbow, 1.0, 0.0, 0.0);
    glTranslatef(0, -0.5, 0.0);
    glColor3f(2.0, 2.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 1.0, 0.5);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 1 
    glRotatef((GLfloat)lfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0.05, -0.65, 0.2);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 2 
    glRotatef((GLfloat)lfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -0.13);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 3
    glRotatef((GLfloat)lfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -0.13);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 4 
    glRotatef((GLfloat)lfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0, 0, -0.13);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    //Draw finger flang 5
    glRotatef((GLfloat)lfingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(-0.1, 0, 0.13);
    glPushMatrix();
    glScalef(0.08, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();

    glPopMatrix();

    //right leg
    glPushMatrix();
    glTranslatef(-0.537, -2, 0);
    glRotatef((GLfloat)rightlegz, 0.0, 0.0, 1.0);
    glRotatef(rightleg, 1.0, 0.0, 0.0);
    glTranslatef(0.07, -0.95, 0);
    glColor3f(0.1, 0.5, 1.0);
    glPushMatrix();
    glScalef(0.466, 1.8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    //right lowerleg 
    glTranslatef(0, -.825, 0.0);
    glRotatef((GLfloat)lowerrightleg, 1.0, 0.0, 0.0);
    glTranslatef(0, -.825, 0.0);
    glPushMatrix();
    glColor3f(2.0, 2.0, 0.0);
    glScalef(0.5, 1.5, 0.5);
    glutWireCube(1);
    glPopMatrix();
    //right foot
    glTranslatef(0, -1, 0);
    glPushMatrix();
    glScalef(0.5, .5, 1.5);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();



    //left leg
    glPushMatrix();
    glTranslatef(0.537, -2, 0);
    glRotatef((GLfloat)leftlegz, 0.0, 0.0, 1.0);
    glRotatef(leftleg, 1.0, 0.0, 0.0);
    glTranslatef(-0.07, -0.95, 0);
    glColor3f(0.1, 0.5, 1.0);
    glPushMatrix();
    glScalef(0.466, 1.8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    //left lowerleg 
    glTranslatef(0, -.825, 0.0);
    glRotatef((GLfloat)lowerleftleg, 1.0, 0.0, 0.0);
    glTranslatef(0, -.825, 0.0);
    glColor3f(2.0, 2.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.5, 0.5);
    glutWireCube(1);
    glPopMatrix();
    //left foot
    glTranslatef(0, -1, 0);
    glPushMatrix();
    glScalef(0.5, .5, 1.5);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
    glPopMatrix();
    glPopMatrix();
}

void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'f':
        moveForward();
        break;
    case 'b':
        moveBackword();
        break;
    case 'r':
        reset();
        break;
        //right arm
    case 'z':
        if (rightarm < 180)
            rightarm = (rightarm + 5) % 360;
        glutPostRedisplay();
        break;

    case 'Z':
        if (rightarm > -90)
            rightarm = (rightarm - 5) % 360;
        glutPostRedisplay();
        break;
    case 'x':
        if (rightarmz < 180)
            rightarmz = (rightarmz + 5) % 360;
        glutPostRedisplay();
        break;
    case 'X':
        if (rightarmz > -90)
            rightarmz = (rightarmz - 5) % 360;
        glutPostRedisplay();
        break;
    case 'c':
        if (rightelbow < 90)
            rightelbow = (rightelbow + 5) % 180;
        glutPostRedisplay();
        break;
    case 'C':
        if (rightelbow > 0)
            rightelbow = (rightelbow - 5) % 180;
        glutPostRedisplay();
        break;

    case 'v':
        if (rightelbowz < 90)
            rightelbowz = (rightelbowz + 5) % 180;
        glutPostRedisplay();
        break;
    case 'V':
        if (rightelbowz > 0)
            rightelbowz = (rightelbowz - 5) % 180;
        glutPostRedisplay();
        break;

    case 'N':
        if (rfingerBase1 > -30)
            rfingerBase1 = (rfingerBase1 - 5) % 360;
        glutPostRedisplay();
        break;
    case 'n':
        if (rfingerBase1 < 30)
            rfingerBase1 = (rfingerBase1 + 5) % 360;
        glutPostRedisplay();
        break;
        //left arm
    case 'h':
        if (leftarm < 180)
            leftarm = (leftarm + 5) % 360;
        glutPostRedisplay();
        break;

    case 'H':
        if (leftarm > -90)
            leftarm = (leftarm - 5) % 360;
        glutPostRedisplay();
        break;
    case 'j':
        if (leftarmz < 180)
            leftarmz = (leftarmz + 5) % 360;
        glutPostRedisplay();
        break;
    case 'J':
        if (leftarmz > -90)
            leftarmz = (leftarmz - 5) % 360;
        glutPostRedisplay();
        break;
    case 'k':
        if (leftelbow < 90)
            leftelbow = (leftelbow + 5) % 180;
        glutPostRedisplay();
        break;
    case 'K':
        if (leftelbow > 0)
            leftelbow = (leftelbow - 5) % 180;
        glutPostRedisplay();
        break;
    case 'l':
        if (leftelbowz < 90)
            leftelbowz = (leftelbowz + 5) % 180;
        glutPostRedisplay();
        break;
    case 'L':
        if (leftelbowz > 0)
            leftelbowz = (leftelbowz - 5) % 180;
        glutPostRedisplay();
        break;

    case 'M':
        if (lfingerBase1 > -30)
            lfingerBase1 = (lfingerBase1 - 5) % 360;
        glutPostRedisplay();
        break;
    case 'm':
        if (lfingerBase1 < 30)
            lfingerBase1 = (lfingerBase1 + 5) % 360;
        glutPostRedisplay();
        break;
        //right leg
    case 'q':
        if (rightleg > -80)
            rightleg = (rightleg - 5) % 360;
        glutPostRedisplay();

        break;

    case 'Q':
        if (rightleg < 80)
            rightleg = (rightleg + 5) % 360;
        glutPostRedisplay();

        break;
    case 'w':
        if (rightlegz > -80)
            rightlegz = (rightlegz - 5) % 360;
        glutPostRedisplay();

        break;

    case 'W':
        if (rightlegz < 80)
            rightlegz = (rightlegz + 5) % 360;
        glutPostRedisplay();

        break;

    case 'e':
        if (lowerrightleg > -30)
            lowerrightleg = (lowerrightleg - 5) % 360;
        glutPostRedisplay();

        break;

    case 'E':
        if (lowerrightleg < 80)
            lowerrightleg = (lowerrightleg + 5) % 360;
        glutPostRedisplay();

        break;
        //left leg
    case 'i':
        if (leftleg > -80)
            leftleg = (leftleg - 5) % 360;
        glutPostRedisplay();

        break;

    case 'I':
        if (leftleg < 80)
            leftleg = (leftleg + 5) % 360;
        glutPostRedisplay();

        break;
    case 'o':
        if (leftlegz > -80)
            leftlegz = (leftlegz - 5) % 360;
        glutPostRedisplay();

        break;

    case 'O':
        if (leftlegz < 80)
            leftlegz = (leftlegz + 5) % 360;
        glutPostRedisplay();

        break;

    case 'p':
        if (lowerleftleg > -30)
            lowerleftleg = (lowerleftleg - 5) % 360;
        glutPostRedisplay();

        break;

    case 'P':
        if (lowerleftleg < 80)
            lowerleftleg = (lowerleftleg + 5) % 360;
        glutPostRedisplay();

        break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}


static void motion(int x, int y)
{
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1500, 1500);
    glutInitWindowPosition(5, 35);
    glutCreateWindow(argv[0]);
    init();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyBoard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}