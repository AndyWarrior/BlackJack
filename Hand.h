#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED
//
//  Hand.h
//  BlackJack
//
//  Created by Ma. Guadalupe Roque on 29/07/14.
//  Copyright (c) 2014 Ma. Guadalupe Roque. All rights reserved.
//

#include <iostream>
#include "Card.h"

class Hand
{
    public:
        Hand();
        char getSuit(int k); //Retorna el suit de la carta
        char getValue(int k);//retorna el valor de la carta k de
        void str(); //retorna en todas las cartas de la mano
        void addCard(Card card); //añade una carta a la mano de cartas
        int getValue();//retorna el valor total de puntos de la mano
        void draw(int x, int y, bool should);//dibuja todas las cartas desde la posición x,y, dependiendo de la cantidad de cartas

    private:
        Card hand[10]={
        };
        int cont;  //cantidad de cartas de la mano

};

Hand :: Hand(){
    cont = 0;
}

char Hand :: getSuit(int k){
    return hand[k].getSuit();
}

char Hand :: getValue(int k){
    return hand[k].getValue();
}

void Hand :: str(){
    for(int i = 0; i < 10; i++){
            cout << hand[i].getSuit() << hand[i].getValue() << " ";
    }
    return;
}

void Hand :: addCard(Card card){
    hand[cont] = card;
    cont++;
}

int Hand :: getValue(){
    int handVal = 0;
    int as = 0;
    char val;
    Card card;
    for(int i = 0; i < 10; i++){
        card = hand[i];
        val = card.getValue();
        if (val == 'T' || val == 'J' || val == 'Q' ||val == 'K'){
            handVal += 10;
        } else if(val == 'A'){
            as++;
        } else if(val != 'z'){
            int v = val - '0';
            handVal += v;
        }
    }
    while(as > 0){
        if( handVal+11 > 21){
            handVal++;
        } else {
            handVal += 11;
        }
        as--;
    }
    return handVal;
}

void Hand :: draw(int x, int y, bool should){

    int num[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char suits[9] = {'C', 'S', 'H', 'D', 'T', 'J', 'Q', 'K', 'A'};
    char vv;
    char s;
    cout << "draw" << endl;
    for(int i = 0; i < 10; i++){
        if(hand[i].getValue() != 'z'){
            hand[i].draw(x,y);
            glColor3ub(1,255,255);
            glRasterPos2f(x+5,y+5);
            vv = hand[i].getValue();
            s = hand[i].getSuit();
            if(should || i==0){
                if(s == 'C'){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[0]);
                } else if(s == 'S'){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[1]);
                } else if(s == 'H'){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[2]);
                } else {
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[3]);
                }

                if(vv == 'T'){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[4]);
                } else if(vv == 'J'){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[5]);
                } else if(vv == 'Q'){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[6]);
                } else if(vv == 'K'){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[7]);
                }  else if(vv == 'A'){
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, suits[8]);
                }else {
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, num[vv-'0']);
                }
            }
            x+=75;
        }
    }
}

#endif // HAND_H_INCLUDED
