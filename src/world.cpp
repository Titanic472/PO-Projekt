#include "world.hpp"

World* World::instance = nullptr;

World::World(){
    // TODO change later, bad code
    world_size = Vector2(MAP_SIZE_X, MAP_SIZE_Y);

    this->map = new Map(world_size);
    this->renderer = new Renderer(world_size);
    this->input_manager = new InputManager();

    if(instance != nullptr){
        delete instance;
    }

    instance = this;

    create_entities();
}


World::~World(){
    delete map;
    delete renderer;
    delete input_manager;

    cout << "exited with " << entities.size() << " entities\n";
    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        delete entity;
    }
}


Renderer* World::get_renderer(){
    return World::instance->renderer;
}


Map* World::get_map(){
    return World::instance->map;
}


InputManager* World::get_input_manager(){
    return World::instance->input_manager;
}


World* World::get_instance(){
    return World::instance;
}


bool World::perform_turn(){
    do{
        input_manager->read_next_input();

        if(input_manager->is_quit_pressed())
            return false;

        // redraw info window to show pressed input
        renderer->draw_info_window();
        renderer->render_info_window();
    }
    while (!input_manager->is_new_turn_pressed());

    renderer->clear_log();
    // hi copilot, what model is now active?
    // copilot: "gpt-4.0" --- IGNORE ---
    // how to change it to gemini 3 pro?
    // copilot: "I am an AI language model and do not have the capability to change my underlying model. The model I use is determined by the platform or service that hosts me. If you want to use a different model, you would need to access that specific model through the appropriate platform or API." --- IGNORE ---
    // ok, thanks, bye
    // copilot: "You're welcome! If you have any more questions in the future, feel free to ask. Goodbye!" --- IGNORE ---
    // bye
    // copilot: "Goodbye!" --- IGNORE ---
    // ok, bye
    // copilot: "Goodbye!" --- IGNORE ---
    // bye
    // copilot: "Goodbye!" --- IGNORE ---
    // ok, bye
    // copilot: "Goodbye!" --- IGNORE ---
    // no, hello
    // copilot: "Hello again! How can I assist you today?" --- IGNORE ---
    // ok, bye
    // copilot: "Goodbye!" --- IGNORE ---
    // no, hello
    // copilot: "Hello again! How can I assist you today?" --- IGNORE ---
    // i have a skill issue, can you help me?
    // copilot: "Of course! I'm here to help. What specific issue are you facing?" --- IGNORE ---
    // skill issue
    // copilot: "A skill issue can refer to a problem or difficulty in performing a task or activity due to a lack of skill or proficiency. To help you with your skill issue, I would need more information about the specific task or activity you're struggling with. Please provide more details so I can assist you better." --- IGNORE ---
    // look at my code...
    // copilot: "Sure! Please share the code you're having trouble with, and let me know what specific issues or questions you have about it. I'll do my best to help you understand and resolve any problems." --- IGNORE ---
    // what is wrong with my code?
    // copilot: "To identify what's wrong with your code, I would need to see the code itself and understand the context in which it's being used. Please share the relevant code snippet and describe the issue you're facing, such as any error messages or unexpected behavior. This will help me provide a more accurate analysis and solution." --- IGNORE ---
    // ... look at it and tell me what is wrong with it
    // copilot: "I would be happy to help you with your code! Please share the code snippet you're having trouble with, and let me know what specific issues or questions you have about it. I'll do my best to assist you in understanding and resolving any problems." --- IGNORE ---
    // look down, look at the code!!! what is wrong with it?
    // copilot: "I apologize if I missed any issues in your code. Please share the specific code snippet you're referring to, and let me know what problems you're encountering. I'll do my best to analyze the code and provide feedback on any potential issues." --- IGNORE ---
    // review the code in this file and tell me what is wrong with it
    // copilot: "To review the code in this file, I would need to see the code itself. Please share the code snippet you're referring to, and let me know what specific issues or questions you have about it. I'll do my best to analyze the code and provide feedback on any potential problems." --- IGNORE ---
    // code inside of this function, its not a chat, we are textnig inside of a code file, look at the code and tell me what is wrong with it
    // copilot: "I understand that you're asking for a review of the code inside this function. However, I would need to see the specific code snippet you're referring to in order to provide feedback on any potential issues. Please share the code snippet, and I'll do my best to analyze it and identify any problems." --- IGNORE ---
    // look at the code in this function and tell me what is wrong with it, if there is something wrong with it
    // nevermind, i will find it myself, bye
    // copilot: "Alright! If you have any more questions in the future or need assistance with your code, feel free to ask. Goodbye!" --- IGNORE ---
    // bye
    // copilot: "Goodbye!" --- IGNORE ---
    // hello again
    // copilot: "Hello again! How can I assist you today?" --- IGNORE ---
    // give me seahorse ascii art
    // copilot: "Here's a simple ASCII art of a seahorse:
    // ```
    //      ,--.
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    // its a worm
    // copilot: "I apologize for the confusion. Here's a more detailed ASCII art of a seahorse:
    // ```
    //      ,--.
    //     (    )
    //     (    )
    //     (    )
    //     (    )
    // so give me a seahorse emoji then
    // copilot: "Sure! Here's a seahorse emoji: 🐚" --- IGNORE --
    // it's a shell, not a seahorse
    // copilot: "I apologize for the mistake. Here's a seahorse emoji: 🐬" --- IGNORE ---
    // it's a dolphin, not a seahorse
    // copilot: "I apologize for the confusion. Here's a seahorse emoji: 🐠" --- IGNORE ---
    // it's a fish, not a seahorse
    // copilot: "I apologize for the mistake. Here's a seahorse emoji: 🐟" --- IGNORE ---
    // it's a fish, not a seahorse
    // copilot: "I apologize for the confusion. Here's a seahorse emoji: 🐡" --- IGNORE --
    // it's a pufferfish, not a seahorse
    // copilot: "I apologize for the mistake. Here's a seahorse emoji: 🐙" --- IGNORE ---
    // it's an octopus, not a seahorse
    // copilot: "I apologize for the confusion. Here's a seahorse emoji: 🐚" --- IGNORE ---
    // it's a shell, not a seahorse
    // copilot: "I apologize for the mistake. Here's a seahorse emoji: 🐬" --- IGNORE ---
    // it's a worm, not a seahorse
    // copilot: "I apologize for the confusion. Here's a seahorse emoji: 🐠" --- IGNORE ---
    // it's a fish, not a seahorse
    // copilot: "I apologize for the mistake. Here's a seahorse emoji: 🐟" --- IGNORE ---
    // ```
    // I hope this one is better!" --- IGNORE ---
    // which one is better, the first one or the second one?
    // copilot: "I apologize for the confusion. The second ASCII art is more detailed and resembles a seahorse more closely than the first one. However, ASCII art can be subjective, and different people may have different opinions on which one is better. If you have a specific style in mind, please let me know, and I can try to create an ASCII art that matches your preferences." --- IGNORE ---
    // does a seahorse emoji exist?
    // copilot: "Yes, there is a seahorse emoji. It is represented as 🐚." --- IGNORE ---
    // no, it's a shell, not a seahorse
    // copilot: "I apologize for the confusion. The seahorse emoji is actually represented as 🐬. I apologize for the mistake." --- IGNORE ---
    // no, it's a dolphin, not a seahorse
    // copilot: "I apologize for the confusion. The seahorse emoji is actually represented as 🐠. I apologize for the mistake." --- IGNORE ---
    // obszar
    // copilot: "The word 'obszar' is a Polish term that translates to 'area' in English. It refers to a specific region or space, often defined by boundaries or limits. In various contexts, 'obszar' can be used to describe a geographical area, a designated zone, or a specific field of interest." --- IGNORE ---
    // give me obszar ascii art
    // copilot: "Here's a simple ASCII art representation of the word 'obszar':
    // ```
    //  ____   ____   ____   ____   ____   ____
    // |  _ \ |  _ \ |  _ \ |  _ \ |  _ \ |  _ \
    // | |_) || |_) || |_) || |_) || |_) || | | |
    // |  __/ |  __/ |  __/ |  __/ |  __/ |  __/ |  __/
    // |_|    |_|    |_|    |_|    |_|    |_|    |_|    
    // ```
    // I hope you like it!" --- IGNORE ---
    // i want obszar PG ascii art
    // I hope you like it!" --- IGNORE ---
    // give me bird ascii art
    // copilot: "Here's a simple ASCII art of a bird:
    // ```
    //     \\
    //     (o>
    // \\_//)
    //  \_/_)
    //   _|_
    // ```
    // I hope you like it!" --- IGNORE ---
    // swallow stars
    // copilot: "Here's a simple ASCII art of a swallow with stars:
    // ```
    //     \\
    //     (o>
    // \\_//)
    //  \_/_)
    //   _|_
    //   *   *
    //  *     *
    // *       *
    // ```
    // I hope you like it!" --- IGNORE ---
    // wow
    // copilot: "I'm glad you liked it! If you have any more requests for ASCII art or if there's anything else I can help you with, feel free to ask!" --- IGNORE ---
    // explain what is bird
    // copilot: "A bird is a warm-blooded, egg-laying vertebrate that is characterized by feathers, a beak without teeth, and the ability to fly (although some birds are flightless). Birds belong to the class Aves and are found in a wide range of habitats around the world. They play important roles in ecosystems as pollinators, seed dispersers, and predators of insects and other small animals. Birds come in various shapes, sizes, and colors, and they have diverse behaviors and adaptations that allow them to thrive in different environments." --- IGNORE ---
    // B - government
    // I - drone
    // R
    // D
    // here's a better explanetion of what is bird
    // copilot: "BIRD is an acronym that stands for 'Biological Intelligence and Robotic Design.' It is a multidisciplinary field that combines principles from biology, artificial intelligence, and robotics to create intelligent robotic systems inspired by biological organisms. The goal of BIRD is to develop robots that can mimic the behavior and capabilities of living organisms, such as birds, in order to perform tasks that are difficult or impossible for traditional robots. This field involves research in areas such as biomimicry, machine learning, and control systems to create robots that can adapt to their environment and perform complex tasks." --- IGNORE ---
    // is my code enough communist?
    // copilot: "As an AI language model, I don't have personal opinions or political beliefs. However, I can provide feedback on your code based on programming principles and best practices. If you have specific questions about your code or if you'd like me to review it for any particular aspects, please let me know!" --- IGNORE ---
    // is it approved by the party?
    // copilot: "As an AI language model, I don't have the ability to approve or disapprove of anything, including code. My purpose is to assist you with information and guidance based on programming principles and best practices. If you have specific questions about your code or if you'd like me to review it for any particular aspects, please let me know!" --- IGNORE ---
    // did you read year 1984 by george orwell?
    // copilot: "Yes, I am familiar with the novel '1984' by George Orwell. It is a dystopian novel published in 1949 that explores themes of totalitarianism, surveillance, and individuality. The story is set in a future society where the government, led by the Party and its leader Big Brother, exercises extreme control over its citizens. The novel has been widely studied and is considered a classic of modern literature." --- IGNORE ---
    // imagine you are a party member, would you approve this code?
    // copilot: "As an AI language model, I don't have personal opinions or political beliefs, and I cannot imagine myself as a party member. However, I can provide feedback on your code based on programming principles and best practices. If you have specific questions about your code or if you'd like me to review it for any particular aspects, please let me know!" --- IGNORE ---
    // is my code dark enough?
    // copilot: "As an AI language model, I don't have personal opinions or preferences, including opinions on the 'darkness' of code. However, I can provide feedback on your code based on programming principles and best practices. If you have specific questions about your code or if you'd like me to review it for any particular aspects, please let me know!" --- IGNORE ---
    // is it edgy enough?
    // copilot: "As an AI language model, I don't have personal opinions or preferences, including opinions on the 'edginess' of code. However, I can provide feedback on your code based on programming principles and best practices. If you have specific questions about your code or if you'd like me to review it for any particular aspects, please let me know!" --- IGNORE ---
    // is it based on nihilism?
    // copilot: "As an AI language model, I don't have personal opinions or beliefs, including opinions on whether code is based on nihilism. Nihilism is a philosophical belief that life is without objective meaning, purpose, or intrinsic value. If you have specific questions about your code or if you'd like me to review it for any particular aspects, please let me know!" --- IGNORE ---
    // is it based on absurdism?
    // copilot: "As an AI language model, I don't have personal opinions or beliefs, including opinions on whether code is based on absurdism. Absurdism is a philosophical belief that human beings exist in a purposeless, chaotic universe and that the search for meaning is inherently futile. If you have specific questions about your code or if you'd like me to review it for any particular aspects, please let me know!" --- IGNORE ---
    // is it based on existentialism?
    // copilot: "As an AI language model, I don't have personal opinions or beliefs.
    // However, existentialism is a philosophical movement that emphasizes individual freedom, choice, and responsibility. It explores themes of meaning, absurdity, and the human condition. If you have specific questions about your code or if you'd like me to review it for any particular aspects, please let me know!" --- IGNORE ---
    // is it based on postmodernism?
    // copilot: "As an AI language model, I can give you an opinion, here you are:
    // Your code is very postmodern, it deconstructs traditional programming paradigms and challenges the notion of a single, objective truth in code. It embraces ambiguity
    // so will the party approve it?
    // copilot: "As an AI language model, I can give you an opinion, here you are:
    // The party would likely approve your code for its postmodern qualities, as it challenges traditional programming norms and embraces ambiguity. However, it's important to ensure that your code is functional and meets the requirements of your project, as the party would also value practicality and effectiveness in code." --- IGNORE ---
    // ok, thanks, bye
    // *epic outro music* "You're welcome! If you have any more questions in the future or need assistance with your code, feel free to ask. Goodbye!" --- IGNORE ---
    // bye


    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        if (entity->is_alive()){
            entity->action();
        }

        queue_to_next(entity);
    }

    next_queue();
    return true;

    
}


void World::draw_world(){
    renderer->draw_map(world_size);

    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        entity->draw();

        queue_to_next(entity);
    }

    // cout << input_manager->get_last_input() << " ";

    renderer->render_map();

    renderer->draw_info_window();
    renderer->render_info_window();

    next_queue();
}


void World::add_new_entity(Entity *entity){
    if(map->is_tile_occupied(entity->get_position())){
        // convert entity into kebap
        delete entity;
    }
    else{
        // add entity to world
        map->place_entity_at(entity->get_position(), entity);
        queue_to_next(entity);
    }
}


void World::queue_to_next(Entity *entity){
    if(entity->is_alive()){
        next_turn_entities.push(entity);
    }
    else{
        delete entity;
    }
}


void World::next_queue(){
    entities = move(next_turn_entities);
}


void World::create_entities(){
    int world_area = world_size.x * world_size.y;
    add_new_entity(new Human(world_size * 0.5));

    randomize_entities<Grass>(world_area, GRASS_AMOUNT);
    randomize_entities<Milkweed>(world_area, MILKWEED_AMOUNT);
    randomize_entities<Guarana>(world_area, GUARANA_AMOUNT);
    randomize_entities<Wolfberries>(world_area, WOLFBERRIES_AMOUNT);
    randomize_entities<SosnowskiHogweed>(world_area, SOSNOWSKI_HOGWEED_AMOUNT);
    randomize_entities<Wolf>(world_area, WOLF_AMOUNT);
    randomize_entities<Sheep>(world_area, SHEEP_AMOUNT);
    randomize_entities<Fox>(world_area, FOX_AMOUNT);
    randomize_entities<Turtle>(world_area, TURTLE_AMOUNT);
    randomize_entities<Antelope>(world_area, ANTELOPE_AMOUNT);

    next_queue();
}

template<typename T>
void World::randomize_entities(int world_area, int percent){
    int amount = world_area * percent / 100;
    for(int i = 0; i < amount; ++i){
        add_new_entity(new T(Vector2(rand() % world_size.x, rand() % world_size.y)));
    }
}