#include <QMessageBox>
#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
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

    connect(m_leftLayout->m_update, &QPushButton::clicked, this, &MainWindow::m_updateButtonAction);
    connect(m_leftLayout->m_delete, &QPushButton::clicked, this, &MainWindow::m_deleteButtonAction);
    connect(m_leftLayout->m_add, &QPushButton::clicked, this, &MainWindow::m_addButtonAction);
    connect(m_leftLayout->m_filter, &QPushButton::clicked, this, &MainWindow::m_filterButtonAction);

    connect(m_middleLayout->m_insertButton, &QPushButton::clicked, this, &MainWindow::m_insertButtonAction);

}

void MainWindow::m_updateButtonAction()
{
    QMessageBox msgBox;
    msgBox.setText("Not implemented yet\n(Very fancy box)");
    msgBox.exec();
}
void MainWindow::m_filterButtonAction()
{
    QMessageBox msgBox;
    msgBox.setText("Not implemented yet\n(Very fancy box)");
    msgBox.exec();
}

void MainWindow::m_addButtonAction()
{
    std::string title = m_leftLayout->m_titleText->text().toStdString();
    std::string artist = m_leftLayout->m_artistText->text().toStdString();
    std::string duration = m_leftLayout->m_durationText->text().toStdString();
    std::string link = m_leftLayout->m_linkText->text().toStdString();

    if (title.empty() or artist.empty() or duration.empty() or link.empty())
    {
        QMessageBox msgBox;
        msgBox.setText("Can't have empty fields!");
        msgBox.exec();
        return;
    }

    Song song(title, artist, duration, link);
    m_allSongs.push_back(song);

    QList<QListWidgetItem *> elements = m_leftLayout->m_listSongs->findItems(song.toString().c_str(), Qt::MatchExactly);
    if (elements.empty())
    {
        m_leftLayout->m_listSongs->insertItem(m_leftLayout->m_listSongs->count(), song.toString().c_str());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Song is already in list");
        msgBox.exec();
    }

}

void MainWindow::m_deleteButtonAction()
{
    int songListRow = m_leftLayout->m_listSongs->currentRow();
    QListWidgetItem *it = m_leftLayout->m_listSongs->takeItem(songListRow);
    QList<QListWidgetItem *> elements = m_rightLayout->m_listPlaylist->findItems(it->text(), Qt::MatchExactly);
    if (not elements.empty())
    {
        QListWidgetItem *it2 = elements.first();
        int songPlaylistRow = m_rightLayout->m_listPlaylist->row(it2);
        it2 = m_rightLayout->m_listPlaylist->takeItem(songPlaylistRow);
        m_playlistSongs.erase(m_playlistSongs.begin() + songPlaylistRow);
        delete it2;
    }

    m_allSongs.erase(m_allSongs.begin() + songListRow);
    delete it;
}

void MainWindow::m_insertButtonAction()
{
    int songListRow = m_leftLayout->m_listSongs->currentRow();
    QListWidgetItem *it = m_leftLayout->m_listSongs->item(songListRow);
    QList<QListWidgetItem *> elements = m_rightLayout->m_listPlaylist->findItems(it->text(), Qt::MatchExactly);
    if (elements.empty())
    {
        m_playlistSongs.push_back(m_allSongs[songListRow]);
        m_rightLayout->m_listPlaylist->insertItem(m_rightLayout->m_listPlaylist->count(), it->text());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Song is already in playlist");
        msgBox.exec();
    }
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


    m_durationLabel = new QLabel("Duration:");
    m_durationText = new QLineEdit();
    m_lineEditsForm->addRow(m_durationLabel, m_durationText);

    m_linkLabel = new QLabel("Link:");
    m_linkText = new QLineEdit();
    m_lineEditsForm->addRow(m_linkLabel, m_linkText);

    m_mainLayout->addLayout(m_lineEditsForm);



    m_buttonLayout = new QVBoxLayout;
    m_firstRow = new QHBoxLayout;

    m_add = new QPushButton("Add");
    m_firstRow->addWidget(m_add);

    m_delete = new QPushButton("Delete");
    m_firstRow->addWidget(m_delete);

    m_update = new QPushButton("Update");
    m_firstRow->addWidget(m_update);

    m_buttonLayout->addLayout(m_firstRow);

    m_filter = new QPushButton("Filter");
    m_buttonLayout->addWidget(m_filter, 0, Qt::AlignCenter);

    m_mainLayout->addLayout(m_buttonLayout);

    parent->addLayout(m_mainLayout);
    //parent->setLayout(m_mainLayout);
}

MainWindow::MiddleLayout::MiddleLayout(QHBoxLayout *parent)
{
    m_mainLayout = new QVBoxLayout();
    m_insertButton = new QPushButton(">");
    m_mainLayout->addWidget(m_insertButton);

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