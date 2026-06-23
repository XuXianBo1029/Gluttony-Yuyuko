#pragma once

// 音樂管理
class sound_class {
public:    
    static sound_class& getInstance(); // 創建單例模式的SoundManager，確保只有一個實例存在
    void load_sound(std::string name, std::string filename); // 載入聲音
    void sound_play(std::string name); // 撥放聲音
    sf::SoundBuffer get_sound_buffer(std::string name); // 撥放聲音

private:
    sound_class() {} // 私有構造函數，以確保只有一個實例
    std::unordered_map<std::string, std::pair<sf::SoundBuffer, sf::Sound>> sounds;
    sf::Sound sound; // 將 sf::Sound 聲明為成員變數
};