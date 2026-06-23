#pragma once

// 食物
class food_class {
public:
    void initial(food_name_enum food_name, game_class& game, sf::RenderWindow& window); // 食物初始化設定    
    bool check_position(int x, int y); // 檢查輸入位置是否一樣    
    void move(game_class& game, Saigyouji_Yuyuko_Fomo_class& Saigyouji_Yuyuko_Fomo); // 食物移動    
    void random_move(game_class& game, Saigyouji_Yuyuko_Fomo_class& Saigyouji_Yuyuko_Fomo); // 食物隨機移動
    void escape_move(game_class& game, Saigyouji_Yuyuko_Fomo_class& Saigyouji_Yuyuko_Fomo); // 食物與幽幽子fumo同樣方向移動
    bool check_exist(); // 檢查食物是否存在    
    int get_growth_value(); // 返回生長值
    void draw(sf::RenderWindow& window, game_class& game); // 畫出食物
    bool play_sound(); // 播放音效
    food_name_enum get_food_name();

private:
    food_name_enum name; // 名字
    object_name_enum object_name; // 物件名稱
    float exist_time; // 存在時間
    int position_x, position_y; // 位置    
    int move_distance; // 每次移動的距離
    int move_interval; // 需要多少次才能移動
    int move_delay; // 移動延遲 還需要多少次才能移動    
    direction_enum direction; // 移動方向
    int growth_value; // 食物的成長值
    sf::Texture texture; // texture 圖片
    bool should_play_sound; // 吃食物播放音效
};