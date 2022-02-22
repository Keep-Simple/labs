let curVal = 0;
let memory = 0;
let lastOp = "";
let previousOperator = "";
let digits = "";

function disabled(op) {
  if (op == "C") return false;
  if (digits == "" && !((op >= "0" && op <= "9") || op == ".")) return true;
  if (op == "=" && previousOperator.length != 1) return true;
  if (op == "." && digits.toString().search(/\./) != -1) return true;
  if (op == "√" && digits.toString().search(/-/) != -1) return true;

  return false;
}

function digitPressed(op) {
  if (disabled(op)) return;
  if (digits.toString().length >= display.maxDigits) return;

  if (
    lastOp.toString().length == 1 &&
    ((lastOp >= "0" && lastOp <= "9") || lastOp == ".")
  ) {
    digits = digits + op.toString();
    display.appendDigit(op.toString());
  } else {
    digits = op;
    display.appendDigit(op.toString());
  }

  lastOp = op;
}

function operatorPressed(op) {
  if (disabled(op)) return;

  if (op == "C" || display.isError) {
    display.clear();
    curVal = 0;
    memory = 0;
    lastOp = "";
    digits = "";
    return;
  }

  lastOp = op;

  if (op == "±") {
    digits = Number(digits.valueOf() * -1);
    display.setDigit(display.displayNumber(digits));
    return;
  }

  switch (previousOperator) {
    case "+":
      digits = Number(digits) + Number(curVal);
      break;
    case "−":
      digits = Number(curVal) - Number(digits);
      break;
    case "×":
      digits = Number(curVal) * Number(digits);
      break;
    case "÷":
      digits = Number(curVal) / Number(digits);
      break;
  }

  if (op == "+" || op == "−" || op == "×" || op == "÷") {
    previousOperator = op;
    curVal = digits.valueOf();
    digits = "";
    display.displayOperator(previousOperator);
    return;
  }

  if (op == "=") {
    display.newLine("=", digits.valueOf());
  }

  curVal = 0;
  previousOperator = "";

  switch (op) {
    case "√":
      digits = Number(Math.sqrt(digits.valueOf()));
      display.newLine("√", digits.valueOf());
      break;

    case "backspace":
      digits = digits.toString().slice(0, -1);
      display.clear();
      display.appendDigit(digits);
      break;
  }
}
