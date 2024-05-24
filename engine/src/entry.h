#include <core/application.h>
#include <core/logger.h>
#include "game_types.h"
#include "core/kmemory.h"

extern b8 create_game(game* out_game);

int main(void){

    initialize_memory();

    game game_inst;

    if(!create_game(&game_inst))
    {
        KFATAL("Could Not Create Game!");
        return -1;
    }

    if(!game_inst.render | !game_inst.update | !game_inst.initialize | !game_inst.on_resize)
    {
        KFATAL("The Game's Function Pointers Must Be Assigned!");
        return -2;
    }


    if(!application_create(&game_inst))
    {
        KINFO("Application Failed To Create!\n");
        return 1;
    }

    if(!application_run())
    {
        KINFO("Application Did Not Shut Down Gracefully\n");
        return 2;
    }

    shutdown_memory();

    return 0;
}