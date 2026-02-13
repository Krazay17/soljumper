#pragma once
#include <map>

class AppState;

enum AppStates {
    MENU,
    GAME,
};
class App {
    private:
    static constexpr double dt = 1.0 / 120.0;
    bool running = true;
    std::map<AppStates, AppState*> AppReg;
    AppState *currentState;
    public:
    void run();
    void fillRegistry();
    void changeAppState(AppStates state);
};