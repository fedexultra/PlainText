#ifndef CHARACTERSTATS_H
#define CHARACTERSTATS_H

#include <QScriptValue>
#include <QString>
#include <QVariant>

#include "constants.h"
#include "metatyperegistry.h"


class CharacterStats {

    public:
        static const int NUM_STATS = 6;

        int value[NUM_STATS];

        CharacterStats() = default;
        CharacterStats(int value);

        int total() const;

        bool operator==(const CharacterStats &other) const;
        bool operator!=(const CharacterStats &other) const;

        CharacterStats operator+(const CharacterStats &other) const;
        CharacterStats &operator+=(const CharacterStats &other);

        bool isNull() const;

        QString toString() const;

        static QString toUserString(const CharacterStats &stats);
        static void fromUserString(const QString &string, CharacterStats &stats);

        static QString toJsonString(const CharacterStats &stats, Options options = NoOptions);
        static void fromVariant(const QVariant &variant, CharacterStats &stats);

        static QScriptValue toScriptValue(QScriptEngine *engine, const CharacterStats &stats);
        static void fromScriptValue(const QScriptValue &object, CharacterStats &stats);
};

typedef QList<CharacterStats> CharacterStatsList;

PT_DECLARE_SERIALIZABLE_METATYPE(CharacterStats)

#endif // CHARACTERSTATS_H
