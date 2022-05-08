import { FileSearchOutlined } from "@ant-design/icons";
import { Button, message, Upload } from "antd";
import { RcFile } from "antd/lib/upload";
import { Student, studentsValidator } from "../utils/schemas";

interface Props {
  onStudents: (students: Student[]) => void;
}

export const LoadStudents: React.FC<Props> = ({ onStudents }) => {
  const onLoad = (file: RcFile): any =>
    new Promise((resolve) => {
      const reader = new FileReader();
      reader.readAsText(file);
      reader.onload = () => {
        const raw = reader.result?.toString() || "[]";
        const students = JSON.parse(raw);

        if (!studentsValidator(students) && studentsValidator.errors) {
          const error = studentsValidator.errors[0];
          message.error(
            `Detected type error at path ${error.instancePath}, ${error.message}. 
             Please fix and try again.`,
            10
          );
          return resolve({});
        }

        if (students.length) {
          onStudents(students);
          message.success(`Loaded students from ${file.name}`);
        } else {
          message.info(`File ${file.name} was emtpy`);
        }
        resolve({});
      };
    });

  return (
    <Upload accept=".json" beforeUpload={onLoad} showUploadList={false}>
      <Button icon={<FileSearchOutlined />}>Load</Button>
    </Upload>
  );
};
