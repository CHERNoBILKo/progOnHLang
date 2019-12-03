/*

1. Понять, что делает эта программа и быть готовым объяснить в ней всё.
2. Заствить ее корректно (так, как  задауумно автором) работать на своих програмно-аппаратных средствах технике / тех, на которых делали все остальное.
3. Заставить её в зависимости от первого параметра командной строки выводить сообщения и вести протокол только по-английски (значение первого
параметра командной строки -- english), 
только по-русски (используя систему кодирования utf-8, значение первого параметра russian), двуязычно, при этом английский текст идет после русского как пояснительный, но равнозначно оформленный, а не в скобках (используя систему кодирования utf-8, значение первого параметра bilingual)

4. Ну и естественно, разобраться в какой последовательности и как создаются события в SDL2.

5. Задание простое: Необходимо при сворачивании окна / потери фокуса через некоторое время выдать сообщение, 
и/или перевести фокус на окно (сделать активным). 
Конкретные параметры и требования определяются индивидуальным вариантом.

Итого 5 подпунктов задания 3 ПЗ 2 ("Программирования на ЯВУ, 3 семестр, И9 -- направление "Программная инженерия", бакалавриат).

*/


#include <cstdlib>
#include <string>

#if defined(_WIN32) || defined(_WINDOWS)
#include "SDL.h"
#else

#include "SDL2/SDL.h"

#endif

char locale = 'r';

void fillScreen(SDL_Window *window) {
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, rand() % 255, rand() % 255, rand() % 255));

    SDL_UpdateWindowSurface(window);
}

int asmFunction() {
    static int internalValue = 1;

#ifdef __GNUC__
    __asm__("movl %0, %%eax\n\t"
            "add %%eax, %0"
    : "=r" (internalValue)
    : "r" (internalValue));
#elif _MSC_VER
    _asm {
        mov eax, internalValue
            add internalValue, eax
    };
#endif

    return internalValue;
}

int eventFilter(void *userdata, SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_q && event->key.keysym.mod == KMOD_LCTRL) {
                SDL_Event exitEvent = {SDL_QUIT};
                SDL_PushEvent(&exitEvent);
            }
            switch (locale) {
                case 'e':
                    SDL_Log("key Down %d", event->key.keysym.sym);
                    break;
                case 'r':
                    SDL_Log("Нажата клавиша %d", event->key.keysym.sym);
                    break;
                default:
                    SDL_Log("Нажата клавиша %d", event->key.keysym.sym);
                    SDL_Log("key Down %d", event->key.keysym.sym);
                    break;

            }
            break;
        case SDL_KEYUP:
            switch (locale) {
                case 'e':
                    SDL_Log("key Up %d", event->key.keysym.sym);
                    break;
                case 'r':
                    SDL_Log("Отпущена клавиша %d", event->key.keysym.sym);
                    break;
                default:
                    SDL_Log("Отпущена клавиша %d", event->key.keysym.sym);
                    SDL_Log("key Up %d", event->key.keysym.sym);
                    break;

            }
            break;
        case SDL_TEXTEDITING:
            switch (locale) {
                case 'e':
                    SDL_Log("Keyboard text editing (composition). Composition is '%s', cursor start from %d and selection lenght is %d",
                            event->edit.text, event->edit.start, event->edit.length);
                    break;
                case 'r':
                    SDL_Log("Редактировние текста клавиатурой (композиция). Композиция '%s', выделение начинается на %d и размер выделенного %d",
                            event->edit.text, event->edit.start, event->edit.length);
                    break;
                default:
                    SDL_Log("Редактировние текста клавиатурой (композиция). Композиция '%s', выделение начинается на %d и размер выделенного %d",
                            event->edit.text, event->edit.start, event->edit.length);
                    SDL_Log("Keyboard text editing (composition). Composition is '%s', cursor start from %d and selection lenght is %d",
                            event->edit.text, event->edit.start, event->edit.length);
                    break;
            }

            break;
        case SDL_TEXTINPUT:
            switch (locale) {
                case 'e':
                    SDL_Log("Keyboard text input. Text is '%s'", event->text.text);
                    break;
                case 'r':
                    SDL_Log("Ввод текста с клавиатуры. Введённый текст '%s'", event->text.text);
                    break;
                default:
                    SDL_Log("Ввод текста с клавиатуры. Введённый текст '%s'", event->text.text);
                    SDL_Log("Keyboard text input. Text is '%s'", event->text.text);
                    break;
            }

            break;
        case SDL_FINGERMOTION:
            SDL_Log("Finger: %li, x: %f, y: %f", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
            break;
        case SDL_FINGERDOWN:
            switch (locale) {
                case 'e':
                    SDL_Log("Finger: %ld down - x: %f, y: %f",
                            event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
                    break;
                case 'r':
                    SDL_Log("Палец: %ld опущен - x: %f, y: %f",
                            event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
                    break;
                default:
                    SDL_Log("Палец: %ld опущен - x: %f, y: %f",
                            event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
                    SDL_Log("Finger: %ld down - x: %f, y: %f",
                            event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
                    break;
            }

            break;
        case SDL_FINGERUP:
            switch (locale) {
                case 'e':
                    SDL_Log("Finger: %ld up - x: %f, y: %f",
                            event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
                    break;
                case 'r':
                    SDL_Log("Палец: %ld поднят - x: %f, y: %f",
                            event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
                    break;
                default:
                    SDL_Log("Палец: %ld поднят - x: %f, y: %f",
                            event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
                    SDL_Log("Finger: %ld up - x: %f, y: %f",
                            event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
                    break;
            }
            break;
        case SDL_MULTIGESTURE:

            switch (locale) {
                case 'e':
                    SDL_Log("Multi Gesture: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y,
                            event->mgesture.dTheta, event->mgesture.dDist);
                    SDL_Log("Multi Gesture: numDownTouch = %i", event->mgesture.numFingers);
                    break;
                case 'r':
                    SDL_Log("Мульти Жест: x = %f, y = %f, dУгл = %f, dРаст = %f", event->mgesture.x, event->mgesture.y,
                            event->mgesture.dTheta, event->mgesture.dDist);
                    SDL_Log("Мульти Жест: кол-во касаний = %i", event->mgesture.numFingers);
                    break;
                default:
                    SDL_Log("Мульти Жест: x = %f, y = %f, dУгл = %f, dРаст = %f", event->mgesture.x, event->mgesture.y,
                            event->mgesture.dTheta, event->mgesture.dDist);
                    SDL_Log("Мульти Жест: кол-во касаний = %i", event->mgesture.numFingers);
                    SDL_Log("Multi Gesture: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y,
                            event->mgesture.dTheta, event->mgesture.dDist);
                    SDL_Log("Multi Gesture: numDownTouch = %i", event->mgesture.numFingers);
                    break;
            }

            break;
        case SDL_DOLLARGESTURE:
            switch (locale) {
                case 'e':
                    SDL_Log("Gesture %ld performed, error: %f", event->dgesture.gestureId, event->dgesture.error);
                    break;
                case 'r':
                    SDL_Log("Произведён жест %ld , ошибка: %f", event->dgesture.gestureId, event->dgesture.error);
                    break;
                default:
                    SDL_Log("Произведён жест %ld , ошибкап: %f", event->dgesture.gestureId, event->dgesture.error);
                    SDL_Log("Gesture %ld performed, error: %f", event->dgesture.gestureId, event->dgesture.error);
                    break;
            }

            break;
        case SDL_DOLLARRECORD:
            switch (locale) {
                case 'e':
                    SDL_Log("Recorded gesture: %ld", event->dgesture.gestureId);
                    break;
                case 'r':
                    SDL_Log("Записанный жест: %ld", event->dgesture.gestureId);
                    break;
                default:
                    SDL_Log("Записанный жест: %ld", event->dgesture.gestureId);
                    SDL_Log("Recorded gesture: %ld", event->dgesture.gestureId);
                    break;
            }
            break;
        case SDL_MOUSEMOTION:
            switch (locale) {
                case 'e':
                    SDL_Log("Mouse Move. X=%d, Y=%d, RelativeX=%d, RelativeY=%d", event->motion.x, event->motion.y,
                            event->motion.xrel, event->motion.yrel);
                    break;
                case 'r':
                    SDL_Log("Мышь сдвинута. X=%d, Y=%d, Относительн.X=%d, Относительн.Y=%d", event->motion.x,
                            event->motion.y,
                            event->motion.xrel, event->motion.yrel);
                    break;
                default:
                    SDL_Log("Мышь сдвинута. X=%d, Y=%d, Относительн.X=%d, Относительн.Y=%d", event->motion.x,
                            event->motion.y,
                            event->motion.xrel, event->motion.yrel);
                    SDL_Log("Mouse Move. X=%d, Y=%d, RelativeX=%d, RelativeY=%d", event->motion.x, event->motion.y,
                            event->motion.xrel, event->motion.yrel);
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT)
                asmFunction();
            switch (locale) {
                case 'e':
                    SDL_Log("Mouse Button Down %u", event->button.button);
                    break;
                case 'r':
                    SDL_Log("Нажата клавиша мыши %u", event->button.button);
                    break;
                default:
                    SDL_Log("Нажата клавиша мыши %u", event->button.button);
                    SDL_Log("Mouse Button Down %u", event->button.button);
                    break;
            }

            break;
        case SDL_MOUSEBUTTONUP:
            switch (locale) {
                case 'e':
                    SDL_Log("Mouse Button Up %u", event->button.button);
                    break;
                case 'r':
                    SDL_Log("Отпущена клавиша мыши %u", event->button.button);
                    break;
                default:
                    SDL_Log("Отпущена клавиша мыши %u", event->button.button);
                    SDL_Log("Mouse Button Up %u", event->button.button);
                    break;
            }
            break;
        case SDL_MOUSEWHEEL:
            switch (locale) {
                case 'e':
                    SDL_Log("Mouse Wheel X=%d, Y=%d", event->wheel.x, event->wheel.y);
                    break;
                case 'r':
                    SDL_Log("Колёсико мыши X=%d, Y=%d", event->wheel.x, event->wheel.y);
                    break;
                default:
                    SDL_Log("Колёсико мыши X=%d, Y=%d", event->wheel.x, event->wheel.y);
                    SDL_Log("Mouse Wheel X=%d, Y=%d", event->wheel.x, event->wheel.y);
                    break;
            }

            break;
        case SDL_QUIT:
            switch (locale) {
                case 'e':
                    SDL_Log("User-requested quit");
                    break;
                case 'r':
                    SDL_Log("Пользователь запросил выход");
                    break;
                default:
                    SDL_Log("Пользователь запросил выход");
                    SDL_Log("User-requested quit");
                    break;
            }

            return 1;
        case SDL_WINDOWEVENT:
            switch (event->window.event) {
                case SDL_WINDOWEVENT_SHOWN:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d shown", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Окно %d показано", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Окно %d показано", event->window.windowID);
                            SDL_Log("Window %d shown", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d hidden", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Окно %d скрыто", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Окно %d скрыто", event->window.windowID);
                            SDL_Log("Window %d hidden", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    fillScreen(SDL_GetWindowFromID(event->window.windowID));

                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d exposed", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Окно %d открыто", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Окно %d открыто", event->window.windowID);
                            SDL_Log("Window %d exposed", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d moved to %d,%d", event->window.windowID, event->window.data1,
                                    event->window.data2);
                            break;
                        case 'r':
                            SDL_Log("Окно %d передвинуто на %d,%d", event->window.windowID, event->window.data1,
                                    event->window.data2);
                            break;
                        default:
                            SDL_Log("Окно %d передвинуто на %d,%d", event->window.windowID, event->window.data1,
                                    event->window.data2);
                            SDL_Log("Window %d moved to %d,%d", event->window.windowID, event->window.data1,
                                    event->window.data2);
                            break;
                    }

                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    SDL_Log("Window %d resized to %dx%d", event->window.windowID, event->window.data1,
                            event->window.data2);
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:

                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d size changed to %dx%d", event->window.windowID, event->window.data1,
                                    event->window.data2);
                            break;
                        case 'r':
                            SDL_Log("Окно %d размер изменился на %dx%d", event->window.windowID, event->window.data1,
                                    event->window.data2);
                            break;
                        default:
                            SDL_Log("Окно %d размер изменился на %dx%d", event->window.windowID, event->window.data1,
                                    event->window.data2);
                            SDL_Log("Window %d size changed to %dx%d", event->window.windowID, event->window.data1,
                                    event->window.data2);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d minimized", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Окно %d свернуто", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Окно %d свернуто", event->window.windowID);
                            SDL_Log("Window %d minimized", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d maximised", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Окно %d развёрнуто на весь экран", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Окно %d развёрнуто на весь экран", event->window.windowID);
                            SDL_Log("Window %d maximised", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d restored", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Окно %d развёрнуто", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Окно %d развёрнуто", event->window.windowID);
                            SDL_Log("Window %d restored", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Mouse entered window %d", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Мышь находится в окне %d", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Мышь находится в окне %d", event->window.windowID);
                            SDL_Log("Mouse entered window %d", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Mouse left window %d", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Мышь покинула окно %d", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Мышь покинула окно %d", event->window.windowID);
                            SDL_Log("Mouse left window %d", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d gained keyboard focus", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Окно %d получило фокус клавиатуры", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Окно %d получило фокус клавиатуры", event->window.windowID);
                            SDL_Log("Window %d gained keyboard focus", event->window.windowID);
                            break;
                    }

                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d lost keyboard focus", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Окно %d потеряло фокус клавиатуры", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Окно %d потеряло фокус клавиатуры", event->window.windowID);
                            SDL_Log("Window %d lost keyboard focus", event->window.windowID);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d closed", event->window.windowID);
                            break;
                        case 'r':
                            SDL_Log("Window %d закрыто", event->window.windowID);
                            break;
                        default:
                            SDL_Log("Window %d закрыто", event->window.windowID);
                            SDL_Log("Window %d closed", event->window.windowID);
                            break;
                    }

                    break;
                default:
                    switch (locale) {
                        case 'e':
                            SDL_Log("Window %d got unknown event %d", event->window.windowID, event->window.event);

                            break;
                        case 'r':
                            SDL_Log("Окно %d получило неизвестное событие %d", event->window.windowID,
                                    event->window.event);

                            break;
                        default:
                            SDL_Log("Окно %d получило неизвестное событие %d", event->window.windowID,
                                    event->window.event);
                            SDL_Log("Window %d got unknown event %d", event->window.windowID, event->window.event);
                            break;
                    }

                    break;
            }
            break;
        default:
            switch (locale) {
                case 'e':
                    SDL_Log("Got unknown event %d", event->type);

                    break;
                case 'r':
                    SDL_Log("Неизвестное событие %d", event->type);

                    break;
                default:
                    SDL_Log("Неизвестное событие %d", event->type);
                    SDL_Log("Got unknown event %d", event->type);
                    break;
            }
            break;
    }

    return 0;
}

Uint32 customEventFunction(Uint32 interval, SDL_Window *param) {
    SDL_Event event = {SDL_WINDOWEVENT};

    switch (locale) {
        case 'e':
            SDL_Log("Timer signaled with interval %d ms", interval);
            break;
        case 'r':
            SDL_Log("Сработал таймер на %d мс", interval);
            break;
        default:
            SDL_Log("Сработал таймер на %d мс", interval);
            SDL_Log("Timer signaled with interval %d ms", interval);
            break;
    }

    event.window.windowID = SDL_GetWindowID(param);
    event.window.event = SDL_WINDOWEVENT_EXPOSED;

    SDL_PushEvent(&event);
    return (interval);
}

Uint32 repeatOnceFunction(Uint32 interval, SDL_Window *param) {
    SDL_Event exitEvent = {SDL_QUIT};


    switch (locale) {
        case 'e':
            SDL_Log("Timer signaled with interval %d ms", interval);
            break;
        case 'r':
            SDL_Log("Сработал таймер на %d мс", interval);
            break;
        default:
            SDL_Log("Сработал таймер на %d мс", interval);
            SDL_Log("Timer signaled with interval %d ms", interval);
            break;
    }

    if (asmFunction() != 0) {
        SDL_HideWindow(param);

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Something going wrong", "Find me! I'm scared", nullptr);

        SDL_Delay(15000); /* 15 sec */


        switch (locale) {
            case 'e':
                SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "You didn't find me! You disappointed me... I'm leaving.");
                break;
            case 'r':
                SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ты не нашел меня! Ты расстроил меня... Я ухожу.");
                break;
            default:
                SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ты не нашел меня! Ты расстроил меня... Я ухожу.");
                SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "You didn't find me! You disappointed me... I'm leaving.");
                break;
        }
        SDL_PushEvent(&exitEvent);
    }

    return 0;
}

void clearFunction(void) {
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    SDL_Window *windowContext = nullptr;
    SDL_TimerID repeatOnceFunctionTimer;
    SDL_TimerID customEventFunctionTimer;
    if (argc >= 1) {
        if (strncmp(argv[1],"--english",9)==0) {
            locale = 'e';
        } else if (strncmp(argv[1],"--russian",9)==0) { locale = 'r'; }
        else if (strncmp(argv[1],"--bilingual",11)==0) { locale = 'i'; }
        else {
            locale = 'e';
        }
    }

    atexit(clearFunction);
    srand((unsigned int) NULL);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL2. See the log for more info.",
                                 nullptr);
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to init SDL2, error: %s", SDL_GetError());
        return 1;
    }

    SDL_SetEventFilter(eventFilter, nullptr);
    switch (locale) {
        case 'e':
            SDL_Log("Start creating window");
            break;
        case 'r':
            SDL_Log("Начинается создание окна");
            break;
        default:
            SDL_Log("Начинается создание окна");
            SDL_Log("Start creating window");
            break;
    }

    if (!(windowContext = SDL_CreateWindow("SDL2: Magic Events", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,
                                           480, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE))) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create window. See the log for more info.",
                                 nullptr);
        switch (locale) {
            case 'e':
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window, error: %s", SDL_GetError());
                break;
            case 'r':
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Неудалось создать окно, ошибка: %s", SDL_GetError());
                break;
            default:
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Неудалось создать окно, ошибка: %s", SDL_GetError());
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window, error: %s", SDL_GetError());
                break;
        }

        return 1;
    } else {
        switch (locale) {
            case 'e':
                SDL_Log("Creating window - succeeded");
                break;
            case 'r':
                SDL_Log("Окно успешно создано");
                break;
            default:
                SDL_Log("Окно успешно создано");
                SDL_Log("Creating window - succeeded");
                break;
        }

    }

    if (!(customEventFunctionTimer = SDL_AddTimer(2000 /* 2 sec */,
                                                  reinterpret_cast<SDL_TimerCallback>(customEventFunction),
                                                  windowContext))) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                                 "Unable to create custom event timer. See the log for more info.", windowContext);
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create custom event timer, error: %s", SDL_GetError());
    }

    if (!(repeatOnceFunctionTimer = SDL_AddTimer(10000 /* 10 sec */,
                                                 reinterpret_cast<SDL_TimerCallback>(repeatOnceFunction),
                                                 windowContext))) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                                 "Unable to create repeat once timer. See the log for more info.", windowContext);
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create repeat once timer, error: %s", SDL_GetError());
    }

    SDL_WaitEvent(nullptr);

    SDL_RemoveTimer(repeatOnceFunctionTimer);
    SDL_RemoveTimer(customEventFunctionTimer);
    switch (locale) {
        case 'e':
            SDL_Log("Start destroying window");
            break;
        case 'r':
            SDL_Log("Начинается удаление окна");

            break;
        default:
            SDL_Log("Начинается удаление окна");
            SDL_Log("Start destroying window");
            break;
    }

    SDL_DestroyWindow(windowContext);
    windowContext = nullptr;
    switch (locale) {
        case 'e':
            SDL_Log("destroying window - succeeded");
            break;
        case 'r':
            SDL_Log("Удаление окна прошло успешно");
            break;
        default:
            SDL_Log("Удаление окна прошло успешно");
            SDL_Log("destroying window - succeeded");
            break;
    }


    return 0;
}
