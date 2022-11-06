import { Form } from "antd";
import { FormInstance } from "antd/lib/form";
import React from "react";

export const EditableContext = React.createContext<FormInstance<any> | null>(
  null
);

interface EditableRowProps {
  index: number;
}

export const EditableRow: React.FC<EditableRowProps> = ({
  index,
  ...props
}) => {
  const [form] = Form.useForm();
  return (
    <Form form={form} component={false}>
      <EditableContext.Provider value={form}>
        <tr {...props} />
      </EditableContext.Provider>
    </Form>
  );
};
