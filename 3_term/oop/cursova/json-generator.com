[
  '{{repeat(100)}}',
  {
    key: '{{index()}}',
    name: '{{firstName()}}',
    surname: '{{surname()}}',
    birthDate: '{{date(new Date(1998, 0, 1), new Date(2004,0,1), )}}',
    grades: [
      '{{repeat(6)}}',
      '{{integer(1, 5)}}'
    ],
  }
]
