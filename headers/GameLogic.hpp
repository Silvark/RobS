#ifndef LGK_HPP
#define LGK_HPP

#include <iostream>

#include "Player.hpp"
#include "Rob.hpp"
#include "Map.hpp"

class Game;

class GameLogic {
  private:
    /* ## FSM ############################################################### //
    0 : menu principal, pas de logique de jeu
    1 : début de partie, il faut placer les robs sur le terrain
      11 : On place les robs du joueur 1
      12 : On place les robs du joueur 2
    2 : jeu en cours, il faut alterner entre J1 et J2
      21 : joueur 1 joue
      22 : joueur 2 joue
    3 : fin du jeu, afficher qui a gagné
      31 : joueur 1 gagne
      32 : joueur 2 gagne
    99 : le jeu se ferme
    // ###################################################################### */
    int fsm;
    sf::Event events;

    Player * one;
    Player * two;

    Rob * controlTarget;

  public:
    GameLogic();
    ~GameLogic();

    void eventMgr(Game * game, const sf::Vector2i& mousePos);
    void physicsMgr(Game * game);
    void checkWinner();
    void changeWeapon(Player * player);
    void changeRob(Player * player);
    void moveRob(Player * player);

    Player * getPlayer(int id) { if (id == 1) {return one;} if (id == 2) {return two;} return nullptr; }

    void setControlTarget(Rob * playable);
    Rob * const getControlTarget() const;

    int const getFSM();

    void placeRob(sf::Vector2f position, Game * game, Player * owner);

};

#endif