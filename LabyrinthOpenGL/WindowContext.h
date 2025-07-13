#pragma once
#include "Include.h"

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC);
void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC);

class WindowContext {
private:
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
    HFONT hFont;
    GLuint fontBase;
    UINT lastMsg;
    WPARAM lastWParam;
    LPARAM lastLParam;
    int width;
    int height;

    // Приватный конструктор
    WindowContext() :
        hwnd(nullptr), hdc(nullptr), hrc(nullptr), hFont(nullptr), fontBase(0),
        lastMsg(0), lastWParam(0), lastLParam(0), width(0), height(0) {}

public:
    // Запрет копирования
    WindowContext(const WindowContext&) = delete;
    WindowContext& operator=(const WindowContext&) = delete;

    static WindowContext& getInstance() {
        static WindowContext instance;
        return instance;
    }

    void setWindow(HWND hwnd_, HDC hdc_, HGLRC hrc_) {
        hwnd = hwnd_;
        hdc = hdc_;
        hrc = hrc_;
        updateSize();
    }

    void setFont(HFONT hFont_, GLuint fontBase_) {
        hFont = hFont_;
        fontBase = fontBase_;
    }

    void updateSize() {
        if (hwnd) {
            RECT rect;
            GetClientRect(hwnd, &rect);
            width = rect.right - rect.left;
            height = rect.bottom - rect.top;
            glViewport(0, 0, width, height);
        }
    }

    void setLastMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
        lastMsg = msg;
        lastWParam = wParam;
        lastLParam = lParam;
    }

    HWND& getHWND() { return hwnd; }
    HDC& getHDC() { return hdc; }
    HGLRC& getHRC() { return hrc; }
    HFONT& getFont() { return hFont; }
    GLuint& getFontBase() { return fontBase; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    UINT getLastMessage() const { return lastMsg; }
    WPARAM getLastWParam() const { return lastWParam; }
    LPARAM getLastLParam() const { return lastLParam; }
};

// WindowContext::getInstance().setLastMessage(uMsg, wParam, lParam);   в WindowProc