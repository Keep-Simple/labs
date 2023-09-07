// № 1       Відповідь:
// let age = 17;
// let adult;
// if (age >= 18) {
//   adult = true;
// } else {
//   adult = false;
// }
// console.log(adult);

// № 2       Відповідь:
// let age = 17;
// let adult;
// if (age >= 18) {
//   adult = true;
// } else {
//   adult = false;
// }
// console.log(adult);

// № 3       Відповідь:
// let age = 17;
// let adult;
// if (age >= 18) {
//   adult = true;
// } else {
//   adult = false;
// }
// console.log(adult);


// № 4       Відповідь:
// let age = 17;
// let result;
// if (age >= 18) {
//   if (age <= 23) {
//     result = 'от 18 до 23';
//   } else {
//     result = 'больше 23';
//   }
// } else {
//   result = 'меньше 18';
// }
// console.log(result);


// № 5       Відповідь:
// let age = 19;
// let result;
// if (age >= 18) {
//   if (age <= 23) {
//     result = 'от 18 до 23';
//   } else {
//     result = 'больше 23';
//   }
// } else {
//   result = 'меньше 18';
// }
// console.log(result);

// № 6       Відповідь:
// The result output is: "Верно"

// № 7       Відповідь:
// let minutes = 45; // Замените на нужное количество минут
// if (minutes >= 0 && minutes <= 20) {
//   console.log('Первая треть часа');
// } else if (minutes > 20 && minutes <= 40) {
//   console.log('Вторая треть часа');
// } else if (minutes > 40 && minutes <= 59) {
//   console.log('Третья треть часа');
// } else {
//   console.log('Недопустимое значение минут');
// }

// № 8       Відповідь:
// let arr = [10, 20, 30]; // Замените на свой массив
// if (arr.length === 3) {
//   let sum = arr.reduce((total, num) => total + num, 0);
//   console.log(`Сумма элементов массива: ${sum}`);
// }

// № 9       Відповідь:
// let number = 1230; // Замените на свое число
// let lastDigit = number % 10;
// if (lastDigit === 0) {
//   console.log('Последняя цифра равна нулю');
// } else {
//   console.log('Последняя цифра не равна нулю');
// }

// № 10       Відповідь:
// let num = 12345; // Замените на свое число
// let lastDigit = num % 10;
// if (lastDigit === 0 || lastDigit === 2 || lastDigit === 4 || lastDigit === 6 || lastDigit === 8) {
//   console.log('Число четное');
// } else {
//   console.log('Число нечетное');
// }

// № 11       Відповідь:
// let number = 123; // Замените на свое число
// if (number % 2 === 0) {
//   console.log('Число четное');
// } else {
//   console.log('Число нечетное');
// }

// № 12       Відповідь:
// let number = 15; // Замените на свое число
// if (number % 3 === 0) {
//   console.log('Число делится на 3');
// } else {
//   console.log('Число не делится на 3');
// }

// № 13       Відповідь:
// let month = 7; // Замените на свое число (от 1 до 12)
// if (month >= 1 && month <= 2 || month === 12) {
//   console.log('Зима');
// } else if (month >= 3 && month <= 5) {
//   console.log('Весна');
// } else if (month >= 6 && month <= 8) {
//   console.log('Лето');
// } else if (month >= 9 && month <= 11) {
//   console.log('Осень');
// } else {
//   console.log('Недопустимое значение месяца');
// }

// № 14       Відповідь:
// let str = 'abcde'; // Замените на свою строку
// if (str.charAt(0) === 'a') {
//   console.log('да');
// } else {
//   console.log('нет');
// }

// № 15       Відповідь:
// let number = 12345; // Замените на свое число
// let firstDigit = parseInt(number.toString().charAt(0));
// if (firstDigit === 1 || firstDigit === 2 || firstDigit === 3) {
//   console.log('да');
// } else {
//   console.log('нет');
// }

// № 16       Відповідь:
// let number = 123; // Замените на свое число
// let digit1 = Math.floor(number / 100);
// let digit2 = Math.floor((number % 100) / 10);
// let digit3 = number % 10;
// let sum = digit1 + digit2 + digit3;
// console.log('Сумма цифр:', sum);

// № 17       Відповідь:
// let number = 123456; // Замените на свое число из 6 цифр
// let digit1 = Math.floor(number / 100000);
// let digit2 = Math.floor((number % 100000) / 10000);
// let digit3 = Math.floor((number % 10000) / 1000);
// let digit4 = Math.floor((number % 1000) / 100);
// let digit5 = Math.floor((number % 100) / 10);
// let digit6 = number % 10;
// let sumFirstThree = digit1 + digit2 + digit3;
// let sumLastThree = digit4 + digit5 + digit6;
// if (sumFirstThree === sumLastThree) {
//   console.log('да');
// } else {
//   console.log('нет');
// }

// № 18       Відповідь:
// let num = 3; // Замените на значение от 1 до 4
// switch (num) {
//   case 1:
//     console.log('зима');
//     break;
//   case 2:
//     console.log('весна');
//     break;
//   case 3:
//     console.log('лето');
//     break;
//   case 4:
//     console.log('осень');
//     break;
//   default:
//     console.log('Ошибка: недопустимое значение');
// }

// № 19       Відповідь:
// let num = -5; // Замените на свое значение
// let result = num >= 0 ? 1 : -1;
// console.log(result);

// № 20       Відповідь:
// let age = prompt('Сколько вам лет?'); // Запросить возраст у пользователя
// if (age >= 18) {
//   alert('Доступ для взрослых');
// } else {
//   alert('Доступ запрещен');
// }
