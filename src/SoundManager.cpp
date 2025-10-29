#include "SoundManager.h"
#include <QDebug>

// Stub implementation for sound system
// To enable actual sound, install Qt Multimedia: sudo apt-get install libqt6multimedia6
// Then update CMakeLists.txt to link Qt6::Multimedia

SoundManager::SoundManager(QObject *parent)
    : QObject(parent),
      m_musicEnabled(true),
      m_soundEnabled(true),
      m_musicVolume(0.5f),
      m_soundVolume(0.7f)
{
    qDebug() << "SoundManager: Stub implementation (Qt Multimedia not available)";
}

SoundManager::~SoundManager()
{
}

void SoundManager::playSound(Sound sound)
{
    if (!m_soundEnabled) return;
    
    // Stub - would play actual sound if Qt Multimedia was available
    const char* soundName = "";
    switch (sound) {
        case Sound::BallHit: soundName = "BallHit"; break;
        case Sound::BrickBreak: soundName = "BrickBreak"; break;
        case Sound::PowerUp: soundName = "PowerUp"; break;
        case Sound::LoseLife: soundName = "LoseLife"; break;
        case Sound::GameOver: soundName = "GameOver"; break;
        case Sound::Victory: soundName = "Victory"; break;
    }
    
    // qDebug() << "SoundManager: Would play sound:" << soundName;
}

void SoundManager::playBackgroundMusic()
{
    if (!m_musicEnabled) return;
    // Stub - would play background music if Qt Multimedia was available
}

void SoundManager::stopBackgroundMusic()
{
    // Stub
}

void SoundManager::setMusicVolume(float volume)
{
    m_musicVolume = qBound(0.0f, volume, 1.0f);
}

void SoundManager::setSoundVolume(float volume)
{
    m_soundVolume = qBound(0.0f, volume, 1.0f);
}

void SoundManager::setMusicEnabled(bool enabled)
{
    m_musicEnabled = enabled;
}

void SoundManager::setSoundEnabled(bool enabled)
{
    m_soundEnabled = enabled;
}
