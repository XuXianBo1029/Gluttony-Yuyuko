#include "Header.h"

// 宣告遊戲
void game_class::initial(sf::RenderWindow& window) {
    game_started = false;
    // Saigyouji Yuyuko Fumo spin.gif
    Saigyouji_Yuyuko_Fumo_spin_gif_textures.clear();
    for (int i = 0; i < 58; i++) {
        sf::Texture texture;
        Saigyouji_Yuyuko_Fumo_spin_gif_textures.push_back(texture);
        if (!Saigyouji_Yuyuko_Fumo_spin_gif_textures[i].loadFromFile("./images/Saigyouji Yuyuko Fumo spin gif/Saigyouji Yuyuko Fumo spin-" + std::to_string(i) + ".png")) {
            printf("./images/Saigyouji Yuyuko Fumo spin gif/Saigyouji Yuyuko Fumo spin-%d.png load failed.\n", i);
            return;
        }
    }
    Saigyouji_Yuyuko_Fumo_spin_gif_i = 43;

    // 開始按鈕
    start_button.setFillColor(sf::Color::White);

    // 開始按鈕字
    if (!start_button_font.loadFromFile("arial.ttf")) {
        printf("arial.ttf load failed.\n");
        return;
    }
    start_button_text.setFont(start_button_font);
    start_button_text.setString("START");
    start_button_text.setFillColor(sf::Color::Red);
    start_button_text.setStyle(sf::Text::Bold);
    map_width = 15;
    map_height = 15;
    map_object.resize(map_width, std::vector<object_name_enum>(map_height, object_name_enum::None));    
    has_food = false;
    for (int x = 0; x < map_object.size(); x++) {
        for (int y = 0; y < map_object[x].size(); y++) {
            map_object[x][y] = object_name_enum::None;
        }
    }
    map_object[map_width / 2][map_height / 2] = object_name_enum::Saigyouji_Yuyuko_Fomo;
}

// 檢查遊戲是否開始
bool game_class::check_game_started() {
    return game_started;
}

// 返回地圖上有什麼
object_name_enum game_class::get_map_object(int position_x, int position_y) {
    return map_object[position_x][position_y];
}

// 設定地圖上有什麼
void game_class::set_map_object(int position_x, int position_y, object_name_enum object) {
    map_object[position_x][position_y] = object;
}

// 畫遊戲開始畫面
void game_class::draw_game_start(sf::RenderWindow& window) {
    // Saigyouji_Yuyuko_Fumo_spin_gif_sprites    
    float x, y;
    sf::Sprite sprite;
    sprite.setTexture(Saigyouji_Yuyuko_Fumo_spin_gif_textures[Saigyouji_Yuyuko_Fumo_spin_gif_i]);
    x = (float)window.getSize().x / 2 / (float)sprite.getGlobalBounds().width;
    y = (float)window.getSize().y / 2 / (float)sprite.getGlobalBounds().height;
    sprite.setScale(x, y);
    x = (float)sprite.getGlobalBounds().width / 2;
    y = (float)sprite.getGlobalBounds().height / 2;
    sprite.setOrigin(x, y);
    x = (float)window.getSize().x / 2;
    y = (float)window.getSize().y / 2;
    sprite.setPosition(x, y);
    window.draw(sprite);
    //Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i].setTexture(Saigyouji_Yuyuko_Fumo_spin_gif_textures[Saigyouji_Yuyuko_Fumo_spin_gif_i]);    
    //x = (float)window.getSize().x * 0.25 / (float)Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i].getGlobalBounds().width;
    //y = (float)window.getSize().y * 0.25 / (float)Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i].getGlobalBounds().height;    
    //Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i].setScale(x, y);            
    //x = (float)Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i].getGlobalBounds().width / 2;
    //y = (float)Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i].getGlobalBounds().height / 2;    
    //Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i].setOrigin(x, y);    
    //Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i].setPosition(x, y);    
    //window.draw(Saigyouji_Yuyuko_Fumo_spin_gif_sprites[Saigyouji_Yuyuko_Fumo_spin_gif_i]);
    Saigyouji_Yuyuko_Fumo_spin_gif_i++;
    if (Saigyouji_Yuyuko_Fumo_spin_gif_i >= Saigyouji_Yuyuko_Fumo_spin_gif_textures.size()) {
        Saigyouji_Yuyuko_Fumo_spin_gif_i = 43;
    }

    // 開始按鈕
    x = (float)window.getSize().x / 4;
    y = (float)window.getSize().y / 14;
    start_button.setSize({ x, y });
    x = (float)start_button.getGlobalBounds().width / 2;
    y = (float)start_button.getGlobalBounds().height / 2;
    start_button.setOrigin(x, y);
    x = (float)window.getSize().x / 2;
    y = (float)window.getSize().y * 86 / 100;
    start_button.setPosition(x, y);
    window.draw(start_button);

    // 開始按鈕 字
    start_button_text.setCharacterSize(window.getSize().x / 20);
    x = (float)start_button_text.getGlobalBounds().width / 2;
    y = (float)start_button_text.getGlobalBounds().height / 2;
    start_button_text.setOrigin(x, y);
    x = (float)window.getSize().x / 2;
    y = (float)window.getSize().y * 85 / 100;
    start_button_text.setPosition(x, y);
    window.draw(start_button_text);
}

// 按下遊戲開始
void game_class::start_game(int mouse_x, int mouse_y) {
    if (start_button.getGlobalBounds().contains((float)mouse_x, (float)mouse_y)) {
        game_started = true;
    }
}

// 返回 地圖上有沒有食物
bool game_class::get_has_food() {
    return has_food;
}

// 地圖上產生食物
void game_class::generate_food() {
    has_food = true;
}

// 地圖上食物被吃了
void game_class::eat_food() {
    has_food = false;
}

// 回傳地圖寬高
int game_class::get_map_width() {
    return map_width;
}

int game_class::get_map_height() {
    return map_height;
}