import { FileSearchOutlined } from "@ant-design/icons";
import { Button, message, notification, Upload } from "antd";
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
        const students: Student[] = JSON.parse(raw);
        const errors = studentsValidator(students);

        if (errors?.length) {
          errors.forEach((e) =>
            notification.error({
              message: `${e.message}`,
              description: `Please fix the detected error: ${e.meta}`,
              placement: "bottomLeft",
              duration: 30,
            })
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
