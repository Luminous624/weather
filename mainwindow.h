#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <QList>
#include <QLabel>
#include <QTimer>
#include "weather_Date.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    //重写父类的方法
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    //获取天气数据
    void getWeatherInfo(QString cityCode);

    //解析Json
    void parseJson(QByteArray& byteArray);

    //更新ui
    void updateUI();
private slots:
    void on_searchButton_clicked();

    void on_search_clicked();

private:
    void onReplied(QNetworkReply* reply);

private:
    QMenu* mExitMenu; //右键退出的菜单
    QAction *mExitAct;//退出的行为-菜单项

    QPoint mOffset;//窗口移动时，鼠标与窗口左上角的偏移

    //Hppt请求
    QNetworkAccessManager *mNetAccessManager;

    Today mToday;
    Day mDay[6];


    //Qlabel数组
    QList<QLabel *> weekList;
    QList<QLabel *> dateList;
    QList<QLabel *> typeList;
    QList<QLabel *> typeIconList;
    QList<QLabel *> aqiList;
    QList<QLabel *> fxList;
    QList<QLabel *> flList;


    QMap<QString, QString> typeMapSmall;
    QMap<QString, QString> typeMapBig;




};
#endif // MAINWINDOW_H
