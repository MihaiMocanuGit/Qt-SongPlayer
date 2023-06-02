#include <QMessageBox>
#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), m_songController{m_allSongs}
{
    this->setupUI();
}

MainWindow::~MainWindow()
{
    //delete m_centralWidget;

    delete m_leftLayout;
    delete m_middleLayout;
    delete m_rightLayout;
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    m_baseLayout = new QHBoxLayout(m_centralWidget);

    m_leftLayout = new LeftLayout(m_baseLayout);
    m_middleLayout = new MiddleLayout(m_baseLayout);
    m_rightLayout = new RightLayout(m_baseLayout);
    this->setCentralWidget(m_centralWidget);

    connect(m_leftLayout->m_delete, &QPushButton::clicked, this, &MainWindow::m_deleteButtonAction);
    connect(m_leftLayout->m_add, &QPushButton::clicked, this, &MainWindow::m_addButtonAction);

    connect(m_middleLayout->m_insertButton, &QPushButton::clicked, this, &MainWindow::m_insertButtonAction);

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
    m_nextButton = new QPushButton("Next");

    m_buttonLayout->addWidget(m_playButton);
    m_buttonLayout->addWidget(m_nextButton);

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
        m_refreshQListWidget(m_leftLayout->m_listSongs);
    }
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
    QMessageBox msgBox;
    msgBox.setText("Not implemented yet\n(Very fancy box)");
    msgBox.exec();
}



void MainWindow::m_insertButtonAction()
{

    m_refreshQListWidget(m_rightLayout->m_listPlaylist);
}

void MainWindow::m_refreshQListWidget(QListWidget *list)
{
    m_leftLayout->m_listSongs->clear();

    for (const auto& songPair : m_allSongs.getSongs())
        list->addItem(songPair.second.toString().c_str());
}