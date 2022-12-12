#ifndef GATISCONSOLE_H
#define GATISCONSOLE_H

#include "miaoumsg.h"
#include "whiskvice.h"
#include "outipi.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GatisConsole; }
QT_END_NAMESPACE

class GatisConsole : public QMainWindow
{
    Q_OBJECT

    WhiskVice tstDev1;
    WhiskVice tstDev2;

public:
    GatisConsole(QWidget *parent = nullptr);
    ~GatisConsole();

private:
    Ui::GatisConsole *ui;
};
#endif // GATISCONSOLE_H
