function checkPythagoreanTriple() {
  const num1 = parseFloat(document.getElementById('num1').value);
  const num2 = parseFloat(document.getElementById('num2').value);
  const num3 = parseFloat(document.getElementById('num3').value);

  const sortedNumbers = [num1, num2, num3].sort((a, b) => b - a);
  const maxNumber = sortedNumbers[0];
  const otherNumbers = sortedNumbers.slice(1);

  if (maxNumber ** 2 === otherNumbers[0] ** 2 + otherNumbers[1] ** 2) {
    document.getElementById('result2').innerHTML = 'Это тройка Пифагора!';
  } else {
    document.getElementById('result2').innerHTML = 'Это не тройка Пифагора.';
  }
}