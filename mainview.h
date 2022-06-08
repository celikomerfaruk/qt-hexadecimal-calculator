#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = nullptr);
    ~MainView();

private:
    Ui::MainView *ui;

private slots:
     void onDigitPressed();
     void onPlusPressed();
     void onMinusPressed();
     void onClrPressed();
     void onEqualPressed();

};
#endif // MAINVIEW_H
