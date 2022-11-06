import { FileSearchOutlined } from "@ant-design/icons"
import { Button, Upload } from "antd"
import { ticketsPersistor } from "../utils"
import { Ticket } from "../utils/schemas"

interface Props {
  onTickets: (tickets: Ticket[]) => void
}

export const LoadTickets: React.FC<Props> = ({ onTickets }) => {
  return (
    <Upload
      accept=".json"
      beforeUpload={(file) => ticketsPersistor.loadFromFile(file, onTickets)}
      showUploadList={false}
    >
      <Button
        icon={<FileSearchOutlined />}
        title="Load tickets from selected file"
      >
        Load
      </Button>
    </Upload>
  )
}
