#ifndef POINT3D_H
#define POINT3D_H

#include <QScriptValue>
#include <QString>
#include <QVariant>

#include "constants.h"
#include "metatyperegistry.h"
#include "vector3d.h"


class Point3D {

    public:
        int x;
        int y;
        int z;

        Point3D() = default;
        Point3D(int x, int y, int z);

        bool operator==(const Point3D &other) const;
        bool operator!=(const Point3D &other) const;

        Point3D operator+(const Vector3D &vector) const;
        Point3D operator-(const Vector3D &vector) const;

        Vector3D operator-(const Point3D &other) const;

        QString toString() const;

        static QString toUserString(const Point3D &point);
        static void fromUserString(const QString &string, Point3D &point);

        static QString toJsonString(const Point3D &point, Options options = NoOptions);
        static void fromVariant(const QVariant &variant, Point3D &point);

        static QScriptValue toScriptValue(QScriptEngine *engine, const Point3D &point);
        static void fromScriptValue(const QScriptValue &object, Point3D &point);
};

PT_DECLARE_SERIALIZABLE_METATYPE(Point3D)

#endif // POINT3D_H
