#ifndef BOT_H
#define BOT_H

#include <ctime>
struct move{
 int index; // индекс хода
 int score; // очки
};

// !!!! Работает только когда размер newBoard равен 9!!!!!!!!!!!!!
bool Winner(char *board,char player);
move MinMax(char *newBoard,char player);
move RandMove(char *newBoard);


move MinMax(char *newBoard,char player)
// ссылка на алгоритм функции https://tproger.ru/translations/tic-tac-toe-minimax/
{

   QVector<int> availSpots;// доступные клетки
   move rezult;
   for (int i=0;i<9;i++)
   {  if (newBoard[i]!='O' && newBoard[i]!='X')
         availSpots.push_back(i);

   }
   // проверка на состояние (победа / поражение / ничья)
   if (Winner(newBoard,'X')){
       rezult.score=10;
       return rezult;
   }

   else if (Winner(newBoard,'O'))
   {
       rezult.score=-10;
       return rezult;
   }
   else if (availSpots.size()==0) // свобоных клеток нет, ничья
   {
       rezult.score=0;
       return rezult;
   }

    QVector<move> Moves; // массив ходов
    for (int i=0; i<availSpots.size();i++)
     {
       rezult.index=availSpots[i];
       newBoard[availSpots[i]]=player; //текущий ход

       if (player=='X'){
          move res=MinMax(newBoard,'O');
          rezult.score=res.score;
       }
       else{
          move res=MinMax(newBoard,'X');
          rezult.score=res.score;

       }

      Moves.push_back(rezult); // помещаем rezult в массив ходов
      newBoard[availSpots[i]]=0; // сброс изменений
     }

    int BestMove=0;

    if (player=='X'){  // если это ход "Х", пройти циклом по ходам и выбрать ход с наибольшим количеством очков
       int bestScore=-10000;
       for (int i=0;i<Moves.size();i++)
          {
             if (Moves[i].score>bestScore){
                bestScore=Moves[i].score;
                BestMove=i;
             }
          }
     }
    else{ // если это ход "О", пройти циклом по ходам и выбрать ход с наименьшим количеством очков

       int bestScore=10000;
       for (int i=0;i<Moves.size();i++)
       {
             if (Moves[i].score<bestScore){
              bestScore=Moves[i].score;
              BestMove=i;
             }
       }
    }

return Moves[BestMove];

}

move RandMove(char *newBoard){

 QVector <int> temp; // временный массив содержит индексы свободных клеток
 move rezult;
 for (int i=0;i<9;i++){
     if (newBoard[i]!='X' && newBoard[i]!='O') temp.push_back(i);
 }
 srand( time( 0 ) ); // автоматическая рандомизация
 int random=rand()%(temp.size()-1);
 rezult.index=temp.at(random);
 rezult.score=1;
 return rezult;
}
bool Winner(char *board,char player)
{
     if (
        board[0]==player && board[1]==player && board[2]==player ||
        board[3]==player && board[4]==player && board[5]==player ||
        board[6]==player && board[7]==player && board[8]==player ||
        board[0]==player && board[3]==player && board[6]==player ||
        board[1]==player && board[4]==player && board[7]==player ||
        board[2]==player && board[5]==player && board[8]==player ||
        board[0]==player && board[4]==player && board[8]==player ||
        board[2]==player && board[4]==player && board[6]==player
        )
     return true;
     return false;

}
#endif // BOT_H
