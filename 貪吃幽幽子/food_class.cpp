#include "Header.h"

void food_class::initial(food_name_enum input_food_name, game_class& game, sf::RenderWindow& window) {
    name = input_food_name;
    exist_time = 10;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 14);
    int x = dist(gen);
    int y = dist(gen);
    while (game.get_map_object(x, y) != object_name_enum::None) {
        x = dist(gen);
        y = dist(gen);
    }
    position_x = x;
    position_y = y;
    if (input_food_name == food_name_enum::cola) {        
        object_name = object_name_enum::cola;
        move_distance = 0;
        move_interval = 0;
        move_delay = move_interval;
        growth_value = 1;
        game.set_map_object(x, y, object_name_enum::cola);
        if (!texture.loadFromFile("./images/cola.png")) {
            printf("./images/cola.png load failed.\n");
            return;
        }
    }
    else if (input_food_name == food_name_enum::hamburger) {
        object_name = object_name_enum::hamburger;
        move_distance = 0;
        move_interval = 0;
        move_delay = move_interval;
        growth_value = 2;
        game.set_map_object(x, y, object_name_enum::hamburger);
        if (!texture.loadFromFile("./images/hamburger.png")) {
            printf("./images/hamburger.png load failed.\n");
            return;
        }
    }
    else if (input_food_name == food_name_enum::Niwatari_Kutaka_Fumo) {
        object_name = object_name_enum::Niwatari_Kutaka_Fumo;
        move_distance = 1;
        move_interval = 10;
        move_delay = move_interval;
        growth_value = 3;
        game.set_map_object(x, y, object_name_enum::Niwatari_Kutaka_Fumo);
        if (!texture.loadFromFile("./images/Niwatari Kutaka Fumo.png")) {
            printf("./images/Niwatari Kutaka Fumo.png load failed.\n");
            return;
        }
    }
    should_play_sound = false;
    direction = direction_enum::None;
}

// 檢查輸入位置是否一樣
bool food_class::check_position(int x, int y) {
    return position_x == x && position_y == y;
}

// 食物移動    
void food_class::move(game_class& game, Saigyouji_Yuyuko_Fomo_class& Saigyouji_Yuyuko_Fomo) {
    //如果不是fumo 就不移動
    if (name == food_name_enum::None || name == food_name_enum::cola || name == food_name_enum::hamburger) {
        return;
    }
    // 如果移動延遲還沒到0 就不移動 否則移動延遲=move_interval
    move_delay--;
    if (move_delay > 0) {
        return;
    }
    else {
        move_delay = move_interval;
    }
    // 要移動的方向 如果是Niwatari_Kutaka_Fumo 移動方向跟幽幽子fumo移動方向一樣
    if (name == food_name_enum::Niwatari_Kutaka_Fumo) {
        escape_move(game, Saigyouji_Yuyuko_Fomo);
    }
    // 否則移動方向為隨機
    else {
        random_move(game, Saigyouji_Yuyuko_Fomo);
    }        
}

// 食物隨機移動
void food_class::random_move(game_class& game, Saigyouji_Yuyuko_Fomo_class& Saigyouji_Yuyuko_Fomo) {
    // 宣告將要移動到的地點
    int move_position_x;
    int move_position_y;

    do {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 4);
        int random_index = dist(gen);
        if (random_index == 1) {
            direction = direction_enum::Up;
        }
        else if (random_index == 2) {
            direction = direction_enum::Down;
        }
        else if (random_index == 3) {
            direction = direction_enum::Left;
        }
        else if (random_index == 4) {
            direction = direction_enum::Right;
        }

        if (direction == direction_enum::None) {
            return;
        }
        else if (direction == direction_enum::Up) {
            move_position_x = position_x;
            move_position_y = abs(position_y - move_distance + game.get_map_height()) % game.get_map_height();
        }
        else if (direction == direction_enum::Down) {
            move_position_x = position_x;
            move_position_y = abs(position_y + move_distance + game.get_map_height()) % game.get_map_height();
        }
        else if (direction == direction_enum::Left) {
            move_position_x = abs(position_x - move_distance + game.get_map_width()) % game.get_map_width();
            move_position_y = position_y;
        }
        else if (direction == direction_enum::Right) {
            move_position_x = abs(position_x + move_distance + game.get_map_width()) % game.get_map_width();
            move_position_y = position_y;
        }
    }
    // 如果要移動到的地點是Saigyouji_Yuyuko_Fomo 就重複到移動地點不是的地方
    while (game.get_map_object(move_position_x, move_position_y) == object_name_enum::Saigyouji_Yuyuko_Fomo);

    game.set_map_object(position_x, position_y, object_name_enum::None);

    position_x = move_position_x;
    position_y = move_position_y;    
        
    game.set_map_object(position_x, position_y, object_name);
}

// 食物與幽幽子fumo同樣方向移動
void food_class::escape_move(game_class& game, Saigyouji_Yuyuko_Fomo_class& Saigyouji_Yuyuko_Fomo) {
    // 宣告將要移動到的地點
    int move_position_x;
    int move_position_y;

    direction = Saigyouji_Yuyuko_Fomo.get_direction();

    if (direction == direction_enum::None) {
        return;
    }
    else if (direction == direction_enum::Up) {
        move_position_x = position_x;
        move_position_y = abs(position_y - move_distance + game.get_map_height()) % game.get_map_height();
    }
    else if (direction == direction_enum::Down) {
        move_position_x = position_x;
        move_position_y = abs(position_y + move_distance + game.get_map_height()) % game.get_map_height();
    }
    else if (direction == direction_enum::Left) {
        move_position_x = abs(position_x - move_distance + game.get_map_width()) % game.get_map_width();
        move_position_y = position_y;
    }
    else if (direction == direction_enum::Right) {
        move_position_x = abs(position_x + move_distance + game.get_map_width()) % game.get_map_width();
        move_position_y = position_y;
    }

    // 如果移動的地方是幽幽子fumo 就隨機移動
    if (game.get_map_object(move_position_x, move_position_y) == object_name_enum::Saigyouji_Yuyuko_Fomo) {
        random_move(game, Saigyouji_Yuyuko_Fomo);
    }
    // 否則移動
    else {
        game.set_map_object(position_x, position_y, object_name_enum::None);

        position_x = move_position_x;
        position_y = move_position_y;

        game.set_map_object(position_x, position_y, object_name);
    }
}

// 檢查食物是否存在
bool food_class::check_exist() {
    return exist_time;
}

// 吃食物 返回食物成長值 撥放音效
int food_class::get_growth_value() {
    exist_time = 0;
    should_play_sound = true;
    return growth_value;
}

// 畫出食物
void food_class::draw(sf::RenderWindow& window, game_class& game) {
    // 如果存在時間是0 就不畫
    if (exist_time == 0) {
        return;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    float x;
    float y;
    x = (float)window.getSize().x / game.get_map_width();
    y = (float)window.getSize().y / game.get_map_height();
    sprite.setScale({ x / sprite.getGlobalBounds().width, y / sprite.getGlobalBounds().height });
    x = (float)sprite.getGlobalBounds().width / 2;
    y = (float)sprite.getGlobalBounds().height / 2;
    sprite.setOrigin(x, y);
    x = (float)window.getSize().x * position_x / game.get_map_width();
    y = (float)window.getSize().y * position_y / game.get_map_height();
    sprite.setPosition(x, y);
    window.draw(sprite);
}

// 播放食物音效
bool food_class::play_sound() {
    if (should_play_sound) {        
        should_play_sound = false;
        return true;
    }
    return false;
}

// 回傳食物名字
food_name_enum food_class::get_food_name() {
    return name;
}