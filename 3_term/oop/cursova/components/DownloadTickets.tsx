import { SaveOutlined } from "@ant-design/icons"
import { Button, message } from "antd"
import { ticketsPersistor } from "../utils"
import { Ticket } from "../utils/schemas"

interface Props {
  tickets: Ticket[]
}

export const DownloadTickets: React.FC<Props> = ({ tickets }) => {
  return (
    <Button
      icon={<SaveOutlined />}
      title="Save tickets to file"
      onClick={() => {
        if (!tickets.length) message.warn("There is nothing to save")
        ticketsPersistor.downloadFileWithTickets(tickets)
      }}
    >
      Save
    </Button>
  )
}
