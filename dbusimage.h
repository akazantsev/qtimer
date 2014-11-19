#ifndef DBUSIMAGE_H
#define DBUSIMAGE_H

#include <QMetaType>
#include <QDBusArgument>

class QImage;

class DBusImage
{
public:
    static const int id;

    DBusImage() = default;
    DBusImage(const QImage &image);

    int width;
    int height;
    int rowstride;
    bool hasAlpha;
    int bitsPerSample;
    int channels;
    QByteArray imageData;
};

Q_DECLARE_METATYPE(DBusImage)

QDBusArgument &operator << (QDBusArgument &arg, const DBusImage &image);
const QDBusArgument &operator >> (const QDBusArgument &arg, DBusImage &image);

#endif // DBUSIMAGE_H
