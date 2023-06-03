#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QMediaPlayer>
#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent, const Repository& songRepo)
        : QMainWindow(parent), m_allSongs{}, m_songController{m_allSongs}
{
    this->setupUI();
    for (const auto &[k, song] : songRepo.getSongs())
        m_songController.addSong(song.getTitle(), song.getArtist(), song.getLink(), song.getLyrics());

    m_refreshQListWidget(m_leftLayout->m_listSongs, m_songController.getSongs());
    m_refreshQListWidget(m_rightLayout->m_listPlaylist, m_songController.getPlaylistSongs());
}


MainWindow::~MainWindow()
{
    //delete m_centralWidget;

    delete m_leftLayout;
    delete m_middleLayout;
    delete m_rightLayout;
    delete m_videoPlayer;
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    m_baseLayout = new QHBoxLayout(m_centralWidget);

    m_leftLayout = new LeftLayout(m_baseLayout);
    m_middleLayout = new MiddleLayout(m_baseLayout);
    m_rightLayout = new RightLayout(m_baseLayout);
    m_videoPlayer = new VideoPlayer(this);

    this->setCentralWidget(m_centralWidget);

    connect(m_leftLayout->m_delete, &QPushButton::clicked, this, &MainWindow::m_deleteButtonAction);
    connect(m_leftLayout->m_add, &QPushButton::clicked, this, &MainWindow::m_addButtonAction);
    connect(m_leftLayout->m_viewLyrics, &QPushButton::clicked, this, &MainWindow::m_viewLyricsButtonAction);
    connect(m_leftLayout->m_sortByTitle, &QPushButton::clicked, this, &MainWindow::m_sortTitleButtonAction);
    connect(m_leftLayout->m_sortByArtist, &QPushButton::clicked, this, &MainWindow::m_sortArtistButtonAction);
    connect(m_leftLayout->m_generateRandomPlaylist, &QPushButton::clicked, this, &MainWindow::m_randomPlaylistButtonAction);

    connect(m_middleLayout->m_insertButton, &QPushButton::clicked, this, &MainWindow::m_insertButtonAction);
    connect(m_middleLayout->m_removeButton, &QPushButton::clicked, this, &MainWindow::m_removeButtonAction);

    connect(m_rightLayout->m_playButton, &QPushButton::clicked, this, &MainWindow::m_playButtonAction);
    connect(m_rightLayout->m_stopButton, &QPushButton::clicked, this, &MainWindow::m_stopButtonAction);

}

MainWindow::LeftLayout::LeftLayout(QHBoxLayout* parent)
{
    m_mainLayout = new QVBoxLayout();

    m_listSongsLabel = new QLabel("All songs");
    m_listSongs = new QListWidget();
    m_mainLayout->addWidget(m_listSongsLabel);
    m_mainLayout->addWidget(m_listSongs);


    m_lineEditsForm = new QFormLayout();
    m_lineEditsForm->setLabelAlignment(Qt::AlignLeft);

    m_titleLabel = new QLabel("Title:");
    m_titleText = new QLineEdit();
    m_lineEditsForm->addRow(m_titleLabel, m_titleText);

    m_artistLabel = new QLabel("Artist:");
    m_artistText = new QLineEdit();
    m_lineEditsForm->addRow(m_artistLabel, m_artistText);

    m_linkLabel = new QLabel("Link:");
    m_linkText = new QLineEdit();
    m_lineEditsForm->addRow(m_linkLabel, m_linkText);

    m_lyricsLabel = new QLabel("Lyrics:");
    m_lyricsText = new QLineEdit();
    m_lineEditsForm->addRow(m_lyricsLabel, m_lyricsText);

    m_mainLayout->addLayout(m_lineEditsForm);



    m_buttonGrid = new QGridLayout;
    m_buttonGrid->setAlignment(Qt::AlignAbsolute);

    m_add = new QPushButton("Add");
    m_buttonGrid->addWidget(m_add, 0, 0);

    m_delete = new QPushButton("Delete");
    m_buttonGrid->addWidget(m_delete, 0, 1);

    m_viewLyrics = new QPushButton("View song lyrics");
    m_buttonGrid->addWidget(m_viewLyrics, 0, 2);


    m_sortByTitle = new QPushButton("Sort Titles");
    m_buttonGrid->addWidget(m_sortByTitle, 1, 0);

    m_sortByArtist = new QPushButton("Sort Artists");
    m_buttonGrid->addWidget(m_sortByArtist, 1, 1);

    m_generateRandomPlaylist = new QPushButton("Generate Random Playlist");
    m_buttonGrid->addWidget(m_generateRandomPlaylist, 1, 2);

    m_mainLayout->addLayout(m_buttonGrid);

    parent->addLayout(m_mainLayout);
    //parent->setLayout(m_mainLayout);
}

MainWindow::MiddleLayout::MiddleLayout(QHBoxLayout *parent)
{
    m_mainLayout = new QVBoxLayout();
    m_insertButton = new QPushButton(">");
    m_mainLayout->setAlignment(Qt::AlignVCenter);
    m_mainLayout->addWidget(m_insertButton);
    m_removeButton = new QPushButton("<");
    m_mainLayout->addWidget(m_removeButton);

    parent->addLayout(m_mainLayout);

}

MainWindow::RightLayout::RightLayout(QHBoxLayout *parent)
{

    m_mainLayout = new QVBoxLayout();

    m_listPlaylistLabel = new QLabel("Playlist");
    m_listPlaylist = new QListWidget();
    m_mainLayout->addWidget(m_listPlaylistLabel);
    m_mainLayout->addWidget(m_listPlaylist);

    m_buttonLayout = new QHBoxLayout();

    m_playButton = new QPushButton("Play");
    m_stopButton = new QPushButton("Stop");

    m_buttonLayout->addWidget(m_playButton);
    m_buttonLayout->addWidget(m_stopButton);

    m_mainLayout->addLayout(m_buttonLayout);

    parent->addLayout(m_mainLayout);
}


void MainWindow::m_addButtonAction()
{
    std::string title = m_leftLayout->m_titleText->text().toStdString();
    std::string artist = m_leftLayout->m_artistText->text().toStdString();
    std::string link = m_leftLayout->m_linkText->text().toStdString();
    std::string lyrics = m_leftLayout->m_lyricsText->text().toStdString();

    if (title.empty() or artist.empty())
    {
        QMessageBox msgBox;
        msgBox.setText("Must have a title and an artist");
        msgBox.exec();
        return;
    }

    try
    {
        m_songController.addSong(title, artist, link, lyrics);
        m_refreshQListWidget(m_leftLayout->m_listSongs, m_songController.getSongs());
        m_modifiedState();
    }
    //song was already present in the songList
    catch (const std::exception &exc)
    {
        QMessageBox msgBox;
        msgBox.setText(exc.what());
        msgBox.exec();
        return;
    }


}

void MainWindow::m_deleteButtonAction()
{
    int songListRow = m_leftLayout->m_listSongs->currentRow();

    //if no row is selected
    if (songListRow != -1)
    {
        QListWidgetItem *it = m_leftLayout->m_listSongs->takeItem(songListRow);
        std::string songStr = it->text().toStdString();
        std::vector<std::string> songAttributes = Song::getBackSongAttributes(songStr);

        m_songController.removeSong(m_songController.findSong(songAttributes[0], songAttributes[1]));

        m_refreshQListWidget(m_rightLayout->m_listPlaylist, m_songController.getPlaylistSongs());

        m_modifiedState();
    }

}



void MainWindow::m_insertButtonAction()
{
    int songListRow = m_leftLayout->m_listSongs->currentRow();

    //if no row is selected
    if (songListRow != -1)
    {
        QListWidgetItem *it = m_leftLayout->m_listSongs->item(songListRow);
        std::string songStr = it->text().toStdString();
        std::vector<std::string> songAttributes = Song::getBackSongAttributes(songStr);

        const Song &ref_song = m_songController.findSong(songAttributes[0], songAttributes[1]);

        try
        {
            m_songController.addToPlaylist(ref_song);
            m_refreshQListWidget(m_rightLayout->m_listPlaylist, m_songController.getPlaylistSongs());

            m_modifiedState();
        }
        //the given song was already in the playlist
        catch (const std::exception& exception)
        {
            QMessageBox msgBox;
            msgBox.setText(exception.what());
            msgBox.exec();
            return;
        }


    }

}

void MainWindow::m_removeButtonAction()
{
    int songListRow = m_rightLayout->m_listPlaylist->currentRow();

    if (songListRow != -1)
    {
        QListWidgetItem *it = m_rightLayout->m_listPlaylist->takeItem(songListRow);
        std::string songStr = it->text().toStdString();
        std::vector<std::string> songAttributes = Song::getBackSongAttributes(songStr);

        m_songController.removeFromPlaylist(m_songController.findSong(songAttributes[0], songAttributes[1]));


        m_modifiedState();
    }
}

void MainWindow::m_viewLyricsButtonAction()
{
    int songListRow = m_leftLayout->m_listSongs->currentRow();

    //if no row is selected
    if (songListRow != -1)
    {
        QListWidgetItem *it = m_leftLayout->m_listSongs->item(songListRow);
        std::string songStr = it->text().toStdString();
        std::vector<std::string> songAttributes = Song::getBackSongAttributes(songStr);

        const Song &ref_song = m_songController.findSong(songAttributes[0], songAttributes[1]);


        QMessageBox msgBox;
        msgBox.setText(ref_song.getLyrics().c_str());
        msgBox.exec();
        return;
    }
}

void MainWindow::m_refreshQListWidget(QListWidget *list, const Repository::SongMap_t& songs)
{
    list->clear();

    for (const auto& songPair : songs)
        list->addItem(songPair.second.toString().c_str());
}

void MainWindow::m_sortTitleButtonAction()
{
    m_leftLayout->m_listSongs->clear();
    m_rightLayout->m_listPlaylist->clear();

    for(const auto& song : m_songController.getSongsSortedByTitle())
        m_leftLayout->m_listSongs->addItem(song.toString().c_str());

    for(const auto& song : m_songController.getPlaylistSortedByTitle())
        m_rightLayout->m_listPlaylist->addItem(song.toString().c_str());

}

void MainWindow::m_sortArtistButtonAction()
{
    m_leftLayout->m_listSongs->clear();
    m_rightLayout->m_listPlaylist->clear();

    for(const auto& song : m_songController.getSongsSortedByArtist())
        m_leftLayout->m_listSongs->addItem(song.toString().c_str());

    for(const auto& song : m_songController.getPlaylistSortedByArtist())
        m_rightLayout->m_listPlaylist->addItem(song.toString().c_str());
}

void MainWindow::m_randomPlaylistButtonAction()
{

    bool ok;
    int minValue = 0;
    static int option = 0;
    int maxValue = (int)m_songController.getSongs().size();




    option = QInputDialog::getInt(this, tr("Generate Random Playlist"), tr("How many songs:"),
                                      option, minValue, maxValue, 1, &ok);
    if (ok)
    {
        m_songController.clearPlaylist();
        m_songController.generateRandomPlaylist(option);
        m_refreshQListWidget(m_rightLayout->m_listPlaylist, m_songController.getPlaylistSongs());

        m_modifiedState();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->type() == QKeyEvent::KeyPress)
    {
        if (e->matches(QKeySequence::Undo))
        {
            m_songController.undo();

            m_refreshQListWidget(m_leftLayout->m_listSongs, m_songController.getSongs());
            m_refreshQListWidget(m_rightLayout->m_listPlaylist, m_songController.getPlaylistSongs());
        }
        else if (e->matches(QKeySequence::Redo)
                 or (e->key() == Qt::Key_Y && e->modifiers().testFlag(Qt::ControlModifier)))
        {
            m_songController.redo();

            m_refreshQListWidget(m_leftLayout->m_listSongs, m_songController.getSongs());
            m_refreshQListWidget(m_rightLayout->m_listPlaylist, m_songController.getPlaylistSongs());
        }

    }
}

void MainWindow::m_modifiedState()
{
    m_songController.clearRedoStack();
}


MainWindow::VideoPlayer::VideoPlayer(QObject *parent)
{
    m_player = new QMediaPlayer(parent);
    m_audioOutput = new QAudioOutput(parent);
    m_videoWidget = new QVideoWidget;
    m_videoWidget->setAttribute( Qt::WA_QuitOnClose, false);
}



void MainWindow::m_playButtonAction()
{
    int songListRow = m_rightLayout->m_listPlaylist->currentRow();

    //if no row is selected
    if (songListRow != -1)
    {
        QListWidgetItem *it = m_rightLayout->m_listPlaylist->item(songListRow);
        std::string songStr = it->text().toStdString();
        std::vector<std::string> songAttributes = Song::getBackSongAttributes(songStr);

        const Song &ref_song = m_songController.findSong(songAttributes[0], songAttributes[1]);

        if (not ref_song.getLink().empty())
        {
            m_videoPlayer->m_player->setSource(QUrl::fromLocalFile(ref_song.getLink().c_str()));
            m_videoPlayer->m_player->setVideoOutput(m_videoPlayer->m_videoWidget);
            m_videoPlayer->m_player->setAudioOutput(m_videoPlayer->m_audioOutput);
            m_videoPlayer->m_videoWidget->setWindowTitle(ref_song.toString().c_str());
            m_videoPlayer->m_videoWidget->show();


            m_videoPlayer->m_player->play();
            m_videoPlayer->m_audioOutput->setMuted(false);
            m_videoPlayer->m_audioOutput->setVolume(50);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Song does not have a link");
            msgBox.exec();
        }

    }
}

void MainWindow::m_stopButtonAction()
{
    m_videoPlayer->m_videoWidget->hide();
    m_videoPlayer->m_audioOutput->setMuted(true);
}

