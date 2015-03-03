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
        char * str(); //retorna en todas las cartas de la mano
        void addCard(Card card); //añade una carta a la mano de cartas
        int getValue();//retorna el valor total de puntos de la mano
        void draw(int x, int y);//dibuja todas las cartas desde la posición x,y, dependiendo de la cantidad de cartas

    private:
        Card hand[10]={
            Card('z','z'), Card('z','z'),
            Card('z','z'),Card('z','z'),
            Card('z','z'),Card('z','z'),
            Card('z','z'),Card('z','z'),
            Card('z','z'), Card('z','z')
        };
        int cont;  //cantidad de cartas de la mano

};

Hand :: Hand(){
    this.cont = 0;
}

char Hand :: getSuit(int k){
    Card card = new Card();
    card = this.hand[k];
    return card.getSuit();
}

char Hand :: getValue(int k){
    Card card = new Card();
    card = this.hand[k];
    return card.getValue();
}

char * Hand :: str(){
    string strhand = "";
    Card card = new Card();
    for(int i = 0; i <= 10; i++){
            card = this.hand[i];
            strhand += card.getSuit();
            strhand += card.getValue() + " ";
    }
    return strhand;
}

void Hand :: addCard(Card card){
    this.hand[this.cont] = card;
    this.cont++;
}

int Hand :: getValue();{
    int handVal = 0;
    int as = 0;
    char val;
    Card card = new Card();
    for(int i = 0; i <= 10; i++){
        card = this.hand[i];
        val = card.getValue();
        if (val == 'T' || val == 'J' || val == 'Q' ||val == 'K'){
            handVal += 10;
        } else if(val == 'A'){
            as++;
        } else if(val != 'z'){
            handVal += val - '0';
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

#endif // HAND_H_INCLUDED
