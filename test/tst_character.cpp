#include "tst_character.h"

void TestCharacter::initTestCase()
{

}

void TestCharacter::cleanupTestCase()
{

}

TestCharacter::TestCharacter(QObject *parent) : QObject(parent)
{

}

void TestCharacter::testConstructor()
{
    Character *character = new Character( QString("David Caine") );

    QTRY_COMPARE(character->getLabel(), QString("DaCa"));
    delete character;

    character = new Character( QString("Matthew"));
    QTRY_COMPARE(character->getLabel(), QString("Ma"));
    delete character;

    character = new Character( QString("Galactron of the 4th World Order"));
    QTRY_COMPARE(character->getLabel(), QString("GaOfTh4tWoOr"));

    character = new Character( QString("Samuel Ricker"), QString("Sammy"),
                               QString("SaRk"));
    QTRY_COMPARE(character->getLabel(), QString("SaRk"));
}

void TestCharacter::testSerialize()
{
    Novel *novel = new Novel(QString("My Title"));
    QList<Scene *> scenes = QList<Scene *>();
    scenes.append(new Scene("Scene 1", "Scene 1 Action"));
    scenes[0]->setId(123);
    scenes.append(new Scene("Scene 2", "Scene 2 Action"));
    scenes[1]->setId(55);
    scenes.append(new Scene("Scene 3", "Scene 3 Action"));
    scenes[2]->setId(42);
    Character *c = new Character(QString("Theodore Roosevelt"),
                                 QString("Teddy"),
                                 QString(),
                                 QImage(),
                                 QColor("#ffaaff"),
                                 novel,
                                 4);

    QJsonObject jCharacter = c->serialize();
    QTRY_COMPARE(jCharacter["name"].toString(), QString("Theodore Roosevelt"));
    QTRY_COMPARE(jCharacter["nickname"].toString(), QString("Teddy"));
    QTRY_COMPARE(jCharacter["label"].toString(), QString("ThRo"));
    QTRY_COMPARE(QColor(jCharacter["color"].toString()), QColor("#ffaaff"));
    Q_ASSERT(jCharacter["id"].toInt() == 4);
}

void TestCharacter::testDeserialize()
{

    QFile *json = new QFile(QString("../../Plotline/test/fixtures/character-deserialize.json"));
    json->open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(json->readAll());
    json->close();

    int testIds[]{9, 10, 11};

    Novel *novel = new Novel(QString("My Novel"));
    QList<Scene *> scenes = QList<Scene *>();
    scenes << new Scene(QString("Scene 1"), QString("Action 1"))
           << new Scene(QString("Scene 2"), QString("Action 2"))
           << new Scene(QString("Scene 3"), QString("Action 3"));
    for (int i = 0; i < 3; ++i)
        scenes[i]->setId(testIds[i]);
    novel->setScenes(scenes);

    QJsonObject jCharacter = doc.object();
    Character *character = Character::deserialize(novel, jCharacter);

    qDebug() << "Character's color: " << character->getColor().name();
    QTRY_COMPARE(character->getName(), QString("Theodore Roosevelt"));
    QTRY_COMPARE(character->getLabel(), QString("ThRo"));
    QTRY_COMPARE(character->getColor(), QColor("#ffaaff"));
}
