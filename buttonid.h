#ifndef BUTTONID_H
#define BUTTONID_H
#include <QPushButton>

class ButtonId : public QPushButton // button with ID
{
    int ID;
public:
    ButtonId(int Id): ID(Id){ }
    int GetID() {return ID;}
signals:
    void clicked();
};

#endif // BUTTONID_H
