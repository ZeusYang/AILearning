#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace ComFunc;

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:white");
    QWidget *widget = new QWidget(this);
    this->setCentralWidget(widget);

    QMenu *menu = ui->menubar->addMenu("测试(&T)");
    QAction *test = new QAction(QString(tr("样例测试(&Y)")));
    connect(test,&QAction::triggered,this,&MainWindow::TestErrorRate);
    test->setShortcut(QKeySequence::New);
    menu->addAction(test);

    QAction *atrian = new QAction("手动训练(&H)");
    connect(atrian,&QAction::triggered,this,&MainWindow::HandTrain);
    menu->addAction(atrian);

    panel = new WriteBoard(this);
    operation = new QLabel(this);
    operation->setText(QString(tr("BP神经网络手写识别")));
    clearb = new QPushButton(this);
    clearb->setText(QString(tr("清除")));
    getit = new QPushButton(this);
    getit->setText(QString(tr("识别")));
    getit->setShortcut(Qt::Key_Return);
    ret = new QLabel(this);
    train = new QPushButton(this);
    train->setText(QString(tr("训练")));
    correction = new QLineEdit;
    correction->setParent(this);
    sure = new QPushButton(this);
    sure->setText(QString(tr("确定")));


    connect(getit,&QPushButton::clicked,this,&MainWindow::Recognize);
    connect(train,&QPushButton::clicked,this,&MainWindow::Test);
    connect(clearb,&QPushButton::clicked,this,&MainWindow::Clear);
    connect(sure,&QPushButton::clicked,this,&MainWindow::CorrectProcess);
    
    QFont showLabel("Microsoft YaHei", 15, 75);
    operation->setFont(showLabel);
    operation->setAlignment(Qt::AlignCenter);
    QFont showret("Microsoft YaHei", 75, 75);
    ret->setFont(showret);
    ret->setAlignment(Qt::AlignCenter);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(panel,0,0,6,7);
    layout->addWidget(operation,0,7,1,3);
    layout->addWidget(train,1,7,1,3);
    layout->addWidget(clearb,2,7,1,3);
    layout->addWidget(getit,3,7,1,3);
    layout->addWidget(ret,4,7,1,3);
    layout->addWidget(correction,5,7,1,2);
    layout->addWidget(sure,5,9,1,1);
    widget->setLayout(layout);

    bpnn = NULL;
    epochMax = 1;
    expectErr = 0.1;
    if (src.openImageFile(TRAIN_IMAGES_URL) && src.openLabelFile(TRAIN_LABELS_URL)){
       // qDebug() << "success!";
        imageSize = src.imageLength();
        numImages = src.numImage();
        InitNeuron();
    }
    //else qDebug() << "open train image file failed";

    if (testData.openImageFile(TEST_IMANGES_URL) && testData.openLabelFile(TEST_LABELS_URL))
    {
        imageSize = testData.imageLength();
        numImages = testData.numImage();

        //cout << "start test ANN with t10k images..." << endl;
        cout << "success!" << endl;

        //int ok_cnt = testRecognition(testData, *bpnn, imageSize, numImages);

        //cout << "digital recognition ok_cnt: " << ok_cnt << ", total: " << numImages << endl;
    }
    else
    {
        cout << "open test image file failed" << endl;
    }
    mode = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete panel;
}

void MainWindow::Clear()
{
    panel->clear();
}

void MainWindow::Test()
{
    cout << "start training ANN..." << endl;
    TrainProcess();
    cout << "training ANN success..." << endl;
    //TestErrorRate();

}

void MainWindow::ErrorTest()
{

}

void MainWindow::HandTrain()
{
    mode = true;
    QMessageBox::information(this,"Tips","手动训练开始!");
}

void MainWindow::CorrectProcess()
{
    if(!mode){
        QMessageBox::information(this,"Tips","当前为非手动训练模式!");
        return;
    }
    double *data;
    data = new double[10];
    memset(data,0,sizeof(data));
    int index = correction->text().toInt();
    if(index >= 0 && index <= 9){
        data[index] = 1.0f;
    }
    bpnn->training(panel->GetMatrix(),data);
    delete []data;
}

void MainWindow::Recognize()
{
    double *output = NULL;
    bpnn->process(panel->GetMatrix(), &output);
    int re = showRecognizedNumber(output);
    ret->setText(QString::number(re));
    //panel->ShowPixel();
}

void MainWindow::InitNeuron()
{
    bpnn = new bpNeuronNet(imageSize, NET_LEARNING_RATE);
        /** add first hidden layer */

    bpnn->addNeuronLayer(NUM_HIDDEN);

        /** add output layer */
    bpnn->addNeuronLayer(NUM_NET_OUT);
}

void MainWindow::TrainProcess()
{
    using namespace ComFunc;
    for (int i = 0; i < epochMax; i++)
    {
        trainEpoch(src, *bpnn, imageSize, numImages);
        src.reset();

    }
}

void MainWindow::TestErrorRate()
{
        imageSize = testData.imageLength();
        numImages = testData.numImage();

        //cout << "start test ANN with t10k images..." << endl;

        //int ok_cnt = testRecognition(testData, *bpnn, imageSize, numImages);

        int ok_cnt = 0;
        double* net_out = NULL;
        char* temp = new char[imageSize];
        double* net_test = new double[imageSize];
        int label = 0;

            if (testData.read(&label, temp))
            {
                preProcessInputData((unsigned char*)temp, net_test, imageSize);
                bpnn->process(net_test, &net_out);

                showNumber((unsigned char*)temp, testData.imageWidth(), testData.imageHeight());
                ret->setText(QString::number(showRecognizedNumber(net_out)));
                panel->SetMatrix(net_test,testData.imageWidth(), testData.imageHeight());

                int idx = -1;
                double max_value = -99999;
                for (int i = 0; i < NUM_NET_OUT; i++)
                {
                    if (net_out[i] > max_value)
                    {
                        max_value = net_out[i];
                        idx = i;
                    }
                }

                if (idx == label)
                {
                    ok_cnt++;
                }
            }
            else
            {
                cout << "read test data failed" << endl;
                //break;
            }


        delete []net_test;
        delete []temp;

        //return ok_cnt;



        //cout << "digital recognition ok_cnt: " << ok_cnt << ", total: " << numImages << endl;
}
