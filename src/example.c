#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Display *d;
    Window w;
    XEvent e;
    const char *msg = "Hello, World!";
    int s;

    // Xサーバーに接続
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Xサーバーに接続できませんでした\n");
        exit(1);
    }

    // デフォルトのスクリーン番号を取得
    // 1つのXサーバーは複数のスクリーンを管理できる
    // 物理ディスプレイでも仮想ディスプレイでも良い
    s = DefaultScreen(d);

    // ウィンドウの作成
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 100, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    
    // XSelectInputでイベントの種類を指定
    // 再描画（ExposureMask）とキー入力（KeyPressMask）のイベントを受け取る
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    // イベントループ
    while (1) {
        XNextEvent(d, &e);
        // ウィンドウが再描画を必要とする場合
        if (e.type == Expose) {
            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            XDrawString(d, w, DefaultGC(d, s), 50, 50, msg, strlen(msg));
        }
        // キー入力を受け取った場合
        if (e.type == KeyPress)
            break;
    }

    // Xサーバーとの接続を閉じる
    XCloseDisplay(d);
    return 0;
}
