#pragma once

#define DEFINE_ANI "ani-goomba-idle"
#define DIE_ANI "die"
#define IDLE_ANI "idle"
#define WALK_ANI "walk"
#define MOVE_ANI "move"
#define CROUCH_ANI "crouch"
#define FLY_ANI "fly"
#define HEADUP_ANI "headup"
#define HEADDOWN_ANI "headdown-idle"
#define HYPHEN "-"

#define DEFAULT_GRAVITY 0.006f
#define DEFAULT_SPEED_LIVE_X 0.05f*2
#define DEFAULT_BEING_ATTACKED_SPEED_X 0.4f
#define DEFAULT_BEING_ATTACKED_SPEED_Y 0.65f*2
#define DEFAULT_BEING_KICK_SPEED 0.08f*4
#define DEFAULT_BEING_KICK_TIME 5000

//GOOMBA
#define GOOMBA_ANI "ani-goomba"
#define GOOMBA_TIME_WILL_DIE 500

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 45
#define GOOMBA_BBOX_HEIGHT_DIE 27


//KOOPAS
#define KOOPAS_ANI "ani-red-koopa-troopa"
#define KOOPAS_TIME_WILL_DIE 5000

#define KOOPAS_BEING_KICK_SPEED 0.08f*4;
#define KOOPAS_WALKING_SPEED 0.08f;

#define KOOPAS_BBOX_WIDTH 16*3
#define KOOPAS_BBOX_HEIGHT 26*3
#define KOOPAS_BBOX_HEIGHT_COUCH 16*3


//PARA_Goomba
#define PARA_GOOMBA_ANI "ani-red-para-goomba"
#define RED_GOOMBA_ANI "ani-red-goomba"
#define PARA_GOOMBA_TIME_LIVE 300
#define PARA_GOOMBA_TIME_JUMP 800
#define PARA_GOOMBA_TIME_FLY 300
#define PARA_GOOMBA_TIME_WILL_DIE 500

#define PARA_GOOMBA_FLY_SPEED_Y 0.8f
#define PARA_GOOMBA_JUMP_SPEED_Y 0.25f
#define PARA_GOOMBA_FLY_SPEED_X 0.1f
#define PARA_GOOMBA_JUMP_SPEED_X 0.05f

#define RED_GOOMBA_BBOX_WIDTH 16*3
#define RED_GOOMBA_BBOX_HEIGHT 45
#define RED_GOOMBA_BBOX_HEIGHT_DIE 27

#define PARA_BBOX_WIDTH 16*3
#define PARA_BBOX_HEIGHT 53
#define PARA_BBOX_FLY_HEIGHT 60

//VENUS_RED
#define VENUS_RED_ANI "ani-red-venus-fire-trap"
#define VENUS_RED_BBOX_WIDTH 48
#define VENUS_RED_BBOX_HEIGHT 48*2

#define VENUS_RED_TIME_IDLE_UP 300
#define VENUS_RED_TIME_ATTACK 100
#define VENUS_RED_TIME_IDLE_DOWN 300
//VENUS_GREEN
#define VENUS_GREEN_ANI "ani-green-venus-fire-trap"
//Bullet venus
#define BULLET_VENUS_ANI     "ani-fire-bullet"
#define BULLET_VENUS_WIDTH     30
#define BULLET_VENUS_HEIGHT    30
//Piranha_plant
#define PIRANHA_PLANT_VENUS_ANI "ani-green-piranha-plant-attack"
#define PIRANHA_PLANT_BBOX_WIDTH 48
#define PIRANHA_PLANT_BBOX_HEIGHT 72


#define BULLET_VENUS_SPEED 0.4f;
//Green Koopa Paratroopa
#define PARATROPA_ANI "ani-green-koopa-paratroopa-fly"
#define PARATROPA_GRAVITY 0.003f
#define PARATROPA_WIDTH     16*3
#define PARATROPA_HEIGHT    26*3
#define PARATROPA_SPEED_Y  0.5f * 3;
#define PARATROPA_SPEED_X  0.15f;
//Green koopas
#define GREEN_KOOPAS_ANI "ani-green-koopa-troopa"