#include "propertygetcommand.h"

#include "util.h"


#define super ApiCommand

PropertyGetCommand::PropertyGetCommand(Player *player, QObject *parent) :
    super(player, parent) {

    setDescription("Syntax: api-property-get <request-id> <object-id> <property-name>");
}

PropertyGetCommand::~PropertyGetCommand() {
}

void PropertyGetCommand::execute(const QString &command) {

    super::execute(command);

    GameObjectPtr object = takeObject(currentArea()->objects());
    if (object.isNull()) {
        sendError(404, "Object not found");
        return;
    }

    QString propertyName = Util::fullPropertyName(object.cast<GameObject *>(), takeWord());

    const QMetaObject *metaObject = object->metaObject();
    int propertyIndex = metaObject->indexOfProperty(propertyName.toAscii().constData());
    QMetaProperty metaProperty = metaObject->property(propertyIndex);

    QVariantMap data;
    data["id"] = object->id();
    data["propertyName"] = propertyName;
    data["readOnly"] = !metaProperty.isStored();
    data[propertyName] = object->property(propertyName.toAscii().constData());
    sendReply(data);
}