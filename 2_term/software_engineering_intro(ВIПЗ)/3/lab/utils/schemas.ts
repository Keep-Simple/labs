import Ajv, { JTDDataType } from "ajv/dist/jtd";
import moment from "moment";

const studentSchema = {
  elements: {
    properties: {
      key: { type: "int32" },
      name: { type: "string" },
      surname: { type: "string" },
      grades: { elements: { type: "int32" } },
    },
    optionalProperties: {
      birthDate: { type: "string" },
    },
  },
} as const;

const ajv = new Ajv({ allErrors: true });
export type Student = JTDDataType<typeof studentSchema>[number];
export const studentsSerializer =
  ajv.compileSerializer<Student[]>(studentSchema);
const _compiledValidator = ajv.compile<Student[]>(studentSchema);

export const customStudentValidators: Partial<
  Record<keyof Student, (s: Student) => string[]>
> = {
  grades: (r) => {
    const messages = [];
    const has_not_number = r.grades.some((g) => !/^-?\d+$/.test(g.toString()));
    const out_of_range = r.grades.map(Number).some((m) => m < 1 || m > 5);

    if (has_not_number) messages.push(`Grades must be coma separated numbers`);
    if (out_of_range) messages.push(`Grade must be in range of 1-5`);

    return messages;
  },
  birthDate: (r) => {
    if (!r.birthDate) return [];
    const date = moment(r.birthDate);
    if (!date.isValid()) return ["Date format is invalid"];
    if (moment().isBefore(date)) return ["Birth date can't be in the future"];
    return [];
  },
} as const;

export type StudentsValidatorReturnType = Array<{
  message: string;
  meta: string;
}>;

export const studentsValidator = (
  students: Student[]
): StudentsValidatorReturnType => {
  _compiledValidator(students);

  const errors: StudentsValidatorReturnType =
    _compiledValidator.errors?.map((e) => ({
      message: e.message
        ? `${capitalize(e.keyword)} error: ${capitalize(e.message)}`
        : "Error",
      meta: `at ${e.instancePath}`,
    })) || [];

  students.forEach((student) =>
    Object.entries(customStudentValidators).map(
      ([propertyName, propertyValidator]) => {
        errors.push(
          ...propertyValidator(student).map((e) => ({
            message: e,
            meta: `at ${propertyName} of ${JSON.stringify(student)}`,
          }))
        );
      }
    )
  );

  return errors;
};

const capitalize = (s: any) => {
  if (typeof s !== "string") return "";
  return s.charAt(0).toUpperCase() + s.slice(1);
};
