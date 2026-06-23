#include "Header.h"

//幽幽子fumo初始設定
void Saigyouji_Yuyuko_Fomo_class::initial(game_class& game) {
    position.clear();
    position.push_back(std::make_pair(game.get_map_width() / 2, game.get_map_height() / 2));
    length = 1;
    move_distance = 1;
    move_interval = 5;
    move_delay = move_interval;
    direction = direction_enum::None;
    growth_amount = 0;
    if (!texture.loadFromFile("./images/Saigyouji Yuyuko Fumo.png")) {
        printf("./images /Saigyouji Yuyuko Fumo.png load failed.)\n");
        return;
    }
}

//畫出幽幽子fumo
void Saigyouji_Yuyuko_Fomo_class::draw(sf::RenderWindow& window, game_class& game) {
    //fumo的高寬度
    float fumo_width = (float)window.getSize().x / game.get_map_width();
    float fumo_height = (float)window.getSize().y / game.get_map_height();

    //sprite設定為幽幽子texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(fumo_width / sprite.getGlobalBounds().width, fumo_height / sprite.getGlobalBounds().height);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    //設定每一隻幽幽子fumo位置，並劃出每一隻幽幽子fumo
    for (int i = 0; i < position.size(); i++) {
        sprite.setPosition((float)window.getSize().x * position[i].first / game.get_map_width(), (float)window.getSize().y * position[i].second / game.get_map_height());
        window.draw(sprite);
    }
}

// 設定移動方向
void Saigyouji_Yuyuko_Fomo_class::set_direction(direction_enum input_direction) {
    direction = input_direction;
}

// 返回方向
direction_enum Saigyouji_Yuyuko_Fomo_class::get_direction() {
    return direction;
}

// 移動事件
void Saigyouji_Yuyuko_Fomo_class::move(game_class& game, food_class& food) {
    move_delay--;
    if (move_delay > 0) {
        return;
    }
    else {
        move_delay = move_interval;
    }
    // 宣告將要移動到的地點
    int move_position_x;
    int move_position_y;
    if (direction == direction_enum::None) {
        return;
    }
    else if (direction == direction_enum::Up) {
        move_position_x = position[0].first;
        move_position_y = abs(position[0].second - move_distance + game.get_map_height()) % game.get_map_height();;
    }
    else if (direction == direction_enum::Down) {
        move_position_x = position[0].first;
        move_position_y = abs(position[0].second + move_distance + game.get_map_height()) % game.get_map_height();
    }
    else if (direction == direction_enum::Left) {
        move_position_x = abs(position[0].first - move_distance + game.get_map_width()) % game.get_map_width();
        move_position_y = position[0].second;
    }
    else if (direction == direction_enum::Right) {
        move_position_x = abs(position[0].first + move_distance + game.get_map_width()) % game.get_map_width();;
        move_position_y = position[0].second;
    }

    // 如果要移動到的地點是Saigyouji_Yuyuko_Fomo 就不要移動
    if (game.get_map_object(move_position_x, move_position_y) == object_name_enum::Saigyouji_Yuyuko_Fomo) {
        return;
    }
    else {
        // 最後一個Saigyouji_Yuyuko_Fomo的位置
        int last_postion_x = position[position.size() - 1].first;
        int last_postion_y = position[position.size() - 1].second;
        // 第二個以上的Saigyouji_Yuyuko_Fomo移動到前一個Saigyouji_Yuyuko_Fomo位置        
        for (int i = position.size() - 1; i > 0; i--) {
            position[i] = position[i - 1];
        }
        // 第一個Saigyouji_Yuyuko_Fomo移動到要移動的地方
        position[0].first = move_position_x;
        position[0].second = move_position_y;
        game.set_map_object(move_position_x, move_position_y, object_name_enum::Saigyouji_Yuyuko_Fomo);
        // 如果有成長值 增加Saigyouji_Yuyuko_Fomo一個，位置在最後一個Saigyouji_Yuyuko_Fomo還沒移動的位置
        if (growth_amount > 0) {
            growth_amount--;
            position.push_back(std::make_pair(last_postion_x, last_postion_y));
            game.set_map_object(last_postion_x, last_postion_y, object_name_enum::Saigyouji_Yuyuko_Fomo);
            length++;
        }
        else {
            game.set_map_object(last_postion_x, last_postion_y, object_name_enum::None);
        }
        // 如果食物還存在、地圖上有實務、要移動到的地點是食物
        if (food.check_exist() && game.get_has_food() &&
            food.check_position(move_position_x, move_position_y)) {
            growth_amount += food.get_growth_value();
            game.eat_food();
        }
    }
}

// 增加成長值
void Saigyouji_Yuyuko_Fomo_class::increase_growth(int amount) {
    growth_amount += amount;
}

// 返回多少個fumo
int Saigyouji_Yuyuko_Fomo_class::get_length() {
    return length;
}