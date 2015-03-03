/*
 * Monica Lozano A01138967
 * Andres Lopez  A01138686
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"

/* GLUT callback Handlers */

Deck deck;
Hand dealer;
Hand player;
bool in_play = false;
bool lost = false;
int contDealer = 0;
int contPlayer = 0;
string autores = "Autores: Monica Lozano A01138967 y Andres Lopez A01138686";
string name = "Blackjack";
GLubyte chDealer[6] = {'D', 'e', 'a', 'l', 'e', 'r'};
GLubyte chPlayer[6] = {'P', 'l', 'a', 'y', 'e', 'r'};
GLubyte points[10] = {'P', 'o', 'i', 'n', 't', 's', ' ', '='};
GLubyte lose[10] = {'Y', 'o', 'u', ' ', 'L', 'o', 's', 'e', '!'};
GLubyte win[10] = {'Y', 'o', 'u', ' ', 'W', 'i', 'n', '!'};
GLubyte num[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
GLint xRaster = 25, yRaster = -19;

static void resize(int width, int height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( 0,width, 0,height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3ub(1,255,255);


    glRasterPos2f(20, 20);
    for (string::iterator i = autores.begin(); i != autores.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    glRasterPos2f(300, 420);
    for (string::iterator i = name.begin(); i != name.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    //dealer name
    glRasterPos2f(50,200);
    int i;
    for (i=0; i<6; i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, chDealer[i]);
    }
    //dealer cards

    dealer.draw(150,200, !in_play);

    //player name
    glColor3ub(1,255,255);
    glRasterPos2f(50,100);
    for (i=0; i<6; i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, chPlayer[i]);
    }
    //player cards
    player.draw(150,100, true);

    //loser message
    if(lost){
        glRasterPos2f(200,400);
        for (i=0; i<10; i++){
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, lose[i]);
        }
    }

    //Game points
    if(!in_play && (contDealer > 0 || contPlayer > 0)){
        //dealer points
        glRasterPos2f(460,200);
        for (i=0; i<7; i++){
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, points[i]);
        }
        for (i=0; i<6; i++){
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, chDealer[i]);
        }
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, points[7]);
        glRasterPos2f(600,200);
        int aux = dealer.getValue();
        do{
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, num[(aux % 10)]);
            aux = aux/10;
            glRasterPos2i(600 -13, 200);
        }while(aux > 0);

        //player points
        glRasterPos2f(460,100);
        for (i=0; i<7; i++){
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, points[i]);
        }
        for (i=0; i<6; i++){
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, chPlayer[i]);
        }
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, points[7]);
        glRasterPos2f(600,100);
        aux = player.getValue();
        do{
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, num[(aux % 10)]);
            aux = aux/10;
            glRasterPos2i(600 -13, 100);
        }while(aux > 0);

    }
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            break;

        case 'd':
        case 'D':
            if(!in_play){
                lost = false;
                in_play = true;
                deck = Deck();
                deck.shuffle();
                dealer = Hand();
                player = Hand();
                //give two cards to each player
                dealer.addCard(deck.dealCard());
                player.addCard(deck.dealCard());
                dealer.addCard(deck.dealCard());
                player.addCard(deck.dealCard());

                cout << "DEALER" << endl;
                dealer.str();
                cout << endl;
                cout << "PLAYER" << endl;
                player.str();
                cout << endl;
            } else {
                contDealer++;
                lost = true;
                in_play = false;
            }


            break;

        case 'h':
        case 'H':
            if(in_play){
                if(player.getValue() <= 21){
                    player.addCard(deck.dealCard());
                    if(player.getValue() > 21){
                        player.str();
                        cout << endl;
                        cout << "YOU LOSE!" << endl;
                        contDealer++;
                        lost = true;
                        in_play = false;
                    }
                } else {
                    player.str();
                    cout << endl;
                    cout << "YOU LOSE!" << endl;
                    contDealer++;
                    lost = true;
                    in_play = false;
                }
            }
            break;

        case 's':
        case 'S':
            if(!in_play){
                cout << "DUDE YOU LOST!" << endl;
            } else {
                while(dealer.getValue() < 17){
                    dealer.addCard(deck.dealCard());
                }
                if(dealer.getValue() > 21){
                    contPlayer++;
                    cout << "YOU WIN!" << endl;
                    cout << "DEALER OVER 21!" << endl;
                } else if(player.getValue() > dealer.getValue()){
                    cout << "YOU WIN!" << endl;
                    contPlayer++;
                } else {
                    contDealer++;
                    lost = true;
                    cout << "YOU LOSE!" << endl;
                }
                  cout << "DEALER"<< dealer.getValue() << endl;
                    dealer.str();
                    cout << endl;
                    cout << "PLAYER" << player.getValue() << endl;
                    player.str();
                    cout << endl;
                in_play = false;
            }
            break;
    }

    glutPostRedisplay();
}

void init()
{
    glLoadIdentity();
    gluOrtho2D( 0,480, 0,640);

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glClearColor(0,0,0,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
