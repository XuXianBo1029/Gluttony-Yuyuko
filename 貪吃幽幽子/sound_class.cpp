#include "Header.h"

// 創建單例模式的SoundManager，確保只有一個實例存在
sound_class& sound_class::getInstance() {
    static sound_class instance;
    return instance;
}

// 載入聲音
void sound_class::load_sound(std::string name, std::string filename) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filename)) {
        sounds[name].first = buffer;        
    }
    else {
        printf("%s load failed.\n", filename.c_str());
    }
}

// 撥放聲音
void sound_class::sound_play(std::string name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        sounds[name].second.setBuffer(sounds[name].first);
        sounds[name].second.play();
    }
    else {
        printf("error, sounds can't find.\n");
    }
}

// 撥放聲音
sf::SoundBuffer sound_class::get_sound_buffer(std::string name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        return it->second.first;
    }
    else {
        printf("error, sounds can't find.\n");
        return sf::SoundBuffer();
    }
}