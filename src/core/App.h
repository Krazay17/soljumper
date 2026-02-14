#pragma once
#include <map>

class AppState;

enum AppStates {
    MENU,
    GAME,
    MINING,
};
class App {
    private:
    static constexpr double dt = 1.0 / 120.0;
    float smoothedFps = 60.0f;
    bool running = true;
    bool showFps = true;
    std::map<AppStates, AppState*> AppReg;
    AppState *currentState;
    public:
    void run();
    void fillRegistry();
    void changeAppState(AppStates state);
    void toggleFps();
};