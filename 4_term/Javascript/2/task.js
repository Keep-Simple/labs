const textArea = document.getElementById('textArea');
const wordCountCheckbox = document.getElementById('wordCount');
const charCountCheckbox = document.getElementById('charCount');
const charCountNoSpacesCheckbox = document.getElementById('charCountNoSpaces');
const spacesCountCheckbox = document.getElementById('spacesCount');
const resultP = document.getElementById('result');

textArea.addEventListener('blur', () => {
  const text = textArea.value;

  let output = '';
  if (wordCountCheckbox.checked) {
    const words = text.split(/\s+/).filter(Boolean);
    output += `Количество слов: ${words.length}<br>`;
  }
  if (charCountCheckbox.checked) {
    output += `Количество символов: ${text.length}<br>`;
  }
  if (charCountNoSpacesCheckbox.checked) {
    const charCountNoSpaces = text.replace(/\s+/g, '').length;
    output += `Количество символов (без пробелов): ${charCountNoSpaces}<br>`;
  }
  if (spacesCountCheckbox.checked) {
    const spacesCount = (text.match(/\s/g) || []).length;
    output += `Количество пробелов: ${spacesCount}<br>`;
  }

  resultP.innerHTML = output;
});