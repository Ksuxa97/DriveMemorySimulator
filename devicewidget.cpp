#include "devicewidget.h"

DeviceWidget::DeviceWidget(int id, QWidget *parent) : QWidget(parent)
{
    deviceLayout = new QGridLayout(this);
    msgBox = new MessageWindow(this);

    device_id = id;

    if((device_id == 2) || (device_id == 5)){
        flashDevice = new FlashDevice(this);
        abstractDevice = flashDevice;
        flashWidget();
    }
    else{
        diskDevice = new DiskDevice(this);
        abstractDevice = diskDevice;
        diskWidget();
    }
}

void DeviceWidget::diskWidget(){
    widgetTitle();
    diskFieldsInscription();
    diskInputFields();
    deviceBtns();
}

void DeviceWidget::flashWidget(){
    widgetTitle();
    flashFieldsInscription();
    flashInputFields();
    deviceBtns();
}

void DeviceWidget::widgetTitle(){
    QLabel *title = new QLabel(this);
    title->setStyleSheet("font-size: 14pt;\n qproperty-alignment: AlignCenter;");
    switch (device_id) {
    case 1:
        title->setText("Жесткий диск");
        break;
    case 2:
        title->setText("Твердотельный накопитель");
        break;
    case 3:
        title->setText("Дискета");
        break;
    case 4:
        title->setText("Оптический диск");
        break;
    case 5:
        title->setText("USB-флэш-накопитель");
        break;
    default:
        break;
    }

    deviceLayout->addWidget(title, 0, 0, 1, 5);
}

void DeviceWidget::diskFieldsInscription(){
    //ряд 1
    QLabel *text = new QLabel(this);
    if(device_id == 4)
        text->setText("Скорость вращения (об/мин):");
    else
        text->setText("Скорость вращения шпинделя (об/мин):");
    deviceLayout->addWidget(text, 1, 0, 1, 2);

    //ряд 2
    text = new QLabel(this);
    if(device_id == 3){
        text->setText("Количество записывающих сторон:");
        deviceLayout->addWidget(text, 2, 0, 1, 2);
    }
    else{
        text->setText("Кэш:");
        deviceLayout->addWidget(text, 2, 0, 1, 2);
    }

    //ряд 3
    if(device_id != 3){
        text = new QLabel("Интерфейс:", this);
        deviceLayout->addWidget(text, 3, 0, 1, 2);
    }

    //ряд 4
    if(device_id == 3)
        text = new QLabel("Пропускная способность (Кбит/с):", this);
    else
        text = new QLabel("Пропускная способность:", this);
    deviceLayout->addWidget(text, 4, 0, 1, 2);

    //ряд 5, 6
    if(device_id != 4){
        text = new QLabel("Количество треков:", this);
        deviceLayout->addWidget(text, 5, 0, 1, 2);

        text = new QLabel("Количество цилиндров:", this);
        deviceLayout->addWidget(text, 6, 0, 1, 2);
    }

    //ряд 7
    text = new QLabel(this);
    text->setText("Объём памяти:");
    deviceLayout->addWidget(text, 7, 0, 1, 2);

    text = new QLabel("Размер сектора (байт):", this);
    deviceLayout->addWidget(text, 7, 2);
    //ряд 11
    text = new QLabel(this);
    if(device_id == 4)
        text->setText("Скорость чтения/записи:");
    else
        text->setText("Время ожидания:");
    deviceLayout->addWidget(text, 11, 2);

    //deviceLayout->setColumnMinimumWidth(1, 10);
}

void DeviceWidget::flashFieldsInscription(){
    QLabel *text = new QLabel("Скорость чтения (МБ/с):", this);
    deviceLayout->addWidget(text, 1, 0, 1, 2);

    text = new QLabel("Скорость записи (МБ/с):", this);
    deviceLayout->addWidget(text, 2, 0, 1, 2);

    text = new QLabel("Интерфейс:", this);
    deviceLayout->addWidget(text, 3, 0, 1, 2);

    text = new QLabel("Пропускная способность:", this);
    deviceLayout->addWidget(text, 4, 0, 1, 2);

    text = new QLabel("Объём памяти:", this);
    deviceLayout->addWidget(text, 5, 0, 1, 2);

    text = new QLabel("Размер сектора (байт):", this);
    deviceLayout->addWidget(text, 5, 2);

    text = new QLabel("IOPS последовательного чтения:", this);
    deviceLayout->addWidget(text, 10, 2);

    text = new QLabel("IOPS последовательной записи:", this);
    deviceLayout->addWidget(text, 11, 2);
}

void DeviceWidget::diskInputFields(){
    //ряд 1 - RPM
    QLineEdit *rpmEdit = new QLineEdit(this);
    StyleSet::setQLineEditStyle(rpmEdit, false);
    rpmEdit->setValidator(new QIntValidator(0, 20000, this));
    connect(rpmEdit, &QLineEdit::textChanged, diskDevice, &DiskDevice::setRPM);
    rpmEdit->setMaximumWidth(150);
    deviceLayout->addWidget(rpmEdit, 1, 2);

    //ряд 2
    if(device_id == 3){
        //количество записывающих сторон
        QComboBox *sidesBox = new QComboBox(this);
        StyleSet::setQComboBoxStyle(sidesBox);
        sidesBox->addItem("<----->");
        sidesBox->addItem("1");
        sidesBox->addItem("2");
        sidesBox->setMaximumWidth(150);
        deviceLayout->addWidget(sidesBox, 2, 2);
        connect(sidesBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), diskDevice, &DiskDevice::setSidesNumber);
    }
    else{
        //кэш
        cacheEdit = new QLineEdit(this);
        StyleSet::setQLineEditStyle(cacheEdit, false);
        cacheEdit->setValidator(new QIntValidator(0, 10000, this));
        cacheEdit->setMaximumWidth(150);
        deviceLayout->addWidget(cacheEdit, 2, 2);
        connect(cacheEdit, &QLineEdit::textChanged, this, &DeviceWidget::currentFieldsData);

        unitBox_1 = new QComboBox(this);
        StyleSet::setQComboBoxStyle(unitBox_1);
        unitBox_1->addItem("<----->");
        unitBox_1->addItem("КБ");
        unitBox_1->addItem("МБ");
        unitBox_1->setMaximumWidth(65);
        deviceLayout->addWidget(unitBox_1, 2, 3);
        connect(unitBox_1, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &DeviceWidget::currentFieldsData);
    }

    QLineEdit *transferEdit = new QLineEdit(this);

    //ряд 3 - интерфейс
    if(device_id != 3){
        QComboBox *interfaceBox = new QComboBox(this);
        StyleSet::setQComboBoxStyle(interfaceBox);
        interfaceBox->addItem("<----->");
        interfaceBox->addItem("SATA 1.0");
        interfaceBox->addItem("SATA 2.0");
        interfaceBox->addItem("SATA 3.0");
        interfaceBox->addItem("SCSI");
        interfaceBox->addItem("Fast SCSI");
        interfaceBox->addItem("Wide SCSI");
        interfaceBox->addItem("Ultra SCSI");
        interfaceBox->addItem("Ultra Wide SCSI");
        interfaceBox->addItem("Ultra2 SCSI");
        interfaceBox->addItem("Ultra2 Wide SCSI");
        interfaceBox->addItem("Ultra3 SCSI");
        if(device_id == 1){
            interfaceBox->addItem("Ultra-320 SCSI");
            interfaceBox->addItem("Ultra-640 SCSI");
            interfaceBox->addItem("ATA-1 (PIO Mode 0)");
            interfaceBox->addItem("ATA-2 (PIO Mode 4)");
            interfaceBox->addItem("ATA-1 (DMA Single 0)");
            interfaceBox->addItem("ATA-2 (DMA Multi 2)");
            interfaceBox->addItem("Ultra ATA/33");
            interfaceBox->addItem("Ultra ATA/167");
        }
        connect(interfaceBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), diskDevice, &DiskDevice::setInterface);
        interfaceBox->setMaximumWidth(150);
        deviceLayout->addWidget(interfaceBox, 3, 2);

        //ряд 4 - пропускная способность
        StyleSet::setQLineEditStyle(transferEdit, true);
        connect(interfaceBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &DeviceWidget::deviceInterfaces);
        connect(this, &DeviceWidget::deviceInterfaceChanged, transferEdit, &QLineEdit::setText);
    }

    //ряд 4 - пропускная способность
    if(device_id == 3){
        transferEdit->setValidator(new QIntValidator(0, 1000, this));
        StyleSet::setQLineEditStyle(transferEdit, false);
        connect(transferEdit, &QLineEdit::textChanged, this, &DeviceWidget::deviceInterfaces);
    }
    transferEdit->setMaximumWidth(150);
    deviceLayout->addWidget(transferEdit, 4, 2);

    //ряд 5, 6
    if(device_id != 4){
        //количество треков
        QLineEdit *tracksEdit = new QLineEdit(this);
        StyleSet::setQLineEditStyle(tracksEdit, false);

        //количество цилиндров
        QLineEdit *cylindersEdit = new QLineEdit(this);
        StyleSet::setQLineEditStyle(cylindersEdit, false);

        if(device_id == 1){
            tracksEdit->setValidator(new QIntValidator(0, 100000, this));
            cylindersEdit->setValidator(new QIntValidator(0, 10000, this));
        }
        else{
            tracksEdit->setValidator(new QIntValidator(0, 135, this));
            cylindersEdit->setValidator(new QIntValidator(0, 100, this));
        }

        connect(tracksEdit, &QLineEdit::textChanged, diskDevice, &DiskDevice::setTracksNumber);
        connect(cylindersEdit, &QLineEdit::textChanged, diskDevice, &DiskDevice::setCylindersNumber);

        tracksEdit->setMaximumWidth(150);
        cylindersEdit->setMaximumWidth(150);
        deviceLayout->addWidget(tracksEdit, 5, 2);
        deviceLayout->addWidget(cylindersEdit, 6, 2);
    }

    //ряд 8 - объем памяти
    memoryEdit = new QLineEdit(this);
    StyleSet::setQLineEditStyle(memoryEdit, false);
    memoryEdit->setValidator(new QIntValidator(0, 1024, this));
    connect(memoryEdit, &QLineEdit::textChanged, this, &DeviceWidget::currentFieldsData);

    memoryEdit->setMaximumWidth(150);
    deviceLayout->addWidget(memoryEdit, 8, 0);

    unitBox_2 = new QComboBox(this);
    StyleSet::setQComboBoxStyle(unitBox_2);
    unitBox_2->addItem("<----->");
    if(device_id != 4){
        unitBox_2->addItem("КБ");
    }
    unitBox_2->addItem("МБ");
    if(device_id == 1){
        unitBox_2->addItem("ГБ");
        unitBox_2->addItem("TБ");
    }
    unitBox_2->setMaximumWidth(65);
    connect(unitBox_2, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &DeviceWidget::currentFieldsData);
    deviceLayout->addWidget(unitBox_2, 8, 1);

    //ряд 8 - размер сектора
    QLineEdit *sectorEdit = new QLineEdit(this);
    StyleSet::setQLineEditStyle(sectorEdit, false);
    sectorEdit->setValidator(new QIntValidator(0, 4096, this));
    connect(sectorEdit, &QLineEdit::textChanged, diskDevice, &DiskDevice::setSectorSize);
    sectorEdit->setMaximumWidth(150);
    deviceLayout->addWidget(sectorEdit, 8, 2);

    //ряд 9 - визуальная картина памяти
    deviceMemory = new MemoryVisualisation(300, this);
    deviceLayout->addWidget(deviceMemory, 9, 0, 1, 5);

    resultEdit_1 = new QLineEdit(this);
    StyleSet::setQLineEditStyle(resultEdit_1, true);
    deviceLayout->addWidget(resultEdit_1, 11, 3, 1, 2);

    //запись данных для визуальной картины
    connect(sectorEdit, &QLineEdit::textChanged, deviceMemory, &MemoryVisualisation::setSectorSize);
}

void DeviceWidget::flashInputFields(){
    //ряд 1 - скорость чтения
    QLineEdit *readSpeedEdit = new QLineEdit(this);
    StyleSet::setQLineEditStyle(readSpeedEdit, false);
    readSpeedEdit->setValidator(new QIntValidator(0, 1000, this));
    readSpeedEdit->setMaximumWidth(150);

    //ряд 2 - скорость записи
    QLineEdit *writeSpeedEdit = new QLineEdit(this);
    StyleSet::setQLineEditStyle(writeSpeedEdit, false);
    writeSpeedEdit->setValidator(new QIntValidator(0, 1000, this));
    writeSpeedEdit->setMaximumWidth(150);

    //ряд 3 - интерфейс
    QComboBox *interfaceBox = new QComboBox(this);
    StyleSet::setQComboBoxStyle(interfaceBox);
    interfaceBox->addItem("<----->");
    if(device_id == 2){
        interfaceBox->addItem("SATA 2.0");
        interfaceBox->addItem("SATA 3.0");
        interfaceBox->addItem("mSATA");
        interfaceBox->addItem("SATA Express");
        interfaceBox->addItem("PCI-Express 2.0 x2");
        interfaceBox->addItem("PCI-Express 2.0 x4");
        interfaceBox->addItem("PCI-Express 2.0 x8");
    }
    else{
        interfaceBox->addItem("USB 1.0");
        interfaceBox->addItem("USB 1.1");
        interfaceBox->addItem("USB 2.0");
        interfaceBox->addItem("USB 3.0");
        interfaceBox->addItem("USB 3.1");
    }
    interfaceBox->setMaximumWidth(150);

    //ряд 4 - пропускная способность
    QLineEdit *transferSpeedEdit = new QLineEdit(this);
    StyleSet::setQLineEditStyle(transferSpeedEdit, true);
    transferSpeedEdit->setMaximumWidth(150);

    //ряд 6 - объем памяти
    memoryEdit = new QLineEdit(this);
    StyleSet::setQLineEditStyle(memoryEdit, false);
    memoryEdit->setValidator(new QIntValidator(0, 1000, this));
    memoryEdit->setMaximumWidth(150);

    unitBox_2 = new QComboBox(this);
    StyleSet::setQComboBoxStyle(unitBox_2);
    unitBox_2->addItem("<----->");
    unitBox_2->addItem("ТБ");
    unitBox_2->addItem("ГБ");
    if(device_id == 5)
        unitBox_2->addItem("МБ");
    unitBox_2->setMaximumWidth(65);

    //ряд 6 - размер сектора
    QLineEdit *sectorEdit = new QLineEdit(this);
    StyleSet::setQLineEditStyle(sectorEdit, false);
    sectorEdit->setValidator(new QIntValidator(0, 10000, this));
    sectorEdit->setMaximumWidth(150);

    //ряд 7 - визуальная картина памяти
    deviceMemory = new MemoryVisualisation(305, this);

    //IOPS чтения
    resultEdit_1 = new QLineEdit(this);
    StyleSet::setQLineEditStyle(resultEdit_1, true);
    //->setMaximumWidth(150);
    //IOPS записи
    resultEdit_2 = new QLineEdit(this);
    StyleSet::setQLineEditStyle(resultEdit_2, true);
    //resultEdit_2->setMaximumWidth(150);

    //размещение полей по сетке
    deviceLayout->addWidget(readSpeedEdit, 1, 2);
    deviceLayout->addWidget(writeSpeedEdit, 2, 2);
    deviceLayout->addWidget(interfaceBox, 3, 2);
    deviceLayout->addWidget(transferSpeedEdit, 4, 2);
    deviceLayout->addWidget(memoryEdit, 6, 0);
    deviceLayout->addWidget(unitBox_2, 6, 1);
    deviceLayout->addWidget(sectorEdit, 6, 2);
    deviceLayout->addWidget(deviceMemory, 7, 0, 1, 4);
    deviceLayout->addWidget(resultEdit_1, 10, 3, 1, 2);
    deviceLayout->addWidget(resultEdit_2, 11, 3, 1, 2);

    connect(readSpeedEdit, &QLineEdit::textChanged, flashDevice, &FlashDevice::setReadSpeed);
    connect(writeSpeedEdit, &QLineEdit::textChanged, flashDevice, &FlashDevice::setWriteSpeed);
    connect(interfaceBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), flashDevice, &FlashDevice::setInterface);
    connect(interfaceBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &DeviceWidget::deviceInterfaces);
    connect(this, &DeviceWidget::deviceInterfaceChanged, transferSpeedEdit, &QLineEdit::setText);
    connect(memoryEdit, &QLineEdit::textChanged, this, &DeviceWidget::currentFieldsData);
    connect(unitBox_2, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &DeviceWidget::currentFieldsData);
    connect(sectorEdit, &QLineEdit::textChanged, flashDevice, &FlashDevice::setSectorSize);

    //запись данных для визуальной картины
    connect(sectorEdit, &QLineEdit::textChanged, deviceMemory, &MemoryVisualisation::setSectorSize);
}

void DeviceWidget::currentFieldsData(QString data){
    if(sender() == cacheEdit){
        cacheSize = data.toInt();
        cacheToBytes(unit_1);
    }
    else if(sender() == unitBox_1){
        unit_1 = data;
        cacheToBytes(unit_1);
    }
    else if(sender() == memoryEdit){
        memorySize = data.toInt();
        memoryToBytes(unit_2);
    }
    else if(sender() == unitBox_2){
        unit_2 = data;
        memoryToBytes(unit_2);
    }
}

void DeviceWidget::cacheToBytes(QString unit){
    if(unit == "КБ"){
        //cacheSize *= 1024;
        diskDevice->setCache(QString("%1").arg(cacheSize*1024));
    }
    else if(unit == "МБ"){
        int tmp = cacheSize * pow(1024, 2);
        diskDevice->setCache(QString("%1").arg(tmp));
    }
}

void DeviceWidget::memoryToBytes(QString unit){
    if(unit == "КБ"){
        abstractDevice->setMemorySize(QString("%1").arg(memorySize*1024));
    }
    else if(unit == "МБ"){
        double tmp = memorySize * pow(1024, 2);
        abstractDevice->setMemorySize(QString("%1").arg(tmp));
    }
    else if(unit == "ГБ"){
        double tmp = memorySize * pow(1024, 3);
        abstractDevice->setMemorySize(QString("%1").arg(tmp));
    }
    else if(unit == "ТБ"){
        double tmp = memorySize * pow(1024, 4);
        abstractDevice->setMemorySize(QString("%1").arg(tmp));
    }
}

void DeviceWidget::deviceInterfaces(QString type){
        float rate = 0;
    if (type == "SATA 1.0"){
        rate = 1500;
        emit deviceInterfaceChanged("1.5 Гбит/с");
    }
    else if (type == "SATA 2.0"){
        rate = 3000;
        emit deviceInterfaceChanged("3 Гбит/с");
    }
    else if (type == "SATA 3.0"){
        rate = 6000;
        emit deviceInterfaceChanged("6 Гбит/с");
    }
    else if (type == "SATA 3.0"){
        rate = 6000;
        emit deviceInterfaceChanged("6 Гбит/с");
    }
    else if (type == "mSATA"){
        rate = 3000;
        emit deviceInterfaceChanged("3 Гбит/с");
    }
    else if (type == "SATA Express"){
        rate = 10000;
        emit deviceInterfaceChanged("10 Гбит/с");
    }
    else if (type == "SCSI"){
        rate = 50;
        emit deviceInterfaceChanged("5 Мбайт/с");
    }
    else if (type == "Fast SCSI"){
        rate = 80;
        emit deviceInterfaceChanged("10 Мбайт/с");
    }
    else if (type == "Wide SCSI"){
        rate = 160;
        emit deviceInterfaceChanged("20 Мбайт/с");
    }
    else if (type == "Ultra SCSI"){
        rate = 160;
        emit deviceInterfaceChanged("20 Мбайт/с");
    }
    else if (type == "Ultra Wide SCSI"){
        rate = 320;
        emit deviceInterfaceChanged("40 Мбайт/с");
    }
    else if (type == "Ultra2 SCSI"){
        rate = 320;
        emit deviceInterfaceChanged("40 Мбайт/с");
    }
    else if (type == "Ultra2 Wide SCSI"){
        rate = 640;
        emit deviceInterfaceChanged("80 Мбайт/с");
    }
    else if (type == "Ultra3 SCSI"){
        rate = 1280;
        emit deviceInterfaceChanged("160 Мбайт/с");
    }
    else if (type == "Ultra-320 SCSI"){
        rate = 2560;
        emit deviceInterfaceChanged("320 Мбайт/с");
    }
    else if (type == "Ultra-640 SCSI"){
        rate = 5120;
        emit deviceInterfaceChanged("640 Мбайт/с");
    }
    else if (type == "ATA-1 (PIO Mode 0)"){
        rate = 26.4;
        emit deviceInterfaceChanged("3.3 Мбайт/с");
    }
    else if (type == "ATA-2 (PIO Mode 4)"){
        rate = 133.6;
        emit deviceInterfaceChanged("16.7 Мбайт/с");
    }
    else if (type == "ATA-1 (DMA Single 0)"){
        rate = 16.8;
        emit deviceInterfaceChanged("2.1 Мбайт/с");
    }
    else if (type == "ATA-2 (DMA Multi 1)"){
        rate = 106.4;
        emit deviceInterfaceChanged("13.3 Мбайт/с");
    }
    else if (type == "Ultra ATA/33"){
        rate = 266.4;
        emit deviceInterfaceChanged("33.3 Мбайт/с");
    }
    else if (type == "Ultra ATA/167"){
        rate = 1064;
        emit deviceInterfaceChanged("133 Мбайт/с");
    }
    else if (type == "PCI-Express 2.0 x2"){
        rate = 8000;
        emit deviceInterfaceChanged("8 Гбит/с");
    }
    else if (type == "PCI-Express 2.0 x4"){
        rate = 16000;
        emit deviceInterfaceChanged("16 Гбит/с");
    }
    else if (type == "PCI-Express 2.0 x8"){
        rate = 32000;
        emit deviceInterfaceChanged("32 Гбит/с");
    }
    else if (type == "USB 1.0"){
        rate = 1.5;
        emit deviceInterfaceChanged("1.5 Мбит/с");
    }
    else if (type == "USB 1.1"){
        rate = 12;
        emit deviceInterfaceChanged("12 Мбит/с");
    }
    else if (type == "USB 2.0"){
        rate = 480;
        emit deviceInterfaceChanged("480 Мбит/с");
    }
    else if (type == "USB 3.0"){
        rate = 5000;
        emit deviceInterfaceChanged("5 Гбит/с");
    }
    else if (type == "USB 3.1"){
        rate = 10000;
        emit deviceInterfaceChanged("10 Гбит/с");
    }
    else{
        int temp = type.toInt();
        rate = (float)temp;
    }

    if((device_id == 2) || (device_id == 5)){
        flashDevice->setTransferRate(rate);
    }
    else{
        diskDevice->setTransferRate(rate);
    }
}

void DeviceWidget::deviceBtns(){
    //кнопка сохранения файла
    writeFileBtn = new QPushButton("Записать файл", this);
    StyleSet::setQPushButtonStyle(writeFileBtn);
    writeFileBtn->setEnabled(false);
    connect(writeFileBtn, &QPushButton::clicked, this, &DeviceWidget::writeInMemory);

    //кнопка расчета
    QPushButton *calcBtn = new QPushButton(this);
    StyleSet::setQPushButtonStyle(calcBtn);
    connect(calcBtn, &QPushButton::clicked, this, &DeviceWidget::checkingErrors);
    connect(this, &DeviceWidget::calculate, this, &DeviceWidget::setResultEdits);

    if((device_id == 2) || (device_id == 5)){
        deviceLayout->addWidget(writeFileBtn, 9, 2);
        calcBtn->setText("Рассчитать IOPS");
        deviceLayout->addWidget(calcBtn, 9, 3, 1, 2);
    }
    else{
        deviceLayout->addWidget(writeFileBtn, 10, 2);

        if(device_id == 4)
            calcBtn->setText("Рассчитать скорость чтения/записи");
        else{
            calcBtn->setText("Рассчитать время ожидания");
            deviceLayout->setColumnMinimumWidth(4, 120);
        }
        deviceLayout->addWidget(calcBtn, 10, 3, 1, 2);
    }

    //кнопка возврата в главное меню
    returnToMenuBtn = new QPushButton(QIcon(":/images/return.png"), "", this);
    returnToMenuBtn->setIconSize(QSize(30, 30));
    returnToMenuBtn->setStyleSheet("border-style: outset;\n");
    returnToMenuBtn->setCursor(Qt::PointingHandCursor);
    deviceLayout->addWidget(returnToMenuBtn, 11, 0, Qt::AlignLeft);
}

void DeviceWidget::checkingErrors(){
    bool errorFlag = false;
    if((device_id == 2) || (device_id == 5)){
        if((flashDevice->getReadSpeed() == 0) ||
           (flashDevice->getWriteSpeed() == 0) ||
           (flashDevice->getTransferRate() == 0) ||
           (flashDevice->getMemorySize() == 0) ||
           (flashDevice->getSectorSize() == 0)){
            errorFlag = true;
        }       
    }
    else{
        if((diskDevice->getRPM() == 0) ||
           (diskDevice->getTransferRate() == 0) ||
           (diskDevice->getMemorySize() == 0) ||
           (diskDevice->getSectorSize() == 0)){
            errorFlag = true;
        }

        if(device_id == 3){
            if(diskDevice->getSidesNumber() == 0){
                errorFlag = true;
            }
        }
        else{
            if(diskDevice->getCache() == 0){
                errorFlag = true;
            }
        }

        if(device_id != 4){
            if((diskDevice->getTracksNumber() == 0) ||
               (diskDevice->getCylindersNumber() == 0)){
                errorFlag = true;
            }
        }
    }

    if(errorFlag){
        msgBox->emptySettings();
    }
    else{
        int sectorsNumber = abstractDevice->getMemorySize() / abstractDevice->getSectorSize();
        deviceMemory->setSectorsNumber(sectorsNumber);
        deviceMemory->drawAllSectors();
        emit calculate();
    }
}

void DeviceWidget::setResultEdits(){
    if((device_id == 1) || (device_id == 3)){
        resultEdit_1->setText(QString::number(diskDevice->getLatency()) + " мс");
    }
    else if(device_id == 4){
        resultEdit_1->setText(QString::number(diskDevice->getReadWriteSpeed()) + " КБ/с");
    }
    else{
        resultEdit_1->setText(QString::number(flashDevice->getReadIOPS()));
        resultEdit_2->setText(QString::number(flashDevice->getWriteIOPS()));
    }
    writeFileBtn->setEnabled(true);
}

void DeviceWidget::writeInMemory(){
    QByteArray tempFileData;
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Сохранить файл"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    if(fileName != ""){
        QFile tempFile(fileName);
        tempFile.open(QIODevice::ReadOnly);
        tempFileData = tempFile.readAll();

        if((device_id == 2) || (device_id == 5)){
            flashDevice->setMemoryFile(tempFileData);
        }
        else{
            diskDevice->setMemoryFile(tempFileData);
        }

        float fileSize = tempFile.size();
        int numberOfSectors = 0;

        float numberOfSectors_ = fileSize / ((float)deviceMemory->getSectorSize());
        if((int)numberOfSectors_ < numberOfSectors_){
            numberOfSectors = (int)numberOfSectors_ + 1;
        }
        else{
            numberOfSectors = (int)numberOfSectors_;
        }

        if((device_id == 2) || (device_id == 5)){
            abstractDevice = flashDevice;
        }
        else{
            abstractDevice = diskDevice;
        }

        if((deviceMemory->getSectorsNumber() - abstractDevice->getFilledSectors()) >= numberOfSectors){
            deviceMemory->filledSectors(numberOfSectors, abstractDevice->getFilledSectors());
            abstractDevice->setFilledSectors(numberOfSectors);
            msgBox->redundancy(numberOfSectors * deviceMemory->getSectorSize() - fileSize);
        }
        else{
            msgBox->memoryOverflow();
        }
    }
}

QPushButton *DeviceWidget::getReturnToMenuBtn()
{
    return returnToMenuBtn;
}

DeviceWidget::~DeviceWidget()
{

}


