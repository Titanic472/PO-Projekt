#include <vector>
#include <queue>

using namespace std;

class World {

    //vector<Entity> entities;
    //queue<Entity> to_free;
    //queue<Entity> to_add;
    
    public:

    static World &instance;

    World();


    ~World();


    void perform_turn();
    /* order:
    entity actions (priority_queue)
    free
    add

    */
    

    void draw_world();


    // functions for entities:

    //void queue_free(Entity entity);

    //void queue_add(Entity entity);

    private:

    // delete entity from entities
    //void entity_free(Entity entity);

    // add entity to entities 
    //void entity_add(Entity entity);

};