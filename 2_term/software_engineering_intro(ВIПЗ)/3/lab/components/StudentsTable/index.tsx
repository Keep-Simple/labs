import { Button, DatePicker, Space, Table } from "antd";
import { Rule } from "antd/lib/form";
import Search from "antd/lib/input/Search";
import { ColumnsType } from "antd/lib/table";
import moment from "moment";
import React, { Ref, useState } from "react";
import { customStudentValidators, Student } from "../../utils/schemas";
import { DownloadStudents } from "../DownloadStudents";
import { LoadStudents } from "../LoadStudents";
import { EditableCell } from "./Cell";
import { EditableRow } from "./Row";

export type StudentsTableEditProps = {
  edit?: {
    component?: (save: () => void, ref: Ref<any>) => React.ReactNode;
    serialize?: (value: any) => any;
    deserialize?: (value: any) => any;
    rules?: Rule[];
  };
  dataIndex: keyof Student;
};

const columns: Array<ColumnsType<Student>[number] & StudentsTableEditProps> = [
  {
    title: "Name",
    dataIndex: "name",
    edit: {},
  },
  {
    title: "Surname",
    dataIndex: "surname",
    edit: {},
  },
  {
    title: "Grades",
    dataIndex: "grades",
    render: (value: number[]) => value.join(","),
    filters: [{ text: "Hide with 2 grade", value: "" }],
    onFilter: (_, record) => !record.grades.includes(2),
    edit: {
      serialize: (value: string) =>
        value.split(",").filter(Boolean).map(Number),
      deserialize: (value: number[]) => value.join(","),
      rules: [
        () => ({
          transform: (value) => value.split(",").filter(Boolean),
          validator: async (_, grades) => {
            const errors = customStudentValidators["grades"]?.({
              grades,
            } as Student);

            if (errors?.length) throw new Error(errors[0]);
          },
        }),
      ],
    },
  },
  {
    title: "Avarage",
    width: "10%",
    dataIndex: "" as any,
    render: (_, record) => {
      if (!record.grades.length) return 0;
      const gradesSum = record.grades.reduce((sum, grade) => sum + grade, 0);
      return (gradesSum / record.grades.length).toFixed(2);
    },
  },
  {
    title: "Birth",
    dataIndex: "birthDate",
    width: "20%",
    defaultSortOrder: "ascend",
    sorter: (a, b) => (moment(a.birthDate).isAfter(b.birthDate) ? 1 : -1),
    render: (value) => moment(value).format("DD-MM-YYYY"),
    edit: {
      component: (save, ref) => (
        <DatePicker
          ref={ref}
          format="DD-MM-YYYY"
          onBlur={save}
          disabledDate={(date) => date.isAfter(moment())}
        />
      ),
      serialize: (value: moment.Moment) => value.toISOString(),
      deserialize: (value: string) => moment(value),
    },
  },
];

export const StudentsTable: React.FC = () => {
  const [students, setStudents] = useState<Student[]>([]);
  const [searchQuery, setSearchQuery] = useState<string>("");

  const handleAdd = () => {
    setStudents((s) => [
      ...s,
      {
        key: s.length,
        name: "John",
        surname: "Doe",
        birthDate: moment().subtract(20, "years").toISOString(),
        grades: [5, 4, 5],
      },
    ]);
  };

  const handleSave = (row: Student) => {
    const newStudents = [...students];
    const index = newStudents.findIndex((Student) => row.key === Student.key);
    newStudents.splice(index, 1, {
      ...newStudents[index],
      ...row,
    });
    setStudents(newStudents);
  };

  const uicolumns = columns.map((col) => {
    if (!col.edit) return col;

    return {
      ...col,
      onCell: (record: Student) => ({
        record,
        edit: col.edit,
        dataIndex: col.dataIndex,
        title: col.title,
        handleSave,
      }),
    };
  });

  const filteredStudents = students.filter((student) =>
    [student.name, student.surname]
      .map((s) => s.toLowerCase())
      .some((s) => s.search(searchQuery.toLowerCase()) !== -1)
  );

  return (
    <Space direction="vertical" size="middle" style={{ display: "flex" }}>
      <Space size="middle">
        <LoadStudents onStudents={setStudents} />
        <DownloadStudents students={filteredStudents} />
        <Button onClick={handleAdd} type="primary">
          Add
        </Button>
      </Space>

      <Search
        allowClear
        placeholder="Search by name or surname"
        value={searchQuery}
        onChange={(e) => setSearchQuery(e.target.value)}
      />

      <Table<Student>
        bordered
        dataSource={filteredStudents}
        columns={uicolumns as typeof columns}
        components={{
          body: {
            row: EditableRow,
            cell: EditableCell,
          },
        }}
        rowClassName={() => "editable-row"}
      />
    </Space>
  );
};
