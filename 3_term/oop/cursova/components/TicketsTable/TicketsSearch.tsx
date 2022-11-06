import { Select, Space } from "antd"
import Search from "antd/lib/input/Search"
import React, { useEffect, useState } from "react"
import { Ticket } from "../../utils/schemas"

interface TicketsSearchProps {
  tickets: Ticket[]
  setTickets: (tickets: Ticket[]) => void
}

const searchTypes = {
  No: { value: "key" },
  Surname: { value: "surname" },
  Phone: { value: "phone" },
  Expires: { value: "ticketExpire" },
} as const

export const TicketsSearch: React.FC<TicketsSearchProps> = ({
  setTickets,
  tickets,
}) => {
  const [searchQuery, setSearchQuery] = useState<string>("")
  const [searchType, setSearchType] =
    useState<keyof typeof searchTypes>("Surname")

  useEffect(() => {
    const filteredTickets = tickets.filter(
      (ticket) =>
        String(ticket[searchTypes[searchType].value])
          .toLowerCase()
          .search(searchQuery.toLowerCase()) !== -1
    )
    setTickets(filteredTickets)
  }, [searchQuery, tickets, searchType])

  return (
    <Space direction="vertical" style={{ width: "100%" }}>
      <Select
        style={{ width: 120 }}
        value={searchType}
        onChange={(value) => setSearchType(value)}
        options={Object.keys(searchTypes).map((k) => ({
          value: k,
          label: k,
        }))}
      />
      <Search
        allowClear
        placeholder="Search ..."
        value={searchQuery}
        onChange={(e) => setSearchQuery(e.target.value)}
      />
    </Space>
  )
}
