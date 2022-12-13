#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList model MEMBER m_model NOTIFY model_changed);
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    Q_INVOKABLE void add_folder(const QString& folder);
signals:
    void model_changed();
private:
    QStringList m_model;
};

#endif // CONTROLLER_H
