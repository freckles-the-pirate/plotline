#include "characteritemmodel.h"

CharacterModel::CharacterModel(Novel *novel, QObject *parent)
    : QAbstractListModel(parent)
{
    mNovel = novel;
}

void CharacterModel::addCharacter()
{
    Character *c = new Character("New Character");
    mNovel->addCharacter(c);
    insertRows(this->rowCount(), 1);
    QModelIndex index = lastRow();
    setData(index, c->name(), Qt::DisplayRole|Qt::EditRole);
    setData(index, QVariant(c->id()), CharacterIdRole);
    setData(index, c->color(), Qt::BackgroundRole);
}

int CharacterModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->characters().count();
}

QVariant CharacterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        qWarning() << "[<] character data: Invalid index";
        return QVariant();
    }

    if (index.row() > mNovel->characters().size()){
        qWarning("[<] character data: invalid row %d", index.row());
        return QVariant();
    }

    Character *c = mNovel->characters()[index.row()];

    if (role == Qt::ForegroundRole){
        QColor textColor = QColor(0, 0, 0);
        if ((255 / 2) > c->color().value())
            textColor = QColor(255, 255, 255);      // White text.
        return QBrush(textColor);
    }if (role == Qt::BackgroundRole || role == ColorRole) {
        if (c->color().isValid())
            return QBrush(c->color());
        return QVariant();
    } else if (role == Qt::DisplayRole || role ==  Qt::EditRole) {
        qDebug("    role = Qt::DisplayRole");
        return c->name();
    } else if (role == CharacterIdRole) {
        qDebug("    role = CharacterIdRole");
        return c->id();
    } else if (role == NameRole) {
        qDebug("    role = NameRole");
        return c->name();
    } else if (role == LabelRole) {
        qDebug("    role = LabelRole");
        return c->label();
    } else if (role == HeadshotRole) {
        qDebug("    role = HeadshotRole");
        QVariant headshot;
        headshot = c->getHeadshot();
        return headshot;
    } else if (role == ColorRole) {
        qDebug("    role = ColorRole");
        if (c->color().isValid())
            return c->color().name();
        return QString();
    } else if (role == ArchivedRole) {
    } else {
        qWarning("[<] character data: Invalid role %d", role);
    }
    return QVariant();
}

QVariant CharacterModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return tr("Character");
    return QVariant();
}

bool CharacterModel::setData(const QModelIndex &index, const QVariant &value,
                             int role)
{
    if (!index.isValid()){
        qWarning() << "[>] character set data: Invalid index";
        return false;
    }

    if (index.row() > mNovel->characters().size()){
        qWarning() << index.row() << " > # of characters(" <<
                      mNovel->characters().count() << ")";
        return false;
    }

    Character *c = mNovel->characters()[index.row()];

    if (role == Qt::BackgroundRole) {
        c->setColor(QColor(value.toString()));
    } else if (role == Qt::DisplayRole || role ==  Qt::EditRole) {
        c->setName(value.toString());
    } else if (role == CharacterIdRole) {
    } else if (role == NameRole) {
        c->setName(value.toString());
    } else if (role == LabelRole) {
        c->setLabel(value.toString());
    } else if (role == HeadshotRole) {
        QImage headshot = value.value<QImage>();
        c->setHeadshot(headshot);
    } else if (role == ColorRole) {
        c->setColor(QColor(value.toString()));
    } else if (role == ArchivedRole) {
    } else {
        qWarning("[>] character set data: Invalid role %d", role);
    }
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemFlag::ItemIsEnabled|Qt::ItemIsSelectable;
}

QModelIndex CharacterModel::lastRow() const
{
    return index(rowCount()-1);
}

bool CharacterModel::insertRows(int row, int count,
                                    const QModelIndex &parent)
{
    qDebug() << "Inserting rows for novel" << mNovel->getWorkingTitle();
    if (parent.isValid() || row + count <=0 )
        return false;

    int end = row + (count-1);

    beginInsertRows(QModelIndex(), row, end);

    for (int i = row; i <= end; ++i)
        mNovel->addCharacter(new Character(""), i);

    endInsertRows();

    return true;
}

bool CharacterModel::removeRows(int row, int count,
                                    const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row >= mNovel->characters().size() || row + count <= 0)
        return false;

    int beginRow = qMax(0, row);
    int endRow = qMin(row + count - 1, mNovel->characters().size() - 1);

    beginRemoveRows(parent, beginRow, endRow);

    while (beginRow <= endRow) {
        mNovel->characters().removeAt(beginRow);
        ++beginRow;
    }

    endRemoveRows();
    return true;
}
