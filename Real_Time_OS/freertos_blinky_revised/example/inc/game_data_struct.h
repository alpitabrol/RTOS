/*
 * Game Data Structures
 */

#ifndef game_data_struct_H_
#define game_data_struct_H_

#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include "game_data_struct.h"

#define	RUN_GAME_PRIORITY		3
#define IMPACTS_TASK_PRIORITY	2
#define GO_TASK_PRIORITY		1
#define DELAY_RUN_GAME			65536
#define	DELAY_GAME_TICK			8192



enum boolean {True, False} boolean_enum;
typedef enum boolean bool_t;


/* user-input tracking */
struct ui_struct
{
	bool_t	move_left;
	bool_t	move_right;

};
typedef struct ui_struct ui_t;

/* coordinate type */
struct go_coord_struct
{
	int16_t	X;
	int16_t	Y;
};
typedef struct go_coord_struct go_coord_t;


/* game record-keeping */
struct game_struct
{
	uint32_t	score;
	char		playerID[4];
	ui_t		input;
	go_t		*enemy_car;
	go_t		*player_car;
};
typedef	struct game_struct	game_t;

/* (g)ame (o)bject record-keeping */
struct go_struct
{
	size_t		ID;
	bool_t		alive;
	bool_t		on_screen;
	bool_t		gameover;
	go_coord_t	pos;
	bool_t		move_up;
	bool_t		move_down;
	go_list_t	*interactions;
	xTaskHandle	task;
	char		taskText[32];
	struct		go_struct	*pNext;
	struct		go_struct	*pPrev;
};
typedef struct go_struct go_t;

struct go_list_struct
{
	size_t		ID;
	bool_t		collision;
	struct	go_list_struct *pNext;
	struct	go_list_struct *pPrev;
};
typedef struct go_list_struct go_list_t;

/*
 * FUNCTION PROTOTYPES
 */

go_t* getGODefaults(go_t *, char *);

go_t* createGONode(char *);

go_t* genesisGO(go_t* , char *, go_coord_t , size_t );

void prvUpdateInteractionList(go_t *, go_t *, uint16_t, bool_t, bool_t);






#endif /* LIBGAMEDS_H_ */
