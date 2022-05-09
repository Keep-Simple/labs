import { Student } from "./schemas";

export const calcAvarageGrade = (student: Student) => {
  if (!student.grades.length) return 0;
  const gradesSum = student.grades.reduce((sum, grade) => sum + grade, 0);
  return (gradesSum / student.grades.length).toFixed(2);
};

export const capitalize = (s: any) => {
  if (typeof s !== "string") return "";
  return s.charAt(0).toUpperCase() + s.slice(1);
};
