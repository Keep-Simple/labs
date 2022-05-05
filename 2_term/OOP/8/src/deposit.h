#pragma once
#include <string>

class BankDeposit {
 protected:
  long open_date;
  long termination_date;
  double rate;
  double amount;

 public:
  BankDeposit(long _open_date, long _terminate_date, double _rate,
              double _amount);
  virtual double calculate_income(long to) = 0;
  virtual double calculate_income() = 0;

  virtual std::string print_class_name() = 0;
};

class SimpleBankDeposit : public BankDeposit {
 public:
  SimpleBankDeposit(long _open_date, long _terminate_date, double _rate,
                    double _amount);
  std::string print_class_name() override;
  double calculate_income(long to) override;
  double calculate_income() override;
};

class ComplexBankDeposit : public BankDeposit {
 public:
  ComplexBankDeposit(long _open_date, long _terminate_date, double _rate,
                     double _amount);
  std::string print_class_name() override;
  double calculate_income(long to) override;
  double calculate_income() override;
};

class VIPBankDeposit : public ComplexBankDeposit {
 public:
  VIPBankDeposit(long _open_date, long _terminate_date, double _rate,
                 double _amount);
  void add_money(double);
  std::string print_class_name() override;
};
