import { SaveOutlined } from "@ant-design/icons"
import { Button, message } from "antd"
import { useMemo } from "react"
import { ticketsPersistor } from "../utils"
import { Ticket } from "../utils/schemas"

interface Props {
  tickets: Ticket[]
}

export const DownloadTickets: React.FC<Props> = ({ tickets }) => {
  const ticketsFile = useMemo(
    () => ticketsPersistor.generateDownloadLink(tickets),
    [tickets]
  )

  return (
    <Button
      icon={<SaveOutlined />}
      download="tickets.json"
      title="Save tickets to file"
      onClick={() => {
        if (!tickets.length) message.warn("There is nothing to save")
      }}
      href={ticketsFile}
    >
      Save
    </Button>
  )
}
