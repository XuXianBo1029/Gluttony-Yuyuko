#include "Header.h"

int main()
{
    // 創建主要視窗
    sf::RenderWindow window(sf::VideoMode(800, 800), L"貪吃幽幽子");
    window.setFramerateLimit(30);
    
    // 視窗圖標icon設定
    sf::Image icon;
    if (!icon.loadFromFile("./images/Saigyouji Yuyuko Fumo.png")) {
        printf("/images/Saigyouji Yuyuko Fumo.png load failed.");
        return 0;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // 宣告遊戲 初始化
    game_class game;
    game.initial(window);
    
    // 宣告音效
    bool play_sound = false;
    food_name_enum play_sound_food_name;    
    sound_class& sounds = sound_class::getInstance();
    sf::Sound sound;
    // 讀取音效
    sounds.load_sound("se_pldead00", "./music/se_pldead00.wav");
    sounds.load_sound("Minecraft Eating Sound Effect", "./music/Minecraft Eating Sound Effect.wav");    

    // 宣告出幽幽子fumo玩家 初始化幽幽子fumo
    Saigyouji_Yuyuko_Fomo_class Saigyouji_Yuyuko_Fomo;
    Saigyouji_Yuyuko_Fomo.initial(game);

    // 隨機
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);    

    // 宣告食物
    food_class food;
    float random_index = dist(gen);
    if (random_index <= 0.5) {
        food.initial(food_name_enum::cola, game, window);
    } else if (random_index <= 0.9) {
        food.initial(food_name_enum::hamburger, game, window);
    } else if (random_index <= 1.0) {
        food.initial(food_name_enum::Niwatari_Kutaka_Fumo, game, window);
    }
    game.generate_food();    

    // 時間
    sf::Clock clock;

    // 視窗還開著就執行迴圈
    while (window.isOpen()) {        
        sf::Event event; // 事件
        // 事件迴圈
        while (window.pollEvent(event)) {
            // 檢查哪一種事件
            // 視窗關閉式健
            if (event.type == sf::Event::Closed) {
                window.close();
            // 按鍵事件
            } else if (event.type == sf::Event::KeyPressed) {
                // 設定方向
                if (event.key.code == sf::Keyboard::Up) {
                    if (Saigyouji_Yuyuko_Fomo.get_direction() != direction_enum::Up &&
                        (Saigyouji_Yuyuko_Fomo.get_length() == 1 ||
                        Saigyouji_Yuyuko_Fomo.get_direction() != direction_enum::Down)) {
                        Saigyouji_Yuyuko_Fomo.set_direction(direction_enum::Up);
                    }
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    if (Saigyouji_Yuyuko_Fomo.get_direction() != direction_enum::Down &&
                        (Saigyouji_Yuyuko_Fomo.get_length() == 1 ||
                        Saigyouji_Yuyuko_Fomo.get_direction() != direction_enum::Up)) {
                        Saigyouji_Yuyuko_Fomo.set_direction(direction_enum::Down);
                    }
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    if (Saigyouji_Yuyuko_Fomo.get_direction() != direction_enum::Left &&
                        (Saigyouji_Yuyuko_Fomo.get_length() == 1 ||
                        Saigyouji_Yuyuko_Fomo.get_direction() != direction_enum::Right)) {
                        Saigyouji_Yuyuko_Fomo.set_direction(direction_enum::Left);
                    }
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    if (Saigyouji_Yuyuko_Fomo.get_direction() != direction_enum::Right &&
                        (Saigyouji_Yuyuko_Fomo.get_length() == 1 ||
                        Saigyouji_Yuyuko_Fomo.get_direction() != direction_enum::Left)) {
                        Saigyouji_Yuyuko_Fomo.set_direction(direction_enum::Right);
                    }
                }
            // 滑鼠按鍵事件
            } else if (event.type == sf::Event::MouseButtonPressed) {
                // 滑鼠按下左鍵
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // 如果遊戲還沒開始
                    if (game.check_game_started() == false) {
                        game.start_game(event.mouseButton.x, event.mouseButton.y);
                    }                    
                }
            }
        }        

        // 如果遊戲還沒開始
        if (game.check_game_started() == false) {
            if (clock.getElapsedTime().asMilliseconds() >= 100) {
                // 清視窗畫面
                window.clear();

                // 畫出遊戲開始按鈕
                game.draw_game_start(window);

                // 視窗顯示            
                window.display();

                clock.restart();
            }            
        } else if (game.check_game_started() == true) {
            if (clock.getElapsedTime().asMilliseconds() >= 100) {
                // 清視窗畫面
                window.clear();

                // 幽幽子fumo移動
                Saigyouji_Yuyuko_Fomo.move(game, food);                

                // 食物移動
                food.move(game, Saigyouji_Yuyuko_Fomo);                

                // 畫出幽幽子fumo            
                Saigyouji_Yuyuko_Fomo.draw(window, game);                

                // 畫食物
                food.draw(window, game);

                // 是否要播放吃食物音效
                if (food.play_sound()) {
                    play_sound = true;
                    play_sound_food_name = food.get_food_name();                    
                }                

                // 視窗顯示
                window.display();                                                                

                // 產生食物
                if (game.get_has_food() == false) {
                    random_index = dist(gen);
                    if (random_index <= 0.1) {
                        food.initial(food_name_enum::cola, game, window);
                    }
                    else if (random_index <= 0.2) {
                        food.initial(food_name_enum::hamburger, game, window);
                    }
                    else if (random_index <= 1.0) {
                        food.initial(food_name_enum::Niwatari_Kutaka_Fumo, game, window);
                    }
                    game.generate_food();
                }                

                //播放吃食物音效
                if (play_sound) {
                    play_sound = false;
                    sounds.sound_play("Minecraft Eating Sound Effect");
                    if (play_sound_food_name == food_name_enum::Niwatari_Kutaka_Fumo ||
                        play_sound_food_name == food_name_enum::Reiuji_Utsuho_Fumo ||
                        play_sound_food_name == food_name_enum::Cirno_Fumo) {
                        sounds.sound_play("se_pldead00");
                    }
                }

                clock.restart();
            }            
        }                        
    }

    return 0;
}