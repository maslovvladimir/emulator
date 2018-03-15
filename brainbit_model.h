#ifndef BRAINBIT_MODEL_H
#define BRAINBIT_MODEL_H

#include <QObject>

class BrainbitModel : public QObject
{
    Q_OBJECT
public:
    explicit BrainbitModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BRAINBIT_MODEL_H