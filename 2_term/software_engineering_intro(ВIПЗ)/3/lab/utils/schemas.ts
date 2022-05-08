import Ajv, { JTDDataType } from "ajv/dist/jtd";

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
    additionalProperties: true,
  },
} as const;

const ajv = new Ajv({ allErrors: true });

export const studentsSerializer =
  ajv.compileSerializer<Student[]>(studentSchema);

export const studentsParser = ajv.compileParser<Student[]>(studentSchema);

export const studentsValidator = ajv.compile<Student[]>(studentSchema);

export type Student = JTDDataType<typeof studentSchema>[number];
