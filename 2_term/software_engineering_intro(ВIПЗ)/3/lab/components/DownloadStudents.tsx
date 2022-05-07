import { SaveOutlined } from "@ant-design/icons";
import { Button } from "antd";
import { useMemo } from "react";
import { Student } from "./StudentsTable";

interface Props {
  students: Student[];
}

export const DownloadStudents: React.FC<Props> = ({ students }) => {
  const studentsFile = useMemo(() => {
    if (!students.length) return "";
    const file = new Blob([JSON.stringify(students)], {
      type: "application/json",
    });
    return URL.createObjectURL(file);
  }, [students]);

  return (
    <Button
      icon={<SaveOutlined />}
      download="students.json"
      href={studentsFile}
    >
      Save
    </Button>
  );
};
