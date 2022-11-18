import {
  Button,
  DatePicker,
  Space,
  Table,
  Statistic,
  Input,
  Select,
} from "antd"
import { Rule } from "antd/lib/form"
import { ColumnsType } from "antd/lib/table"
import moment from "moment"
import React, { Ref, useMemo, useState } from "react"
import { TicketsUtils } from "../../utils"
import { Ticket, ticketTypes } from "../../utils/schemas"
import { DownloadTickets } from "../DownloadTickets"
import { LoadTickets } from "../LoadTickets"
import { EditableCell } from "./Cell"
import { EditableRow } from "./Row"
import { TicketsSearch } from "./TicketsSearch"

export type TicketsTableEditProps = {
  edit?: {
    component?: (save: () => void, ref: Ref<any>) => React.ReactNode
    serialize?: (value: any) => any
    deserialize?: (value: any) => any
    rules?: Rule[]
  }
  dataIndex: keyof Ticket
}

const columns: Array<ColumnsType<Ticket>[number] & TicketsTableEditProps> = [
  {
    title: "No",
    dataIndex: "key",
  },
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
    title: "Phone",
    dataIndex: "phone",
    edit: {
      component: (save, ref) => <Input ref={ref} onBlur={save} type="tel" />,
      serialize: (value: string) => Number(value),
      deserialize: (value: number) => String(value),
    },
  },
  {
    title: "Type",
    dataIndex: "ticketType",
    filters: ["Adult", "Child", "Student"].map((type) => ({
      text: `Show ${type}`,
      value: type,
    })),
    onFilter: (value, record) => record.ticketType == value,
    edit: {
      component: (save, ref) => (
        <Select
          ref={ref}
          onChange={save}
          options={ticketTypes.map((type) => ({ value: type, label: type }))}
        />
      ),
    },
  },
  {
    title: "Expires",
    dataIndex: "ticketExpire",
    width: "20%",
    defaultSortOrder: "descend",
    sorter: (a, b) => (moment(a.ticketExpire).isAfter(b.ticketExpire) ? 1 : -1),
    render: (value) => moment(value).format("YYYY-MM-DD"),
    edit: {
      component: (save, ref) => (
        <DatePicker ref={ref} format="YYYY-MM-DD" onBlur={save} />
      ),
      serialize: (value: moment.Moment) => value.toISOString(),
      deserialize: (value: string) => moment(value),
    },
  },
]

export const TicketsTable: React.FC = () => {
  const [tickets, setTickets] = useState<Ticket[]>([])
  const [filteredTickets, setFilteredTickets] = useState<Ticket[]>([])

  const handleAdd = () => {
    setTickets((s) => [
      ...s,
      {
        key: s.length,
        name: "Nick",
        surname: "Doe",
        ticketExpire: moment().add(1, "years").toISOString(),
        ticketType: "Adult",
        phone: 380984955366,
      },
    ])
  }

  const handleSave = (row: Ticket) => {
    const newTickets = [...tickets]
    const index = newTickets.findIndex((ticket) => row.key === ticket.key)
    newTickets.splice(index, 1, {
      ...newTickets[index],
      ...row,
    })
    setTickets(newTickets)
  }

  const uicolumns = columns.map((col) => {
    if (!col.edit) return col

    return {
      ...col,
      onCell: (record: Ticket) => ({
        record,
        edit: col.edit,
        dataIndex: col.dataIndex,
        title: col.title,
        handleSave,
      }),
    }
  })

  const mostUsed = useMemo(
    () => TicketsUtils.mostUsedTicket(filteredTickets),
    [filteredTickets]
  )

  return (
    <Space direction="vertical" size="middle" style={{ display: "flex" }}>
      <Space size="middle">
        <LoadTickets onTickets={setTickets} />
        <DownloadTickets tickets={filteredTickets} />
        <Button onClick={handleAdd} type="primary" title="Add ticket entry">
          Add
        </Button>
      </Space>

      {mostUsed && (
        <Statistic
          title={`${mostUsed.ticketType} ticket is the most used`}
          value={mostUsed.count}
        />
      )}

      <TicketsSearch tickets={tickets} setTickets={setFilteredTickets} />

      <Table<Ticket>
        bordered
        dataSource={filteredTickets}
        columns={uicolumns as typeof columns}
        pagination={{
          pageSizeOptions: [2, 10, 30, 50, 100],
          defaultPageSize: 30,
        }}
        components={{
          body: {
            row: EditableRow,
            cell: EditableCell,
          },
        }}
        rowClassName={() => "editable-row"}
      />
    </Space>
  )
}
