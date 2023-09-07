function solveEquation() {
  const a = parseFloat(document.getElementById('a').value);
  const b = parseFloat(document.getElementById('b').value);
  const c = parseFloat(document.getElementById('c').value);

  const discriminant = b * b - 4 * a * c;

  if (discriminant > 0) {
    const root1 = (-b + Math.sqrt(discriminant)) / (2 * a);
    const root2 = (-b - Math.sqrt(discriminant)) / (2 * a);
    document.getElementById('result').innerHTML = `Корни уравнения: x1 = ${root1.toFixed(2)}, x2 = ${root2.toFixed(2)}`;
  } else if (discriminant === 0) {
    const root = -b / (2 * a);
    document.getElementById('result').innerHTML = `Уравнение имеет один корень: x = ${root.toFixed(2)}`;
  } else {
    document.getElementById('result').innerHTML = 'Уравнение не имеет действительных корней';
  }
}
