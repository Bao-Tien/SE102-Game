#pragma once

//#define MARIO_WALKING_SPEED		0.15f 
//0.1f
#define VELOCITY_Y_SPEEDUP_MAX		0.3f
#define VELOCITY_Y_SPEEDUP		0.2f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.0006f
#define VELOCITY_X_SPEEDUP_MAX  0.38f
#define VELOCITY_X_MAX          0.24f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_JUMP_SPEED_Y				0.3f
#define MARIO_HIGH_JUMP_SPEED_Y				0.3f*1.5

#define MARIO_ACCELERATION_WALK     0.005f
#define MARIO_ACCELERATION_RUN     0.01f
#define MARIO_ACCELERATION_DIE     0.02f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_HIGH_JUMP       301
#define MARIO_STATE_RUN_RIGHT		350
#define MARIO_STATE_RUN_LEFT        351
#define MARIO_STATE_ATTACK			390
#define MARIO_STATE_FLY				391
#define MARIO_STATE_DIE				400

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON		3
#define	MARIO_LEVEL_FIRE		4
#define	MARIO_LEVEL_FROG		5
#define	MARIO_LEVEL_TANOOKI		6
#define	MARIO_LEVEL_HAMMER		7

#define MARIO_SMALL_BBOX_WIDTH  12*3
#define MARIO_SMALL_BBOX_HEIGHT 15*3

#define MARIO_BIG_BBOX_WIDTH  15*3
#define MARIO_BIG_BBOX_HEIGHT 27*3

#define MARIO_FROG_BBOX_WIDTH  21*3
#define MARIO_FROG_BBOX_HEIGHT 24*3
#define MARIO_FROG_BBOX_HEIGHT_NOT_IDLE 31*3

#define MARIO_TANOOKI_BBOX_WIDTH  21*3
#define MARIO_TANOOKI_BBOX_HEIGHT 29*3
#define MARIO_TANOOKI_BBOX_WIDTH_NOT_IDLE  23*3

#define MARIO_RACCOON_BBOX_WIDTH  21*3
#define MARIO_RACCOON_BBOX_HEIGHT 28*3



#define MARIO_UNTOUCHABLE_TIME 5000

//< !--Small Mario-- >
#define MARIO_ANI_SMALL_IDLE_FRONT  "ani-small-mario-idle-front"
#define MARIO_ANI_SMALL_IDLE        "ani-small-mario-idle"
#define MARIO_ANI_SMALL_WALKING     "ani-small-mario-walk"
#define MARIO_ANI_SMALL_SKID        "ani-small-mario-skid"
#define MARIO_ANI_SMALL_RUN         "ani-small-mario-run"
#define MARIO_ANI_SMALL_JUMP        "ani-small-mario-jump"
#define MARIO_ANI_SMALL_HIGH_JUMP   "ani-small-mario-high-jump"
#define MARIO_ANI_SMALL_DIE         "ani-small-mario-die"
/*"ani-small-mario-die"
"ani-small-mario-slide"
"ani-small-mario-hold"
"ani-small-mario-kick"
"ani-small-mario-dive"
"ani-small-mario-swim"
"ani-small-mario-climb"*/

//<!--Big Mario-->
#define MARIO_ANI_BIG_IDLE          "ani-big-mario-idle"
#define MARIO_ANI_BIG_IDLE_FRONT    "ani-big-mario-idle-front"
#define MARIO_ANI_BIG_WALK          "ani-big-mario-walk"
#define MARIO_ANI_BIG_SKID          "ani-big-mario-skid"
#define MARIO_ANI_BIG_RUN           "ani-big-mario-run"
#define MARIO_ANI_BIG_JUMP          "ani-big-mario-jump"
#define MARIO_ANI_BIG_HIGH_JUMP     "ani-big-mario-high-jump"
#define MARIO_ANI_BIG_ROLL          "ani-big-mario-roll"

//<!--Raccoon Mario-->
#define MARIO_ANI_RACCOON_IDLE_FRONT       "ani-raccoon-mario-idle-front"
#define MARIO_ANI_RACCOON_IDLE             "ani-raccoon-mario-idle"
#define MARIO_ANI_RACCOON_WALK             "ani-raccoon-mario-walk"
#define MARIO_ANI_RACCOON_SKID             "ani-raccoon-mario-skid"
#define MARIO_ANI_RACCOON_RUN              "ani-raccoon-mario-run"
#define MARIO_ANI_RACCOON_JUM              "ani-raccoon-mario-jump"
#define MARIO_ANI_RACCOON_SPEED_UP         "ani-raccoon-mario-speed-up"
#define MARIO_ANI_RACCOON_FLY              "ani-raccoon-mario-fly"
#define MARIO_ANI_RACCOON_SPIN             "ani-raccoon-mario-spin"
#define MARIO_ANI_RACCOON_ROLL             "ani-raccoon-mario-roll"
#define MARIO_ANI_RACCOON_ATTACK           "ani-raccoon-mario-attack"

//<!--Fire Mario-->
#define MARIO_ANI_FIRE_IDLE             "ani-fire-mario-idle"
#define MARIO_ANI_FIRE_WALK             "ani-fire-mario-walk"
#define MARIO_ANI_FIRE_SKID             "ani-fire-mario-skid"
#define MARIO_ANI_FIRE_RUN              "ani-fire-mario-run"
#define MARIO_ANI_FIRE_JUMP             "ani-fire-mario-jump"
#define MARIO_ANI_FIRE_HIGH_JUMP        "ani-fire-mario-high-jump"

//<!-- Hammer Mario -->
#define MARIO_ANI_HAMMER_IDLE             "ani-hammer-mario-idle-side"
#define MARIO_ANI_HAMMER_WALK             "ani-hammer-mario-walk"
#define MARIO_ANI_HAMMER_SKID             "ani-hammer-mario-skid"
#define MARIO_ANI_HAMMER_RUN              "ani-hammer-mario-run"
#define MARIO_ANI_HAMMER_JUMP             "ani-hammer-mario-jump"
#define MARIO_ANI_HAMMER_HIGH_JUMP        "ani-hammer-mario-high-jump"
#define MARIO_ANI_HAMMER_ROLL             "ani-hammer-mario-roll"

//< !--Mario Frog-- >
#define MARIO_ANI_FROG_IDLE             "ani-frog-mario-idle"
#define MARIO_ANI_FROG_WALK             "ani-frog-mario-walk"
#define MARIO_ANI_FROG_JUMP             "ani-frog-mario-jump"

//<!--Tanooki Mario-->
#define MARIO_ANI_TANOOKI_IDLE             "ani-tanooki-mario-idle"
#define MARIO_ANI_TANOOKI_SPIN             "ani-tanooki-mario-spin"
#define MARIO_ANI_TANOOKI_WALK             "ani-tanooki-mario-walk"
#define MARIO_ANI_TANOOKI_SKID             "ani-tanooki-mario-skid"
#define MARIO_ANI_TANOOKI_RUN              "ani-tanooki-mario-run"
#define MARIO_ANI_TANOOKI_JUMP             "ani-tanooki-mario-jump"
#define MARIO_ANI_TANOOKI_SPEED_UP         "ani-tanooki-mario-speed-up"
#define MARIO_ANI_TANOOKI_FLY              "ani-tanooki-mario-fly"
#define MARIO_ANI_TANOOKI_ROLL             "ani-tanooki-mario-roll"