#include "bank.h"

bool Bank::deposit(float payment)
{
    if(payment>0){
        balance += payment;

    }
}

bool Bank::pay(float payment)
{
    if(payment>0&&(balance-payment)>=0)
        balance -= payment;
}

float Bank::getBalance() const
{
    return balance;
}

Bank::Bank()
{

}
