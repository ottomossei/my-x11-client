#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Button
{
public:
    Button(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    void Draw(Display *display, Window window, GC gc)
    {
        XFillRectangle(display, window, gc, x, y, width, height);
    }

    bool IsInside(int mouseX, int mouseY)
    {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }

private:
    int x, y, width, height;
};

class SimpleWindow
{
public:
    SimpleWindow(int width, int height) : width(width), height(height), button(20, 20, 10, 10)
    {
        display = XOpenDisplay(nullptr);
        if (display == nullptr)
        {
            throw std::runtime_error("Cannot open display");
        }
        screen = DefaultScreen(display);
        window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1,
                                     BlackPixel(display, screen), WhitePixel(display, screen));
        XSelectInput(display, window, ExposureMask | ButtonPressMask);
        XMapWindow(display, window);
    }

    ~SimpleWindow()
    {
        XCloseDisplay(display);
    }

    void Run()
    {
        XEvent event;
        bool running = true;
        while (running)
        {
            XNextEvent(display, &event);
            if (!ProcessEvent(event))
            {
                running = false;
            }
        }
    }

private:
    Display *display;
    int screen;
    Window window;
    int width;
    int height;
    std::string message = "Hello, World!";
    Button button;

    bool ProcessEvent(const XEvent &event)
    {
        switch (event.type)
        {
        case Expose:
            return HandleExposeEvent(event);
        case ButtonPress:
            return HandleButtonPressEvent(event);
        default:
            return true;
        }
    }

    bool HandleExposeEvent(const XEvent &event)
    {
        button.Draw(display, window, DefaultGC(display, screen));
        XDrawString(display, window, DefaultGC(display, screen), 50, 50, message.c_str(), message.length());
        return true;
    }

    bool HandleButtonPressEvent(const XEvent &event)
    {
        if (button.IsInside(event.xbutton.x, event.xbutton.y))
        {
            return false; // ボタン内でクリックされた場合はループを終了
        }
        return true; // それ以外の場合は続行
    }
};

int main()
{
    try
    {
        SimpleWindow win(200, 100);
        win.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
