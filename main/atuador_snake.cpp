#include <SDL.h>
#include "SDL_opengl.h"
#include "atuador_snake.h"
atuador::atuador(int p_x, int p_y, int comp, int alt, int r, int g, int b){
    posx = p_x;
    posy = p_y;
    this->comp = comp;
    this-> alt = alt;
    cor_red = r;
    cor_green = g;
    cor_blue = b;
}
void atuador::criar(){
//CRIANDO PERSONAGEM
    glBegin(GL_QUADS);//Quadrado
    glColor4ub(cor_red,cor_green,cor_blue,255);
    glVertex2f(posx,posy);
    glVertex2f(posx+comp,posy);
    glVertex2f(posx+comp,posy+alt);
    glVertex2f(posx,posy+alt);
    glEnd();
//
}
void atuador::criar(int vis){
//CRIANDO PERSONAGEM
    glBegin(GL_QUADS);//Quadrado
    glColor4ub(cor_red,cor_green,cor_blue,vis);
    glVertex2f(posx,posy);
    glVertex2f(posx+comp,posy);
    glVertex2f(posx+comp,posy+alt);
    glVertex2f(posx,posy+alt);
    glEnd();
//
}
void atuador::andar(int a, char x_y){
    if(x_y == 'X')this->posx -= a;
    else this->posy -= a;
}
void atuador::andar(atuador obj){
    this->posx = obj.posx;
    this->posy = obj.posy;
}
bool atuador::colisao (atuador obj){
    if(this->posy+this->alt < obj.posy)return false;
    if(this->posy > obj.posy+obj.alt)return false;
    if(this->posx+this->comp < obj.posx)return false;
    if(this->posx > obj.posx+obj.comp)return false;
    return true;
}
bool atuador::cor(atuador obj){
    if(this->cor_red == obj.cor_red && this->cor_green == obj.cor_green && this->cor_blue == obj.cor_blue) return true;
    return false;
}
