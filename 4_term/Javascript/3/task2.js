const sourceTextarea2 = document.getElementById('sourceTextarea2');
const transliterateCheckbox2 = document.getElementById('transliterate2');
const output2 = document.getElementById('output2');

sourceTextarea2.addEventListener('blur', function (event) {
  let text = event.target.value;
  const isTranslit = transliterateCheckbox2.checked;

  if (isTranslit) {
    output2.innerText = toTranslit2(text);
  } else {
    output2.innerText = fromTranslit2(text);
  }
});

function toTranslit2(text) {
  const dictionary = {
    'а': 'a', 'б': 'b', 'в': 'v', 'г': 'g', 'д': 'd', 'е': 'e', 'ё': 'yo',
    'ж': 'zh', 'з': 'z', 'и': 'i', 'й': 'j', 'к': 'k', 'л': 'l', 'м': 'm',
    'н': 'n', 'о': 'o', 'п': 'p', 'р': 'r', 'с': 's', 'т': 't', 'у': 'u',
    'ф': 'f', 'х': 'h', 'ц': 'c', 'ч': 'ch', 'ш': 'sh', 'щ': 'sch', 'ъ': 'y',
    'ы': 'y', 'ь': "'", 'э': 'e', 'ю': 'yu', 'я': 'ya'
  };

  return text.split('').map(char => dictionary[char] || char).join('');
}

function fromTranslit2(text) {
  const reverseDictionary = {
    'a': 'а', 'b': 'б', 'v': 'в', 'g': 'г', 'd': 'д', 'e': 'е',
    'yo': 'ё', 'zh': 'ж', 'z': 'з', 'i': 'и', 'j': 'й', 'k': 'к',
    'l': 'л', 'm': 'м', 'n': 'н', 'o': 'о', 'p': 'п', 'r': 'р',
    's': 'с', 't': 'т', 'u': 'у', 'f': 'ф', 'h': 'х', 'c': 'ц',
    'ch': 'ч', 'sh': 'ш', 'sch': 'щ', 'y': 'ы', "'": 'ь', 'yu': 'ю', 'ya': 'я'
  };

  let result = "";
  for (let i = 0; i < text.length; i++) {
    // проверяем комбинации из 3 символов
    if (i < text.length - 2 && reverseDictionary[text.substring(i, i + 3)]) {
      result += reverseDictionary[text.substring(i, i + 3)];
      i += 2;
    }
    // проверяем комбинации из 2 символов
    else if (i < text.length - 1 && reverseDictionary[text.substring(i, i + 2)]) {
      result += reverseDictionary[text.substring(i, i + 2)];
      i += 1;
    }
    // проверяем 1 символ
    else if (reverseDictionary[text[i]]) {
      result += reverseDictionary[text[i]];
    }
    // если символа нет в словаре, просто добавляем его к результату
    else {
      result += text[i];
    }
  }
  return result;
}
