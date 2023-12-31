#ifndef BANK_H
#define BANK_H


class Bank
{
private:
    float balance=0;
public:
    Bank();
    Bank(float balance);
    bool deposit(float newBalance);
    bool pay(float newBalance);
    float getBalance() const;
};

#endif // BANK_H
