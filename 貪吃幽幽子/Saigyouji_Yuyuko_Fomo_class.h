#pragma once

// 幽幽子fumo
class Saigyouji_Yuyuko_Fomo_class {
public:
    void initial(game_class& game); //幽幽子fumo初始設定
    void draw(sf::RenderWindow& window, game_class& game); // 畫出幽幽子fumo    
    void set_direction(direction_enum direction); // 設定移動方向    
    direction_enum get_direction(); // 返回移動方向    
    void move(game_class& game, food_class& food); // 幽幽子fumo移動    
    void increase_growth(int amount); // 增加成長值
    int get_length(); // 返回多少個fumo

private:
    std::vector<std::pair<int, int>> position; // 每個fumo位置
    int length; // 多少個fumo
    int move_distance; // 每次移動的距離
    int move_interval; // 需要多少次才能移動
    int move_delay; // 移動延遲 還需要多少次才能移動
    direction_enum direction; // 當前移動方向    
    int growth_amount; // 吃了多少食物移動時成長    
    sf::Texture texture; // texture 幽幽子fumo圖片
};