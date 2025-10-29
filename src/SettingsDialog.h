#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QCheckBox>
#include <QSlider>
#include <QComboBox>
#include <QSettings>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    
    // Getters for settings
    bool isMusicEnabled() const;
    bool isSoundEnabled() const;
    int musicVolume() const;
    int soundVolume() const;
    bool isFullscreen() const;
    bool isVsyncEnabled() const;
    QString leftKey() const;
    QString rightKey() const;
    
    void loadSettings();
    void saveSettings();

signals:
    void settingsChanged();

private slots:
    void onAccepted();
    void onRejected();

private:
    void createAudioTab();
    void createGraphicsTab();
    void createControlsTab();
    
    QTabWidget *m_tabWidget;
    
    // Audio settings
    QCheckBox *m_musicEnabledCheck;
    QCheckBox *m_soundEnabledCheck;
    QSlider *m_musicVolumeSlider;
    QSlider *m_soundVolumeSlider;
    
    // Graphics settings
    QCheckBox *m_fullscreenCheck;
    QCheckBox *m_vsyncCheck;
    
    // Controls settings
    QComboBox *m_leftKeyCombo;
    QComboBox *m_rightKeyCombo;
    
    QSettings m_settings;
};

#endif
