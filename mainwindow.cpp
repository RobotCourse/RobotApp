
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString config = "config.xml";
    SensorTimer *xtion = new SensorTimer("Robot", "Sensor_xtion", "xtion", config, 33);
    QTime startTime = QTime::fromMSecsSinceStartOfDay(51073041);
//    Simulator *xtion = new Simulator("Robot", "Sensor_xtion", "xtion", config, startTime, 1);
    xtion->setOutputNodesName(QStringList() << "xtionVis;xtionSto;ProcessorCore");

    VisualizationMono *xtionVis = new VisualizationMono("Robot", "Sensor_xtion", "xtionVis", config);
    xtionVis->setInputNodesName(QStringList() << "xtion");
    xtionVis->connectExternalTrigger(0, DRAINSLOT);

    StorageMono *xtionSto = new StorageMono("Robot", "Sensor_xtion", "xtionSto", config);
    xtionSto->setInputNodesName(QStringList() << "xtion");
    xtionSto->connectExternalTrigger(0, DRAINSLOT);

    SensorTimer *urg = new SensorTimer("Robot", "Sensor_URG", "urg", config, 25);
    urg->setOutputNodesName(QStringList() << "urgVis;urgSto;ProcessorCore");

    StorageMono *urgSto = new StorageMono("Robot", "Sensor_URG", "urgSto", config);
    urgSto->setInputNodesName(QStringList() << "urg");
    urgSto->connectExternalTrigger(0, DRAINSLOT);

    VisualizationMono *urgVis = new VisualizationMono("Robot", "Sensor_URG", "urgVis", config);
    urgVis->setInputNodesName(QStringList() << "urg");
    urgVis->connectExternalTrigger(0, DRAINSLOT);

    SourceDrainMono *EncoderIMU = new SourceDrainMono("Robot", "Sensor_EncoderIMU", "EncoderIMU", config);
    EncoderIMU->connectInternalTrigger(SOURCESLOT);
    EncoderIMU->connectExternalTrigger(0, DRAINSLOT);
    EncoderIMU->setInputNodesName(QStringList() << "ProcessorCore");
    EncoderIMU->setOutputNodesName(QStringList() << "EncoderIMUVis;EncoderIMUSto;ProcessorCore");

    VisualizationMono *EncoderIMUVis = new VisualizationMono("Robot", "Sensor_EncoderIMU", "EncoderIMUVis", config);
    EncoderIMUVis->setInputNodesName(QStringList() << "EncoderIMU");
    EncoderIMUVis->connectExternalTrigger(0, DRAINSLOT);

    StorageMono *EncoderIMUSto = new StorageMono("Robot", "Sensor_EncoderIMU", "EncoderIMUSto", config);
    EncoderIMUSto->setInputNodesName(QStringList() << "EncoderIMU");
    EncoderIMUSto->connectExternalTrigger(0, DRAINSLOT);

    ProcessorMulti *ProcessorCore = new ProcessorMulti("Robot", "Processor_Core", "ProcessorCore", config);
    ProcessorCore->setInputNodesName(QStringList() << "EncoderIMU" << "urg" << "xtion");
    ProcessorCore->setOutputNodesName(QStringList() << "EncoderIMU");
    ProcessorCore->connectExternalTrigger(0, PROCESSORSLOT);

    edge.addNode(xtion, 1, 1);
    edge.addNode(xtionVis, 0, 0);
    edge.addNode(xtionSto, 1, 1);
    edge.addNode(urg, 1, 1);
    edge.addNode(urgSto, 1, 1);
    edge.addNode(urgVis, 0, 0);
    edge.addNode(EncoderIMU, 1, 1);
    edge.addNode(EncoderIMUVis, 0, 0);
    edge.addNode(EncoderIMUSto, 1, 1);
    edge.addNode(ProcessorCore, 1, 1);
    edge.connectAll();

    connect(ui->open, &QPushButton::clicked, &edge, &Edge::openAllNodesSlot);
    connect(ui->close, &QPushButton::clicked, &edge, &Edge::closeAllNodesSlot);
    connect(ui->start, &QPushButton::clicked, xtion, &SensorTimer::startTimerSlot);
    connect(ui->stop, &QPushButton::clicked, xtion, &SensorTimer::stopTimerSlot);
//    connect(ui->start, &QPushButton::clicked, xtion, &Simulator::startSimulatorSlot);
//    connect(ui->stop, &QPushButton::clicked, xtion, &Simulator::stopSimulatorSlot);
    connect(ui->start, &QPushButton::clicked, urg, &SensorTimer::startTimerSlot);
    connect(ui->stop, &QPushButton::clicked, urg, &SensorTimer::stopTimerSlot);

    QWidget *color = xtionVis->getVisualizationWidgets()[0];
    QWidget *depth = xtionVis->getVisualizationWidgets()[1];
    ui->area1->setWidget(color);
    ui->area2->setWidget(depth);
    QWidget *laser = urgVis->getVisualizationWidgets()[0];
    ui->area3->setWidget(laser);
    ui->tabWidget->addTab(&edge, "Monitor");
    QWidget *odom = EncoderIMUVis->getVisualizationWidgets()[0];
    ui->tabWidget->addTab(odom, "odom");
}

MainWindow::~MainWindow()
{
    delete ui;
}
