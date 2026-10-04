#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *mainQ, struct game_state state) 
{
    uint64_t value = serialize(state);
    insert_at_tail(&mainQ->data, value);
    
    return;
}

struct game_state dequeue(struct queue *mainQ) 
{
    uint64_t value = remove_from_head(&mainQ->data);
    struct game_state state = deserialize(value);

    return (state);//{0}; //why was the {} here? also originally just struct game_state, no var name.
}

int number_of_moves(struct game_state start) 
{ 
    uint8_t board[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,0}};
    struct game_state solved;
    solved.num_steps = 0;
    solved.empty_col = 3;
    solved.empty_row = 3;
    
    int count = 1;
    for (int i = 0; i < 4; i++) //row
    {
        for (int j = 0; j < 4; j++) //col
        {
            solved.tiles[i][j] = (uint8_t)board[i][j];
            count++;
        }
    }

    uint64_t serialSolve = serialize(solved);
    
    struct linked_list mainList = {NULL};
    struct queue mainQ = {mainList};
    
    struct linked_list checkList = {NULL};
    struct queue checkQ = {checkList};
    
    enqueue(&mainQ, start);
    enqueue(&checkQ, start);

    while (mainQ.data.head != NULL) //while queue is not empty
    {
        struct game_state curr = dequeue(&mainQ);
        uint64_t serialCurr = serialize(curr);
        if(serialCurr == serialSolve)//look for finished board, where is the final state?
        {
            int result = (int)curr.num_steps;
            free_list(checkList);
            free_list(mainList);
            return result;
        }
        else
        {
            struct game_state moveState[4] = {curr, curr, curr, curr}; //up, down, left, right
            move_up(&moveState[0]);
            move_down(&moveState[1]);
            move_left(&moveState[2]);
            move_right(&moveState[3]);
            //uint64_t moves[4] = {serialize(moveState[0]), serialize(moveState[1]), serialize(moveState[2]), serialize(moveState[3])};
            for (int i = 0; i < 4; i++) //look for matches in checkDoub
            {
                if (serialize(moveState[i]) != serialCurr)
                {
                    int flag = 1;
                    struct list_node * end = checkQ.data.head;
                    
                    while (end != NULL && flag)
                    {
                        uint64_t checkVal = end->value;

                        if (checkVal == serialize(moveState[i]))
                        {
                            flag = 0;
                        }
                        end = end->next;

                    }

                    if (flag)
                    {
                        enqueue(&mainQ, moveState[i]);
                        enqueue(&checkQ, moveState[i]);
                    }
                }
            }
        } 
    }
    //bfs goes here
    //compare serialized values of the struct game_state
    //call move [direction], not a recursive step - the next state will be the same as prev if a move is not possible there
 //add children to linked list before looking at oldest item(next parent)
 //1 active queue
 //1 linked list list (for past states, dont add children to queue)


    return 0; 
}
