#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QVector>
#include <QLabel>
#include "buttonid.h"

enum state {human,AI_rand,AI};



class Game : public QWidget
{
    Q_OBJECT

public:

    Game(QWidget *pwgt=0);
    ~Game();


private slots:
    void slotButtonClicked(); //нажатие на игровое поле
    void slotRadioBottom(); // переключение режима игры
    void Reset(); //сброс
private:
    char board[9]={'0','0','0','0','0','0','0','0','0'};
    QVector <ButtonId *> masButton;
    state stateGame; // режим игры
    QLabel *console; //вывод состояния игры
    bool flagSecondPlayer; // флаг наличия второго игрока (режим human)
    bool flagEnd; //игра окончена
    bool BoardIsFull();
    ButtonId *createButton( int index);
    QRadioButton *m_human;
    QRadioButton *m_AI_rand;
    QRadioButton *m_AI;
    QPushButton *reset;

};

#endif // GAME_H
