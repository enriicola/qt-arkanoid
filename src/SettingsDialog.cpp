#include "SettingsDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), m_settings("QtArkanoid", "Arkanoid")
{
    setWindowTitle("Settings");
    setMinimumSize(500, 400);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    m_tabWidget = new QTabWidget(this);
    createAudioTab();
    createGraphicsTab();
    createControlsTab();
    
    mainLayout->addWidget(m_tabWidget);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);
    QPushButton *applyButton = new QPushButton("Apply", this);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(applyButton);
    
    mainLayout->addLayout(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, this, &SettingsDialog::onAccepted);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsDialog::onRejected);
    connect(applyButton, &QPushButton::clicked, this, [this]() {
        saveSettings();
        emit settingsChanged();
    });
    
    loadSettings();
}

void SettingsDialog::createAudioTab()
{
    QWidget *audioTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(audioTab);
    
    // Music group
    QGroupBox *musicGroup = new QGroupBox("Music");
    QVBoxLayout *musicLayout = new QVBoxLayout(musicGroup);
    
    m_musicEnabledCheck = new QCheckBox("Enable Music");
    musicLayout->addWidget(m_musicEnabledCheck);
    
    QHBoxLayout *musicVolLayout = new QHBoxLayout();
    musicVolLayout->addWidget(new QLabel("Volume:"));
    m_musicVolumeSlider = new QSlider(Qt::Horizontal);
    m_musicVolumeSlider->setRange(0, 100);
    musicVolLayout->addWidget(m_musicVolumeSlider);
    QLabel *musicVolLabel = new QLabel("50%");
    musicVolLayout->addWidget(musicVolLabel);
    
    connect(m_musicVolumeSlider, &QSlider::valueChanged, [musicVolLabel](int value) {
        musicVolLabel->setText(QString("%1%").arg(value));
    });
    
    musicLayout->addLayout(musicVolLayout);
    layout->addWidget(musicGroup);
    
    // Sound effects group
    QGroupBox *soundGroup = new QGroupBox("Sound Effects");
    QVBoxLayout *soundLayout = new QVBoxLayout(soundGroup);
    
    m_soundEnabledCheck = new QCheckBox("Enable Sound Effects");
    soundLayout->addWidget(m_soundEnabledCheck);
    
    QHBoxLayout *soundVolLayout = new QHBoxLayout();
    soundVolLayout->addWidget(new QLabel("Volume:"));
    m_soundVolumeSlider = new QSlider(Qt::Horizontal);
    m_soundVolumeSlider->setRange(0, 100);
    soundVolLayout->addWidget(m_soundVolumeSlider);
    QLabel *soundVolLabel = new QLabel("70%");
    soundVolLayout->addWidget(soundVolLabel);
    
    connect(m_soundVolumeSlider, &QSlider::valueChanged, [soundVolLabel](int value) {
        soundVolLabel->setText(QString("%1%").arg(value));
    });
    
    soundLayout->addLayout(soundVolLayout);
    layout->addWidget(soundGroup);
    
    layout->addStretch();
    m_tabWidget->addTab(audioTab, "Audio");
}

void SettingsDialog::createGraphicsTab()
{
    QWidget *graphicsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(graphicsTab);
    
    QGroupBox *displayGroup = new QGroupBox("Display");
    QVBoxLayout *displayLayout = new QVBoxLayout(displayGroup);
    
    m_fullscreenCheck = new QCheckBox("Fullscreen Mode");
    displayLayout->addWidget(m_fullscreenCheck);
    
    m_vsyncCheck = new QCheckBox("Enable VSync");
    displayLayout->addWidget(m_vsyncCheck);
    
    layout->addWidget(displayGroup);
    layout->addStretch();
    
    m_tabWidget->addTab(graphicsTab, "Graphics");
}

void SettingsDialog::createControlsTab()
{
    QWidget *controlsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(controlsTab);
    
    QGroupBox *keysGroup = new QGroupBox("Keyboard Controls");
    QVBoxLayout *keysLayout = new QVBoxLayout(keysGroup);
    
    QHBoxLayout *leftKeyLayout = new QHBoxLayout();
    leftKeyLayout->addWidget(new QLabel("Move Left:"));
    m_leftKeyCombo = new QComboBox();
    m_leftKeyCombo->addItem("A");
    m_leftKeyCombo->addItem("Left Arrow");
    leftKeyLayout->addWidget(m_leftKeyCombo);
    leftKeyLayout->addStretch();
    keysLayout->addLayout(leftKeyLayout);
    
    QHBoxLayout *rightKeyLayout = new QHBoxLayout();
    rightKeyLayout->addWidget(new QLabel("Move Right:"));
    m_rightKeyCombo = new QComboBox();
    m_rightKeyCombo->addItem("D");
    m_rightKeyCombo->addItem("Right Arrow");
    rightKeyLayout->addWidget(m_rightKeyCombo);
    rightKeyLayout->addStretch();
    keysLayout->addLayout(rightKeyLayout);
    
    QLabel *noteLabel = new QLabel("Note: Both A/D and Arrow keys are always active");
    noteLabel->setStyleSheet("color: gray; font-style: italic;");
    keysLayout->addWidget(noteLabel);
    
    layout->addWidget(keysGroup);
    layout->addStretch();
    
    m_tabWidget->addTab(controlsTab, "Controls");
}

void SettingsDialog::loadSettings()
{
    m_musicEnabledCheck->setChecked(m_settings.value("audio/musicEnabled", true).toBool());
    m_soundEnabledCheck->setChecked(m_settings.value("audio/soundEnabled", true).toBool());
    m_musicVolumeSlider->setValue(m_settings.value("audio/musicVolume", 50).toInt());
    m_soundVolumeSlider->setValue(m_settings.value("audio/soundVolume", 70).toInt());
    
    m_fullscreenCheck->setChecked(m_settings.value("graphics/fullscreen", false).toBool());
    m_vsyncCheck->setChecked(m_settings.value("graphics/vsync", true).toBool());
    
    QString leftKey = m_settings.value("controls/leftKey", "A").toString();
    m_leftKeyCombo->setCurrentText(leftKey);
    
    QString rightKey = m_settings.value("controls/rightKey", "D").toString();
    m_rightKeyCombo->setCurrentText(rightKey);
}

void SettingsDialog::saveSettings()
{
    m_settings.setValue("audio/musicEnabled", m_musicEnabledCheck->isChecked());
    m_settings.setValue("audio/soundEnabled", m_soundEnabledCheck->isChecked());
    m_settings.setValue("audio/musicVolume", m_musicVolumeSlider->value());
    m_settings.setValue("audio/soundVolume", m_soundVolumeSlider->value());
    
    m_settings.setValue("graphics/fullscreen", m_fullscreenCheck->isChecked());
    m_settings.setValue("graphics/vsync", m_vsyncCheck->isChecked());
    
    m_settings.setValue("controls/leftKey", m_leftKeyCombo->currentText());
    m_settings.setValue("controls/rightKey", m_rightKeyCombo->currentText());
    
    m_settings.sync();
}

void SettingsDialog::onAccepted()
{
    saveSettings();
    emit settingsChanged();
    accept();
}

void SettingsDialog::onRejected()
{
    loadSettings();
    reject();
}

bool SettingsDialog::isMusicEnabled() const
{
    return m_musicEnabledCheck->isChecked();
}

bool SettingsDialog::isSoundEnabled() const
{
    return m_soundEnabledCheck->isChecked();
}

int SettingsDialog::musicVolume() const
{
    return m_musicVolumeSlider->value();
}

int SettingsDialog::soundVolume() const
{
    return m_soundVolumeSlider->value();
}

bool SettingsDialog::isFullscreen() const
{
    return m_fullscreenCheck->isChecked();
}

bool SettingsDialog::isVsyncEnabled() const
{
    return m_vsyncCheck->isChecked();
}

QString SettingsDialog::leftKey() const
{
    return m_leftKeyCombo->currentText();
}

QString SettingsDialog::rightKey() const
{
    return m_rightKeyCombo->currentText();
}
