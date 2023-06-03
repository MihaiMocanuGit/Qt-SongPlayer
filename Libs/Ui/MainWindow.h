#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QListWidget>
#include <QKeyEvent>

#include <deque>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "../Controller/SongController.h"
#include "../Repository/Playlist.h"

class MainWindow : public QMainWindow

{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const Repository& songRepo = {});
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *e) override;


private:
    Repository m_allSongs;
    SongController m_songController;

    void setupUI();

    void m_modifiedState();

    QWidget* m_centralWidget;
    QHBoxLayout* m_baseLayout;
    struct LeftLayout
    {
        explicit LeftLayout(QHBoxLayout* parent);

        QVBoxLayout* m_mainLayout;

        QLabel* m_listSongsLabel;
        QListWidget* m_listSongs;

        QFormLayout* m_lineEditsForm;

        QLabel* m_titleLabel;
        QLineEdit* m_titleText;

        QLabel* m_artistLabel;
        QLineEdit* m_artistText;

        QLabel* m_lyricsLabel;
        QLineEdit* m_lyricsText;

        QLabel* m_linkLabel;
        QLineEdit* m_linkText;

        QGridLayout* m_buttonGrid;
        QPushButton *m_add, *m_delete, *m_viewLyrics;
        QPushButton *m_sortByTitle, *m_sortByArtist, *m_generateRandomPlaylist;

    };
    LeftLayout* m_leftLayout;
    void m_addButtonAction();
    void m_deleteButtonAction();
    void m_viewLyricsButtonAction();

    void m_sortTitleButtonAction();
    void m_sortArtistButtonAction();
    void m_randomPlaylistButtonAction();


    struct MiddleLayout
    {
        MiddleLayout(QHBoxLayout* parent);

        QVBoxLayout* m_mainLayout;
        QPushButton* m_insertButton;
        QPushButton* m_removeButton;
    };
    MiddleLayout* m_middleLayout;
    void m_insertButtonAction();
    void m_removeButtonAction();

    struct RightLayout
    {
        RightLayout(QHBoxLayout* parent);
        QVBoxLayout* m_mainLayout;

        QLabel* m_listPlaylistLabel;
        QListWidget* m_listPlaylist;
        QHBoxLayout* m_buttonLayout;
        QPushButton* m_playButton;
    };
    RightLayout* m_rightLayout;

    struct VideoPlayer
    {
        VideoPlayer();

        QMediaPlayer *m_player;
        QAudioOutput *m_audioOutput;
        QVideoWidget *m_videoWidget;

        ~VideoPlayer();
    };
    VideoPlayer* m_videoPlayer;
    void m_playButtonAction();



    void m_refreshQListWidget(QListWidget* list, const Repository::SongMap_t& songs);
};