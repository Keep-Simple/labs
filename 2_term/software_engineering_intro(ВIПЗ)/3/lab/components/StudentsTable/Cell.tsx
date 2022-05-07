import { Form, Input, InputRef } from "antd";
import React, { useContext, useEffect, useRef, useState } from "react";
import { Student, StudentsTableEditProps } from ".";
import { EditableContext } from "./Row";

interface EditableCellProps {
  title: React.ReactNode;
  children: React.ReactNode;
  record: Student;
  handleSave: (record: Student) => void;
}

export const EditableCell: React.FC<
  EditableCellProps & StudentsTableEditProps
> = ({
  title,
  children,
  dataIndex,
  record,
  handleSave,
  edit,
  ...restProps
}) => {
  const [editing, setEditing] = useState(false);
  const inputRef = useRef<InputRef>(null);
  const form = useContext(EditableContext)!;

  useEffect(() => {
    if (editing) inputRef.current?.focus();
  }, [editing]);

  let childNode = children;

  if (edit) {
    edit.component ||= (save) => (
      <Input ref={inputRef} onPressEnter={save} onBlur={save} />
    );
    edit.serialize ||= (v) => v;
    edit.deserialize ||= (v) => v;

    const toggleEdit = () => {
      setEditing(!editing);
      form.setFieldsValue({
        [dataIndex]: edit.deserialize!(record[dataIndex]),
      });
    };

    const save = async () => {
      try {
        const values = await form.validateFields([dataIndex]);
        toggleEdit();
        handleSave({
          ...record,
          [dataIndex]: edit.serialize!(values[dataIndex]),
        });
      } catch (errInfo) {
        console.log("Save failed:", errInfo);
      }
    };

    childNode = editing ? (
      <Form.Item
        style={{ margin: 0 }}
        name={dataIndex}
        rules={[
          {
            required: true,
            message: `${title} is required.`,
          },
          ...(edit?.rules || []),
        ]}
      >
        {edit?.component(save, inputRef)}
      </Form.Item>
    ) : (
      <div className="editable-cell-value-wrap" onClick={toggleEdit}>
        {children}
      </div>
    );
  }

  return <td {...restProps}>{childNode}</td>;
};
