#include <iostream>
#include "xcbeventhandle.h"
#include <QApplication>
using namespace std;
#define ESTCAP_ERR_NODISPLAY          2
#define ESTCAP_ERR_NODAMAGE           5

const xcb_query_extension_reply_t *m_pXrandrExt;
xcb_connection_t * m_pXcbConnection;
xcb_screen_t *pScreen;

xcb_screen_t *  GetDisplayOfScreen(int screen)
{
    xcb_screen_iterator_t iter;

    iter = xcb_setup_roots_iterator(xcb_get_setup(m_pXcbConnection));
    for (; iter.rem; --screen, xcb_screen_next(&iter))
        if (screen == 0)
            return iter.data;

    return NULL;
}

int main(int argc,   char* argv [])
{
    QApplication app(argc, argv);
    qDebug() <<"************************************";
    qDebug() <<"********welcome use screen**********";
    qDebug() <<"************************************";
    int scr;
    m_pXcbConnection = xcb_connect(":0", &scr);
    if (!m_pXcbConnection || xcb_connection_has_error(m_pXcbConnection))
    {
        printf("Failed to connect to display.");
        m_pXcbConnection = NULL;
        return ESTCAP_ERR_NODISPLAY;
    }

    pScreen = GetDisplayOfScreen(scr);
    if (!pScreen) {
        printf("Failed to get screen for display.");
        return ESTCAP_ERR_NODISPLAY;
    }

    m_pXrandrExt = xcb_get_extension_data(m_pXcbConnection, &xcb_randr_id);
    if (!m_pXrandrExt) {
        printf("Failed to find XDAMAGE.");
        return ESTCAP_ERR_NODAMAGE;
    }

    XcbEventFilter filter(m_pXrandrExt->first_event);
    app.installNativeEventFilter(&filter);
    return app.exec();
}

