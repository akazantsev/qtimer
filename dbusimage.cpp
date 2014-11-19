#include <QDBusMetaType>
#include <QDBusArgument>
#include <QImage>
#include <QDebug>

#include "dbusimage.h"

QDBusArgument &operator << (QDBusArgument &arg, const DBusImage &image)
{
    arg.beginStructure();
    arg << image.width << image.height << image.rowstride << image.hasAlpha
        << image.bitsPerSample << image.channels << image.imageData;
    arg.endStructure();

    return arg;
}

const QDBusArgument &operator >> (const QDBusArgument &arg, DBusImage &image)
{
    arg.beginStructure();
    arg >> image.width >> image.height >> image.rowstride >> image.hasAlpha
        >> image.bitsPerSample >> image.channels >> image.imageData;
    arg.endStructure();

    return arg;
}

DBusImage::DBusImage(const QImage &image)
{
    width = image.width();
    height = image.height();
    rowstride = image.bytesPerLine();
    hasAlpha = image.hasAlphaChannel();
    channels = 4; // I like 4
    bitsPerSample = image.depth() / channels;

    imageData = QByteArray(reinterpret_cast<const char*> (image.rgbSwapped().bits()),
                           image.byteCount());
}

const int DBusImage::id(qDBusRegisterMetaType<DBusImage>());
