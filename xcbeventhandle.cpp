#include "xcbeventhandle.h"
#include <QCoreApplication>

XcbEventFilter::XcbEventFilter(int randrBase):
m_randrBase(randrBase)
{

}

xcb_connection_t *XcbEventFilter::connection()
{
    static xcb_connection_t *s_con = nullptr;
    if (!s_con) {
        s_con = reinterpret_cast<xcb_connection_t*>(qApp->property("x11Connection").value<void*>());
    }
    Q_ASSERT(qApp);
    return s_con;
}

bool XcbEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long int *result)
{
    Q_UNUSED(result)
    if (eventType != "xcb_generic_event_t") {
        return false;
    }
    auto event = static_cast<xcb_generic_event_t *>(message);
    const uint8_t m_eventType = event->response_type & ~0x80;
    if (m_eventType == m_randrBase + XCB_RANDR_SCREEN_CHANGE_NOTIFY) {

        auto *xrrEvent=reinterpret_cast<xcb_randr_screen_change_notify_event_t*>(event);
        qDebug() << xrrEvent->width << xrrEvent->height <<xrrEvent->mwidth <<xrrEvent->mheight;

    }
    return false;
}
