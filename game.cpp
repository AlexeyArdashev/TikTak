#include <QGridLayout>
#include <QDebug>
#include "game.h"
#include "bot.h"

move stepOp; // ход соперника

Game::Game(QWidget *pwgt): QWidget (pwgt)
{

    setMaximumSize(200,200);
    resize(200,200);
    QGridLayout *ptopLayout=new QGridLayout;
    int ID=0;
    flagSecondPlayer =false; // флаг хода второго игрока (нужно когда режим human)
    flagEnd=false;
    stateGame=AI;
    ButtonId* current;
    m_human=new QRadioButton ("&human");
    m_AI_rand=new QRadioButton("&AI_rand");
    m_AI=new QRadioButton("&AI");
    reset=new QPushButton("Reset");

    ptopLayout->addWidget(m_human,0,0);
    ptopLayout->addWidget(m_AI_rand,0,1);
    ptopLayout->addWidget(m_AI,0,2);
    m_AI->setChecked(true);

    connect(m_human,SIGNAL(clicked()),SLOT(slotRadioBottom()));
    connect(m_AI_rand,SIGNAL(clicked()),SLOT(slotRadioBottom()));
    connect(m_AI,SIGNAL(clicked()),SLOT(slotRadioBottom()));
    connect(reset,SIGNAL(clicked()),SLOT(Reset()));

   for(int i=1;i<4;i++)
       for (int j=0;j<3;j++)
       {
           current=createButton(ID);
           ptopLayout->addWidget(current,i,j);
           masButton.push_back(current);
           ID++;
       }

   console = new QLabel();
   console->setWordWrap(true);
   console->setAlignment(Qt::AlignCenter);
   console->setMinimumSize(150,50);
   ptopLayout->addWidget(console,4,0,1,3);
   ptopLayout->addWidget(reset,5,0,1,3);

   setLayout(ptopLayout);
}

Game::~Game(){
   for (int i=0; i<masButton.size();i++) delete masButton[i];
   delete m_human;
   delete m_AI_rand;
   delete m_AI;
   delete reset;

}
ButtonId* Game::createButton(int index)
{
    ButtonId *pcmd=new ButtonId(index);
    pcmd->setMinimumSize(60,60);
    pcmd->setMaximumSize(60,60);
    QFont font;
    font.setPointSize(26);
    pcmd->setFont(font);
    connect(pcmd,SIGNAL(clicked()),SLOT (slotButtonClicked()));
    return pcmd;
}

void Game::slotButtonClicked(){
 int id=((ButtonId*)sender())->GetID();
 if (board[id]=='X' || board[id]=='O' || flagEnd) return; // если уже кнопка была нажата или игра закончена - выход

 if (!flagSecondPlayer){
    ((ButtonId*)sender())->setText("X");
    board[id]='X';
 }

 // qDebug()<<id;

 bool rez=Winner(board,'X');
 if (rez) {
     //  qDebug()<<"'X' is win";
    console->setText("Крестики победили");
       flagEnd=true;
       return;
   }

 if (BoardIsFull())  {
    console->setText("Ничья");
    flagEnd=true;
    return;
   }

  switch(stateGame){
   case AI:
    stepOp=MinMax(board,'O');
   break;
   case AI_rand:
    stepOp= RandMove(board);
   break;
   case human:
     if (flagSecondPlayer==false) {
        flagSecondPlayer=true;
     return;
     }
    stepOp.index=id;
    flagSecondPlayer=false;
   break;
  }

 board[stepOp.index]='O';
 masButton[stepOp.index]->setText("O");
 rez=Winner(board,'O');
   if (rez) {
     console->setText("Нолики победили");
     flagEnd=true;
   }

}
void Game::slotRadioBottom(){
  Reset();
  if (m_AI_rand->isChecked()) stateGame=AI_rand;
  else if (m_AI->isChecked()) stateGame=AI;
  else stateGame=human;
}
void Game::Reset(){
  for (int i=0;i<9;i++){
    board[i]='0';
    masButton[i]->setText("");
    flagSecondPlayer=false;
  }
  flagEnd=false;
  console->setText("");
}

bool Game::BoardIsFull(){
  for (int i=0;i<9;i++)
  if (board[i]!='X' && board[i]!='O') return false;
return true;
}
