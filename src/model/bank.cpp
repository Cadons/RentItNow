#include "bank.h"

bool Bank::deposit(float payment)
{
    if(payment>0){
        balance += payment;
 return true;
    }
    return false;

}

bool Bank::pay(float payment)
{
    if(payment>0&&(balance-payment)>=0)
    {

        balance -= payment;
        return true;
    }
    return false;
}

float Bank::getBalance() const
{
    return balance;
}

Bank::Bank()
{

}

Bank::Bank(float balance):balance(balance)
{

}
