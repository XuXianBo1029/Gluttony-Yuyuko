#pragma once

class game_class {
public:
    void initial(sf::RenderWindow& window); // 遊戲初始化 
    bool check_game_started(); // 檢查遊戲是否開始
    object_name_enum get_map_object(int position_x, int position_y); // 返回地圖物件
    void set_map_object(int position_x, int position_y, object_name_enum); // 設定地圖物件
    void draw_game_start(sf::RenderWindow& window); // 畫遊戲開始畫面    
    void start_game(int mouse_x, int mouse_y); // 按下遊戲開始           
    bool get_has_food(); // 返回 地圖上有沒有食物        
    void generate_food(); // 地圖上產生食物
    void eat_food(); // 地圖上食物被吃了
    int get_map_width();
    int get_map_height();

private:
    bool game_started; // 遊戲是否開始
    std::vector<std::vector<object_name_enum>> map_object; // 地圖物件
    std::vector<sf::Texture> Saigyouji_Yuyuko_Fumo_spin_gif_textures; // 幽幽子gif
    //vector<Sprite> Saigyouji_Yuyuko_Fumo_spin_gif_sprites; // 幽幽子gif
    int Saigyouji_Yuyuko_Fumo_spin_gif_i; // 幽幽子gif 第i張
    sf::RectangleShape start_button; // 開始按鈕
    sf::Font start_button_font; // 開始按鈕字型
    sf::Text start_button_text; // 開始按鈕字
    int map_width; // 地圖寬
    int map_height; // 地圖高    
    bool has_food; // 地圖上使否有食物
};