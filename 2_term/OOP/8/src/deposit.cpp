#include "deposit.h"

#include <algorithm>

BankDeposit::BankDeposit(long _open_date, long _terminate_date, double _rate,
                         double _amount) {
  open_date = _open_date;
  termination_date = _terminate_date;
  rate = _rate;
  amount = _amount;
}

std::string BankDeposit::print_class_name() { return "BankDeposit"; }

SimpleBankDeposit::SimpleBankDeposit(long _open_date, long _terminate_date,
                                     double _rate, double _amount)
    : BankDeposit(_open_date, _terminate_date, _rate, _amount) {}

double SimpleBankDeposit::calculate_income(long to) {
  auto month_count = (to - this->open_date) / (60. * 60 * 24 * 30);
  return this->amount * rate * month_count;
}

double SimpleBankDeposit::calculate_income() {
  return this->calculate_income(this->termination_date);
}

std::string SimpleBankDeposit::print_class_name() {
  return "SimpleBankDeposit";
}

ComplexBankDeposit::ComplexBankDeposit(long _open_date, long _terminate_date,
                                       double _rate, double _amount)
    : BankDeposit(_open_date, _terminate_date, _rate, _amount) {}

double ComplexBankDeposit::calculate_income(long to) {
  auto month_count = (to - this->open_date) / (60. * 60 * 24 * 30);
  auto progressive_amount = this->amount;
  for (auto i = 0; i < month_count; i++) {
    progressive_amount += progressive_amount * rate;
  }
  return progressive_amount - this->amount;
}

double ComplexBankDeposit::calculate_income() {
  return this->calculate_income(this->termination_date);
}

std::string ComplexBankDeposit::print_class_name() {
  return "ComplexBankDeposit";
}

VIPBankDeposit::VIPBankDeposit(long _open_date, long _terminate_date,
                               double _rate, double _amount)
    : ComplexBankDeposit(_open_date, _terminate_date, _rate, _amount) {}

std::string VIPBankDeposit::print_class_name() { return "VIPBankDeposit"; }

void VIPBankDeposit::add_money(double money) {
  this->amount += money;
  this->rate = std::min(.02, this->rate + money / 1000000);
}
