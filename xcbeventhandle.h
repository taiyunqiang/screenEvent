// Qt
#include <QDebug>

#include <QAbstractNativeEventFilter>
#include <xcb/xcb.h>
#include <xcb/randr.h>
class XcbEventFilter : public QAbstractNativeEventFilter
{
public:
    XcbEventFilter(int randrBase);
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long int *result) override;
    xcb_connection_t * connection();
    int m_randrBase;
};
