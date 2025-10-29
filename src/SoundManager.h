#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <memory>

// Stub implementation - can be extended with actual audio libraries
// when Qt Multimedia is installed (requires libqt6multimedia6)

class SoundManager : public QObject
{
    Q_OBJECT

public:
    enum class Sound {
        BallHit,
        BrickBreak,
        PowerUp,
        LoseLife,
        GameOver,
        Victory
    };

    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager();

    void playSound(Sound sound);
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void setMusicVolume(float volume);
    void setSoundVolume(float volume);
    void setMusicEnabled(bool enabled);
    void setSoundEnabled(bool enabled);

    bool isMusicEnabled() const { return m_musicEnabled; }
    bool isSoundEnabled() const { return m_soundEnabled; }
    float musicVolume() const { return m_musicVolume; }
    float soundVolume() const { return m_soundVolume; }

private:
    bool m_musicEnabled;
    bool m_soundEnabled;
    float m_musicVolume;
    float m_soundVolume;
};

#endif
