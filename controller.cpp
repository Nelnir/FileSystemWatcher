#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{

}

Controller::~Controller()
{

}

void Controller::add_folder(const QString& folder)
{
    QString file = folder.sliced(8);
    m_model.append(file);
    qDebug() << "ADDED FOLDER: " << m_model;
    emit model_changed();
}
