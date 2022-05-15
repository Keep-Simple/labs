import { SaveOutlined } from "@ant-design/icons";
import { Button, message } from "antd";
import { useMemo } from "react";
import { Student, studentsSerializer } from "../utils/schemas";

interface Props {
  students: Student[];
}

export const DownloadStudents: React.FC<Props> = ({ students }) => {
  const studentsFile = useMemo(() => {
    if (!students.length) return;

    const raw = studentsSerializer(students);
    return URL.createObjectURL(
      new Blob([raw], {
        type: "application/json",
      })
    );
  }, [students]);

  return (
    <Button
      icon={<SaveOutlined />}
      download="students.json"
      title="Save students to file"
      onClick={() => {
        if (!students.length) message.warn("There is nothing to save");
      }}
      href={studentsFile}
    >
      Save
    </Button>
  );
};
