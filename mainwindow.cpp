#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QWidget>
#include <QWidgetAction>
#include <QWindow>
#include <QPainter>
#include <QPen>
#include "weathertool.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);//设置窗口无边框
    setFixedSize(width(),height()); //设置固定窗口大


    //ui初始化
    //将控件添加到控件数组
    weekList << ui->lbWeek0 << ui->lbWeek1 << ui->lbWeek2 << ui->lbWeek3 << ui->lbWeek4 << ui->lbWeek5;
    dateList << ui->lbDate0 << ui->lbDate1 << ui->lbDate2 << ui->lbDate3 << ui->lbDate4 << ui->lbDate5;
    typeList << ui->lbType0 << ui->lbType1 << ui->lbType2 << ui->lbType3 << ui->lbType4 << ui->lbType5;
    typeIconList << ui->label << ui->label_2 << ui->label_3 << ui->label_4 << ui->label_5 << ui->label_6;
    aqiList << ui->lbAqi0 << ui->lbAqi1 << ui->lbAqi2 << ui->lbAqi3 << ui->lbAqi4 << ui->lbAqi5;
    fxList << ui->lbFx0 << ui->lbFx1 << ui->lbFx2 << ui->lbFx3 << ui->lbFx4 << ui->lbFx5;
    flList << ui->lbFl0 << ui->lbFl1 << ui->lbFl2 << ui->lbFl3 << ui->lbFl4 << ui->lbFl5;


    /* 图片资源文件管理 */
    typeMapSmall.insert("晴", ":/new/prefix1/res1/weatherSmall/A01_Qing.png");
    typeMapSmall.insert("多云", ":/new/prefix1/res1/weatherSmall/A04_DuoYun.png");
    typeMapSmall.insert("阴", ":/new/prefix1/res1/weatherSmall/A05_Ying.png");
    typeMapSmall.insert("有风", ":/new/prefix1/res1/weatherSmall/A06_YouFeng.png");
    typeMapSmall.insert("飓风", ":/new/prefix1/res1/weatherSmall/A17_JuFeng.png");
    typeMapSmall.insert("霾", ":/new/prefix1/res1/weatherSmall/A19_Mai.png");
    typeMapSmall.insert("阵雨", ":/new/prefix1/res1/weatherSmall/B01_ZhenYu.png");
    typeMapSmall.insert("雷阵雨", ":/new/prefix1/res1/weatherSmall/B02_LeiZhenYu.png");
    typeMapSmall.insert("雷阵雨并伴有冰雹", ":/res1/weatherSmall/B03_LeiYuBingBao.png");
    typeMapSmall.insert("小雨", ":/new/prefix1/res1/weatherSmall/B04_XiaoYu.png");
    typeMapSmall.insert("中雨", ":/new/prefix1/res1/weatherSmall/B05_ZhongYu.png");
    typeMapSmall.insert("大雨", ":/new/prefix1/res1/weatherSmall/B06_DaYu.png");
    typeMapSmall.insert("暴雨", ":/new/prefix1/res1/weatherSmall/B07_BaoYu.png");
    typeMapSmall.insert("大暴雨", ":/new/prefix1/res1/weatherSmall/B08_DaBaoYu.png");
    typeMapSmall.insert("特大暴雨", ":/new/prefix1/res1/weatherSmall/B09_TeDaBaoYu.png");
    typeMapSmall.insert("雨夹雪", ":/new/prefix1/res1/weatherSmall/B21_YuJiaXue.png");
    typeMapSmall.insert("冻雨", ":/new/prefix1/res1/weatherSmall/B23_DongYu.png");
    typeMapSmall.insert("阵雪", ":/new/prefix1/res1/weatherSmall/C02_ZhenXue.png");
    typeMapSmall.insert("小雪", ":/new/prefix1/res1/weatherSmall/C03_XiaoXue.png");
    typeMapSmall.insert("中雪", ":/new/prefix1/res1/weatherSmall/C04_ZhongXue.png");
    typeMapSmall.insert("大雪", ":/new/prefix1/res1/weatherSmall/C05_DaXue.png");
    typeMapSmall.insert("暴雪", ":/new/prefix1/res1/weatherSmall/C06_BaoXue.png");
    typeMapSmall.insert("浮尘", ":/new/prefix1/res1/weatherSmall/C10_FuChen.png");
    typeMapSmall.insert("扬沙", ":/new/prefix1/res1/weatherSmall/C11_YangSha.png");
    typeMapSmall.insert("沙尘暴", ":/new/prefix1/res1/weatherSmall/C12_ShaChenBao.png");
    typeMapSmall.insert("强沙尘暴", ":/new/prefix1/res1/weatherSmall/C13_QiangShaChenBao.png");
    typeMapSmall.insert("雾", ":/new/prefix1/res1/weatherSmall/C14_Wu.png");
    typeMapSmall.insert("大暴雪", ":/new/prefix1/res1/weatherSmall/DaBaoXue.png");
    typeMapSmall.insert("雷暴雪", ":/new/prefix1/res1/weatherSmall/LeiBaoDaYu.png");
    typeMapSmall.insert("特大暴雪", ":/new/prefix1/res1/weatherSmall/TeDaBaoXue.png");
    typeMapSmall.insert("冰雹", ":/new/prefix1/res1/weatherSmall/BingBao.png");

    /* BIG */
    typeMapBig.insert("晴", ":/new/prefix1/res1/weatherBig/A01_Qing.png");
    typeMapBig.insert("多云", ":/new/prefix1/res1/weatherBig/A04_DuoYun.png");
    typeMapBig.insert("阴", ":/new/prefix1/res1/weatherBig/A05_Ying.png");
    typeMapBig.insert("有风", ":/new/prefix1/res1/weatherBig/A06_YouFeng.png");
    typeMapBig.insert("飓风", ":/new/prefix1/res1/weatherBig/A17_JuFeng.png");
    typeMapBig.insert("霾", ":/new/prefix1/res1/weatherBig/A19_Mai.png");
    typeMapBig.insert("阵雨", ":/new/prefix1/res1/weatherBig/B01_ZhenYu.png");
    typeMapBig.insert("雷阵雨", ":/res1/weatherBig/B02_LeiZhenYu.png");
    typeMapBig.insert("雷阵雨并伴有冰雹", ":/res1/weatherBig/B03_LeiYuBingBao.png");
    typeMapBig.insert("小雨", ":/new/prefix1/res1/weatherBig/B04_XiaoYu.png");
    typeMapBig.insert("中雨", ":/new/prefix1/res1/weatherBig/B05_ZhongYu.png");
    typeMapBig.insert("大雨", ":/new/prefix1/res1/weatherBig/B06_DaYu.png");
    typeMapBig.insert("暴雨", ":/new/prefix1/res1/weatherBig/B07_BaoYu.png");
    typeMapBig.insert("大暴雨", ":/new/prefix1/res1/weatherBig/B08_DaBaoYu.png");
    typeMapBig.insert("特大暴雨", ":/new/prefix1/res1/weatherBig/B09_TeDaBaoYu.png");
    typeMapBig.insert("雨夹雪", ":/new/prefix1/res1/weatherBig/B21_YuJiaXue.png");
    typeMapBig.insert("冻雨", ":/new/prefix1/res1/weatherBig/B23_DongYu.png");
    typeMapBig.insert("阵雪", ":/new/prefix1/res1/weatherBig/C02_ZhenXue.png");
    typeMapBig.insert("小雪", ":/new/prefix1/res1/weatherBig/C03_XiaoXue.png");
    typeMapBig.insert("中雪", ":/new/prefix1/res1/weatherBig/C04_ZhongXue.png");
    typeMapBig.insert("大雪", ":/new/prefix1/res1/weatherBig/C05_DaXue.png");
    typeMapBig.insert("暴雪", ":/new/prefix1/res1/weatherBig/C06_BaoXue.png");
    typeMapBig.insert("浮尘", ":/new/prefix1/res1/weatherBig/C10_FuChen.png");
    typeMapBig.insert("扬沙", ":/new/prefix1/res1/weatherBig/C11_YangSha.png");
    typeMapBig.insert("沙尘暴", ":/new/prefix1/res1/weatherBig/C12_ShaChenBao.png");
    typeMapBig.insert("强沙尘暴", ":/new/prefix1/res1/weatherBig/C13_QiangShaChenBao.png");
    typeMapBig.insert("雾", ":/new/prefix1/res1/weatherBig/C14_Wu.png");
    typeMapBig.insert("大暴雪", ":/new/prefix1/res1/weatherBig/DaBaoXue.png");
    typeMapBig.insert("雷暴雪", ":/new/prefix1/res1/weatherBig/LeiBaoDaYu.png");
    typeMapBig.insert("特大暴雪", ":/new/prefix1/res1/weatherBig/TeDaBaoXue.png");
    typeMapBig.insert("冰雹", ":/new/prefix1/res1/weatherBig/BingBao.png");


    //构建右键菜单
    mExitMenu = new QMenu(this);
    mExitAct =new QAction();

    mExitAct->setText("退出");
    mExitAct->setIcon(QIcon(":/new/prefix1/res/close.png"));

    mExitMenu->addAction(mExitAct);

    connect(mExitAct,&QAction::triggered, this,[=](){
       qApp->exit(0);
    });  //构建槽函数，实现右键关闭


    mNetAccessManager = new QNetworkAccessManager(this);
    connect(mNetAccessManager,&QNetworkAccessManager::finished,this,&MainWindow::onReplied);

    //直接在构造中，请求天气数据，"101010100"是北京的天气编码
    //getWeatherInfo("101010100");
   //getWeatherInfo("101280101");
    getWeatherInfo("北京");
}

MainWindow::~MainWindow()
{
    delete ui;
}


//重写父类中的虚函数
//父类中默认的实现是忽略右键菜单事件
//重写后可以处理右键菜单
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    //右键弹出菜单
    mExitMenu->exec(QCursor::pos());//根据鼠标位置弹出菜单界面

    event->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mOffset=event->globalPos()-this->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()-mOffset);
}

void MainWindow::getWeatherInfo(QString cityName)
{
     QString cityCode = WeatherTool::getCityCode(cityName);
    if(cityCode.isEmpty()){
        QMessageBox::warning(this,"天气","请检查是否正确！",QMessageBox::Ok);
        return;
    }
    QUrl url("http://t.weather.itboy.net/api/weather/city/" + cityCode);
    mNetAccessManager->get(QNetworkRequest(url));
}

void MainWindow::parseJson(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(byteArray,&err);
    if(err.error!=QJsonParseError::NoError){
        return;
}

    //开始解析
    QJsonObject rootObj =doc.object();
    qDebug()<<rootObj.value("message").toString();

    //1.解析日期和城市
    mToday.date=rootObj.value("data").toString();
    mToday.city=rootObj.value("cityInfo").toObject().value("city").toString();

    //2.解析yesterday
    QJsonObject objData =rootObj.value("data").toObject();
    QJsonObject objYesterday=objData.value("yesterday").toObject();
    mDay[0].week=objYesterday.value("week").toString();
    mDay[0].date=objYesterday.value("ymd").toString();
    mDay[0].type=objYesterday.value("type").toString();

    //高温低温
    QString s;
    s = objYesterday.value("high").toString().split(" ").at(1);//18℃
    s = s.left(s.length() - 1);//18
    mDay[0].high=s.toInt();

    s = objYesterday.value("low").toString().split(" ").at(1);
    s = s.left(s.length() - 1);
    mDay[0].low=s.toInt();

    //风向风力
    mDay[0].fx=objYesterday.value("fx").toString();
    mDay[0].fl=objYesterday.value("fl").toString();

    //污染指数
    mDay[0].aqi=objYesterday.value("aqi").toDouble();

    //3.解析forcast中5天的数据
    QJsonArray forecastArr=objData.value("forecast").toArray();
    int i;
    for(i=0;i<5;i++)
    {
        QJsonObject objForecast=forecastArr[i].toObject();
        mDay[i+1].week=objForecast.value("week").toString();
        mDay[i+1].date=objForecast.value("ymd").toString();
        mDay[i+1].type=objForecast.value("type").toString();

        QString s;
        s = objForecast.value("high").toString().split(" ").at(1);//18℃
        s = s.left(s.length() - 1);//18
        mDay[i+1].high=s.toInt();

        s = objForecast.value("low").toString().split(" ").at(1);
        s = s.left(s.length() - 1);
        mDay[i+1].low=s.toInt();

        mDay[i+1].fx=objForecast.value("fx").toString();
        mDay[i+1].fl=objForecast.value("fl").toString();
        mDay[i+1].aqi=objForecast.value("aqi").toDouble();
    }

    //4.解析今天的数据
    mToday.ganmao=objData.value("ganmao").toString();
    mToday.wendu=objData.value("wendu").toString().toDouble();
    mToday.shidu=objData.value("shidu").toString();
    mToday.pm25=objData.value("pm25").toDouble();
    mToday.quality=objData.value("quality").toString();
    mDay->week=objData.value("week").toString();


    //forecast中第一个数组元素就是今天的数据
    mToday.type = mDay[1].type;
    mToday.fx = mDay[1].fx;
    mToday.fl = mDay[1].fl;
    mToday.high = mDay[1].high;
    mToday.low = mDay[1].low;
    mDay->week=mDay[1].week;

    //5.更新ui
    updateUI();
}

void MainWindow::updateUI()
{
    //更新日期
    ui->lbWeek->setText(mDay->week);
    ui->lbDate->setText(QDateTime::fromString(mToday.date,"yyyymmdd").toString("yyyy/mm/dd")+""+mDay[1].date);
    //更新城市
    ui->lbplace->setText(mToday.city);
    //更新今天
    ui->Logo->setPixmap(typeMapBig[mToday.type]);
    ui->lbTem->setText(QString::number(mToday.wendu));
    ui->lbALL_2->setText(mToday.type);
    ui->lbALL->setText(QString::number(mToday.low)+"~"+QString::number(mToday.high)+"℃");
    ui->idenx->setText("感冒指数:"+mToday.ganmao);
    ui->text1_1->setText(mToday.fx);
    ui->text1_2->setText(mToday.fl);
    ui->text2_2->setText(QString::number(mToday.pm25));
    ui->text3_2->setText(mToday.shidu);
    ui->text4_2->setText(mToday.quality);

   //更新六天
    for(int i=0;i<6;i++)
    {
        //更新日期和时间
        weekList[i]->setText("周"+mDay[i].week.right(1));
        ui->lbWeek0->setText("昨天");
        ui->lbWeek1->setText("今天");
        ui->lbWeek2->setText("明天");
        QStringList ymdList =mDay[i].date.split("-");
        dateList[i]->setText(ymdList[1] + "/" + ymdList[2]);
        //更新天气类型
        typeList[i]->setText(mDay[i].type);
        typeIconList[i]->setPixmap(typeMapSmall[mDay[i].type]);
       // typeIconList[i]->setPixmap(typeMapSmall[day[i].type]);
        //更新空气质量
        if(mDay[i].aqi <= 50)
        {
            aqiList[i]->setText("优");
            aqiList[i]->setStyleSheet("background-color: rgb(121, 182, 0);");
        }
        else if(mDay[i].aqi <= 100)
        {
            aqiList[i]->setText("良");
            aqiList[i]->setStyleSheet("background-color: rgb(255, 187, 23);");
        }
        else if(mDay[i].aqi <= 150)
        {
            aqiList[i]->setText("轻度");
            aqiList[i]->setStyleSheet("background-color: rgb(182, 121, 182);");
        }
        else if(mDay[i].aqi <= 200)
        {
            aqiList[i]->setText("中度");
            aqiList[i]->setStyleSheet("background-color: rgb(182, 60, 91);");
        }
        else if(mDay[i].aqi <= 250)
        {
            aqiList[i]->setText("重度");
            aqiList[i]->setStyleSheet("background-color: rgb(182, 0, 0);");
        }
        else
        {
            aqiList[i]->setText("严重");
            aqiList[i]->setStyleSheet("background-color: rgb(120, 0, 0);");
        }
        //更新风力风向
        fxList[i]->setText(mDay[i].fx);
        flList[i]->setText(mDay[i].fl);
    }
    }

void MainWindow::onReplied(QNetworkReply *reply)
{
 //请求数据
 //   qDebug()<<"onReplied success";

    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug()<<"operation:"<<reply->operation();
    qDebug()<<"status code:"<<status_code;
    qDebug()<<"url:"<<reply->url();
    qDebug()<<"raw header:"<<reply->rawHeaderList();

 //判断请求是否出错
    if(reply->error()!=QNetworkReply::NoError||status_code!=200)
    {
        qDebug()<<reply->errorString().toLatin1().data();
        QMessageBox::warning(this,"天气","请求数据失败",QMessageBox::Ok);
    }
    else
    {
       QByteArray byteArray = reply->readAll();
       qDebug()<<"read all:"<<byteArray.data();
       parseJson(byteArray);
    }

    //释放内存，防止内存泄漏
    reply->deleteLater();
}


void MainWindow::on_search_clicked()
{
    QString cityName = ui->lineEdit->text();
    getWeatherInfo(cityName);
}
