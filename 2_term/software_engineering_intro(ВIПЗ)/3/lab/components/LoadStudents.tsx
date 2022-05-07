import { FileSearchOutlined } from "@ant-design/icons";
import { Button, Upload, message } from "antd";
import { RcFile } from "antd/lib/upload";
import { Student } from "./StudentsTable";

interface Props {
  onStudents: (students: Student[]) => void;
}

export const LoadStudents: React.FC<Props> = ({ onStudents }) => {
  const onLoad = (file: RcFile): any =>
    new Promise((resolve) => {
      const reader = new FileReader();
      reader.readAsText(file);
      reader.onload = () => {
        try {
          const students: Student[] = JSON.parse(
            reader.result?.toString() || ""
          );
          onStudents(students);
          message.success(`Loaded students from ${file.name}`);
          resolve({});
        } catch {
          message.error(
            `Failed loading students. Make sure file isn't corrupted`
          );
        }
      };
    });

  return (
    <Upload accept=".json" beforeUpload={onLoad} showUploadList={false}>
      <Button icon={<FileSearchOutlined />}>Load</Button>
    </Upload>
  );
};
