// № 1       Відповідь:
// for (let i = 1; i <= 100; i++) {
//   console.log(i);
// }

// № 2       Відповідь:
// for (let i = 11; i <= 33; i++) {
//   console.log(i);
// }

// № 3       Відповідь:
// for (let i = 0; i <= 100; i += 2) {
//   console.log(i);
// }

// № 4       Відповідь:
// for (let i = 1; i <= 99; i += 2) {
//   console.log(i);
// }

// № 5       Відповідь:
// for (let i = 30; i >= 0; i--) {
//   console.log(i);
// }

// № 6       Відповідь:
// let i = 10;
// while (i >= 1) {
//  console.log(i);
//  i--; // Уменьшаем значение переменной i на каждой итерации
// }

// № 7       Відповідь:
// let i = 10;
// while (i >= 1) {
//  console.log(i);
//  i--; // Уменьшаем значение переменной i на каждой итерации
// }

// № 8       Відповідь:
// let i = 10;
// while (i >= 1) {
//  console.log(i);
//  i--;
// }

// № 9       Відповідь:
// let i = 10;
// while (i >= 1) {
//  console.log(i);
//  i--;
// }

// № 10       Відповідь:
// let i = 10;
// while (i >= 1) {
//  console.log(i);
//  i--;
// }

// № 11       Відповідь:
// for (let i = 1; i <= 100; i++) {
//   console.log(i);
// }

// № 12       Відповідь:
// for (let i = 11; i <= 33; i++) {
//   console.log(i);
// }

// № 13       Відповідь:
// for (let i = 0; i <= 100; i += 2) {
//   console.log(i);
// }

// № 14       Відповідь:
// for (let i = 1; i <= 99; i += 2) {
//   console.log(i);
// }

// № 15       Відповідь:
// for (let i = 100; i >= 0; i--) {
//   console.log(i);
// }

// № 16       Відповідь:
// let product = 1;
// for (let i = 1; i <= 20; i++) {
//   product *= i;
// }
// console.log("Произведение чисел от 1 до 20:", product);

// № 17       Відповідь:
// let sum = 0;
// for (let i = 2; i <= 100; i += 2) {
//   sum += i;
// }
// console.log("Сумма четных чисел от 2 до 100:", sum);

// № 18       Відповідь:
// let sum = 0;
// for (let i = 1; i <= 99; i += 2) {
//   sum += i;
// }
// console.log("Сумма нечетных чисел от 1 до 99:", sum);

// № 19       Відповідь:
// let arr = ['a', 'b', 'c', 'd', 'e'];
// for (let i = 0; i < arr.length; i++) {
//   console.log(arr[i]);
// }

// № 20       Відповідь:
// Проблема в данном коде связана с условием в цикле for. 
// Условие i <= arr.length приводит к выполнению цикла на одну итерацию больше, 
// чем количество элементов в массиве. Это приводит к тому, что в последней итерации, 
// когда i равно длине массива, обращение к элементу arr[i] выходит за пределы массива и возвращает undefined.
// Чтобы исправить это, нужно изменить условие цикла на i < arr.length. 
// Вот исправленный код:
// let arr = [1, 2, 3, 4, 5];
// for (let i = 0; i < arr.length; i++) {
//   console.log(arr[i]);
// }

// № 21       Відповідь:
// let arr = [1, 2, 3, 4, 5];
// for (let i = 0; i < arr.length; i++) {
//   if (arr[i] % 2 !== 0) {
//     console.log(arr[i]);
//   }
// }

// № 22       Відповідь:
// let arr = [1, 2, 3, 4, 5];
// let product = 1;
// for (let i = 0; i < arr.length; i++) {
//   product *= arr[i];
// }
// console.log(product);

// № 23       Відповідь:
// let arr = [1, 2, 3, 4, 5];
// let sumOfSquares = 0;
// for (let i = 0; i < arr.length; i++) {
//   sumOfSquares += arr[i] ** 2;
// }
// console.log(sumOfSquares);

// № 24       Відповідь:
// let arr = [2, 5, 9, 15, 1, 4];
// for (let i = 0; i < arr.length; i++) {
//   if (arr[i] > 3 && arr[i] < 10) {
//     console.log(arr[i]);
//   }
// }

// № 25       Відповідь:
// let arr = [3, -5, 9, -2, 7, -1, 8];
// let sum = 0;
// for (let i = 0; i < arr.length; i++) {
//   if (arr[i] > 0) {
//     sum += arr[i];
//   }
// }
// console.log(sum); // Выведет сумму положительных элементов: 3 + 9 + 7 + 8 = 27

// № 26       Відповідь:
// let arr = [3, -5, 9, -2, 7, -1, 8];
// let sum = 0;
// for (let i = 0; i < arr.length; i++) {
//   if (arr[i] > 0) {
//     sum += arr[i];
//   }
// }
// console.log(sum); // Выведет сумму положительных элементов: 3 + 9 + 7 + 8 = 27

// № 27       Відповідь:
// let arr = [10, 20, 30, 50, 235, 3000];
// for (let i = 0; i < arr.length; i++) {
//   let firstDigit = String(arr[i])[0];
//   if (firstDigit === '1' || firstDigit === '2' || firstDigit === '5') {
//     console.log(arr[i]);
//   }
// }

// № 28       Відповідь:
// let arr = [1, 2, 3, 4, 5];
// for (let i = arr.length - 1; i >= 0; i--) {
//   console.log(arr[i]);
// }

// № 29       Відповідь:
// let arr = [0, 1, 2, 3, 4, 5];
// for (let i = 0; i < arr.length; i++) {
//   if (arr[i] === i) {
//     console.log(arr[i]);
//   }
// }

// № 30       Відповідь:
// let arr = [1, 2, 3, 4, 5];
// for (let i = 0; i < arr.length; i++) {
//   document.write(arr[i] + "<br>");
// }

// № 31       Відповідь:
// let arr = [1, 2, 3, 4, 5];
// for (let i = 0; i < arr.length; i++) {
//   document.write("<p>" + arr[i] + "</p>");
// }

// № 32       Відповідь:
// let daysOfWeek = ["Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"];
// for (let i = 0; i < daysOfWeek.length; i++) {
//   if (i === 5 || i === 6) {
//     document.write("<strong>" + daysOfWeek[i] + "</strong><br>");
//   } else {
//     document.write(daysOfWeek[i] + "<br>");
//   }
// }

// № 33       Відповідь:
// let daysOfWeek = ["Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"];
// let day = new Date().getDay(); // Получаем текущий день недели (0 - воскресенье, 6 - суббота)
// for (let i = 0; i < daysOfWeek.length; i++) {
//   if (i === day) {
//     document.write("<em>" + daysOfWeek[i] + "</em><br>");
//   } else {
//     document.write(daysOfWeek[i] + "<br>");
//   }
// }
